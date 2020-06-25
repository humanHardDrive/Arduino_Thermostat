EESchema Schematic File Version 4
LIBS:RemoteSensor-cache
EELAYER 29 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 5
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
L Mechanical:MountingHole_Pad H2
U 1 1 5ED8175C
P 7150 4100
F 0 "H2" H 7250 4149 50  0000 L CNN
F 1 "MountingHole_Pad" H 7250 4058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5_DIN965_Pad" H 7150 4100 50  0001 C CNN
F 3 "~" H 7150 4100 50  0001 C CNN
	1    7150 4100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5ED820A4
P 7150 3750
F 0 "H1" H 7250 3799 50  0000 L CNN
F 1 "MountingHole_Pad" H 7250 3708 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5_DIN965_Pad" H 7150 3750 50  0001 C CNN
F 3 "~" H 7150 3750 50  0001 C CNN
	1    7150 3750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5ED83464
P 8200 3750
F 0 "H3" H 8300 3799 50  0000 L CNN
F 1 "MountingHole_Pad" H 8300 3708 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5_DIN965_Pad" H 8200 3750 50  0001 C CNN
F 3 "~" H 8200 3750 50  0001 C CNN
	1    8200 3750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5ED84C2B
P 8200 4100
F 0 "H4" H 8300 4149 50  0000 L CNN
F 1 "MountingHole_Pad" H 8300 4058 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5_DIN965_Pad" H 8200 4100 50  0001 C CNN
F 3 "~" H 8200 4100 50  0001 C CNN
	1    8200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3850 7700 3850
Wire Wire Line
	7150 4200 7700 4200
$Comp
L SparkFun-PowerSymbols:GND #GND0118
U 1 1 5ED93B1B
P 7700 3850
F 0 "#GND0118" H 7750 3800 45  0001 L BNN
F 1 "GND" H 7700 3680 45  0000 C CNN
F 2 "" H 7700 3750 60  0001 C CNN
F 3 "" H 7700 3750 60  0001 C CNN
	1    7700 3850
	1    0    0    -1  
$EndComp
Connection ~ 7700 3850
Wire Wire Line
	7700 3850 8200 3850
$Comp
L SparkFun-PowerSymbols:GND #GND0119
U 1 1 5ED940BC
P 7700 4200
F 0 "#GND0119" H 7750 4150 45  0001 L BNN
F 1 "GND" H 7700 4030 45  0000 C CNN
F 2 "" H 7700 4100 60  0001 C CNN
F 3 "" H 7700 4100 60  0001 C CNN
	1    7700 4200
	1    0    0    -1  
$EndComp
Connection ~ 7700 4200
Wire Wire Line
	7700 4200 8200 4200
$Sheet
S 3950 1500 2100 1950
U 5EE9FD3C
F0 "Power" 50
F1 "Power.sch" 50
$EndSheet
$Sheet
S 1400 4000 2100 1950
U 5EF41F85
F0 "Reset" 50
F1 "Reset.sch" 50
$EndSheet
$Sheet
S 1400 1500 2100 1950
U 5EF5F91F
F0 "Processor" 50
F1 "Processor.sch" 50
$EndSheet
$Sheet
S 3950 4000 2100 1950
U 5EF070B6
F0 "USB" 50
F1 "USB.sch" 50
$EndSheet
$EndSCHEMATC
