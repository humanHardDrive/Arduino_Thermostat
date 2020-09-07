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
L RemoteSensor-rescue:Jumper_2_Open-Jumper JP1
U 1 1 5EF0D6FF
P 7200 3600
F 0 "JP1" H 7200 3835 50  0000 C CNN
F 1 "Jumper_2_Open" H 7200 3744 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 7200 3600 50  0001 C CNN
F 3 "~" H 7200 3600 50  0001 C CNN
	1    7200 3600
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:Jumper_2_Open-Jumper JP2
U 1 1 5EF0E1DD
P 7850 3400
F 0 "JP2" H 7850 3635 50  0000 C CNN
F 1 "Jumper_2_Open" H 7850 3544 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 7850 3400 50  0001 C CNN
F 3 "~" H 7850 3400 50  0001 C CNN
	1    7850 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 3400 6600 3400
Wire Wire Line
	6600 3600 7000 3600
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
$Comp
L RemoteSensor-rescue:MMBT2222A-TP-dk_Transistors-Bipolar-BJT-Single Q4
U 1 1 5EF2CE7F
P 2600 5500
F 0 "Q4" H 2788 5553 60  0000 L CNN
F 1 "MMBT2222A-TP" H 2788 5447 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2800 5700 60  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMBT2222A(SOT-23).pdf" H 2800 5800 60  0001 L CNN
F 4 "MMBT2222ATPMSCT-ND" H 2800 5900 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-TP" H 2800 6000 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2800 6100 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 2800 6200 60  0001 L CNN "Family"
F 8 "https://www.mccsemi.com/pdf/Products/MMBT2222A(SOT-23).pdf" H 2800 6300 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/micro-commercial-co/MMBT2222A-TP/MMBT2222ATPMSCT-ND/717394" H 2800 6400 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SOT23" H 2800 6500 60  0001 L CNN "Description"
F 11 "Micro Commercial Co" H 2800 6600 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2800 6700 60  0001 L CNN "Status"
	1    2600 5500
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:MMBT2222A-TP-dk_Transistors-Bipolar-BJT-Single Q5
U 1 1 5EF2EBF2
P 2600 6350
F 0 "Q5" H 2788 6297 60  0000 L CNN
F 1 "MMBT2222A-TP" H 2788 6403 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2800 6550 60  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMBT2222A(SOT-23).pdf" H 2800 6650 60  0001 L CNN
F 4 "MMBT2222ATPMSCT-ND" H 2800 6750 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-TP" H 2800 6850 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2800 6950 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 2800 7050 60  0001 L CNN "Family"
F 8 "https://www.mccsemi.com/pdf/Products/MMBT2222A(SOT-23).pdf" H 2800 7150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/micro-commercial-co/MMBT2222A-TP/MMBT2222ATPMSCT-ND/717394" H 2800 7250 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SOT23" H 2800 7350 60  0001 L CNN "Description"
F 11 "Micro Commercial Co" H 2800 7450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2800 7550 60  0001 L CNN "Status"
	1    2600 6350
	1    0    0    1   
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R23
U 1 1 5EF30FEC
P 2150 5500
F 0 "R23" V 1945 5500 50  0000 C CNN
F 1 "10k" V 2036 5500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2190 5490 50  0001 C CNN
F 3 "~" H 2150 5500 50  0001 C CNN
	1    2150 5500
	0    1    1    0   
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R24
U 1 1 5EF32BAD
P 2150 6350
F 0 "R24" V 2250 6350 50  0000 C CNN
F 1 "10k" V 2350 6350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2190 6340 50  0001 C CNN
F 3 "~" H 2150 6350 50  0001 C CNN
	1    2150 6350
	0    1    1    0   
$EndComp
Wire Wire Line
	2300 6350 2400 6350
Wire Wire Line
	2300 5500 2400 5500
Wire Wire Line
	2700 6150 2700 6050
Wire Wire Line
	2700 6050 2000 5650
Wire Wire Line
	2000 5650 2000 5500
Wire Wire Line
	2700 5700 2700 5850
Wire Wire Line
	2700 5850 2000 6200
Wire Wire Line
	2000 6200 2000 6350
Wire Wire Line
	2000 6350 1550 6350
Connection ~ 2000 6350
Wire Wire Line
	2000 5500 1550 5500
Connection ~ 2000 5500
Wire Wire Line
	2700 5300 2700 5100
Wire Wire Line
	2700 5100 3550 5100
Wire Wire Line
	2700 6550 2700 6750
Wire Wire Line
	2700 6750 3550 6750
Text Label 1550 5500 0    50   ~ 0
RTS
Text Label 1550 6350 0    50   ~ 0
DTR
Text GLabel 3550 5100 2    50   Input ~ 0
FLASH
Text GLabel 3550 6750 2    50   Input ~ 0
RST
Wire Wire Line
	7400 3600 8600 3600
Wire Wire Line
	8050 3400 8600 3400
Text Label 8600 3400 2    50   ~ 0
RTS
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
Text Label 8600 3600 2    50   ~ 0
DTR
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
