EESchema Schematic File Version 4
LIBS:Thermostat_Remote-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L dk_Embedded-Microcontrollers:ATMEGA328P-AU U?
U 1 1 5D4925A1
P 5600 3350
F 0 "U?" H 5928 3453 60  0000 L CNN
F 1 "ATMEGA328P-AU" H 5928 3347 60  0000 L CNN
F 2 "digikey-footprints:TQFP-32_7x7mm" H 5800 3550 60  0001 L CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en608326" H 5800 3650 60  0001 L CNN
F 4 "ATMEGA328P-AU-ND" H 5800 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "ATMEGA328P-AU" H 5800 3850 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 5800 3950 60  0001 L CNN "Category"
F 7 "Embedded - Microcontrollers" H 5800 4050 60  0001 L CNN "Family"
F 8 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en608326" H 5800 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/microchip-technology/ATMEGA328P-AU/ATMEGA328P-AU-ND/1832260" H 5800 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "IC MCU 8BIT 32KB FLASH 32TQFP" H 5800 4350 60  0001 L CNN "Description"
F 11 "Microchip Technology" H 5800 4450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5800 4550 60  0001 L CNN "Status"
	1    5600 3350
	1    0    0    -1  
$EndComp
$Comp
L FM25V10:FM25V10 U?
U 1 1 5D493B84
P 8700 2400
F 0 "U?" H 8700 3031 50  0000 C CNN
F 1 "FM25V10" H 8700 2940 50  0000 C CNN
F 2 "FM25V10:SOIC127P601X172-8N" H 8700 3100 50  0001 C CNN
F 3 "" H 8700 2400 50  0001 C CNN
	1    8700 2400
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Switches:JOYSTICK_MINI S?
U 1 1 5D494A36
P 8700 4350
F 0 "S?" H 8700 4810 45  0000 C CNN
F 1 "JOYSTICK_MINI" H 8700 4726 45  0000 C CNN
F 2 "JOYSTICK_MINI" H 8700 4650 20  0001 C CNN
F 3 "" H 8700 4350 50  0001 C CNN
F 4 "SWCH-09905" H 8700 4631 60  0000 C CNN "Field4"
	1    8700 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1750 5700 1750
Wire Wire Line
	5800 1750 5700 1750
Connection ~ 5700 1750
Wire Wire Line
	5600 4850 5700 4850
Wire Wire Line
	5700 4850 5800 4850
Connection ~ 5700 4850
$Comp
L SparkFun-PowerSymbols:GND #GND?
U 1 1 5D496417
P 5700 4850
F 0 "#GND?" H 5750 4800 45  0001 L BNN
F 1 "GND" H 5700 4680 45  0000 C CNN
F 2 "" H 5700 4750 60  0001 C CNN
F 3 "" H 5700 4750 60  0001 C CNN
	1    5700 4850
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND?
U 1 1 5D4969B9
P 8200 4450
F 0 "#GND?" H 8250 4400 45  0001 L BNN
F 1 "GND" H 8200 4280 45  0000 C CNN
F 2 "" H 8200 4350 60  0001 C CNN
F 3 "" H 8200 4350 60  0001 C CNN
	1    8200 4450
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY?
U 1 1 5D497264
P 5700 1700
F 0 "#SUPPLY?" H 5750 1700 45  0001 L BNN
F 1 "3.3V" H 5700 1976 45  0000 C CNN
F 2 "XXX-00000" H 5700 1881 60  0000 C CNN
F 3 "" H 5700 1700 60  0001 C CNN
	1    5700 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 1700 5700 1750
$Comp
L SparkFun-PowerSymbols:GND #GND?
U 1 1 5D497918
P 8700 2950
F 0 "#GND?" H 8750 2900 45  0001 L BNN
F 1 "GND" H 8700 2780 45  0000 C CNN
F 2 "" H 8700 2850 60  0001 C CNN
F 3 "" H 8700 2850 60  0001 C CNN
	1    8700 2950
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY?
U 1 1 5D497E3F
P 8700 1650
F 0 "#SUPPLY?" H 8750 1650 45  0001 L BNN
F 1 "3.3V" H 8700 1926 45  0000 C CNN
F 2 "XXX-00000" H 8700 1831 60  0000 C CNN
F 3 "" H 8700 1650 60  0001 C CNN
	1    8700 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1650 8700 1900
