EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 4450 2350 0    50   ~ 0
TEMP_PIN
Wire Wire Line
	5000 2350 4450 2350
$Comp
L RemoteSensor-rescue:3.3V-SparkFun-PowerSymbols #SUPPLY?
U 1 1 5EF6911C
P 5600 1500
AR Path="/5EF6911C" Ref="#SUPPLY?"  Part="1" 
AR Path="/5EF5F91F/5EF6911C" Ref="#SUPPLY0116"  Part="1" 
F 0 "#SUPPLY0116" H 5650 1500 45  0001 L BNN
F 1 "3.3V" H 5600 1776 45  0000 C CNN
F 2 "XXX-00000" H 5600 1681 60  0000 C CNN
F 3 "" H 5600 1500 60  0001 C CNN
	1    5600 1500
	1    0    0    -1  
$EndComp
Connection ~ 5600 1500
Wire Wire Line
	5600 1500 5600 1750
Wire Wire Line
	4150 2150 5000 2150
Wire Wire Line
	4150 1800 4150 2150
Wire Wire Line
	4650 1950 5000 1950
Wire Wire Line
	4650 1800 4650 1950
$Comp
L RemoteSensor-rescue:R_US-Device R?
U 1 1 5EF69133
P 4150 1650
AR Path="/5EF69133" Ref="R?"  Part="1" 
AR Path="/5EF5F91F/5EF69133" Ref="R15"  Part="1" 
F 0 "R15" H 4218 1696 50  0000 L CNN
F 1 "10k" H 4218 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4190 1640 50  0001 C CNN
F 3 "~" H 4150 1650 50  0001 C CNN
	1    4150 1650
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:ESP-12F-RF_Module U?
U 1 1 5EF6913A
P 5600 2550
AR Path="/5EF6913A" Ref="U?"  Part="1" 
AR Path="/5EF5F91F/5EF6913A" Ref="U7"  Part="1" 
F 0 "U7" H 5600 3531 50  0000 C CNN
F 1 "ESP-12F" H 5600 3440 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 5600 2550 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 5250 2650 50  0001 C CNN
	1    5600 2550
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF69140
P 5600 3250
AR Path="/5EF69140" Ref="#GND?"  Part="1" 
AR Path="/5EF5F91F/5EF69140" Ref="#GND0114"  Part="1" 
F 0 "#GND0114" H 5650 3200 45  0001 L BNN
F 1 "GND" H 5600 3080 45  0000 C CNN
F 2 "" H 5600 3150 60  0001 C CNN
F 3 "" H 5600 3150 60  0001 C CNN
	1    5600 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1500 4650 1500
Wire Wire Line
	4150 1500 4650 1500
Connection ~ 4650 1500
$Comp
L RemoteSensor-rescue:R_US-Device R?
U 1 1 5EF69149
P 4650 1650
AR Path="/5EF69149" Ref="R?"  Part="1" 
AR Path="/5EF5F91F/5EF69149" Ref="R16"  Part="1" 
F 0 "R16" H 4718 1696 50  0000 L CNN
F 1 "10k" H 4718 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4690 1640 50  0001 C CNN
F 3 "~" H 4650 1650 50  0001 C CNN
	1    4650 1650
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:NAV_SWITCH-SparkFun-Switches S?
U 1 1 5EF6B1EF
P 9500 1200
AR Path="/5EF6B1EF" Ref="S?"  Part="1" 
AR Path="/5EF5F91F/5EF6B1EF" Ref="S1"  Part="1" 
F 0 "S1" H 9500 1660 45  0000 C CNN
F 1 "NAV_SWITCH" H 9500 1576 45  0000 C CNN
F 2 "NAV_SWITCH" H 9500 1550 20  0001 C CNN
F 3 "" H 9500 1200 50  0001 C CNN
F 4 "SWCH-08301" H 9500 1481 60  0000 C CNN "Field4"
	1    9500 1200
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF6B1F5
P 9900 1200
AR Path="/5EF6B1F5" Ref="#GND?"  Part="1" 
AR Path="/5EF5F91F/5EF6B1F5" Ref="#GND0115"  Part="1" 
F 0 "#GND0115" H 9950 1150 45  0001 L BNN
F 1 "GND" H 9900 1030 45  0000 C CNN
F 2 "" H 9900 1100 60  0001 C CNN
F 3 "" H 9900 1100 60  0001 C CNN
	1    9900 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 1200 9900 1200
