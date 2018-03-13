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
Sheet 2 5
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
L GNDD #PWR?
U 1 1 5AA6A86D
P 1750 2200
F 0 "#PWR?" H 1750 1950 50  0001 C CNN
F 1 "GNDD" H 1750 2075 50  0000 C CNN
F 2 "" H 1750 2200 50  0001 C CNN
F 3 "" H 1750 2200 50  0001 C CNN
	1    1750 2200
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR?
U 1 1 5AA6A887
P 2150 2200
F 0 "#PWR?" H 2150 1950 50  0001 C CNN
F 1 "GNDREF" H 2150 2050 50  0000 C CNN
F 2 "" H 2150 2200 50  0001 C CNN
F 3 "" H 2150 2200 50  0001 C CNN
	1    2150 2200
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 5AA6A8AD
P 2550 2200
F 0 "#PWR?" H 2550 1950 50  0001 C CNN
F 1 "GNDA" H 2550 2050 50  0000 C CNN
F 2 "" H 2550 2200 50  0001 C CNN
F 3 "" H 2550 2200 50  0001 C CNN
	1    2550 2200
	1    0    0    -1  
$EndComp
$Comp
L L_Small L?
U 1 1 5AA6A8CC
P 1950 2150
F 0 "L?" H 1980 2190 50  0000 L CNN
F 1 "100nH" H 1980 2110 50  0000 L CNN
F 2 "" H 1950 2150 50  0001 C CNN
F 3 "" H 1950 2150 50  0001 C CNN
	1    1950 2150
	0    1    -1   0   
$EndComp
$Comp
L L_Small L?
U 1 1 5AA6A960
P 2350 2150
F 0 "L?" H 2380 2190 50  0000 L CNN
F 1 "100nH" H 2380 2110 50  0000 L CNN
F 2 "" H 2350 2150 50  0001 C CNN
F 3 "" H 2350 2150 50  0001 C CNN
	1    2350 2150
	0    1    -1   0   
$EndComp
Wire Wire Line
	2550 2200 2550 2150
Wire Wire Line
	2550 2150 2450 2150
Wire Wire Line
	2050 2150 2250 2150
Wire Wire Line
	2150 2150 2150 2200
Connection ~ 2150 2150
Wire Wire Line
	1850 2150 1750 2150
Wire Wire Line
	1750 2150 1750 2200
Text Notes 5125 3350 0    394  ~ 79
TBC
$EndSCHEMATC
