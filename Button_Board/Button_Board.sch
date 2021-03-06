EESchema Schematic File Version 4
LIBS:Button_Board-cache
EELAYER 29 0
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
L Connector_Generic:Conn_01x10 J1
U 1 1 5D50EF2F
P 4300 2750
F 0 "J1" H 4218 3367 50  0000 C CNN
F 1 "Conn_01x10" H 4218 3276 50  0000 C CNN
F 2 "Connector_JST:JST_PH_B10B-PH-SM4-TB_1x10-1MP_P2.00mm_Vertical" H 4300 2750 50  0001 C CNN
F 3 "~" H 4300 2750 50  0001 C CNN
	1    4300 2750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4500 3250 4500 3500
$Comp
L SparkFun-PowerSymbols:GND #GND01
U 1 1 5D510A11
P 4500 3750
F 0 "#GND01" H 4550 3700 45  0001 L BNN
F 1 "GND" H 4500 3580 45  0000 C CNN
F 2 "" H 4500 3650 60  0001 C CNN
F 3 "" H 4500 3650 60  0001 C CNN
	1    4500 3750
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Switches:JOYSTICK_MINI S1
U 1 1 5DBA4CA4
P 5650 2450
F 0 "S1" H 5650 2910 45  0000 C CNN
F 1 "JOYSTICK_MINI" H 5650 2826 45  0000 C CNN
F 2 "JOYSTICK_MINI" H 5650 2750 20  0001 C CNN
F 3 "" H 5650 2450 50  0001 C CNN
F 4 "SWCH-09905" H 5650 2731 60  0000 C CNN "Field4"
	1    5650 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2350 5150 2350
Wire Wire Line
	4500 2450 5150 2450
Wire Wire Line
	4500 2750 6150 2750
Wire Wire Line
	6150 2750 6150 2550
Wire Wire Line
	6150 2450 6200 2450
Wire Wire Line
	6200 2450 6200 2700
Wire Wire Line
	6200 2700 4500 2700
Wire Wire Line
	4500 2700 4500 2650
Wire Wire Line
	6150 2350 6250 2350
Wire Wire Line
	6250 2350 6250 2800
Wire Wire Line
	6250 2800 4550 2800
Wire Wire Line
	4550 2800 4550 2550
Wire Wire Line
	4550 2550 4500 2550
Wire Wire Line
	5150 2550 5150 3250
Wire Wire Line
	5150 3250 4500 3250
Connection ~ 4500 3250
$Comp
L dk_Test-Points:RCT-0C TP2
U 1 1 5DBAC4F9
P 5300 3150
F 0 "TP2" H 5350 3243 50  0000 L CNN
F 1 "RCT-0C" H 5350 3152 50  0000 L CNN
F 2 "digikey-footprints:PROBE_PAD_0805" H 5500 3350 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 5500 3450 60  0001 L CNN
F 4 "A106144CT-ND" H 5500 3550 60  0001 L CNN "Digi-Key_PN"
F 5 "RCT-0C" H 5500 3650 60  0001 L CNN "MPN"
F 6 "Test and Measurement" H 5500 3750 60  0001 L CNN "Category"
F 7 "Test Points" H 5500 3850 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 5500 3950 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/te-connectivity-amp-connectors/RCT-0C/A106144CT-ND/3477801" H 5500 4050 60  0001 L CNN "DK_Detail_Page"
F 10 "PC TEST POINT NATURAL" H 5500 4150 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 5500 4250 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5500 4350 60  0001 L CNN "Status"
	1    5300 3150
	1    0    0    -1  
$EndComp
$Comp
L dk_Test-Points:RCT-0C TP4
U 1 1 5DBAD6EA
P 5650 3050
F 0 "TP4" H 5700 3143 50  0000 L CNN
F 1 "RCT-0C" H 5700 3052 50  0000 L CNN
F 2 "digikey-footprints:PROBE_PAD_0805" H 5850 3250 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 5850 3350 60  0001 L CNN
F 4 "A106144CT-ND" H 5850 3450 60  0001 L CNN "Digi-Key_PN"
F 5 "RCT-0C" H 5850 3550 60  0001 L CNN "MPN"
F 6 "Test and Measurement" H 5850 3650 60  0001 L CNN "Category"
F 7 "Test Points" H 5850 3750 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 5850 3850 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/te-connectivity-amp-connectors/RCT-0C/A106144CT-ND/3477801" H 5850 3950 60  0001 L CNN "DK_Detail_Page"
F 10 "PC TEST POINT NATURAL" H 5850 4050 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 5850 4150 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5850 4250 60  0001 L CNN "Status"
	1    5650 3050
	1    0    0    -1  