$Comp
L RemoteSensor-rescue:LM50CIM3-LM50CIM3 U?
U 1 1 5EF73CDC
P 9450 2550
AR Path="/5EF73CDC" Ref="U?"  Part="1" 
AR Path="/5EF5F91F/5EF73CDC" Ref="U8"  Part="1" 
F 0 "U8" H 9450 2915 50  0000 C CNN
F 1 "LM50CIM3" H 9450 2824 50  0000 C CNN
F 2 "SOT95P260X110-3N" H 9450 2550 50  0001 L BNN
F 3 "" H 9450 2550 50  0001 L BNN
F 4 "LM50CIM3/NOPBCT-ND" H 9450 2550 50  0001 L BNN "Field4"
F 5 "Texas Instruments" H 9450 2550 50  0001 L BNN "Field5"
F 6 "https://www.digikey.com/product-detail/en/texas-instruments/LM50CIM3-NOPB/LM50CIM3-NOPBCT-ND/120169?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 9450 2550 50  0001 L BNN "Field6"
F 7 "LM50CIM3/NOPB" H 9450 2550 50  0001 L BNN "Field7"
F 8 "SOT-23 Texas Instruments" H 9450 2550 50  0001 L BNN "Field8"
	1    9450 2550
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:3.3V-SparkFun-PowerSymbols #SUPPLY?
U 1 1 5EF73CE2
P 8750 2350
AR Path="/5EF73CE2" Ref="#SUPPLY?"  Part="1" 
AR Path="/5EF5F91F/5EF73CE2" Ref="#SUPPLY0119"  Part="1" 
F 0 "#SUPPLY0119" H 8800 2350 45  0001 L BNN
F 1 "3.3V" H 8750 2626 45  0000 C CNN
F 2 "XXX-00000" H 8750 2531 60  0000 C CNN
F 3 "" H 8750 2350 60  0001 C CNN
	1    8750 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 2550 8750 2350
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF73CE9
P 8750 3150
AR Path="/5EF73CE9" Ref="#GND?"  Part="1" 
AR Path="/5EF5F91F/5EF73CE9" Ref="#GND0117"  Part="1" 
F 0 "#GND0117" H 8800 3100 45  0001 L BNN
F 1 "GND" H 8750 2980 45  0000 C CNN
F 2 "" H 8750 3050 60  0001 C CNN
F 3 "" H 8750 3050 60  0001 C CNN
	1    8750 3150
	1    0    0    -1  
$EndComp
Text Label 10550 2550 2    50   ~ 0
TEMP_PIN
Wire Wire Line
	10150 2550 10550 2550
Wire Wire Line
	8750 2750 8750 3150
$Comp
L RemoteSensor-rescue:R_US-Device R?
U 1 1 5EF7CD26
P 9450 3900
AR Path="/5EF7CD26" Ref="R?"  Part="1" 
AR Path="/5EF5F91F/5EF7CD26" Ref="R17"  Part="1" 
F 0 "R17" V 9245 3900 50  0000 C CNN
F 1 "1k" V 9336 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 9490 3890 50  0001 C CNN
F 3 "~" H 9450 3900 50  0001 C CNN
	1    9450 3900
	0    1    1    0   
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R?
U 1 1 5EF7CD2C
P 9450 4250
AR Path="/5EF7CD2C" Ref="R?"  Part="1" 
AR Path="/5EF5F91F/5EF7CD2C" Ref="R18"  Part="1" 
F 0 "R18" V 9245 4250 50  0000 C CNN
F 1 "1k" V 9336 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 9490 4240 50  0001 C CNN
F 3 "~" H 9450 4250 50  0001 C CNN
	1    9450 4250
	0    1    1    0   
