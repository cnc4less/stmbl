EESchema Schematic File Version 2
LIBS:transistors
LIBS:stm32
LIBS:conn
LIBS:stmbl_4.0-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 9 14
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L lmr1420X IC1
U 1 1 565A1FC6
P 4300 2300
F 0 "IC1" H 4100 2550 60  0000 C CNN
F 1 "lmr1420X" H 4250 2050 60  0000 C CNN
F 2 "" H 4200 2300 60  0001 C CNN
F 3 "" H 4200 2300 60  0000 C CNN
	1    4300 2300
	1    0    0    -1  
$EndComp
$Comp
L C C50
U 1 1 566068C0
P 6050 2550
F 0 "C50" H 6075 2650 50  0000 L CNN
F 1 "47µ" H 6075 2450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6088 2400 30  0001 C CNN
F 3 "" H 6050 2550 60  0000 C CNN
F 4 "6.3V" H 6050 2550 60  0001 C CNN "Voltage"
	1    6050 2550
	1    0    0    -1  
$EndComp
$Comp
L R R74
U 1 1 5660690B
P 5100 2400
F 0 "R74" V 5180 2400 50  0000 C CNN
F 1 "5.6k" V 5100 2400 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5030 2400 30  0001 C CNN
F 3 "" H 5100 2400 30  0000 C CNN
	1    5100 2400
	0    1    1    0   
$EndComp
$Comp
L R R60
U 1 1 56606967
P 4850 2650
F 0 "R60" V 4930 2650 50  0000 C CNN
F 1 "1k" V 4850 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4780 2650 30  0001 C CNN
F 3 "" H 4850 2650 30  0000 C CNN
	1    4850 2650
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D9
U 1 1 566069A3
P 5450 2650
F 0 "D9" H 5450 2750 50  0000 C CNN
F 1 "60V 1A" H 5450 2550 50  0000 C CNN
F 2 "" H 5450 2650 60  0001 C CNN
F 3 "" H 5450 2650 60  0000 C CNN
	1    5450 2650
	0    1    1    0   
$EndComp
$Comp
L C C35
U 1 1 56606BAA
P 5000 2200
F 0 "C35" H 5025 2300 50  0000 L CNN
F 1 "0.22µ 16V" H 5025 2100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5038 2050 30  0001 C CNN
F 3 "" H 5000 2200 60  0000 C CNN
	1    5000 2200
	0    -1   -1   0   
$EndComp
$Comp
L INDUCTOR L1
U 1 1 56606C2D
P 5750 2200
F 0 "L1" V 5700 2200 50  0000 C CNN
F 1 "15µH 1.5A" V 5850 2200 50  0000 C CNN
F 2 "" H 5750 2200 60  0001 C CNN
F 3 "" H 5750 2200 60  0000 C CNN
	1    5750 2200
	0    -1   -1   0   
$EndComp
$Comp
L LM7812 U2
U 1 1 566074A9
P 2900 4950
F 0 "U2" H 3050 4754 60  0000 C CNN
F 1 "zldo1117" H 2900 5150 60  0000 C CNN
F 2 "stmbl:SOT-223" H 2900 4950 60  0001 C CNN
F 3 "" H 2900 4950 60  0000 C CNN
	1    2900 4950
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 566075DC
P 3400 5250
F 0 "C18" H 3425 5350 50  0000 L CNN
F 1 "4.7µ" H 3425 5150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3438 5100 30  0001 C CNN
F 3 "" H 3400 5250 60  0000 C CNN
F 4 "16V" H 3400 5250 60  0001 C CNN "Voltage"
	1    3400 5250
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 566076FA
P 2400 5250
F 0 "C8" H 2425 5350 50  0000 L CNN
F 1 "4.7µ" H 2425 5150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2438 5100 30  0001 C CNN
F 3 "" H 2400 5250 60  0000 C CNN
F 4 "16V" H 2400 5250 60  0001 C CNN "Voltage"
	1    2400 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2200 4850 2200
Wire Wire Line
	5150 2200 5450 2200
Wire Wire Line
	5450 2200 5450 2500
Wire Wire Line
	6050 2200 6050 2400
Wire Wire Line
	6050 2400 5250 2400
Wire Wire Line
	6050 2800 6050 2700
Connection ~ 6050 2400
Wire Wire Line
	4950 2400 4750 2400
Wire Wire Line
	4850 2500 4850 2400
Connection ~ 4850 2400
Wire Wire Line
	3850 2400 3850 2800
Wire Wire Line
	3100 2200 3850 2200
Wire Wire Line
	3850 2300 3750 2300
Wire Wire Line
	3750 2300 3750 2200
Connection ~ 3750 2200
Wire Wire Line
	4750 2300 5250 2300
