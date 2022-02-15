EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L MCU_Module:Arduino_Nano_v3.x A?
U 1 1 6123ABC6
P 6750 3300
F 0 "A?" H 7450 2150 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 5950 2200 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6750 3300 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 6750 3300 50  0001 C CNN
	1    6750 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6123B62A
P 6850 4650
F 0 "#PWR?" H 6850 4400 50  0001 C CNN
F 1 "GND" H 6855 4477 50  0000 C CNN
F 2 "" H 6850 4650 50  0001 C CNN
F 3 "" H 6850 4650 50  0001 C CNN
	1    6850 4650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6123B8E0
P 6950 2000
F 0 "#PWR?" H 6950 1850 50  0001 C CNN
F 1 "+5V" H 6965 2173 50  0000 C CNN
F 2 "" H 6950 2000 50  0001 C CNN
F 3 "" H 6950 2000 50  0001 C CNN
	1    6950 2000
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion:P82B96 U?
U 1 1 6123C38D
P 8700 3050
F 0 "U?" H 8700 3667 50  0000 C CNN
F 1 "P82B96" H 8700 3576 50  0000 C CNN
F 2 "" H 8700 3050 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/P82B96.pdf" H 8700 3050 50  0001 C CNN
	1    8700 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2000 6950 2300
Wire Wire Line
	6750 4300 6850 4300
Wire Wire Line
	6850 4300 6850 4650
Connection ~ 6850 4300
Wire Wire Line
	9400 2750 9300 2750
Wire Wire Line
	9300 2950 10000 2950
Wire Wire Line
	8100 3150 7900 3150
Wire Wire Line
	7900 3150 7900 2250
Wire Wire Line
	9850 2250 9850 1550
Text GLabel 10000 1550 2    50   Input ~ 0
SDA_buf
Text GLabel 9850 1550 0    50   Input ~ 0
SCL_buf
$Comp
L power:+5V #PWR?
U 1 1 61241FE8
P 8000 2750
F 0 "#PWR?" H 8000 2600 50  0001 C CNN
F 1 "+5V" H 8015 2923 50  0000 C CNN
F 2 "" H 8000 2750 50  0001 C CNN
F 3 "" H 8000 2750 50  0001 C CNN
	1    8000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 2750 8100 2750
$Comp
L power:GND #PWR?
U 1 1 61242B86
P 8100 3350
F 0 "#PWR?" H 8100 3100 50  0001 C CNN
F 1 "GND" H 8105 3177 50  0000 C CNN
F 2 "" H 8100 3350 50  0001 C CNN
F 3 "" H 8100 3350 50  0001 C CNN
	1    8100 3350
	1    0    0    -1  
$EndComp
Text GLabel 1100 2750 0    50   Input ~ 0
SCL_buf
Text GLabel 2650 2550 2    50   Input ~ 0
SDA_buf
$Comp
L Interface_Expansion:P82B96 U?
U 1 1 612435AE
P 1850 2650
F 0 "U?" H 1850 3267 50  0000 C CNN
F 1 "P82B96" H 1850 3176 50  0000 C CNN
F 2 "" H 1850 2650 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/P82B96.pdf" H 1850 2650 50  0001 C CNN
	1    1850 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 2750 1100 2750
Wire Wire Line
	2650 2550 2450 2550
$Comp
L power:+5V #PWR?
U 1 1 61245168
P 8750 1950
F 0 "#PWR?" H 8750 1800 50  0001 C CNN
F 1 "+5V" H 8765 2123 50  0000 C CNN
F 2 "" H 8750 1950 50  0001 C CNN
F 3 "" H 8750 1950 50  0001 C CNN
	1    8750 1950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 61245905
P 10400 2650
F 0 "#PWR?" H 10400 2500 50  0001 C CNN
F 1 "+5V" V 10415 2778 50  0000 L CNN
F 2 "" H 10400 2650 50  0001 C CNN
F 3 "" H 10400 2650 50  0001 C CNN
	1    10400 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 612465DD
P 8750 2050
F 0 "R?" H 8809 2096 50  0000 L CNN
F 1 "R_Small" H 8809 2005 50  0000 L CNN
F 2 "" H 8750 2050 50  0001 C CNN
F 3 "~" H 8750 2050 50  0001 C CNN
	1    8750 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 61246F04
P 10200 2650
F 0 "R?" V 10004 2650 50  0000 C CNN
F 1 "R_Small" V 10095 2650 50  0000 C CNN
F 2 "" H 10200 2650 50  0001 C CNN
F 3 "~" H 10200 2650 50  0001 C CNN
	1    10200 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	10000 1550 10000 2650
Wire Wire Line
	7900 2250 8750 2250
Wire Wire Line
	8750 2150 8750 2250
Connection ~ 8750 2250
Wire Wire Line
	8750 2250 9850 2250
Wire Wire Line
	10300 2650 10400 2650
Wire Wire Line
	10100 2650 10000 2650
Connection ~ 10000 2650
Wire Wire Line
	10000 2650 10000 2950
Text GLabel 2650 2350 2    50   Input ~ 0
SDA
Text GLabel 2650 2950 2    50   Input ~ 0
SCL
Wire Wire Line
	2650 2350 2450 2350
Wire Wire Line
	2650 2950 2450 2950
$Comp
L power:+5V #PWR?
U 1 1 61249694
P 1100 2350
F 0 "#PWR?" H 1100 2200 50  0001 C CNN
F 1 "+5V" H 1115 2523 50  0000 C CNN
F 2 "" H 1100 2350 50  0001 C CNN
F 3 "" H 1100 2350 50  0001 C CNN
	1    1100 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6124A0AA
P 1100 2950
F 0 "#PWR?" H 1100 2700 50  0001 C CNN
F 1 "GND" H 1105 2777 50  0000 C CNN
F 2 "" H 1100 2950 50  0001 C CNN
F 3 "" H 1100 2950 50  0001 C CNN
	1    1100 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 2350 1250 2350
Wire Wire Line
	1250 2950 1100 2950
Wire Wire Line
	7250 3800 9300 3800
Wire Wire Line
	9300 3350 9300 3800
Wire Wire Line
	7250 3700 9400 3700
Wire Wire Line
	9400 3700 9400 2750
$EndSCHEMATC