$EndComp
Text GLabel 9050 1200 0    50   Input ~ 0
CENTER_BTN
Wire Wire Line
	9050 1200 9200 1200
Wire Wire Line
	3900 1950 4650 1950
Connection ~ 4650 1950
Text GLabel 6550 2950 2    50   Input ~ 0
RST
Text GLabel 6550 2250 2    50   Input ~ 0
RADIO_RX
Text GLabel 6550 2050 2    50   Input ~ 0
RADIO_TX
Text GLabel 9050 1100 0    50   Input ~ 0
UP_BTN
Wire Wire Line
	9050 1100 9200 1100
Wire Wire Line
	9050 1300 9200 1300
Text GLabel 8900 3900 0    50   Input ~ 0
RADIO_TX
Text GLabel 8900 4250 0    50   Input ~ 0
RADIO_RX
Wire Wire Line
	8900 4250 9300 4250
Wire Wire Line
	8900 3900 9300 3900
Wire Wire Line
	6200 2050 6550 2050
Wire Wire Line
	6200 2250 6550 2250
Wire Wire Line
	6200 2550 6550 2550
Wire Wire Line
	6200 2650 6550 2650
Wire Wire Line
	6200 2950 6550 2950
Wire Wire Line
	6300 5750 6300 5900
Wire Wire Line
	6300 5900 5650 5900
Wire Wire Line
	5650 5900 5650 5450
Wire Wire Line
	5650 5450 5800 5450
Wire Wire Line
	5650 5450 5650 5350
Wire Wire Line
	5650 5350 5800 5350
Connection ~ 5650 5450
Wire Wire Line
	5650 5350 5650 5250
Wire Wire Line
	5650 5250 5800 5250
Connection ~ 5650 5350
$Comp
L RemoteSensor-rescue:3.3V-SparkFun-PowerSymbols #SUPPLY0120
U 1 1 5EF03A19
P 6200 4000
F 0 "#SUPPLY0120" H 6250 4000 45  0001 L BNN
F 1 "3.3V" H 6200 4276 45  0000 C CNN
F 2 "XXX-00000" H 6200 4181 60  0000 C CNN
F 3 "" H 6200 4000 60  0001 C CNN
	1    6200 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4000 6200 4050
$Comp
L RemoteSensor-rescue:MCP23008-E_P-dk_Interface-I-O-Expanders U9
U 1 1 5EEF9F80
P 6300 4750
F 0 "U9" H 6650 5500 60  0000 C CNN
F 1 "MCP23008-E_P" H 6650 5400 60  0000 C CNN
F 2 "Package_SO:SOIC-18W_7.5x11.6mm_P1.27mm" H 6500 4950 60  0001 L CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en021920" H 6500 5050 60  0001 L CNN
F 4 "MCP23008-E/P-ND" H 6500 5150 60  0001 L CNN "Digi-Key_PN"
F 5 "MCP23008-E/P" H 6500 5250 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 6500 5350 60  0001 L CNN "Category"
F 7 "Interface - I/O Expanders" H 6500 5450 60  0001 L CNN "Family"
F 8 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en021920" H 6500 5550 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/microchip-technology/MCP23008-E-P/MCP23008-E-P-ND/735951" H 6500 5650 60  0001 L CNN "DK_Detail_Page"
F 10 "IC I/O EXPANDER I2C 8B 18DIP" H 6500 5750 60  0001 L CNN "Description"
F 11 "Microchip Technology" H 6500 5850 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6500 5950 60  0001 L CNN "Status"
	1    6300 4750
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND0122
U 1 1 5EF09AEA
P 6300 5900
F 0 "#GND0122" H 6350 5850 45  0001 L BNN
F 1 "GND" H 6300 5730 45  0000 C CNN
F 2 "" H 6300 5800 60  0001 C CNN
F 3 "" H 6300 5800 60  0001 C CNN
	1    6300 5900
	1    0    0    -1  
