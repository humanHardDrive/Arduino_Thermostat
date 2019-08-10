EESchema Schematic File Version 4
LIBS:Thermostat_Layout-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
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
L dk_Embedded-Microcontrollers:ATMEGA328P-AU U2
U 1 1 5D3DFFF8
P 6300 2950
F 0 "U2" H 6628 3053 60  0000 L CNN
F 1 "ATMEGA328P-AU" H 6628 2947 60  0000 L CNN
F 2 "digikey-footprints:TQFP-32_7x7mm" H 6500 3150 60  0001 L CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en608326" H 6500 3250 60  0001 L CNN
F 4 "ATMEGA328P-AU-ND" H 6500 3350 60  0001 L CNN "Digi-Key_PN"
F 5 "ATMEGA328P-AU" H 6500 3450 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 6500 3550 60  0001 L CNN "Category"
F 7 "Embedded - Microcontrollers" H 6500 3650 60  0001 L CNN "Family"
F 8 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en608326" H 6500 3750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/microchip-technology/ATMEGA328P-AU/ATMEGA328P-AU-ND/1832260" H 6500 3850 60  0001 L CNN "DK_Detail_Page"
F 10 "IC MCU 8BIT 32KB FLASH 32TQFP" H 6500 3950 60  0001 L CNN "Description"
F 11 "Microchip Technology" H 6500 4050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6500 4150 60  0001 L CNN "Status"
	1    6300 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4450 6400 4450
Wire Wire Line
	6400 4450 6500 4450
Connection ~ 6400 4450
$Comp
L SparkFun-PowerSymbols:GND #GND0101
U 1 1 5D3E1674
P 6400 4450
F 0 "#GND0101" H 6450 4400 45  0001 L BNN
F 1 "GND" H 6400 4280 45  0000 C CNN
F 2 "" H 6400 4350 60  0001 C CNN
F 3 "" H 6400 4350 60  0001 C CNN
	1    6400 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1350 6400 1350
Wire Wire Line
	6400 1350 6500 1350
Connection ~ 6400 1350
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0101
U 1 1 5D3E1EE5
P 6400 1250
F 0 "#SUPPLY0101" H 6450 1250 45  0001 L BNN
F 1 "3.3V" H 6400 1526 45  0000 C CNN
F 2 "XXX-00000" H 6400 1431 60  0000 C CNN
F 3 "" H 6400 1250 60  0001 C CNN
	1    6400 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 1250 6400 1350
$Comp
L Device:C C1
U 1 1 5D3E2A64
P 5200 4250
F 0 "C1" H 5315 4296 50  0000 L CNN
F 1 "100nF" H 5315 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5238 4100 50  0001 C CNN
F 3 "~" H 5200 4250 50  0001 C CNN
	1    5200 4250
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0102
U 1 1 5D3E37E7
P 5200 4400
F 0 "#GND0102" H 5250 4350 45  0001 L BNN
F 1 "GND" H 5200 4230 45  0000 C CNN
F 2 "" H 5200 4300 60  0001 C CNN
F 3 "" H 5200 4300 60  0001 C CNN
	1    5200 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4050 5200 4050
Wire Wire Line
	5200 4050 5200 4100
$Comp
L Device:R_US R1
U 1 1 5D431858
P 1950 1350
F 0 "R1" H 2018 1396 50  0000 L CNN
F 1 "4.7K" H 2018 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1990 1340 50  0001 C CNN
F 3 "~" H 1950 1350 50  0001 C CNN
	1    1950 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 5D4319D2
P 2350 1350
F 0 "R2" H 2418 1396 50  0000 L CNN
F 1 "4.7K" H 2418 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2390 1340 50  0001 C CNN
F 3 "~" H 2350 1350 50  0001 C CNN
	1    2350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1200 2150 1200
Wire Wire Line
	2350 1500 2350 1700
Wire Wire Line
	2350 1700 1550 1700
Wire Wire Line
	1950 1500 1550 1500
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0103
U 1 1 5D432D22
P 2150 1200
F 0 "#SUPPLY0103" H 2200 1200 45  0001 L BNN
F 1 "3.3V" H 2150 1476 45  0000 C CNN
F 2 "XXX-00000" H 2150 1381 60  0000 C CNN
F 3 "" H 2150 1200 60  0001 C CNN
	1    2150 1200
	1    0    0    -1  
$EndComp
Connection ~ 2150 1200
Wire Wire Line
	2150 1200 2350 1200
