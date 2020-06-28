EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
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
L Device:R_US R?
U 1 1 5EF5A915
P 5350 4750
AR Path="/5EF5A915" Ref="R?"  Part="1" 
AR Path="/5EF41F85/5EF5A915" Ref="R9"  Part="1" 
F 0 "R9" H 5418 4796 50  0000 L CNN
F 1 "10k" H 5418 4705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5390 4740 50  0001 C CNN
F 3 "~" H 5350 4750 50  0001 C CNN
	1    5350 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5EF5A91B
P 4350 4750
AR Path="/5EF5A91B" Ref="R?"  Part="1" 
AR Path="/5EF41F85/5EF5A91B" Ref="R7"  Part="1" 
F 0 "R7" H 4418 4796 50  0000 L CNN
F 1 "10k" H 4418 4705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4390 4740 50  0001 C CNN
F 3 "~" H 4350 4750 50  0001 C CNN
	1    4350 4750
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF5A921
P 5650 4150
AR Path="/5EF5A921" Ref="#GND?"  Part="1" 
AR Path="/5EF41F85/5EF5A921" Ref="#GND0109"  Part="1" 
F 0 "#GND0109" H 5700 4100 45  0001 L BNN
F 1 "GND" H 5650 3980 45  0000 C CNN
F 2 "" H 5650 4050 60  0001 C CNN
F 3 "" H 5650 4050 60  0001 C CNN
	1    5650 4150
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC2G02 U?
U 2 1 5EF5A927
P 5650 4050
AR Path="/5EF5A927" Ref="U?"  Part="2" 
AR Path="/5EF41F85/5EF5A927" Ref="U6"  Part="2" 
F 0 "U6" H 5625 4317 50  0000 C CNN
F 1 "74LVC2G02" H 5625 4226 50  0000 C CNN
F 2 "Package_SO:VSSOP-8_2.3x2mm_P0.5mm" H 5650 4050 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 5650 4050 50  0001 C CNN
	2    5650 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3950 5650 3700
Wire Wire Line
	4800 3900 4800 3650
$Comp
L 74xGxx:74LVC2G02 U?
U 1 1 5EF5A92F
P 4800 4000
AR Path="/5EF5A92F" Ref="U?"  Part="1" 
AR Path="/5EF41F85/5EF5A92F" Ref="U6"  Part="1" 
F 0 "U6" H 4775 4267 50  0000 C CNN
F 1 "74LVC2G02" H 4775 4176 50  0000 C CNN
F 2 "Package_SO:VSSOP-8_2.3x2mm_P0.5mm" H 4800 4000 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 4800 4000 50  0001 C CNN
	1    4800 4000
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF5A935
P 4800 4100
AR Path="/5EF5A935" Ref="#GND?"  Part="1" 
AR Path="/5EF41F85/5EF5A935" Ref="#GND0110"  Part="1" 
F 0 "#GND0110" H 4850 4050 45  0001 L BNN
F 1 "GND" H 4800 3930 45  0000 C CNN
F 2 "" H 4800 4000 60  0001 C CNN
F 3 "" H 4800 4000 60  0001 C CNN
	1    4800 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4000 5200 4000
Wire Wire Line
	5900 4050 5900 4400
Wire Wire Line
	5900 4400 4500 4400
Wire Wire Line
	4500 4400 4500 4050
Wire Wire Line
	5350 4100 5350 4500
Wire Wire Line
	4500 3950 4350 3950
Wire Wire Line
	4350 3950 4350 4600
Wire Wire Line
	4350 4900 4350 4950
Wire Wire Line
	5350 4950 5350 4900
$Comp
L RemoteSensor-rescue:2N7002-dk_Transistors-FETs-MOSFETs-Single Q?
U 1 1 5EF5A94D
P 6500 3950
AR Path="/5EF5A94D" Ref="Q?"  Part="1" 
AR Path="/5EF41F85/5EF5A94D" Ref="Q2"  Part="1" 
F 0 "Q2" H 6608 4003 60  0000 L CNN
F 1 "2N7002" H 6608 3897 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 6700 4150 60  0001 L CNN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 6700 4250 60  0001 L CNN
F 4 "2N7002NCT-ND" H 6700 4350 60  0001 L CNN "Digi-Key_PN"
F 5 "2N7002" H 6700 4450 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 6700 4550 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 6700 4650 60  0001 L CNN "Family"
F 8 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 6700 4750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/on-semiconductor/2N7002/2N7002NCT-ND/244664" H 6700 4850 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 60V 115MA SOT-23" H 6700 4950 60  0001 L CNN "Description"
F 11 "ON Semiconductor" H 6700 5050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6700 5150 60  0001 L CNN "Status"
	1    6500 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5EF5A953
P 6200 4750
AR Path="/5EF5A953" Ref="R?"  Part="1" 
AR Path="/5EF41F85/5EF5A953" Ref="R10"  Part="1" 
F 0 "R10" H 6268 4796 50  0000 L CNN
F 1 "10k" H 6268 4705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6240 4740 50  0001 C CNN
F 3 "~" H 6200 4750 50  0001 C CNN
	1    6200 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4600 6200 4050