$EndComp
Connection ~ 6300 5900
Text GLabel 5300 4450 0    50   Input ~ 0
CENTER_BTN
Text Label 5400 5050 0    50   ~ 0
SDA
Text Label 5400 5150 0    50   ~ 0
SCL
Wire Wire Line
	5400 5150 5800 5150
Wire Wire Line
	5400 5050 5800 5050
$Comp
L RemoteSensor-rescue:R_US-Device R19
U 1 1 5EF1D3A2
P 5000 5400
F 0 "R19" H 5068 5446 50  0000 L CNN
F 1 "10k" H 5068 5355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5040 5390 50  0001 C CNN
F 3 "~" H 5000 5400 50  0001 C CNN
	1    5000 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 5550 5800 5550
$Comp
L RemoteSensor-rescue:3.3V-SparkFun-PowerSymbols #SUPPLY0121
U 1 1 5EF20521
P 5000 5250
F 0 "#SUPPLY0121" H 5050 5250 45  0001 L BNN
F 1 "3.3V" H 4700 5350 45  0000 C CNN
F 2 "XXX-00000" H 4700 5250 60  0000 C CNN
F 3 "" H 5000 5250 60  0001 C CNN
	1    5000 5250
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R20
U 1 1 5EF20C41
P 7000 1650
F 0 "R20" H 7068 1696 50  0000 L CNN
F 1 "10k" H 7068 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 7040 1640 50  0001 C CNN
F 3 "~" H 7000 1650 50  0001 C CNN
	1    7000 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 1800 7000 2150
Wire Wire Line
	6200 2150 7000 2150
$Comp
L RemoteSensor-rescue:R_US-Device R21
U 1 1 5EF266EA
P 7000 3000
F 0 "R21" H 7068 3046 50  0000 L CNN
F 1 "10k" H 7068 2955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 7040 2990 50  0001 C CNN
F 3 "~" H 7000 3000 50  0001 C CNN
	1    7000 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2850 7000 2850
Wire Wire Line
	7000 3150 7000 3250
Wire Wire Line
	7000 3250 5600 3250
Connection ~ 5600 3250
Wire Wire Line
	5300 4250 5800 4250
Wire Wire Line
	5300 4350 5800 4350
Wire Wire Line
	5300 4450 5800 4450
Text GLabel 5300 4550 0    50   Input ~ 0
BATT_STS
Text GLabel 5300 4650 0    50   Input ~ 0
CHARGE_STS
Text GLabel 5300 4750 0    50   Input ~ 0
CHARGER_STS
Wire Wire Line
	5300 4550 5800 4550
Wire Wire Line
	5300 4650 5800 4650
Wire Wire Line
	5300 4750 5800 4750
Text GLabel 6550 2550 2    50   Input ~ 0
SLEEP_PIN
Text GLabel 5300 4850 0    50   Input ~ 0
HB_PIN
Text GLabel 5300 4950 0    50   Input ~ 0
BATT_PIN
Wire Wire Line
	5300 4850 5800 4850
Wire Wire Line
	5300 4950 5800 4950
Text GLabel 6550 2650 2    50   Input ~ 0
EXP_RST
Text GLabel 4700 5550 0    50   Input ~ 0
EXP_RST
Wire Wire Line
	4700 5550 5000 5550
Connection ~ 5000 5550
Wire Wire Line
	5600 1500 6450 1500
$Comp
L RemoteSensor-rescue:R_US-Device R22
U 1 1 5EF17614
P 6450 1650
F 0 "R22" H 6518 1696 50  0000 L CNN
F 1 "10k" H 6518 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6490 1640 50  0001 C CNN
F 3 "~" H 6450 1650 50  0001 C CNN
	1    6450 1650
	1    0    0    -1  
