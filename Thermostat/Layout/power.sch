EESchema Schematic File Version 4
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
L dk_Diodes-Bridge-Rectifiers:MB6S D?
U 1 1 5ECDA9BE
P 4000 2400
F 0 "D?" H 4444 2453 60  0000 L CNN
F 1 "MB6S" H 4444 2347 60  0000 L CNN
F 2 "digikey-footprints:TO-269AA" H 4200 2600 60  0001 L CNN
F 3 "https://www.onsemi.com/pub/Collateral/MB8S-D.PDF" H 4200 2700 60  0001 L CNN
F 4 "MB6SCT-ND" H 4200 2800 60  0001 L CNN "Digi-Key_PN"
F 5 "MB6S" H 4200 2900 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 4200 3000 60  0001 L CNN "Category"
F 7 "Diodes - Bridge Rectifiers" H 4200 3100 60  0001 L CNN "Family"
F 8 "https://www.onsemi.com/pub/Collateral/MB8S-D.PDF" H 4200 3200 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/on-semiconductor/MB6S/MB6SCT-ND/965654" H 4200 3300 60  0001 L CNN "DK_Detail_Page"
F 10 "BRIDGE RECT 1P 600V 500MA 4SOIC" H 4200 3400 60  0001 L CNN "Description"
F 11 "ON Semiconductor" H 4200 3500 60  0001 L CNN "Manufacturer"
F 12 "Active" H 4200 3600 60  0001 L CNN "Status"
	1    4000 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5ED1B285
P 3250 2400
F 0 "#PWR?" H 3250 2150 50  0001 C CNN
F 1 "GND" H 3255 2227 50  0000 C CNN
F 2 "" H 3250 2400 50  0001 C CNN
F 3 "" H 3250 2400 50  0001 C CNN
	1    3250 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2400 3600 2400
$Comp
L Device:C C?
U 1 1 5ED1B81B
P 4900 2550
F 0 "C?" H 5015 2596 50  0000 L CNN
F 1 "C" H 5015 2505 50  0000 L CNN
F 2 "" H 4938 2400 50  0001 C CNN
F 3 "~" H 4900 2550 50  0001 C CNN
	1    4900 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5ED1C2D0
P 5300 2550
F 0 "C?" H 5415 2596 50  0000 L CNN
F 1 "C" H 5415 2505 50  0000 L CNN
F 2 "" H 5338 2400 50  0001 C CNN
F 3 "~" H 5300 2550 50  0001 C CNN
	1    5300 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5ED1C615
P 5700 2550
F 0 "C?" H 5815 2596 50  0000 L CNN
F 1 "C" H 5815 2505 50  0000 L CNN
F 2 "" H 5738 2400 50  0001 C CNN
F 3 "~" H 5700 2550 50  0001 C CNN
	1    5700 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5ED1C979
P 6100 2550
F 0 "C?" H 6215 2596 50  0000 L CNN
F 1 "C" H 6215 2505 50  0000 L CNN
F 2 "" H 6138 2400 50  0001 C CNN
F 3 "~" H 6100 2550 50  0001 C CNN
	1    6100 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2400 5300 2400
Wire Wire Line
	5300 2400 5700 2400
Connection ~ 5300 2400
Wire Wire Line
	5700 2400 6100 2400
Connection ~ 5700 2400
Wire Wire Line
	4900 2700 5300 2700
Wire Wire Line
	5300 2700 5700 2700
Connection ~ 5300 2700
Wire Wire Line
	5700 2700 6100 2700
Connection ~ 5700 2700
Wire Wire Line
	4400 2400 4900 2400
Connection ~ 4900 2400
$Comp
L power:GND #PWR?
U 1 1 5ED1E9C2
P 4900 2800
F 0 "#PWR?" H 4900 2550 50  0001 C CNN
F 1 "GND" H 4905 2627 50  0000 C CNN
F 2 "" H 4900 2800 50  0001 C CNN
F 3 "" H 4900 2800 50  0001 C CNN
	1    4900 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2800 4900 2700
Connection ~ 4900 2700
$EndSCHEMATC