Wire Wire Line
	5250 2300 5250 2200
Connection ~ 5250 2200
Wire Wire Line
	3400 5500 3400 5400
Wire Wire Line
	2400 5400 2400 5500
Wire Wire Line
	2900 5200 2900 5500
Wire Wire Line
	2400 5100 2400 4900
Connection ~ 2400 4900
Wire Wire Line
	3300 4900 3650 4900
Wire Wire Line
	3400 4800 3400 5100
$Comp
L +5V #PWR20
U 1 1 5660786F
P 1900 4800
F 0 "#PWR20" H 1900 4650 50  0001 C CNN
F 1 "+5V" H 1900 4940 50  0000 C CNN
F 2 "" H 1900 4800 60  0000 C CNN
F 3 "" H 1900 4800 60  0000 C CNN
	1    1900 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR51
U 1 1 566078DE
P 3400 4800
F 0 "#PWR51" H 3400 4650 50  0001 C CNN
F 1 "+3.3V" H 3400 4940 50  0000 C CNN
F 2 "" H 3400 4800 60  0000 C CNN
F 3 "" H 3400 4800 60  0000 C CNN
	1    3400 4800
	1    0    0    -1  
$EndComp
Connection ~ 6050 2200
Wire Wire Line
	1900 4800 1900 4900
Connection ~ 3400 4900
$Comp
L GND #PWR33
U 1 1 5660843E
P 2500 2500
F 0 "#PWR33" H 2500 2250 50  0001 C CNN
F 1 "GND" H 2500 2350 50  0000 C CNN
F 2 "" H 2500 2500 60  0000 C CNN
F 3 "" H 2500 2500 60  0000 C CNN
	1    2500 2500
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR32
U 1 1 56608476
P 2500 2200
F 0 "#PWR32" H 2500 2050 50  0001 C CNN
F 1 "+24V" H 2500 2340 50  0000 C CNN
F 2 "" H 2500 2200 60  0000 C CNN
F 3 "" H 2500 2200 60  0000 C CNN
	1    2500 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2300 2500 2300
Wire Wire Line
	2500 2300 2500 2200
Wire Wire Line
	2400 2400 2500 2400
Wire Wire Line
	2500 2400 2500 2500
Connection ~ 2150 4900
$Comp
L CONN_01X02 P3
U 1 1 566CDEAC
P 2200 2350
F 0 "P3" H 2200 2500 50  0000 C CNN
F 1 "CONN_01X02" V 2300 2350 50  0000 C CNN
F 2 "stmbl:akl182-2" H 2200 2350 60  0001 C CNN
F 3 "" H 2200 2350 60  0000 C CNN
	1    2200 2350
	-1   0    0    1   
$EndComp
$Comp
L testpoint T4
U 1 1 56819741
P 2150 4700
F 0 "T4" H 2150 4800 60  0000 C CNN
F 1 "testpoint" H 2150 4600 60  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 2150 4700 60  0001 C CNN
F 3 "" H 2150 4700 60  0000 C CNN
	1    2150 4700
	0    -1   -1   0   
$EndComp
$Comp
L testpoint T11
U 1 1 568197A1
P 3650 4700
F 0 "T11" H 3650 4800 60  0000 C CNN
F 1 "testpoint" H 3650 4600 60  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3650 4700 60  0001 C CNN
F 3 "" H 3650 4700 60  0000 C CNN
	1    3650 4700
	0    -1   -1   0   
$EndComp
$Comp
L testpoint T12
U 1 1 5682CF3A
P 3700 5500
F 0 "T12" H 3700 5600 60  0000 C CNN
F 1 "testpoint" H 3700 5400 60  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3700 5500 60  0001 C CNN
F 3 "" H 3700 5500 60  0000 C CNN
	1    3700 5500
	1    0    0    -1  
$EndComp
$Comp
L lm25011 U4
U 1 1 570D946D
P 4350 1550
F 0 "U4" H 4350 2003 60  0000 C CNN
F 1 "lm25011" H 4350 1897 60  0000 C CNN
F 2 "" H 4350 1550 60  0001 C CNN
F 3 "" H 4350 1550 60  0000 C CNN
	1    4350 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 4900 2500 4900
$Comp
L GND #PWR21
U 1 1 57744A84
P 1900 5550
F 0 "#PWR21" H 1900 5300 50  0001 C CNN
F 1 "GND" H 1900 5400 50  0000 C CNN
F 2 "" H 1900 5550 60  0000 C CNN
F 3 "" H 1900 5550 60  0000 C CNN
	1    1900 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 5550 1900 5500
Wire Wire Line
	1900 5500 3500 5500
Connection ~ 2400 5500
Connection ~ 2900 5500
Connection ~ 3400 5500
$EndSCHEMATC
