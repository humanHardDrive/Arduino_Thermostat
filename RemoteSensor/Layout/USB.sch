EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L RemoteSensor-rescue:Ferrite_Bead-Device FB1
U 1 1 5EF07BAD
P 5800 2350
F 0 "FB1" H 5663 2304 50  0000 R CNN
F 1 "Ferrite_Bead" H 5663 2395 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5730 2350 50  0001 C CNN
F 3 "~" H 5800 2350 50  0001 C CNN
	1    5800 2350
	-1   0    0    1   
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R25
U 1 1 5EF0826F
P 4400 3500
F 0 "R25" V 4195 3500 50  0000 C CNN
F 1 "27" V 4286 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4440 3490 50  0001 C CNN
F 3 "~" H 4400 3500 50  0001 C CNN
	1    4400 3500
	0    1    1    0   
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R26
U 1 1 5EF088E2
P 4800 3600
F 0 "R26" V 4595 3600 50  0000 C CNN
F 1 "27" V 4686 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4840 3590 50  0001 C CNN
F 3 "~" H 4800 3600 50  0001 C CNN
	1    4800 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 2500 5800 2900
Wire Wire Line
	5200 3200 5050 3200
Wire Wire Line
	5050 3200 5050 3800
Wire Wire Line
	5050 3800 5200 3800
$Comp
L RemoteSensor-rescue:C-Device C10
U 1 1 5EF0B19A
P 5050 4150
F 0 "C10" H 5165 4196 50  0000 L CNN
F 1 "100n" H 5165 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5088 4000 50  0001 C CNN
F 3 "~" H 5050 4150 50  0001 C CNN
	1    5050 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4000 5050 3800
Connection ~ 5050 3800
Wire Wire Line
	4550 3500 5200 3500
Wire Wire Line
	5050 3200 5050 2650
Wire Wire Line
	5050 2650 6000 2650
Wire Wire Line
	6000 2650 6000 2900
Connection ~ 5050 3200
$Comp
L RemoteSensor-rescue:V_USB-SparkFun-PowerSymbols #SUPPLY0122
U 1 1 5EF0F32D
P 5800 2200
F 0 "#SUPPLY0122" H 5850 2200 45  0001 L BNN
F 1 "V_USB" H 5800 2476 45  0000 C CNN
F 2 "XXX-00000" H 5800 2381 60  0000 C CNN
F 3 "" H 5800 2200 60  0001 C CNN
	1    5800 2200
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:C-Device C9
U 1 1 5EF16A27
P 4650 4150
F 0 "C9" H 4765 4196 50  0000 L CNN
F 1 "47p" H 4765 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4688 4000 50  0001 C CNN
F 3 "~" H 4650 4150 50  0001 C CNN
	1    4650 4150
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:C-Device C8
U 1 1 5EF171E4
P 4250 4150
F 0 "C8" H 4365 4196 50  0000 L CNN
F 1 "47p" H 4365 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4288 4000 50  0001 C CNN
F 3 "~" H 4250 4150 50  0001 C CNN
	1    4250 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4300 4650 4300
Wire Wire Line
	4650 4300 5050 4300
Connection ~ 4650 4300
Wire Wire Line
	4650 4000 4650 3600
Wire Wire Line
	4250 3500 4250 4000
Wire Wire Line
	4650 3600 3600 3600
Connection ~ 4650 3600
Wire Wire Line
	4250 3500 3600 3500
Connection ~ 4250 3500
Text GLabel 3600 3500 0    50   Input ~ 0
USBDM
Text GLabel 3600 3600 0    50   Input ~ 0
USBDP
Wire Wire Line
	5050 2650 3750 2650
Connection ~ 5050 2650
Text Label 3750 2650 0    50   ~ 0
VCCIO
Wire Wire Line
	6600 3200 6750 3200
Wire Wire Line
	6750 3200 6750 2500
Wire Wire Line
	6600 3300 6900 3300
Wire Wire Line
	6900 3300 6900 2500
Text GLabel 6900 2500 1    50   Input ~ 0
PRG_RX
Text GLabel 6750 2500 1    50   Input ~ 0
PRG_TX
Wire Wire Line
	4650 4300 4650 4850
Wire Wire Line
	4650 4850 5800 4850
Wire Wire Line
	6000 4850 6000 4700
Wire Wire Line
	5800 4700 5800 4850
Connection ~ 5800 4850
Wire Wire Line
	5800 4850 6000 4850
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND0113
U 1 1 5EF4CBA7
P 6000 4850
F 0 "#GND0113" H 6050 4800 45  0001 L BNN
F 1 "GND" H 6000 4680 45  0000 C CNN
F 2 "" H 6000 4750 60  0001 C CNN
F 3 "" H 6000 4750 60  0001 C CNN
	1    6000 4850
	1    0    0    -1  
$EndComp
Connection ~ 6000 4850
Wire Wire Line
	4950 3600 5200 3600
$Comp
L RemoteSensor-rescue:FT231XS-Interface_USB U10
U 1 1 5EF43B07
P 5900 3800
F 0 "U10" H 5900 4881 50  0000 C CNN
F 1 "FT231XS" H 5900 4790 50  0000 C CNN
F 2 "Package_SO:SSOP-20_3.9x8.7mm_P0.635mm" H 6500 2850 50  0001 C CNN
F 3 "http://www.ftdichip.com/Products/ICs/FT231X.html" H 5900 3800 50  0001 C CNN
	1    5900 3800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
