EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
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
L RF_Module:ESP-07 U?
U 1 1 5ECDD494
P 5750 3550
F 0 "U?" H 5750 4531 50  0000 C CNN
F 1 "ESP-07" H 5750 4440 50  0000 C CNN
F 2 "RF_Module:ESP-07" H 5750 3550 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 5400 3650 50  0001 C CNN
	1    5750 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5ECDDAED
P 5750 2300
F 0 "#PWR?" H 5750 2150 50  0001 C CNN
F 1 "+3.3V" H 5765 2473 50  0000 C CNN
F 2 "" H 5750 2300 50  0001 C CNN
F 3 "" H 5750 2300 50  0001 C CNN
	1    5750 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5ECDDBEC
P 5750 4350
F 0 "#PWR?" H 5750 4100 50  0001 C CNN
F 1 "GND" H 5755 4177 50  0000 C CNN
F 2 "" H 5750 4350 50  0001 C CNN
F 3 "" H 5750 4350 50  0001 C CNN
	1    5750 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4250 5750 4300
$Comp
L Device:R_US R?
U 1 1 5ECDE4EF
P 4850 2700
F 0 "R?" H 4918 2746 50  0000 L CNN
F 1 "10k" H 4918 2655 50  0000 L CNN
F 2 "" V 4890 2690 50  0001 C CNN
F 3 "~" H 4850 2700 50  0001 C CNN
	1    4850 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5ECDEC58
P 4400 2700
F 0 "R?" H 4468 2746 50  0000 L CNN
F 1 "10k" H 4468 2655 50  0000 L CNN
F 2 "" V 4440 2690 50  0001 C CNN
F 3 "~" H 4400 2700 50  0001 C CNN
	1    4400 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2300 5750 2450
Wire Wire Line
	5150 2950 4850 2950
Wire Wire Line
	4850 2850 4850 2950
Connection ~ 4850 2950
Wire Wire Line
	4850 2950 3750 2950
Wire Wire Line
	4400 2850 4400 3150
Wire Wire Line
	4400 3150 5150 3150
Wire Wire Line
	4400 2550 4400 2450
Wire Wire Line
	4400 2450 4850 2450
Wire Wire Line
	4850 2450 4850 2550
Wire Wire Line
	4850 2450 5750 2450
Connection ~ 4850 2450
Connection ~ 5750 2450
Wire Wire Line
	5750 2450 5750 2750
Text Label 3750 2950 0    50   ~ 0
RST
$Comp
L Device:R_US R?
U 1 1 5ECE0813
P 6950 4050
F 0 "R?" H 7018 4096 50  0000 L CNN
F 1 "10k" H 7018 4005 50  0000 L CNN
F 2 "" V 6990 4040 50  0001 C CNN
F 3 "~" H 6950 4050 50  0001 C CNN
	1    6950 4050
	1    0    0    -1  
$EndComp
Text GLabel 6800 3350 2    50   Output ~ 0
SCL
Text GLabel 6800 3450 2    50   BiDi ~ 0
SDA
Wire Wire Line
	6350 3350 6800 3350
Wire Wire Line
	6800 3450 6350 3450
$Comp
L Switch:SW_Push SW?
U 1 1 5ECE3073
P 6800 2950
F 0 "SW?" H 6800 3235 50  0000 C CNN
F 1 "SW_Push" H 6800 3144 50  0000 C CNN
F 2 "" H 6800 3150 50  0001 C CNN
F 3 "~" H 6800 3150 50  0001 C CNN
	1    6800 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3050 7050 3050
Wire Wire Line
	6350 3250 7050 3250
Wire Wire Line
	6600 2950 6350 2950
Text Label 7050 3050 2    50   ~ 0
RADIO_TX
Text Label 7050 3250 2    50   ~ 0
RADIO_RX
$Comp
L power:GND #PWR?
U 1 1 5ECE3F4E
P 7400 2950
F 0 "#PWR?" H 7400 2700 50  0001 C CNN
F 1 "GND" H 7405 2777 50  0000 C CNN
F 2 "" H 7400 2950 50  0001 C CNN
F 3 "" H 7400 2950 50  0001 C CNN
	1    7400 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2950 7400 2950
$Comp
L Device:R_US R?
U 1 1 5ED1305D
P 2000 1500
F 0 "R?" H 2068 1546 50  0000 L CNN
F 1 "4.7K" H 2068 1455 50  0000 L CNN
F 2 "" V 2040 1490 50  0001 C CNN
F 3 "~" H 2000 1500 50  0001 C CNN
	1    2000 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5ED13CB4
P 2500 1500
F 0 "R?" H 2568 1546 50  0000 L CNN
F 1 "4.7K" H 2568 1455 50  0000 L CNN
F 2 "" V 2540 1490 50  0001 C CNN
F 3 "~" H 2500 1500 50  0001 C CNN
	1    2500 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 1650 2000 1750
Wire Wire Line
	2500 1650 2500 1900
Wire Wire Line
	2000 1350 2250 1350
$Comp
L power:+3.3V #PWR?
U 1 1 5ED15313
P 2250 1150
F 0 "#PWR?" H 2250 1000 50  0001 C CNN
F 1 "+3.3V" H 2265 1323 50  0000 C CNN
F 2 "" H 2250 1150 50  0001 C CNN
F 3 "" H 2250 1150 50  0001 C CNN
	1    2250 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1150 2250 1350
Connection ~ 2250 1350
Wire Wire Line
	2250 1350 2500 1350
Text GLabel 1700 1750 0    50   BiDi ~ 0
SCL
Text GLabel 1700 1900 0    50   BiDi ~ 0
SDA
Wire Wire Line
	2000 1750 1700 1750
Wire Wire Line
	1700 1900 2500 1900
$Comp
L Switch:SW_Push SW?
U 1 1 5ED16D65
P 2100 3200
F 0 "SW?" H 2100 3485 50  0000 C CNN
F 1 "SW_Push" H 2100 3394 50  0000 C CNN
F 2 "" H 2100 3400 50  0001 C CNN
F 3 "~" H 2100 3400 50  0001 C CNN
	1    2100 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5ED18146
P 2450 3200
F 0 "#PWR?" H 2450 2950 50  0001 C CNN
F 1 "GND" H 2455 3027 50  0000 C CNN
F 2 "" H 2450 3200 50  0001 C CNN
F 3 "" H 2450 3200 50  0001 C CNN
	1    2450 3200
	1    0    0    -1  
$EndComp
Text Label 1500 3200 0    50   ~ 0
RST
Wire Wire Line
	1500 3200 1900 3200
Wire Wire Line
	2300 3200 2450 3200
Wire Wire Line
	6350 3950 6750 3950
Text Label 6750 3950 2    50   ~ 0
RST
Wire Wire Line
	6350 3850 6950 3850
Wire Wire Line
	6950 3850 6950 3900
Wire Wire Line
	6950 4200 6950 4300
Wire Wire Line
	6950 4300 5750 4300
Connection ~ 5750 4300
Wire Wire Line
	5750 4300 5750 4350
$EndSCHEMATC