Text GLabel 1550 1500 0    50   BiDi ~ 0
SDA
Text GLabel 1550 1700 0    50   Input ~ 0
SCL
Wire Wire Line
	1800 3100 2200 3100
$Comp
L SparkFun-PowerSymbols:GND #GND0106
U 1 1 5D47A3DC
P 1800 3100
F 0 "#GND0106" H 1850 3050 45  0001 L BNN
F 1 "GND" H 1800 2930 45  0000 C CNN
F 2 "" H 1800 3000 60  0001 C CNN
F 3 "" H 1800 3000 60  0001 C CNN
	1    1800 3100
	1    0    0    -1  
$EndComp
Text Label 1800 2200 0    50   ~ 0
X1
Text Label 2200 2200 0    50   ~ 0
X2
Wire Wire Line
	5800 1850 5000 1850
Wire Wire Line
	5800 1950 5000 1950
Text Label 5000 1850 0    50   ~ 0
X1
Text Label 5000 1950 0    50   ~ 0
X2
Wire Wire Line
	5800 3850 5000 3850
Text GLabel 5000 3850 0    50   Input ~ 0
EXP_INT
Wire Wire Line
	5800 1750 5000 1750
Text GLabel 5000 1750 0    50   Output ~ 0
LCD_D7
Wire Wire Line
	5800 2050 5000 2050
Wire Wire Line
	5800 2150 5000 2150
Wire Wire Line
	5800 2250 5000 2250
Text GLabel 5000 2050 0    50   Output ~ 0
LCD_D6
Text GLabel 5000 2150 0    50   Output ~ 0
LCD_D5
Text GLabel 5000 2250 0    50   Output ~ 0
LCD_D4
Wire Wire Line
	5800 2350 5000 2350
Wire Wire Line
	5000 2450 5800 2450
Text GLabel 5000 2350 0    50   Output ~ 0
LCD_EN
Text GLabel 5000 2450 0    50   Output ~ 0
LCD_RS
Wire Wire Line
	5800 2550 5000 2550
Text GLabel 5000 2550 0    50   Output ~ 0
MEM_CS
Wire Wire Line
	5800 2650 5000 2650
Wire Wire Line
	5800 2750 5000 2750
Wire Wire Line
	5800 2850 5000 2850
Text GLabel 5000 2650 0    50   Output ~ 0
MOSI
Text GLabel 5000 2750 0    50   Input ~ 0
MISO
Text GLabel 5000 2850 0    50   Output ~ 0
SCK
Wire Wire Line
	5800 2950 5000 2950
Wire Wire Line
	5800 3050 5000 3050
Text GLabel 5000 2950 0    50   Output ~ 0
EXP_CS
Text GLabel 5000 3050 0    50   Output ~ 0
EXP_RST
Wire Wire Line
	5800 3150 5000 3150
Wire Wire Line
	5800 3250 5000 3250
Text GLabel 5000 3150 0    50   Output ~ 0
RF_CE
Text GLabel 5000 3250 0    50   Output ~ 0
RF_CS
Wire Wire Line
	5800 3350 5000 3350
Wire Wire Line
	5800 3450 5000 3450
Text GLabel 5000 3350 0    50   BiDi ~ 0
SDA
Text GLabel 5000 3450 0    50   Output ~ 0
SCL
Wire Wire Line
	5800 3650 5000 3650
Wire Wire Line
	5800 3750 5000 3750
Text GLabel 5000 3650 0    50   Input ~ 0
UC_RX
Text GLabel 5000 3750 0    50   Output ~ 0
UC_TX
$Comp
L Connector:TestPoint TP1
U 1 1 5D48AFDB
P 5300 1650
F 0 "TP1" H 5358 1813 50  0000 L CNN
F 1 "HB_OUTPUT" H 5358 1722 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 5358 1631 50  0000 L CNN
F 3 "~" H 5500 1650 50  0001 C CNN
	1    5300 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 1650 5300 1650
