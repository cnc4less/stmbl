#include "commands.h"
#include "hal.h"
#include "math.h"
#include "defines.h"
#include "angle.h"
#include "stm32f4xx_conf.h"
#include "hw/hw.h"

/*
Sanyo denki absolute encoder, tested with PA035C

10 0010001000000101 10 0001110110110000 10 0011011101001010 11

10001000100000010110000111011011000010001101110100101011
10....word A......10.....word B.....10......word C....11

2.5mbit
3 16 bit words

word A:
constant, alarm/model?

word B:
16 bit pos, LSB first

word C:
1. bit: MSB pos bit
2..15: checksum/multiturn?
*/

//TODO: error,ready pin, af mapping

#define NUM_OF_SAMPLES_S  400
#define TIM_FREQ 84.0
#define TIM_DIV 5.0
#define SIG_FREQ 2.5
#define OVER (TIM_FREQ / TIM_DIV / SIG_FREQ)//one bit
#define OFFSET (OVER / 2.0)//half bit
#define SIG_POS_START 16

HAL_COMP(encs);

HAL_PIN(en);
HAL_PIN(start);
HAL_PIN(offset);
HAL_PIN(d);
HAL_PIN(pos);
HAL_PIN(error);
HAL_PIN(cc);

volatile uint32_t reply_buf[NUM_OF_SAMPLES_S + 1];
volatile uint32_t request_buf[24];
DMA_InitTypeDef dma_tx_config;
DMA_InitTypeDef dma_rx_config;

static void hw_init(volatile void *ctx_ptr, volatile hal_pin_inst_t *pin_ptr) {
  // struct encs_ctx_t *ctx = (struct encs_ctx_t *)ctx_ptr;
  struct encs_pin_ctx_t *pins = (struct encs_pin_ctx_t *)pin_ptr;

  GPIO_InitTypeDef GPIO_InitStruct;
  //TX enable
  GPIO_InitStruct.GPIO_Pin   = FB0_Z_TXEN_PIN;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(FB0_Z_TXEN_PORT, &GPIO_InitStruct);
  GPIO_ResetBits(FB0_Z_TXEN_PORT,FB0_Z_TXEN_PIN);

  //TX
  GPIO_InitStruct.GPIO_Pin = FB0_Z_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(FB0_Z_PORT, &GPIO_InitStruct);
  GPIO_ResetBits(FB0_Z_PORT,FB0_Z_PIN);

  //RX
  //v3 only
  // GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
  // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  // GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_Init(GPIOB, &GPIO_InitStruct);

  //TIM8 triggers DMA to sample reply
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 32;//14MHz
  TIM_TimeBaseStructure.TIM_Prescaler = 1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM8,ENABLE);
  TIM_DMACmd(TIM8, TIM_DMA_Update, ENABLE);
  TIM_Cmd(TIM8, ENABLE);
  
  //TODO: use defines...
  uint32_t tx_high   = GPIO_BSRR_BS_14;
  uint32_t tx_low    = GPIO_BSRR_BR_14;
  uint32_t txen_high = GPIO_BSRR_BS_15;
  uint32_t txen_low  = GPIO_BSRR_BR_15;
  int pos = 0;
  request_buf[pos++] = tx_high | txen_high;
  request_buf[pos++] = tx_high;
  request_buf[pos++] = tx_high;
  request_buf[pos++] = tx_high;
  
  request_buf[pos++] = tx_low;//start bit
  
  request_buf[pos++] = tx_low; //sync
  request_buf[pos++] = tx_high;//sync
  request_buf[pos++] = tx_low; //sync
  
  request_buf[pos++] = tx_low; //frame
  request_buf[pos++] = tx_low; //frame
  //encoder address
  request_buf[pos++] = tx_low; //EA
  request_buf[pos++] = tx_low; //EA
  request_buf[pos++] = tx_low; //EA
  //command code = CDF1 = Absolute lower 24-bit data request
  request_buf[pos++] = tx_high;//CC
  request_buf[pos++] = tx_low; //CC
  request_buf[pos++] = tx_low; //CC
  request_buf[pos++] = tx_low; //CC
  request_buf[pos++] = tx_low; //CC
  //crc of 10 bit, frame code to command code
  request_buf[pos++] = tx_low; //crc
  request_buf[pos++] = tx_low; //crc
  request_buf[pos++] = tx_high;//crc
  
  request_buf[pos++] = tx_high;//stop bit
  request_buf[pos++] = tx_high;
  request_buf[pos++] = tx_high | txen_low;
  
  //DMA tx config
  dma_tx_config.DMA_Channel = DMA_Channel_7; //TIM8_UP
  dma_tx_config.DMA_PeripheralBaseAddr = (uint32_t)&FB0_Z_PORT->BSRRL;
  dma_tx_config.DMA_Memory0BaseAddr = (uint32_t)&request_buf;
  dma_tx_config.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  dma_tx_config.DMA_BufferSize = pos;
  dma_tx_config.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  dma_tx_config.DMA_MemoryInc = DMA_MemoryInc_Enable;
  dma_tx_config.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  dma_tx_config.DMA_MemoryDataSize = DMA_PeripheralDataSize_Word;
  dma_tx_config.DMA_Mode = DMA_Mode_Normal;
  dma_tx_config.DMA_Priority = DMA_Priority_VeryHigh;
  dma_tx_config.DMA_FIFOMode = DMA_FIFOMode_Disable;
  dma_tx_config.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  dma_tx_config.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  dma_tx_config.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  
  //DMA rx config
  dma_rx_config.DMA_Channel = DMA_Channel_7; //TIM8_UP
  dma_rx_config.DMA_PeripheralBaseAddr = (uint32_t)&FB0_Z_PORT->IDR;
  dma_rx_config.DMA_Memory0BaseAddr = (uint32_t)&reply_buf;
  dma_rx_config.DMA_DIR = DMA_DIR_PeripheralToMemory;
  dma_rx_config.DMA_BufferSize = NUM_OF_SAMPLES_S;
  dma_rx_config.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  dma_rx_config.DMA_MemoryInc = DMA_MemoryInc_Enable;
  dma_rx_config.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  dma_rx_config.DMA_MemoryDataSize = DMA_PeripheralDataSize_Word;
  dma_rx_config.DMA_Mode = DMA_Mode_Normal;
  dma_rx_config.DMA_Priority = DMA_Priority_High;
  dma_rx_config.DMA_FIFOMode = DMA_FIFOMode_Disable;
  dma_rx_config.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  dma_rx_config.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  dma_rx_config.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  PIN(en) = 1.0;
  PIN(offset) = 120.0;
}

