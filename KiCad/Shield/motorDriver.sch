EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:adc122s101
LIBS:l298_th
LIBS:Proto1-cache
EELAYER 25 0
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
$Comp
L CONN_01X04 J2
U 1 1 5AA69EB0
P 8375 2900
F 0 "J2" H 8375 3150 50  0000 C CNN
F 1 "CONN_01X04" V 8475 2900 50  0000 C CNN
F 2 "Sockets_MOLEX_KK-System:Socket_MOLEX-KK-RM2-54mm_Lock_4pin_straight" H 8375 2900 50  0001 C CNN
F 3 "" H 8375 2900 50  0001 C CNN
	1    8375 2900
	1    0    0    -1  
$EndComp
Text GLabel 8075 2750 0    35   Input ~ 0
PHASE_A
Text GLabel 8075 2850 0    35   Input ~ 0
PHASE_A-
Text GLabel 8075 2950 0    35   Input ~ 0
PHASE_B
Text GLabel 8075 3050 0    35   Input ~ 0
PHASE_B-
$Comp
L L298_TH U2
U 1 1 5AA6A712
P 5250 3250
F 0 "U2" H 5250 3200 35  0000 C CNN
F 1 "L298_TH" H 5250 3300 35  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-15_Vertical_StaggeredType1" H 5250 3200 35  0001 C CNN
F 3 "" H 5250 3200 35  0001 C CNN
	1    5250 3250
	1    0    0    -1  
$EndComp
Text GLabel 5850 2700 2    35   Input ~ 0
PHASE_A
Text GLabel 5850 2800 2    35   Input ~ 0
PHASE_A-
Text GLabel 5850 2900 2    35   Input ~ 0
PHASE_B
Text GLabel 5850 3000 2    35   Input ~ 0
PHASE_B-
$Comp
L GNDD #PWR012
U 1 1 5AA6A83B
P 4650 3900
F 0 "#PWR012" H 4650 3650 50  0001 C CNN
F 1 "GNDD" H 4650 3775 50  0000 C CNN
F 2 "" H 4650 3900 50  0001 C CNN
F 3 "" H 4650 3900 50  0001 C CNN
	1    4650 3900
	1    0    0    -1  
$EndComp
Text GLabel 4650 3000 0    35   Input ~ 0
MOTOR_ENA
Text GLabel 4650 3100 0    35   Input ~ 0
MOTOR_ENB
Text GLabel 4650 3300 0    35   Input ~ 0
MOTOR_1_1
Text GLabel 4650 3400 0    35   Input ~ 0
MOTOR_1_2
Text GLabel 4650 3500 0    35   Input ~ 0
MOTOR_2_1
Text GLabel 4650 3600 0    35   Input ~ 0
MOTOR_2_2
$Comp
L C_Small C2
U 1 1 5AA6ACA6
P 1000 1075
F 0 "C2" H 1010 1145 50  0000 L CNN
F 1 "100nF" H 1010 995 50  0000 L CNN
F 2 "" H 1000 1075 50  0001 C CNN
F 3 "" H 1000 1075 50  0001 C CNN
	1    1000 1075
	-1   0    0    1   
$EndComp
$Comp
L GNDD #PWR013
U 1 1 5AA6AEAD
P 1000 1225
F 0 "#PWR013" H 1000 975 50  0001 C CNN
F 1 "GNDD" H 1000 1100 50  0000 C CNN
F 2 "" H 1000 1225 50  0001 C CNN
F 3 "" H 1000 1225 50  0001 C CNN
	1    1000 1225
	1    0    0    -1  
$EndComp
Text Notes 4175 2500 0    35   ~ 0
double check power requirements
Text GLabel 1000 775  0    35   Input ~ 0
+5V
Text GLabel 1100 875  2    35   Input ~ 0
MOTOR_VS
$Comp
L C_Small C3
U 1 1 5AA6B308
P 1675 1075
F 0 "C3" H 1685 1145 50  0000 L CNN
F 1 "100nF" H 1685 995 50  0000 L CNN
F 2 "" H 1675 1075 50  0001 C CNN
F 3 "" H 1675 1075 50  0001 C CNN
	1    1675 1075
	-1   0    0    1   
$EndComp
$Comp
L GNDD #PWR014
U 1 1 5AA6B30E
P 1675 1225
F 0 "#PWR014" H 1675 975 50  0001 C CNN
F 1 "GNDD" H 1675 1100 50  0000 C CNN
F 2 "" H 1675 1225 50  0001 C CNN
F 3 "" H 1675 1225 50  0001 C CNN
	1    1675 1225
	1    0    0    -1  
$EndComp
Text GLabel 1675 775  0    35   Input ~ 0
+5V
Text GLabel 1775 875  2    35   Input ~ 0
MOTOR_VSS
Text GLabel 4650 2700 0    35   Input ~ 0
MOTOR_VS
Text GLabel 4650 2800 0    35   Input ~ 0
MOTOR_VSS
Wire Wire Line
	8175 2750 8075 2750
Wire Wire Line
	8175 2850 8075 2850
Wire Wire Line
	8175 2950 8075 2950
Wire Wire Line
	8175 3050 8075 3050
Wire Wire Line
	5750 2700 5850 2700
Wire Wire Line
	5750 2800 5850 2800
Wire Wire Line
	5750 2900 5850 2900
Wire Wire Line
	5750 3000 5850 3000
Wire Wire Line
	4750 3800 4650 3800
Wire Wire Line
	4650 3800 4650 3900
Wire Wire Line
	4750 3000 4650 3000
Wire Wire Line
	4750 3100 4650 3100
Wire Wire Line
	4750 3300 4650 3300
Wire Wire Line
	4750 3400 4650 3400
Wire Wire Line
	4750 3500 4650 3500
Wire Wire Line
	4750 3600 4650 3600
Wire Wire Line
	1000 1175 1000 1225
Wire Wire Line
	1000 975  1000 775 
Wire Wire Line
	1000 875  1100 875 
Connection ~ 1000 875 
Wire Wire Line
	1675 1175 1675 1225
Wire Wire Line
	1675 975  1675 775 
Wire Wire Line
	1675 875  1775 875 
Connection ~ 1675 875 
Wire Wire Line
	4650 2700 4750 2700
Wire Wire Line
	4750 2800 4650 2800
Wire Wire Line
	5750 3500 5850 3500
Wire Wire Line
	5850 3500 5850 3700
Wire Wire Line
	5850 3600 5750 3600
Connection ~ 5850 3600
$Comp
L GNDD #PWR015
U 1 1 5AA879F1
P 5850 3700
F 0 "#PWR015" H 5850 3450 50  0001 C CNN
F 1 "GNDD" H 5850 3575 50  0000 C CNN
F 2 "" H 5850 3700 50  0001 C CNN
F 3 "" H 5850 3700 50  0001 C CNN
	1    5850 3700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
