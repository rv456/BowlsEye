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
LIBS:adc122s101
LIBS:valves
EELAYER 25 0
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
L ADC122S101 U1
U 1 1 5A71E19B
P 5325 2525
F 0 "U1" H 5325 2675 60  0000 C CNN
F 1 "ADC122S101" H 5325 2225 60  0000 C CNN
F 2 "BowlsEye:MyVSSOP-8_3.0x3.0mm_Pitch0.65mm" H 5325 2375 60  0001 C CNN
F 3 "" H 5325 2375 60  0001 C CNN
	1    5325 2525
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 J1
U 1 1 5A71E24C
P 3225 2575
F 0 "J1" H 3225 3025 50  0000 C CNN
F 1 "CONN_01X08" V 3325 2575 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 3225 2575 50  0001 C CNN
F 3 "" H 3225 2575 50  0001 C CNN
	1    3225 2575
	-1   0    0    1   
$EndComp
Wire Wire Line
	4875 2375 4825 2375
Wire Wire Line
	4875 2475 4825 2475
Wire Wire Line
	4875 2575 4825 2575
Wire Wire Line
	4875 2675 4825 2675
Wire Wire Line
	5775 2375 5825 2375
Wire Wire Line
	5775 2475 5825 2475
Wire Wire Line
	5775 2575 5825 2575
Wire Wire Line
	5775 2675 5825 2675
Text GLabel 4825 2375 0    35   Input ~ 0
CS
Text GLabel 4825 2475 0    35   Input ~ 0
VA
Text GLabel 4825 2575 0    35   Input ~ 0
GND
Text GLabel 4825 2675 0    35   Input ~ 0
IN2
Text GLabel 5825 2375 2    35   Input ~ 0
SCLK
Text GLabel 5825 2475 2    35   Input ~ 0
DOUT
Text GLabel 5825 2575 2    35   Input ~ 0
DIN
Text GLabel 5825 2675 2    35   Input ~ 0
IN1
Text GLabel 3475 2225 2    35   Input ~ 0
CS
Wire Wire Line
	3425 2225 3475 2225
Wire Wire Line
	3425 2325 3475 2325
Wire Wire Line
	3425 2425 3475 2425
Wire Wire Line
	3425 2525 3475 2525
Wire Wire Line
	3425 2625 3475 2625
Wire Wire Line
	3425 2725 3475 2725
Wire Wire Line
	3425 2825 3475 2825
Wire Wire Line
	3425 2925 3475 2925
Text GLabel 3475 2325 2    35   Input ~ 0
VA
Text GLabel 3475 2425 2    35   Input ~ 0
GND
Text GLabel 3475 2525 2    35   Input ~ 0
IN2
Text GLabel 3475 2925 2    35   Input ~ 0
SCLK
Text GLabel 3475 2825 2    35   Input ~ 0
DOUT
Text GLabel 3475 2725 2    35   Input ~ 0
DIN
Text GLabel 3475 2625 2    35   Input ~ 0
IN1
$EndSCHEMATC
