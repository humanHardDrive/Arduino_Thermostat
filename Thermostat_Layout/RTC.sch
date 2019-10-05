EESchema Schematic File Version 4
LIBS:Thermostat_Layout-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
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
L Timer_RTC:DS3231MZ U9
U 1 1 5D3F90D1
P 5750 3150
F 0 "U9" H 5750 2661 50  0000 C CNN
F 1 "DS3231MZ" H 5750 2570 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5750 2650 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231M.pdf" H 5750 2550 50  0001 C CNN
	1    5750 3150
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND015
U 1 1 5D3F958C
P 5750 3850
F 0 "#GND015" H 5800 3800 45  0001 L BNN
F 1 "GND" H 5750 3680 45  0000 C CNN
F 2 "" H 5750 3750 60  0001 C CNN
F 3 "" H 5750 3750 60  0001 C CNN
	1    5750 3850
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY08
U 1 1 5D3F99F0
P 5750 2550
F 0 "#SUPPLY08" H 5800 2550 45  0001 L BNN
F 1 "3.3V" H 5750 2826 45  0000 C CNN
F 2 "XXX-00000" H 5750 2731 60  0000 C CNN
F 3 "" H 5750 2550 60  0001 C CNN
	1    5750 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2750 5750 2700
Wire Wire Line
	5650 2600 7000 2600
Wire Wire Line
	7000 2600 7000 2700
Wire Wire Line
	5650 2600 5650 2750
Wire Wire Line
	5750 3550 5750 3850
Wire Wire Line
	5750 3550 7000 3550
Connection ~ 5750 3550
Wire Wire Line
	7000 3550 7000 3000
$Comp
L Device:Battery_Cell BT1
U 1 1 5D3FA2FA
P 7000 2900
F 0 "BT1" H 7118 2996 50  0000 L CNN
F 1 "Battery_Cell" H 7118 2905 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_3000_1x12mm" V 7000 2960 50  0001 C CNN
F 3 "~" V 7000 2960 50  0001 C CNN
	1    7000 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3350 5150 3350
Wire Wire Line
	5150 3350 5150 2700
Wire Wire Line
	5150 2700 5750 2700
Connection ~ 5750 2700
Wire Wire Line
	5750 2700 5750 2550
Wire Wire Line
	5250 2950 4900 2950
Wire Wire Line
	5250 3050 4900 3050
Text GLabel 4900 2950 0    50   Input ~ 0
SCL
Text GLabel 4900 3050 0    50   BiDi ~ 0
SDA
$EndSCHEMATC
