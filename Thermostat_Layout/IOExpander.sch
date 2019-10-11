EESchema Schematic File Version 4
LIBS:Thermostat_Layout-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3050 3400 3000 3400
Wire Wire Line
	3000 3400 3000 3500
Wire Wire Line
	3000 3500 3050 3500
Wire Wire Line
	3000 3500 3000 3600
Wire Wire Line
	3000 3600 3050 3600
Connection ~ 3000 3500
Wire Wire Line
	3050 2700 2550 2700
Wire Wire Line
	3050 2900 2550 2900
Wire Wire Line
	3000 3600 3000 3900
Wire Wire Line
	3000 3900 3750 3900
Connection ~ 3000 3600
$Comp
L SparkFun-PowerSymbols:GND #GND010
U 1 1 5D3F48BE
P 3750 3900
F 0 "#GND010" H 3800 3850 45  0001 L BNN
F 1 "GND" H 3750 3730 45  0000 C CNN
F 2 "" H 3750 3800 60  0001 C CNN
F 3 "" H 3750 3800 60  0001 C CNN
	1    3750 3900
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY06
U 1 1 5D3F4F5E
P 3750 1700
F 0 "#SUPPLY06" H 3800 1700 45  0001 L BNN
F 1 "3.3V" H 3750 1976 45  0000 C CNN
F 2 "XXX-00000" H 3750 1881 60  0000 C CNN
F 3 "" H 3750 1700 60  0001 C CNN
	1    3750 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2000 2550 2000
Wire Wire Line
	3050 2100 2550 2100
Text GLabel 2550 2700 0    50   Input ~ 0
EXP_INT
Text GLabel 2550 2900 0    50   Input ~ 0
EXP_RST
Text GLabel 2550 2100 0    50   Input ~ 0
SCK
Text GLabel 2550 2000 0    50   Input ~ 0
SDA
Wire Wire Line
	4450 2900 5000 2900
Wire Wire Line
	4450 3000 5000 3000
Wire Wire Line
	4450 3100 5000 3100
Wire Wire Line
	4450 3200 5000 3200
Wire Wire Line
	4450 3300 5000 3300
Wire Wire Line
	4450 3400 5000 3400
Text GLabel 5000 2900 2    50   Input ~ 0
UP_BTN
Text GLabel 5000 3000 2    50   Input ~ 0
DWN_BTN
Text GLabel 5000 3100 2    50   Input ~ 0
MODE_BTN
Text GLabel 5000 3200 2    50   Input ~ 0
FAN_BTN
Text GLabel 5000 3300 2    50   Input ~ 0
SETTINGS_BTN
Text GLabel 5000 3400 2    50   Input ~ 0
REMOTE_BTN
Text GLabel 5000 3500 2    50   Input ~ 0
SCHED_BTN
Wire Wire Line
	5000 3500 4450 3500
Text GLabel 5000 2000 2    50   Input ~ 0
HEAT_ON
Text GLabel 5000 2100 2    50   Input ~ 0
COOL_ON
Text GLabel 5000 2200 2    50   Input ~ 0
FAN_ON
Text GLabel 5000 2300 2    50   Input ~ 0
LCD_LED
Wire Wire Line
	5000 2000 4450 2000
Wire Wire Line
	5000 2100 4450 2100
Wire Wire Line
	5000 2200 4450 2200
Wire Wire Line
	5000 2300 4450 2300
$Comp
L Connector_Generic:Conn_01x10 J5
U 1 1 5D49FB9C
P 8900 2250
F 0 "J5" H 8980 2242 50  0000 L CNN
F 1 "Conn_01x10" H 8980 2151 50  0000 L CNN
F 2 "Connector_JST:JST_PH_S10B-PH-SM4-TB_1x10-1MP_P2.00mm_Horizontal" H 8900 2250 50  0001 C CNN
F 3 "~" H 8900 2250 50  0001 C CNN
	1    8900 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1850 8000 1850