Wire Wire Line
	8700 1900 9200 1900
Wire Wire Line
	9200 1900 9200 2250
Connection ~ 8700 1900
Wire Wire Line
	8700 1900 8700 1950
Wire Wire Line
	9200 2250 9200 2550
Connection ~ 9200 2250
$Comp
L LM50CIM3:LM50CIM3 U?
U 1 1 5D498B24
P 2450 1950
F 0 "U?" H 2450 2315 50  0000 C CNN
F 1 "LM50CIM3" H 2450 2224 50  0000 C CNN
F 2 "SOT95P260X110-3N" H 2450 1950 50  0001 L BNN
F 3 "" H 2450 1950 50  0001 L BNN
F 4 "LM50CIM3/NOPBCT-ND" H 2450 1950 50  0001 L BNN "Field4"
F 5 "Texas Instruments" H 2450 1950 50  0001 L BNN "Field5"
F 6 "https://www.digikey.com/product-detail/en/texas-instruments/LM50CIM3-NOPB/LM50CIM3-NOPBCT-ND/120169?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 2450 1950 50  0001 L BNN "Field6"
F 7 "LM50CIM3/NOPB" H 2450 1950 50  0001 L BNN "Field7"
F 8 "SOT-23 Texas Instruments" H 2450 1950 50  0001 L BNN "Field8"
	1    2450 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 3250 4600 3250
Wire Wire Line
	5100 3150 4600 3150
Wire Wire Line
	5100 3050 4600 3050
Text GLabel 4600 3050 0    50   Output ~ 0
MOSI
Text GLabel 4600 3150 0    50   Input ~ 0
MISO
Text GLabel 4600 3250 0    50   Output ~ 0
SCK
Wire Wire Line
	3150 1950 3400 1950
Text Label 3400 1950 0    50   ~ 0
ANA_TEMP
$Comp
L SparkFun-PowerSymbols:GND #GND?
U 1 1 5D4A9E90
P 1750 2150
F 0 "#GND?" H 1800 2100 45  0001 L BNN
F 1 "GND" H 1750 1980 45  0000 C CNN
F 2 "" H 1750 2050 60  0001 C CNN
F 3 "" H 1750 2050 60  0001 C CNN
	1    1750 2150
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY?
U 1 1 5D4AA7A4
P 1750 1950
F 0 "#SUPPLY?" H 1800 1950 45  0001 L BNN
F 1 "3.3V" H 1750 2226 45  0000 C CNN
F 2 "XXX-00000" H 1750 2131 60  0000 C CNN
F 3 "" H 1750 1950 60  0001 C CNN
	1    1750 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 2700 7650 2700
Wire Wire Line
	8200 2550 7650 2550
Wire Wire Line
	8200 2400 7650 2400
Wire Wire Line
	8200 2250 7650 2250
Text GLabel 7650 2250 0    50   Input ~ 0
MEM_CS
Text GLabel 7650 2400 0    50   Output ~ 0
MISO
Text GLabel 7650 2550 0    50   Input ~ 0
MOSI
Text GLabel 7650 2700 0    50   Input ~ 0
SCK
Wire Wire Line
	8200 4250 7800 4250
Wire Wire Line
	8200 4350 7800 4350
Wire Wire Line
	9200 4250 9600 4250
Wire Wire Line
	9200 4350 9600 4350
Wire Wire Line
	9200 4450 9600 4450
Text Label 7800 4250 0    50   ~ 0
UP_BTN
Text Label 7800 4350 0    50   ~ 0
DWN_BTN
Text Label 9250 4250 0    50   ~ 0
LEFT_BTN
Text Label 9250 4350 0    50   ~ 0
RIGHT_BTN
Text Label 9250 4450 0    50   ~ 0
CENTER_BTN
$EndSCHEMATC