$EndComp
$Comp
L dk_Test-Points:RCT-0C TP5
U 1 1 5DBAEFCD
P 6000 2950
F 0 "TP5" H 6050 3043 50  0000 L CNN
F 1 "RCT-0C" H 6050 2952 50  0000 L CNN
F 2 "digikey-footprints:PROBE_PAD_0805" H 6200 3150 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 6200 3250 60  0001 L CNN
F 4 "A106144CT-ND" H 6200 3350 60  0001 L CNN "Digi-Key_PN"
F 5 "RCT-0C" H 6200 3450 60  0001 L CNN "MPN"
F 6 "Test and Measurement" H 6200 3550 60  0001 L CNN "Category"
F 7 "Test Points" H 6200 3650 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 6200 3750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/te-connectivity-amp-connectors/RCT-0C/A106144CT-ND/3477801" H 6200 3850 60  0001 L CNN "DK_Detail_Page"
F 10 "PC TEST POINT NATURAL" H 6200 3950 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 6200 4050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6200 4150 60  0001 L CNN "Status"
	1    6000 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2850 4500 2850
Wire Wire Line
	5650 2950 4500 2950
Wire Wire Line
	5300 3050 4500 3050
$Comp
L dk_Test-Points:RCT-0C TP1
U 1 1 5DBB57F7
P 5000 3600
F 0 "TP1" H 5050 3693 50  0000 L CNN
F 1 "RCT-0C" H 5050 3602 50  0000 L CNN
F 2 "digikey-footprints:PROBE_PAD_0805" H 5200 3800 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 5200 3900 60  0001 L CNN
F 4 "A106144CT-ND" H 5200 4000 60  0001 L CNN "Digi-Key_PN"
F 5 "RCT-0C" H 5200 4100 60  0001 L CNN "MPN"
F 6 "Test and Measurement" H 5200 4200 60  0001 L CNN "Category"
F 7 "Test Points" H 5200 4300 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 5200 4400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/te-connectivity-amp-connectors/RCT-0C/A106144CT-ND/3477801" H 5200 4500 60  0001 L CNN "DK_Detail_Page"
F 10 "PC TEST POINT NATURAL" H 5200 4600 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 5200 4700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5200 4800 60  0001 L CNN "Status"
	1    5000 3600
	1    0    0    -1  
$EndComp
$Comp
L dk_Test-Points:RCT-0C TP3
U 1 1 5DBB616E
P 5550 3600
F 0 "TP3" H 5600 3693 50  0000 L CNN
F 1 "RCT-0C" H 5600 3602 50  0000 L CNN
F 2 "digikey-footprints:PROBE_PAD_0805" H 5750 3800 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 5750 3900 60  0001 L CNN
F 4 "A106144CT-ND" H 5750 4000 60  0001 L CNN "Digi-Key_PN"
F 5 "RCT-0C" H 5750 4100 60  0001 L CNN "MPN"
F 6 "Test and Measurement" H 5750 4200 60  0001 L CNN "Category"
F 7 "Test Points" H 5750 4300 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 5750 4400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/te-connectivity-amp-connectors/RCT-0C/A106144CT-ND/3477801" H 5750 4500 60  0001 L CNN "DK_Detail_Page"
F 10 "PC TEST POINT NATURAL" H 5750 4600 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 5750 4700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5750 4800 60  0001 L CNN "Status"
	1    5550 3600
	1    0    0    -1  
$EndComp
$Comp
L dk_Test-Points:RCT-0C TP6
U 1 1 5DBB6C27
P 6150 3600
F 0 "TP6" H 6200 3693 50  0000 L CNN
F 1 "RCT-0C" H 6200 3602 50  0000 L CNN
F 2 "digikey-footprints:PROBE_PAD_0805" H 6350 3800 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 6350 3900 60  0001 L CNN
F 4 "A106144CT-ND" H 6350 4000 60  0001 L CNN "Digi-Key_PN"
F 5 "RCT-0C" H 6350 4100 60  0001 L CNN "MPN"
F 6 "Test and Measurement" H 6350 4200 60  0001 L CNN "Category"
F 7 "Test Points" H 6350 4300 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773266&DocType=DS&DocLang=English" H 6350 4400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/te-connectivity-amp-connectors/RCT-0C/A106144CT-ND/3477801" H 6350 4500 60  0001 L CNN "DK_Detail_Page"
F 10 "PC TEST POINT NATURAL" H 6350 4600 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 6350 4700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6350 4800 60  0001 L CNN "Status"
	1    6150 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3500 5000 3500
Connection ~ 4500 3500
Wire Wire Line
	4500 3500 4500 3750
Wire Wire Line
	5000 3500 5550 3500
Connection ~ 5000 3500
Wire Wire Line
	5550 3500 6150 3500
Connection ~ 5550 3500
$Comp
L Mechanical:MountingHole H1
U 1 1 5DBBB08A
P 8050 2050
F 0 "H1" H 8150 2096 50  0000 L CNN
F 1 "MountingHole" H 8150 2005 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_ISO7380_Pad" H 8050 2050 50  0001 C CNN
F 3 "~" H 8050 2050 50  0001 C CNN
	1    8050 2050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5DBBB1E7
P 8050 2350
F 0 "H2" H 8150 2396 50  0000 L CNN
F 1 "MountingHole" H 8150 2305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_ISO7380_Pad" H 8050 2350 50  0001 C CNN
F 3 "~" H 8050 2350 50  0001 C CNN
	1    8050 2350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