$EndComp
Connection ~ 6450 1500
Wire Wire Line
	6450 1500 7000 1500
Wire Wire Line
	6450 1800 6450 1950
Wire Wire Line
	6200 1950 6450 1950
Wire Wire Line
	6450 1950 6550 1950
Connection ~ 6450 1950
Text GLabel 6550 1950 2    50   Input ~ 0
FLASH
Text GLabel 10000 3900 2    50   Input ~ 0
PRG_RX
Text GLabel 10000 4250 2    50   Input ~ 0
PRG_TX
Wire Wire Line
	9600 3900 10000 3900
Wire Wire Line
	9600 4250 10000 4250
Text GLabel 5300 4350 0    50   Input ~ 0
DOWN_BTN
Text GLabel 5300 4250 0    50   Input ~ 0
UP_BTN
Text GLabel 9050 1300 0    50   Input ~ 0
DOWN_BTN
$Comp
L RemoteSensor-rescue:SW_Push-Switch SW2
U 1 1 5EF8556A
P 2100 1300
AR Path="/5EF8556A" Ref="SW2"  Part="1" 
AR Path="/5EF5F91F/5EF8556A" Ref="SW2"  Part="1" 
F 0 "SW2" H 2100 1585 50  0000 C CNN
F 1 "FLASH" H 2100 1494 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_TL3342" H 2100 1500 50  0001 C CNN
F 3 "~" H 2100 1500 50  0001 C CNN
	1    2100 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5950 2200 5950
Wire Wire Line
	2000 6350 2200 6350
Text GLabel 2000 6350 0    50   Input ~ 0
BATT_PIN
Text GLabel 2000 5950 0    50   Input ~ 0
HB_PIN
Wire Wire Line
	1800 4600 2100 4600
Text GLabel 1800 4600 0    50   Input ~ 0
WAKE_STS
Text GLabel 3900 1950 0    50   Input ~ 0
RST
Wire Wire Line
	2500 5950 2650 5950
Wire Wire Line
	2500 6350 2650 6350
$Comp
L RemoteSensor-rescue:R_US-Device R?
U 1 1 5EF7FA3A
P 2350 6350
AR Path="/5EF7FA3A" Ref="R?"  Part="1" 
AR Path="/5EF5F91F/5EF7FA3A" Ref="R13"  Part="1" 
F 0 "R13" V 2145 6350 50  0000 C CNN
F 1 "100" V 2236 6350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2390 6340 50  0001 C CNN
F 3 "~" H 2350 6350 50  0001 C CNN
	1    2350 6350
	0    1    1    0   
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R?
U 1 1 5EF7FA34
P 2350 5950
AR Path="/5EF7FA34" Ref="R?"  Part="1" 
AR Path="/5EF5F91F/5EF7FA34" Ref="R12"  Part="1" 
F 0 "R12" V 2555 5950 50  0000 C CNN
F 1 "100" V 2464 5950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2390 5940 50  0001 C CNN
F 3 "~" H 2350 5950 50  0001 C CNN
	1    2350 5950
	0    -1   -1   0   
$EndComp
Connection ~ 3150 6350
Wire Wire Line
	3150 6450 3150 6350
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF7FA2C
P 3150 6450
AR Path="/5EF7FA2C" Ref="#GND?"  Part="1" 
AR Path="/5EF5F91F/5EF7FA2C" Ref="#GND0121"  Part="1" 
F 0 "#GND0121" H 3200 6400 45  0001 L BNN
F 1 "GND" H 3150 6280 45  0000 C CNN
F 2 "" H 3150 6350 60  0001 C CNN
F 3 "" H 3150 6350 60  0001 C CNN
	1    3150 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 6350 2950 6350
Wire Wire Line
	3150 5950 3150 6350