Wire Wire Line
	8700 1950 8000 1950
Wire Wire Line
	8700 2050 8000 2050
Wire Wire Line
	8700 2150 8000 2150
Wire Wire Line
	8700 2250 8000 2250
Wire Wire Line
	8700 2350 8000 2350
Wire Wire Line
	8700 2450 8000 2450
Wire Wire Line
	8700 2550 8000 2550
$Comp
L SparkFun-PowerSymbols:GND #GND012
U 1 1 5D4A3239
P 8700 2750
F 0 "#GND012" H 8750 2700 45  0001 L BNN
F 1 "GND" H 8700 2580 45  0000 C CNN
F 2 "" H 8700 2650 60  0001 C CNN
F 3 "" H 8700 2650 60  0001 C CNN
	1    8700 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3600 5000 3600
Text GLabel 5000 3600 2    50   Input ~ 0
UNUSED_BTN
Text GLabel 8000 1850 0    50   Input ~ 0
UP_BTN
Text GLabel 8000 1950 0    50   Input ~ 0
DWN_BTN
Text GLabel 8000 2050 0    50   Input ~ 0
MODE_BTN
Text GLabel 8000 2150 0    50   Input ~ 0
FAN_BTN
Text GLabel 8000 2250 0    50   Input ~ 0
SETTINGS_BTN
Text GLabel 8000 2350 0    50   Input ~ 0
REMOTE_BTN
Text GLabel 8000 2450 0    50   Input ~ 0
SCHED_BTN
Text GLabel 8000 2550 0    50   Input ~ 0
UNUSED_BTN
$Comp
L Relay_SolidState:TLP3545 U4
U 1 1 5D4AAA5A
P 2900 5650
F 0 "U4" H 2900 5975 50  0000 C CNN
F 1 "TLP3545" H 2900 5884 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 2900 5350 50  0001 C CNN
F 3 "https://toshiba.semicon-storage.com/info/docget.jsp?did=12663&prodName=TLP3545" H 2900 5650 50  0001 C CNN
	1    2900 5650
	1    0    0    -1  
$EndComp
$Comp
L Relay_SolidState:TLP3545 U6
U 1 1 5D4B0D89
P 4000 5650
F 0 "U6" H 4000 5975 50  0000 C CNN
F 1 "TLP3545" H 4000 5884 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 4000 5350 50  0001 C CNN
F 3 "https://toshiba.semicon-storage.com/info/docget.jsp?did=12663&prodName=TLP3545" H 4000 5650 50  0001 C CNN
	1    4000 5650
	1    0    0    -1  
$EndComp
$Comp
L Relay_SolidState:TLP3545 U7
U 1 1 5D4B27F7
P 5100 5650
F 0 "U7" H 5100 5975 50  0000 C CNN
F 1 "TLP3545" H 5100 5884 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 5100 5350 50  0001 C CNN
F 3 "https://toshiba.semicon-storage.com/info/docget.jsp?did=12663&prodName=TLP3545" H 5100 5650 50  0001 C CNN
	1    5100 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R10
U 1 1 5D4B3F71
P 2450 5900
F 0 "R10" H 2518 5946 50  0000 L CNN
F 1 "100Ω" H 2518 5855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2490 5890 50  0001 C CNN
F 3 "~" H 2450 5900 50  0001 C CNN
	1    2450 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R11
U 1 1 5D4B4905
P 3550 5900
F 0 "R11" H 3618 5946 50  0000 L CNN
F 1 "100Ω" H 3618 5855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3590 5890 50  0001 C CNN
F 3 "~" H 3550 5900 50  0001 C CNN
	1    3550 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R12
U 1 1 5D4B5111
P 4650 5900
F 0 "R12" H 4718 5946 50  0000 L CNN
F 1 "100Ω" H 4718 5855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4690 5890 50  0001 C CNN
F 3 "~" H 4650 5900 50  0001 C CNN
	1    4650 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5750 2600 5750
Wire Wire Line
	3550 5750 3700 5750