$Comp
L LM50CIM3:LM50CIM3 U1
U 1 1 5D48CD29
P 2100 4150
F 0 "U1" H 2100 4515 50  0000 C CNN
F 1 "LM50CIM3" H 2100 4424 50  0000 C CNN
F 2 "SOT95P260X110-3N" H 2100 4150 50  0001 L BNN
F 3 "" H 2100 4150 50  0001 L BNN
F 4 "LM50CIM3/NOPBCT-ND" H 2100 4150 50  0001 L BNN "Field4"
F 5 "Texas Instruments" H 2100 4150 50  0001 L BNN "Field5"
F 6 "https://www.digikey.com/product-detail/en/texas-instruments/LM50CIM3-NOPB/LM50CIM3-NOPBCT-ND/120169?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 2100 4150 50  0001 L BNN "Field6"
F 7 "LM50CIM3/NOPB" H 2100 4150 50  0001 L BNN "Field7"
F 8 "SOT-23 Texas Instruments" H 2100 4150 50  0001 L BNN "Field8"
	1    2100 4150
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0107
U 1 1 5D48DCED
P 1400 4350
F 0 "#GND0107" H 1450 4300 45  0001 L BNN
F 1 "GND" H 1400 4180 45  0000 C CNN
F 2 "" H 1400 4250 60  0001 C CNN
F 3 "" H 1400 4250 60  0001 C CNN
	1    1400 4350
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0104
U 1 1 5D48E2F2
P 1400 4150
F 0 "#SUPPLY0104" H 1450 4150 45  0001 L BNN
F 1 "3.3V" H 1400 4426 45  0000 C CNN
F 2 "XXX-00000" H 1400 4331 60  0000 C CNN
F 3 "" H 1400 4150 60  0001 C CNN
	1    1400 4150
	1    0    0    -1  
$EndComp
Text Label 2800 4150 0    50   ~ 0
ANA_TEMP
Wire Wire Line
	5800 3950 5000 3950
Wire Wire Line
	5800 4150 5000 4150
Text Label 5000 3950 0    50   ~ 0
ANA_TEMP
Text GLabel 5000 4150 0    50   Input ~ 0
BATT_MON
$Comp
L FM25V10:FM25V10 U7
U 1 1 5D493642
P 4000 5850
F 0 "U7" H 4000 6481 50  0000 C CNN
F 1 "FM25V10" H 4000 6390 50  0000 C CNN
F 2 "FM25V10:SOIC127P601X172-8N" H 4000 6550 50  0001 C CNN
F 3 "" H 4000 5850 50  0001 C CNN
	1    4000 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 5700 4700 5700
Wire Wire Line
	4700 5700 4700 6000
Wire Wire Line
	4700 6000 4500 6000
Wire Wire Line
	4000 5400 4700 5400
Wire Wire Line
	4700 5400 4700 5700
Connection ~ 4700 5700
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0110
U 1 1 5D496E24
P 4700 5400
F 0 "#SUPPLY0110" H 4750 5400 45  0001 L BNN
F 1 "3.3V" H 4700 5676 45  0000 C CNN
F 2 "XXX-00000" H 4700 5581 60  0000 C CNN
F 3 "" H 4700 5400 60  0001 C CNN
	1    4700 5400
	1    0    0    -1  
$EndComp
Connection ~ 4700 5400
$Comp
L SparkFun-PowerSymbols:GND #GND0117
U 1 1 5D497357
P 4000 6400
F 0 "#GND0117" H 4050 6350 45  0001 L BNN
F 1 "GND" H 4000 6230 45  0000 C CNN
F 2 "" H 4000 6300 60  0001 C CNN
F 3 "" H 4000 6300 60  0001 C CNN
	1    4000 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5700 3000 5700
Wire Wire Line
	3500 5850 3000 5850
Wire Wire Line
	3500 6000 3000 6000
Wire Wire Line
	3500 6150 3000 6150
Text GLabel 3000 5700 0    50   Input ~ 0
MEM_CS
Text GLabel 3000 5850 0    50   Output ~ 0
MISO
Text GLabel 3000 6000 0    50   Input ~ 0
MOSI
Text GLabel 3000 6150 0    50   Input ~ 0
SCK
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5D47414E
P 9400 1600
F 0 "J1" H 9480 1642 50  0000 L CNN
F 1 "Conn_01x03" H 9480 1551 50  0000 L CNN
F 2 "Connector_JST:JST_PH_S3B-PH-SM4-TB_1x03-1MP_P2.00mm_Horizontal" H 9400 1600 50  0001 C CNN
F 3 "~" H 9400 1600 50  0001 C CNN
	1    9400 1600
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND0105
U 1 1 5D4748F4
P 9050 1850
F 0 "#GND0105" H 9100 1800 45  0001 L BNN
F 1 "GND" H 9050 1680 45  0000 C CNN
F 2 "" H 9050 1750 60  0001 C CNN
F 3 "" H 9050 1750 60  0001 C CNN
	1    9050 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 1600 9050 1600