Wire Wire Line
	5350 4950 6200 4950
Wire Wire Line
	6200 4950 6200 4900
Connection ~ 5350 4950
Wire Wire Line
	5900 4050 6200 4050
Connection ~ 5900 4050
Connection ~ 6200 4050
Wire Wire Line
	6500 3750 6500 3450
$Comp
L RemoteSensor-rescue:3.3V-SparkFun-PowerSymbols #SUPPLY?
U 1 1 5EF5A963
P 4800 3650
AR Path="/5EF5A963" Ref="#SUPPLY?"  Part="1" 
AR Path="/5EF41F85/5EF5A963" Ref="#SUPPLY0114"  Part="1" 
F 0 "#SUPPLY0114" H 4850 3650 45  0001 L BNN
F 1 "3.3V" H 4800 3926 45  0000 C CNN
F 2 "XXX-00000" H 4800 3831 60  0000 C CNN
F 3 "" H 4800 3650 60  0001 C CNN
	1    4800 3650
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:3.3V-SparkFun-PowerSymbols #SUPPLY?
U 1 1 5EF5A969
P 5650 3700
AR Path="/5EF5A969" Ref="#SUPPLY?"  Part="1" 
AR Path="/5EF41F85/5EF5A969" Ref="#SUPPLY0115"  Part="1" 
F 0 "#SUPPLY0115" H 5700 3700 45  0001 L BNN
F 1 "3.3V" H 5650 3976 45  0000 C CNN
F 2 "XXX-00000" H 5650 3881 60  0000 C CNN
F 3 "" H 5650 3700 60  0001 C CNN
	1    5650 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4150 6500 4300
Wire Wire Line
	5200 4000 5200 3100
Connection ~ 5200 4000
Wire Wire Line
	5200 4000 5350 4000
Wire Wire Line
	6200 4050 6200 3100
$Comp
L Device:R_US R?
U 1 1 5EF5A980
P 4950 4750
AR Path="/5EF5A980" Ref="R?"  Part="1" 
AR Path="/5EF41F85/5EF5A980" Ref="R8"  Part="1" 
F 0 "R8" H 5018 4796 50  0000 L CNN
F 1 "10k" H 5018 4705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4990 4740 50  0001 C CNN
F 3 "~" H 4950 4750 50  0001 C CNN
	1    4950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4950 4950 4900
Wire Wire Line
	4950 4950 5350 4950
Connection ~ 4950 4950
Wire Wire Line
	4350 4950 4950 4950
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF5A98A
P 5350 4950
AR Path="/5EF5A98A" Ref="#GND?"  Part="1" 
AR Path="/5EF41F85/5EF5A98A" Ref="#GND0111"  Part="1" 
F 0 "#GND0111" H 5400 4900 45  0001 L BNN
F 1 "GND" H 5350 4780 45  0000 C CNN
F 2 "" H 5350 4850 60  0001 C CNN
F 3 "" H 5350 4850 60  0001 C CNN
	1    5350 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4600 4950 4000
Wire Wire Line
	4950 4000 5050 4000
Connection ~ 5050 4000
$Comp
L Switch:SW_Push SW?
U 1 1 5EF5D1D1
P 5550 2050
AR Path="/5EF5D1D1" Ref="SW?"  Part="1" 
AR Path="/5EF41F85/5EF5D1D1" Ref="SW1"  Part="1" 
F 0 "SW1" H 5550 2335 50  0000 C CNN
F 1 "BTN_RST" H 5550 2244 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_TL3342" H 5550 2250 50  0001 C CNN
F 3 "~" H 5550 2250 50  0001 C CNN
	1    5550 2050
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF5D1D7
P 5900 2050
AR Path="/5EF5D1D7" Ref="#GND?"  Part="1" 
AR Path="/5EF41F85/5EF5D1D7" Ref="#GND0112"  Part="1" 
F 0 "#GND0112" H 5950 2000 45  0001 L BNN
F 1 "GND" H 5900 1880 45  0000 C CNN
F 2 "" H 5900 1950 60  0001 C CNN
F 3 "" H 5900 1950 60  0001 C CNN
	1    5900 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2050 5900 2050
Text GLabel 5200 2050 0    50   Input ~ 0
RST
Text GLabel 5200 3100 1    50   Input ~ 0
WAKE_STS
Text GLabel 6200 3100 1    50   Input ~ 0
SLEEP_STS
Text GLabel 6750 3450 2    50   Input ~ 0
RST
Text GLabel 6750 4300 2    50   Input ~ 0
CENTER_BTN
Text GLabel 3950 3950 0    50   Input ~ 0
SLEEP_PIN
Text GLabel 3950 4500 0    50   Input ~ 0
HB_PIN
Wire Wire Line
	3950 4500 5350 4500
Connection ~ 5350 4500
Wire Wire Line
	5350 4500 5350 4600
Wire Wire Line
	3950 3950 4350 3950
Connection ~ 4350 3950
Wire Wire Line
	6750 3450 6500 3450
Wire Wire Line
	6500 4300 6750 4300
Wire Wire Line
	5200 2050 5350 2050
$EndSCHEMATC