Wire Wire Line
	4650 5750 4800 5750
$Comp
L SparkFun-PowerSymbols:GND #GND08
U 1 1 5D4B7A1D
P 2450 6050
F 0 "#GND08" H 2500 6000 45  0001 L BNN
F 1 "GND" H 2450 5880 45  0000 C CNN
F 2 "" H 2450 5950 60  0001 C CNN
F 3 "" H 2450 5950 60  0001 C CNN
	1    2450 6050
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND09
U 1 1 5D4C6759
P 3550 6050
F 0 "#GND09" H 3600 6000 45  0001 L BNN
F 1 "GND" H 3550 5880 45  0000 C CNN
F 2 "" H 3550 5950 60  0001 C CNN
F 3 "" H 3550 5950 60  0001 C CNN
	1    3550 6050
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND011
U 1 1 5D4C6D83
P 4650 6050
F 0 "#GND011" H 4700 6000 45  0001 L BNN
F 1 "GND" H 4650 5880 45  0000 C CNN
F 2 "" H 4650 5950 60  0001 C CNN
F 3 "" H 4650 5950 60  0001 C CNN
	1    4650 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5550 2600 5550
Wire Wire Line
	3550 5550 3700 5550
Wire Wire Line
	4650 5550 4800 5550
Wire Wire Line
	3200 5550 3200 5150
Wire Wire Line
	3200 5750 3200 6150
Wire Wire Line
	4300 5550 4300 5150
Wire Wire Line
	4300 5750 4300 6150
Wire Wire Line
	5400 5550 5400 5150
Wire Wire Line
	5400 5750 5400 6150
Text GLabel 3200 5150 1    50   Input ~ 0
HEAT_HOT
Text GLabel 4300 5150 1    50   Input ~ 0
COOL_HOT
Text GLabel 5400 5150 1    50   Input ~ 0
FAN_HOT
Text GLabel 3200 6150 3    50   Output ~ 0
COMMON
Text GLabel 4300 6150 3    50   Output ~ 0
COMMON
Text GLabel 5400 6150 3    50   Output ~ 0
COMMON
Wire Wire Line
	2450 5550 2450 5450
Wire Wire Line
	3550 5550 3550 5450
Wire Wire Line
	4650 5550 4650 5450
Text GLabel 2450 5450 1    50   Input ~ 0
HEAT_ON
Text GLabel 3550 5450 1    50   Input ~ 0
COOL_ON
Text GLabel 4650 5450 1    50   Input ~ 0
FAN_ON
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5D4F7015
P 8850 4050
F 0 "J4" H 8930 4042 50  0000 L CNN
F 1 "Conn_01x04" H 8930 3951 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-4_1x04_P2.54mm_Horizontal" H 8850 4050 50  0001 C CNN
F 3 "~" H 8850 4050 50  0001 C CNN
	1    8850 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 3950 8100 3950
Wire Wire Line
	8650 4050 8100 4050
Wire Wire Line
	8650 4150 8100 4150
Wire Wire Line
	8650 4250 8100 4250
Text GLabel 8100 3950 0    50   Output ~ 0
HEAT_HOT
Text GLabel 8100 4050 0    50   Output ~ 0
COOL_HOT
Text GLabel 8100 4150 0    50   Output ~ 0
FAN_HOT
Text GLabel 8100 4250 0    50   Input ~ 0
COMMON
$Comp
L Interface_Expansion:MCP23017_SO U5
U 1 1 5DA26DAE
P 3750 2800
F 0 "U5" H 3750 4081 50  0000 C CNN
F 1 "MCP23017_SO" H 3750 3990 50  0000 C CNN
F 2 "Package_SO:SOIC-28W_7.5x17.9mm_P1.27mm" H 3950 1800 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf" H 3950 1700 50  0001 L CNN
	1    3750 2800
	1    0    0    -1  
$EndComp
Connection ~ 3750 3900
$EndSCHEMATC