static void rt_func(float period, volatile void *ctx_ptr, volatile hal_pin_inst_t *pin_ptr) {
  // struct encs_ctx_t *ctx      = (struct encs_ctx_t *)ctx_ptr;
  struct encs_pin_ctx_t *pins = (struct encs_pin_ctx_t *)pin_ptr;

   if(PIN(en) > 0.0){
      //request
      TIM8->ARR = 32;//2.545 Mhz
      DMA_Cmd(DMA2_Stream1, DISABLE);
      DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_TCIF1);
      DMA_DeInit(DMA2_Stream1);
      DMA_Init(DMA2_Stream1, &dma_tx_config);
      DMA_Cmd(DMA2_Stream1, ENABLE);
      //wait for DMA transfer complete
      while (DMA_GetFlagStatus(DMA2_Stream1, DMA_FLAG_TCIF1) == RESET);
      //TODO: set pin to input
      //reply
      TIM8->ARR = 4;//16.8 Mhz
      DMA_Cmd(DMA2_Stream1, DISABLE);
      DMA_ClearFlag(DMA2_Stream1, DMA_FLAG_TCIF1);
      DMA_DeInit(DMA2_Stream1);
      DMA_Init(DMA2_Stream1, &dma_rx_config);
      DMA_Cmd(DMA2_Stream1, ENABLE);
      //wait for DMA transfer complete
      while (DMA_GetFlagStatus(DMA2_Stream1, DMA_FLAG_TCIF1) == RESET);

      int i = 0;
      //skip leading ones
      for(; i < NUM_OF_SAMPLES_S/5; i++){
         if(!(reply_buf[i] & FB0_Z_PIN)){
            break;
         }
      }
      //skip zeros
      for(; i < NUM_OF_SAMPLES_S/5; i++){
         if(reply_buf[i] & FB0_Z_PIN){
            break;
         }
      }
      int start = i + OFFSET;//position of first bit
      int d = 0;
      int p = 0;

      p = CLAMP((int)((18 + SIG_POS_START) * OVER + start + 0.5), 0, NUM_OF_SAMPLES_S - 1);
      d += (reply_buf[p] & FB0_Z_PIN) != 0;

      for(int j = 0; j < 16; j++){
         p = CLAMP((int)(((15 - j) + SIG_POS_START) * OVER + start + 0.5), 0, NUM_OF_SAMPLES_S - 1);
         d = d << 1;
         d += (reply_buf[p] & FB0_Z_PIN) != 0;
      }

      PIN(d) = d;
      PIN(start) = start;
      PIN(pos) = (d * M_PI * 2.0 / 131072.0) - M_PI;
   }

}

hal_comp_t encs_comp_struct = {
    .name      = "encs",
    .nrt       = 0,
    .rt        = rt_func,
    .frt       = 0,
    .nrt_init  = 0,
    .hw_init   = hw_init,
    .rt_start  = 0,
    .frt_start = 0,
    .rt_stop   = 0,
    .frt_stop  = 0,
    .ctx_size  = 0,
    .pin_count = sizeof(struct encs_pin_ctx_t) / sizeof(struct hal_pin_inst_t),
};