Wire Wire Line
	9050 1600 9050 1850
Wire Wire Line
	8800 1700 9200 1700
Wire Wire Line
	9200 1500 8800 1500
$Comp
L Device:R_US R3
U 1 1 5D475940
P 8650 1500
F 0 "R3" V 8445 1500 50  0000 C CNN
F 1 "1kΩ" V 8536 1500 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8690 1490 50  0001 C CNN
F 3 "~" H 8650 1500 50  0001 C CNN
	1    8650 1500
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R4
U 1 1 5D4760EE
P 8650 1700
F 0 "R4" V 8445 1700 50  0000 C CNN
F 1 "1kΩ" V 8536 1700 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8690 1690 50  0001 C CNN
F 3 "~" H 8650 1700 50  0001 C CNN
	1    8650 1700
	0    1    1    0   
$EndComp
Text GLabel 8500 1500 0    50   Input ~ 0
UC_TX
Text GLabel 8500 1700 0    50   Output ~ 0
UC_RX
$Comp
L Switch:SW_Push SW1
U 1 1 5D523EF5
P 8300 5000
F 0 "SW1" H 8300 5285 50  0000 C CNN
F 1 "SW_Push" H 8300 5194 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_TL3342" H 8300 5200 50  0001 C CNN
F 3 "~" H 8300 5200 50  0001 C CNN
	1    8300 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3550 5000 3550
Text GLabel 5000 3550 0    50   Input ~ 0
UC_RST
Wire Wire Line
	8100 5000 7800 5000
Text GLabel 7500 5000 0    50   Input ~ 0
UC_RST
$Comp
L SparkFun-PowerSymbols:GND #GND0123
U 1 1 5D527C49
P 8500 5000
F 0 "#GND0123" H 8550 4950 45  0001 L BNN
F 1 "GND" H 8500 4830 45  0000 C CNN
F 2 "" H 8500 4900 60  0001 C CNN
F 3 "" H 8500 4900 60  0001 C CNN
	1    8500 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R13
U 1 1 5D52827F
P 7800 4850
F 0 "R13" H 7868 4896 50  0000 L CNN
F 1 "10kΩ" H 7868 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7840 4840 50  0001 C CNN
F 3 "~" H 7800 4850 50  0001 C CNN
	1    7800 4850
	1    0    0    -1  
$EndComp
Connection ~ 7800 5000
Wire Wire Line
	7800 5000 7500 5000
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY0111
U 1 1 5D528D3B
P 7800 4700
F 0 "#SUPPLY0111" H 7850 4700 45  0001 L BNN
F 1 "3.3V" H 7800 4976 45  0000 C CNN
F 2 "XXX-00000" H 7800 4881 60  0000 C CNN
F 3 "" H 7800 4700 60  0001 C CNN
	1    7800 4700
	1    0    0    -1  
$EndComp
Connection ~ 1800 3100
Connection ~ 1800 2650
Wire Wire Line
	1800 2650 1800 2200
Connection ~ 2200 2650
Wire Wire Line
	2200 2650 2200 2200
Wire Wire Line
	2200 2650 2200 2800
Wire Wire Line
	2150 2650 2200 2650
Wire Wire Line
	1800 2650 1800 2800
Wire Wire Line
	1850 2650 1800 2650
$Comp
L Device:C C3
U 1 1 5D477AC7
P 2200 2950
F 0 "C3" H 2315 2996 50  0000 L CNN
F 1 "22pF" H 2315 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 2238 2800 50  0001 C CNN
F 3 "~" H 2200 2950 50  0001 C CNN
	1    2200 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5D4774F7
P 1800 2950
F 0 "C2" H 1915 2996 50  0000 L CNN
F 1 "22pF" H 1915 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1838 2800 50  0001 C CNN
F 3 "~" H 1800 2950 50  0001 C CNN
	1    1800 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 5D476A0F
P 2000 2650
F 0 "Y1" H 2000 2918 50  0000 C CNN
F 1 "Crystal" H 2000 2827 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_SeikoEpson_MC405-2Pin_9.6x4.1mm" H 2000 2650 50  0001 C CNN
F 3 "~" H 2000 2650 50  0001 C CNN
	1    2000 2650
	1    0    0    -1  
$EndComp
$EndSCHEMATC