Wire Wire Line
	2950 5950 3150 5950
$Comp
L RemoteSensor-rescue:LED-Device D?
U 1 1 5EF7FA23
P 2800 6350
AR Path="/5EF7FA23" Ref="D?"  Part="1" 
AR Path="/5EF5F91F/5EF7FA23" Ref="D2"  Part="1" 
F 0 "D2" H 2793 6095 50  0000 C CNN
F 1 "BATT_LED" H 2793 6186 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2800 6350 50  0001 C CNN
F 3 "~" H 2800 6350 50  0001 C CNN
	1    2800 6350
	-1   0    0    1   
$EndComp
$Comp
L RemoteSensor-rescue:LED-Device D?
U 1 1 5EF7FA1D
P 2800 5950
AR Path="/5EF7FA1D" Ref="D?"  Part="1" 
AR Path="/5EF5F91F/5EF7FA1D" Ref="D1"  Part="1" 
F 0 "D1" H 2793 5695 50  0000 C CNN
F 1 "HB_LED" H 2793 5786 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2800 5950 50  0001 C CNN
F 3 "~" H 2800 5950 50  0001 C CNN
	1    2800 5950
	-1   0    0    1   
$EndComp
$Comp
L RemoteSensor-rescue:2N7002-dk_Transistors-FETs-MOSFETs-Single Q?
U 1 1 5EF6FC40
P 2400 4500
AR Path="/5EF6FC40" Ref="Q?"  Part="1" 
AR Path="/5EF5F91F/5EF6FC40" Ref="Q3"  Part="1" 
F 0 "Q3" H 2508 4553 60  0000 L CNN
F 1 "2N7002" H 2508 4447 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2600 4700 60  0001 L CNN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 2600 4800 60  0001 L CNN
F 4 "2N7002NCT-ND" H 2600 4900 60  0001 L CNN "Digi-Key_PN"
F 5 "2N7002" H 2600 5000 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2600 5100 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 2600 5200 60  0001 L CNN "Family"
F 8 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 2600 5300 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/on-semiconductor/2N7002/2N7002NCT-ND/244664" H 2600 5400 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 60V 115MA SOT-23" H 2600 5500 60  0001 L CNN "Description"
F 11 "ON Semiconductor" H 2600 5600 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2600 5700 60  0001 L CNN "Status"
	1    2400 4500
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND?
U 1 1 5EF6FC2F
P 2400 4700
AR Path="/5EF6FC2F" Ref="#GND?"  Part="1" 
AR Path="/5EF5F91F/5EF6FC2F" Ref="#GND0116"  Part="1" 
F 0 "#GND0116" H 2450 4650 45  0001 L BNN
F 1 "GND" H 2400 4530 45  0000 C CNN
F 2 "" H 2400 4600 60  0001 C CNN
F 3 "" H 2400 4600 60  0001 C CNN
	1    2400 4700
	1    0    0    -1  
$EndComp
Text Label 1950 4200 0    50   ~ 0
SDA
Text Label 1950 4100 0    50   ~ 0
SCL
Wire Wire Line
	1950 4200 2550 4200
Wire Wire Line
	2550 4100 1950 4100
Wire Wire Line
	2400 4000 2400 4300
Wire Wire Line
	2550 4000 2400 4000
Wire Wire Line
	2400 3900 2550 3900
$Comp
L RemoteSensor-rescue:3.3V-SparkFun-PowerSymbols #SUPPLY?
U 1 1 5EF6FC22
P 2400 3900
AR Path="/5EF6FC22" Ref="#SUPPLY?"  Part="1" 
AR Path="/5EF5F91F/5EF6FC22" Ref="#SUPPLY0118"  Part="1" 
F 0 "#SUPPLY0118" H 2450 3900 45  0001 L BNN
F 1 "3.3V" H 2400 4176 45  0000 C CNN
F 2 "XXX-00000" H 2400 4081 60  0000 C CNN
F 3 "" H 2400 3900 60  0001 C CNN
	1    2400 3900
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:Conn_01x04-Connector_Generic J?
U 1 1 5EF6FC1C
P 2750 4000
AR Path="/5EF6FC1C" Ref="J?"  Part="1" 
AR Path="/5EF5F91F/5EF6FC1C" Ref="J3"  Part="1" 
F 0 "J3" H 2830 3992 50  0000 L CNN
F 1 "LCD_HEADER" H 2830 3901 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2750 4000 50  0001 C CNN
F 3 "~" H 2750 4000 50  0001 C CNN
	1    2750 4000
	1    0    0    -1  
$EndComp
Text Label 1750 2950 0    50   ~ 0
SDA
Text Label 1750 2800 0    50   ~ 0
SCL
Wire Wire Line
	2800 2950 1750 2950
Wire Wire Line
	2800 2800 2800 2950
Wire Wire Line
	2200 2800 1750 2800
Wire Wire Line
	2200 2450 2200 2500
Connection ~ 2200 2450
Wire Wire Line
	2800 2450 2800 2500
Wire Wire Line
	2200 2450 2800 2450
Wire Wire Line
	2200 2300 2200 2450
$Comp
L RemoteSensor-rescue:3.3V-SparkFun-PowerSymbols #SUPPLY?
U 1 1 5EF6D225
P 2200 2300
AR Path="/5EF6D225" Ref="#SUPPLY?"  Part="1" 
AR Path="/5EF5F91F/5EF6D225" Ref="#SUPPLY0117"  Part="1" 
F 0 "#SUPPLY0117" H 2250 2300 45  0001 L BNN
F 1 "3.3V" H 2200 2576 45  0000 C CNN
F 2 "XXX-00000" H 2200 2481 60  0000 C CNN
F 3 "" H 2200 2300 60  0001 C CNN
	1    2200 2300
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R?
U 1 1 5EF6D21F
P 2800 2650
AR Path="/5EF6D21F" Ref="R?"  Part="1" 
AR Path="/5EF5F91F/5EF6D21F" Ref="R14"  Part="1" 
F 0 "R14" H 2868 2696 50  0000 L CNN
F 1 "4.7k" H 2868 2605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2840 2640 50  0001 C CNN
F 3 "~" H 2800 2650 50  0001 C CNN
	1    2800 2650
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:R_US-Device R?
U 1 1 5EF6D219
P 2200 2650
AR Path="/5EF6D219" Ref="R?"  Part="1" 
AR Path="/5EF5F91F/5EF6D219" Ref="R11"  Part="1" 
F 0 "R11" H 2268 2696 50  0000 L CNN
F 1 "4.7k" H 2268 2605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2240 2640 50  0001 C CNN
F 3 "~" H 2200 2650 50  0001 C CNN
	1    2200 2650
	1    0    0    -1  
$EndComp
$Comp
L RemoteSensor-rescue:GND-SparkFun-PowerSymbols #GND0123
U 1 1 5EF95E82
P 2550 1300
AR Path="/5EF95E82" Ref="#GND0123"  Part="1" 
AR Path="/5EF5F91F/5EF95E82" Ref="#GND0123"  Part="1" 
F 0 "#GND0123" H 2600 1250 45  0001 L BNN
F 1 "GND" H 2550 1130 45  0000 C CNN
F 2 "" H 2550 1200 60  0001 C CNN
F 3 "" H 2550 1200 60  0001 C CNN
	1    2550 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 1300 2550 1300
Text GLabel 1650 1300 0    50   Input ~ 0
FLASH
Wire Wire Line
	1650 1300 1900 1300
Wire Wire Line
	6200 2350 6500 2350
Wire Wire Line
	6200 2450 6500 2450
Text Label 6500 2350 2    50   ~ 0
SCL
Text Label 6500 2450 2    50   ~ 0
SDA
$EndSCHEMATC
