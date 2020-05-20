EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Schema Global Respirateur"
Date "2020-05-02"
Rev "V0.1"
Comp "OMYXair"
Comment1 "2 Capteurs Analogiques + 2 Servos"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Respi:Teensy_Teensy3.2 U1
U 1 1 5EAD2CA1
P 5800 3950
F 0 "U1" H 5800 5587 60  0000 C CNN
F 1 "Teensy3.2" H 5800 5481 60  0000 C CNN
F 2 "Teensy:Teensy30_31_32_LC" H 5800 3200 60  0001 C CNN
F 3 "" H 5800 3200 60  0001 C CNN
	1    5800 3950
	1    0    0    -1  
$EndComp
$Comp
L XG_Lib:MPXV50xxDP U_P1
U 1 1 5EAD9925
P 1725 2950
F 0 "U_P1" H 1295 2996 50  0000 R CNN
F 1 "MPXV50xxDP" H 1295 2905 50  0000 R CNN
F 2 "XG_PCB_Lib:MPXV_SOP" H 1225 2600 50  0001 C CNN
F 3 "http://www.nxp.com/files/sensors/doc/data_sheet/MPXA6115A.pdf" H 1725 3550 50  0001 C CNN
	1    1725 2950
	1    0    0    -1  
$EndComp
$Comp
L XG_Lib:MPXV50xxDP U_V1
U 1 1 5EADB474
P 1725 4200
F 0 "U_V1" H 1295 4246 50  0000 R CNN
F 1 "MPXV50xxDP" H 1295 4155 50  0000 R CNN
F 2 "XG_PCB_Lib:MPXV_SOP" H 1225 3850 50  0001 C CNN
F 3 "http://www.nxp.com/files/sensors/doc/data_sheet/MPXA6115A.pdf" H 1725 4800 50  0001 C CNN
	1    1725 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV2
U 1 1 5EADC69A
P 5500 1125
F 0 "RV2" H 5431 1171 50  0000 R CNN
F 1 "10k" H 5431 1080 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5500 1125 50  0001 C CNN
F 3 "~" H 5500 1125 50  0001 C CNN
	1    5500 1125
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x04 SW1
U 1 1 5EADEA8E
P 1725 1300
F 0 "SW1" V 1725 1630 50  0000 L CNN
F 1 "SW_DIP_x04" V 1770 1630 50  0001 L CNN
F 2 "Button_Switch_THT:SW_DIP_SPSTx04_Slide_6.7x11.72mm_W7.62mm_P2.54mm_LowProfile" H 1725 1300 50  0001 C CNN
F 3 "~" H 1725 1300 50  0001 C CNN
	1    1725 1300
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J_12+1
U 1 1 5EAE19E9
P 9000 1000
F 0 "J_12+1" H 8918 867 50  0000 C CNN
F 1 "Conn_01x01" H 8918 866 50  0001 C CNN
F 2 "" H 9000 1000 50  0001 C CNN
F 3 "~" H 9000 1000 50  0001 C CNN
	1    9000 1000
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J_12-1
U 1 1 5EAE29A9
P 9000 1350
F 0 "J_12-1" H 8918 1217 50  0000 C CNN
F 1 "Conn_01x01" H 8918 1216 50  0001 C CNN
F 2 "" H 9000 1350 50  0001 C CNN
F 3 "~" H 9000 1350 50  0001 C CNN
	1    9000 1350
	-1   0    0    1   
$EndComp
$Comp
L Motor:Motor_DC Turbine1
U 1 1 5EAE3803
P 10050 1125
F 0 "Turbine1" H 10208 1075 50  0000 L CNN
F 1 "Motor_DC" H 10208 1030 50  0001 L CNN
F 2 "" H 10050 1035 50  0001 C CNN
F 3 "~" H 10050 1035 50  0001 C CNN
	1    10050 1125
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small Cv2
U 1 1 5EAE506D
P 2175 7400
F 0 "Cv2" H 2267 7446 50  0000 L CNN
F 1 "10nF" H 2267 7355 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L9.0mm_W2.7mm_P7.50mm_MKT" H 2175 7400 50  0001 C CNN
F 3 "~" H 2175 7400 50  0001 C CNN
	1    2175 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 900  10050 925 
Wire Wire Line
	10050 1425 10050 1500
Wire Wire Line
	10050 1500 9325 1500
Wire Wire Line
	9325 1500 9325 1350
Wire Wire Line
	9325 1350 9200 1350
Wire Wire Line
	9325 900  9325 1000
Wire Wire Line
	9325 1000 9200 1000
Wire Wire Line
	9325 900  10050 900 
Wire Notes Line
	8250 600  8250 2050
Text Notes 9000 1800 0    50   ~ 0
Turbine alimentation 12 V DC Nouvelle Turbine\nTurbine Decathlon 5V - 6A
$Comp
L power:GNDPWR #PWR0101
U 1 1 5EAEA24A
P 1725 3325
F 0 "#PWR0101" H 1725 3125 50  0001 C CNN
F 1 "GNDPWR" H 1729 3171 50  0001 C CNN
F 2 "" H 1725 3275 50  0001 C CNN
F 3 "" H 1725 3275 50  0001 C CNN
	1    1725 3325
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0102
U 1 1 5EAEAED7
P 1725 4600
F 0 "#PWR0102" H 1725 4400 50  0001 C CNN
F 1 "GNDPWR" H 1729 4446 50  0001 C CNN
F 2 "" H 1725 4550 50  0001 C CNN
F 3 "" H 1725 4550 50  0001 C CNN
	1    1725 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0103
U 1 1 5EAEC039
P 5500 1350
F 0 "#PWR0103" H 5500 1150 50  0001 C CNN
F 1 "GNDPWR" H 5504 1196 50  0001 C CNN
F 2 "" H 5500 1300 50  0001 C CNN
F 3 "" H 5500 1300 50  0001 C CNN
	1    5500 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0104
U 1 1 5EAF3626
P 6925 5000
F 0 "#PWR0104" H 6925 4800 50  0001 C CNN
F 1 "GNDPWR" V 6930 4892 50  0001 R CNN
F 2 "" H 6925 4950 50  0001 C CNN
F 3 "" H 6925 4950 50  0001 C CNN
	1    6925 5000
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0105
U 1 1 5EAF3A50
P 4675 4100
F 0 "#PWR0105" H 4675 3950 50  0001 C CNN
F 1 "+3.3V" V 4690 4228 50  0000 L CNN
F 2 "" H 4675 4100 50  0001 C CNN
F 3 "" H 4675 4100 50  0001 C CNN
	1    4675 4100
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0107
U 1 1 5EAF61A6
P 5500 875
F 0 "#PWR0107" H 5500 725 50  0001 C CNN
F 1 "+3.3V" H 5515 1048 50  0000 C CNN
F 2 "" H 5500 875 50  0001 C CNN
F 3 "" H 5500 875 50  0001 C CNN
	1    5500 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 875  5500 975 
Wire Wire Line
	5500 1275 5500 1350
Wire Wire Line
	5650 1125 5975 1125
Text Label 5775 1125 0    50   ~ 0
A1_IE
Text Notes 5600 1300 0    50   ~ 0
 Consigne \nRapport I/Cycle
$Comp
L Device:R_POT RV3
U 1 1 5EB009C6
P 6550 1125
F 0 "RV3" H 6481 1171 50  0000 R CNN
F 1 "10k" H 6481 1080 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6550 1125 50  0001 C CNN
F 3 "~" H 6550 1125 50  0001 C CNN
	1    6550 1125
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0108
U 1 1 5EB009D0
P 6550 1350
F 0 "#PWR0108" H 6550 1150 50  0001 C CNN
F 1 "GNDPWR" H 6554 1196 50  0001 C CNN
F 2 "" H 6550 1300 50  0001 C CNN
F 3 "" H 6550 1300 50  0001 C CNN
	1    6550 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 5EB009DA
P 6550 875
F 0 "#PWR0109" H 6550 725 50  0001 C CNN
F 1 "+3.3V" H 6565 1048 50  0000 C CNN
F 2 "" H 6550 875 50  0001 C CNN
F 3 "" H 6550 875 50  0001 C CNN
	1    6550 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 875  6550 975 
Wire Wire Line
	6550 1275 6550 1350
Wire Wire Line
	6700 1125 7025 1125
Text Label 6750 1125 0    50   ~ 0
A2_Pinsp
Text Notes 6650 1300 0    50   ~ 0
   Consigne \nPression Inspi
$Comp
L Device:R_POT RV4
U 1 1 5EB02747
P 7525 1125
F 0 "RV4" H 7456 1171 50  0000 R CNN
F 1 "10k" H 7456 1080 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7525 1125 50  0001 C CNN
F 3 "~" H 7525 1125 50  0001 C CNN
	1    7525 1125
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0110
U 1 1 5EB02751
P 7525 1350
F 0 "#PWR0110" H 7525 1150 50  0001 C CNN
F 1 "GNDPWR" H 7529 1196 50  0001 C CNN
F 2 "" H 7525 1300 50  0001 C CNN
F 3 "" H 7525 1300 50  0001 C CNN
	1    7525 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0111
U 1 1 5EB0275B
P 7525 875
F 0 "#PWR0111" H 7525 725 50  0001 C CNN
F 1 "+3.3V" H 7540 1048 50  0000 C CNN
F 2 "" H 7525 875 50  0001 C CNN
F 3 "" H 7525 875 50  0001 C CNN
	1    7525 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7525 875  7525 975 
Wire Wire Line
	7525 1275 7525 1350
Wire Wire Line
	7675 1125 8000 1125
Text Label 7725 1125 0    50   ~ 0
A3_PExp
Text Notes 7625 1300 0    50   ~ 0
  Consigne \nPression Expi
$Comp
L Device:R_POT RV1
U 1 1 5EB04354
P 4475 1125
F 0 "RV1" H 4406 1171 50  0000 R CNN
F 1 "10k" H 4406 1080 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4475 1125 50  0001 C CNN
F 3 "~" H 4475 1125 50  0001 C CNN
	1    4475 1125
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0112
U 1 1 5EB0435E
P 4475 1350
F 0 "#PWR0112" H 4475 1150 50  0001 C CNN
F 1 "GNDPWR" H 4479 1196 50  0001 C CNN
F 2 "" H 4475 1300 50  0001 C CNN
F 3 "" H 4475 1300 50  0001 C CNN
	1    4475 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0113
U 1 1 5EB04368
P 4475 875
F 0 "#PWR0113" H 4475 725 50  0001 C CNN
F 1 "+3.3V" H 4490 1048 50  0000 C CNN
F 2 "" H 4475 875 50  0001 C CNN
F 3 "" H 4475 875 50  0001 C CNN
	1    4475 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4475 875  4475 975 
Wire Wire Line
	4475 1275 4475 1350
Wire Wire Line
	4625 1125 4950 1125
Text Label 4750 1125 0    50   ~ 0
A0_Cy
Text Notes 4575 1300 0    50   ~ 0
   Consigne\nCycles  msec 
Wire Notes Line
	4050 2050 4050 600 
Wire Notes Line
	4050 2050 11150 2050
Text Notes 5525 1800 0    50   ~ 0
Gestion locale des consignes
Wire Wire Line
	4800 4600 4400 4600
Wire Wire Line
	4800 4700 4400 4700
Wire Wire Line
	4800 4800 4400 4800
Wire Wire Line
	4800 4900 4400 4900
Text Label 4475 4600 0    50   ~ 0
A0_Cy
Text Label 4475 4700 0    50   ~ 0
A1_IE
Text Label 4450 4800 0    50   ~ 0
A2_Pinsp
Text Label 4450 4900 0    50   ~ 0
A3_PExp
Wire Wire Line
	1725 2650 1725 2550
Wire Wire Line
	1725 3900 1725 3800
Text Notes 775  3425 0    50   ~ 0
Mesure de Pression\n      Patient
Text Notes 700  4775 0    50   ~ 0
Mesure Débit Volume\n    à l'Expiration \n        Venturi
Text Label 2550 3075 0    50   ~ 0
A7_Pression
Text Label 2575 4350 0    50   ~ 0
A6_Venturi
Wire Wire Line
	4800 5200 4400 5200
Wire Wire Line
	4800 5300 4400 5300
Text Label 4400 5200 0    50   ~ 0
A6_Venturi
Text Label 4400 5300 0    50   ~ 0
A7_Pression
Wire Wire Line
	6800 5000 6925 5000
Wire Wire Line
	4800 4100 4675 4100
$Comp
L power:GNDPWR #PWR0114
U 1 1 5EB23DF1
P 2175 7550
F 0 "#PWR0114" H 2175 7350 50  0001 C CNN
F 1 "GNDPWR" H 2179 7396 50  0001 C CNN
F 2 "" H 2175 7500 50  0001 C CNN
F 3 "" H 2175 7500 50  0001 C CNN
	1    2175 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2175 7250 2175 7300
Wire Wire Line
	2175 7500 2175 7550
$Comp
L Device:C_Small Cp2
U 1 1 5EB28CE3
P 1200 7400
F 0 "Cp2" H 1292 7446 50  0000 L CNN
F 1 "10nF" H 1292 7355 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L9.0mm_W2.7mm_P7.50mm_MKT" H 1200 7400 50  0001 C CNN
F 3 "~" H 1200 7400 50  0001 C CNN
	1    1200 7400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0115
U 1 1 5EB28D01
P 1200 7550
F 0 "#PWR0115" H 1200 7350 50  0001 C CNN
F 1 "GNDPWR" H 1204 7396 50  0001 C CNN
F 2 "" H 1200 7500 50  0001 C CNN
F 3 "" H 1200 7500 50  0001 C CNN
	1    1200 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 7250 1200 7300
Wire Wire Line
	1200 7500 1200 7550
Wire Notes Line
	650  6775 6875 6775
Text Notes 2600 6750 0    50   ~ 0
Decouplage Alimentation
$Comp
L Motor:Motor_Servo_Futaba_J M_IN1
U 1 1 5EB3B4D0
P 9950 2900
F 0 "M_IN1" H 10282 2919 50  0000 L CNN
F 1 "Motor_Servo_Futaba_J" H 10282 2874 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9950 2710 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 9950 2710 50  0001 C CNN
	1    9950 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0116
U 1 1 5EB3D356
P 9600 3050
F 0 "#PWR0116" H 9600 2850 50  0001 C CNN
F 1 "GNDPWR" H 9604 2896 50  0001 C CNN
F 2 "" H 9600 3000 50  0001 C CNN
F 3 "" H 9600 3000 50  0001 C CNN
	1    9600 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 3000 9600 3000
Wire Wire Line
	9600 3000 9600 3050
Text Label 9075 2800 0    50   ~ 0
Servo_Valve_In
Wire Wire Line
	9050 2800 9650 2800
$Comp
L Motor:Motor_Servo_Futaba_J M_OUT1
U 1 1 5EB4A24B
P 9950 3525
F 0 "M_OUT1" H 10282 3544 50  0000 L CNN
F 1 "Motor_Servo_Futaba_J" H 10282 3499 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9950 3335 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 9950 3335 50  0001 C CNN
	1    9950 3525
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0117
U 1 1 5EB4A255
P 9600 3675
F 0 "#PWR0117" H 9600 3475 50  0001 C CNN
F 1 "GNDPWR" H 9604 3521 50  0001 C CNN
F 2 "" H 9600 3625 50  0001 C CNN
F 3 "" H 9600 3625 50  0001 C CNN
	1    9600 3675
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 3625 9600 3625
Wire Wire Line
	9600 3625 9600 3675
Text Label 9075 3425 0    50   ~ 0
Servo_Valve_Out
Wire Wire Line
	9050 3425 9650 3425
Text Label 4225 2900 0    50   ~ 0
Servo_Valve_In
Wire Wire Line
	4200 2900 4800 2900
Text Label 4225 3000 0    50   ~ 0
Servo_Valve_Out
Wire Wire Line
	4200 3000 4800 3000
$Comp
L Device:CP_Small Ci1
U 1 1 5EB542ED
P 2675 7425
F 0 "Ci1" H 2763 7471 50  0000 L CNN
F 1 "470uF" H 2763 7380 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D7.5mm_P2.50mm" H 2675 7425 50  0001 C CNN
F 3 "~" H 2675 7425 50  0001 C CNN
	1    2675 7425
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0118
U 1 1 5EB5431F
P 2675 7575
F 0 "#PWR0118" H 2675 7375 50  0001 C CNN
F 1 "GNDPWR" H 2679 7421 50  0001 C CNN
F 2 "" H 2675 7525 50  0001 C CNN
F 3 "" H 2675 7525 50  0001 C CNN
	1    2675 7575
	1    0    0    -1  
$EndComp
Wire Wire Line
	2675 7575 2675 7525
$Comp
L Device:CP_Small Co1
U 1 1 5EB57FC2
P 3550 7425
F 0 "Co1" H 3638 7471 50  0000 L CNN
F 1 "470uF" H 3638 7380 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D7.5mm_P2.50mm" H 3550 7425 50  0001 C CNN
F 3 "~" H 3550 7425 50  0001 C CNN
	1    3550 7425
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0119
U 1 1 5EB57FF4
P 3550 7575
F 0 "#PWR0119" H 3550 7375 50  0001 C CNN
F 1 "GNDPWR" H 3554 7421 50  0001 C CNN
F 2 "" H 3550 7525 50  0001 C CNN
F 3 "" H 3550 7525 50  0001 C CNN
	1    3550 7575
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 7575 3550 7525
Wire Wire Line
	3550 7250 3550 7325
Wire Wire Line
	2675 7250 2675 7325
$Comp
L power:+3.3V #PWR0120
U 1 1 5EB6541C
P 6925 5100
F 0 "#PWR0120" H 6925 4950 50  0001 C CNN
F 1 "+3.3V" V 6940 5228 50  0000 L CNN
F 2 "" H 6925 5100 50  0001 C CNN
F 3 "" H 6925 5100 50  0001 C CNN
	1    6925 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 5100 6925 5100
$Comp
L Connector_Generic:Conn_01x01 JS_5+1
U 1 1 5EB67EFA
P 9600 4350
F 0 "JS_5+1" H 9518 4217 50  0000 C CNN
F 1 "Conn_01x01" H 9518 4216 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 9600 4350 50  0001 C CNN
F 3 "~" H 9600 4350 50  0001 C CNN
	1    9600 4350
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 JS_5-1
U 1 1 5EB69787
P 9600 4700
F 0 "JS_5-1" H 9518 4567 50  0000 C CNN
F 1 "Conn_01x01" H 9518 4566 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 9600 4700 50  0001 C CNN
F 3 "~" H 9600 4700 50  0001 C CNN
	1    9600 4700
	-1   0    0    1   
$EndComp
$Comp
L power:GNDPWR #PWR0121
U 1 1 5EB6CB8F
P 9875 4775
F 0 "#PWR0121" H 9875 4575 50  0001 C CNN
F 1 "GNDPWR" H 9879 4621 50  0001 C CNN
F 2 "" H 9875 4725 50  0001 C CNN
F 3 "" H 9875 4725 50  0001 C CNN
	1    9875 4775
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 4700 9875 4700
Wire Wire Line
	9875 4700 9875 4775
Wire Wire Line
	9800 4350 10125 4350
Wire Notes Line
	9325 5200 11000 5200
Text Notes 10475 4700 0    50   ~ 0
Alimentation\nServo Moteur\n    5V DC
Wire Notes Line
	1575 7725 1575 6825
Wire Notes Line
	2525 7725 2525 6825
Wire Notes Line
	3425 7700 3425 6800
Text Notes 750  6925 0    50   ~ 0
Capteur Pression
Text Notes 1775 6925 0    50   ~ 0
Capteur Venturi
Text Notes 2800 6925 0    50   ~ 0
Servo In
Text Notes 3550 6925 0    50   ~ 0
Servo Out
Wire Notes Line
	4325 7700 4325 6800
$Comp
L power:GNDPWR #PWR0122
U 1 1 5EB96442
P 1775 1675
F 0 "#PWR0122" H 1775 1475 50  0001 C CNN
F 1 "GNDPWR" H 1779 1521 50  0001 C CNN
F 2 "" H 1775 1625 50  0001 C CNN
F 3 "" H 1775 1625 50  0001 C CNN
	1    1775 1675
	1    0    0    -1  
$EndComp
Wire Wire Line
	1625 1600 1625 1650
Wire Wire Line
	1625 1650 1725 1650
Wire Wire Line
	1925 1650 1925 1600
Wire Wire Line
	1725 1600 1725 1650
Connection ~ 1725 1650
Wire Wire Line
	1725 1650 1775 1650
Wire Wire Line
	1825 1600 1825 1650
Connection ~ 1825 1650
Wire Wire Line
	1825 1650 1925 1650
Wire Wire Line
	1775 1675 1775 1650
Connection ~ 1775 1650
Wire Wire Line
	1775 1650 1825 1650
Wire Wire Line
	1625 1000 1625 625 
Wire Wire Line
	1725 1000 1725 625 
Text Label 1625 950  1    50   ~ 0
Maint_7
Text Label 1725 950  1    50   ~ 0
Calib_8
Wire Wire Line
	4425 3400 4800 3400
Wire Wire Line
	4425 3500 4800 3500
Text Label 4475 3400 0    50   ~ 0
Maint_7
Text Label 4475 3500 0    50   ~ 0
Calib_8
$Comp
L power:+5V #PWR0123
U 1 1 5EBC8B27
P 1725 3800
F 0 "#PWR0123" H 1725 3650 50  0001 C CNN
F 1 "+5V" H 1740 3973 50  0000 C CNN
F 2 "" H 1725 3800 50  0001 C CNN
F 3 "" H 1725 3800 50  0001 C CNN
	1    1725 3800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0124
U 1 1 5EBC9916
P 1725 2550
F 0 "#PWR0124" H 1725 2400 50  0001 C CNN
F 1 "+5V" H 1740 2723 50  0000 C CNN
F 2 "" H 1725 2550 50  0001 C CNN
F 3 "" H 1725 2550 50  0001 C CNN
	1    1725 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0125
U 1 1 5EBCBF36
P 1200 7250
F 0 "#PWR0125" H 1200 7100 50  0001 C CNN
F 1 "+5V" H 1215 7423 50  0000 C CNN
F 2 "" H 1200 7250 50  0001 C CNN
F 3 "" H 1200 7250 50  0001 C CNN
	1    1200 7250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0126
U 1 1 5EBD148F
P 2175 7250
F 0 "#PWR0126" H 2175 7100 50  0001 C CNN
F 1 "+5V" H 2190 7423 50  0000 C CNN
F 2 "" H 2175 7250 50  0001 C CNN
F 3 "" H 2175 7250 50  0001 C CNN
	1    2175 7250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 JC_5+1
U 1 1 5EBD569F
P 9600 5550
F 0 "JC_5+1" H 9518 5417 50  0000 C CNN
F 1 "Conn_01x01" H 9518 5416 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 9600 5550 50  0001 C CNN
F 3 "~" H 9600 5550 50  0001 C CNN
	1    9600 5550
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 JC_5-1
U 1 1 5EBD56A5
P 9600 5900
F 0 "JC_5-1" H 9518 5767 50  0000 C CNN
F 1 "Conn_01x01" H 9518 5766 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 9600 5900 50  0001 C CNN
F 3 "~" H 9600 5900 50  0001 C CNN
	1    9600 5900
	-1   0    0    1   
$EndComp
$Comp
L power:GNDPWR #PWR0127
U 1 1 5EBD56AB
P 9875 5975
F 0 "#PWR0127" H 9875 5775 50  0001 C CNN
F 1 "GNDPWR" H 9879 5821 50  0001 C CNN
F 2 "" H 9875 5925 50  0001 C CNN
F 3 "" H 9875 5925 50  0001 C CNN
	1    9875 5975
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 5900 9875 5900
Wire Wire Line
	9875 5900 9875 5975
$Comp
L power:+5V #PWR0128
U 1 1 5EBD56B3
P 10125 5475
F 0 "#PWR0128" H 10125 5325 50  0001 C CNN
F 1 "+5V" H 10140 5648 50  0000 C CNN
F 2 "" H 10125 5475 50  0001 C CNN
F 3 "" H 10125 5475 50  0001 C CNN
	1    10125 5475
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 5550 10125 5550
Wire Wire Line
	10125 5550 10125 5475
Wire Notes Line
	9325 6400 11000 6400
Text Notes 10475 5900 0    50   ~ 0
  Alimentation\n Capteur 5V DC\nArduino - Teensy
Wire Notes Line
	9325 4000 9325 6400
$Comp
L power:VCC #PWR0129
U 1 1 5EBD9E2A
P 10125 4225
F 0 "#PWR0129" H 10125 4075 50  0001 C CNN
F 1 "VCC" H 10142 4398 50  0000 C CNN
F 2 "" H 10125 4225 50  0001 C CNN
F 3 "" H 10125 4225 50  0001 C CNN
	1    10125 4225
	1    0    0    -1  
$EndComp
Wire Wire Line
	10125 4225 10125 4300
$Comp
L power:VCC #PWR0130
U 1 1 5EBDE926
P 2675 7250
F 0 "#PWR0130" H 2675 7100 50  0001 C CNN
F 1 "VCC" H 2692 7423 50  0000 C CNN
F 2 "" H 2675 7250 50  0001 C CNN
F 3 "" H 2675 7250 50  0001 C CNN
	1    2675 7250
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0131
U 1 1 5EBE4041
P 3550 7250
F 0 "#PWR0131" H 3550 7100 50  0001 C CNN
F 1 "VCC" H 3567 7423 50  0000 C CNN
F 2 "" H 3550 7250 50  0001 C CNN
F 3 "" H 3550 7250 50  0001 C CNN
	1    3550 7250
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0132
U 1 1 5EBE9A97
P 9500 3525
F 0 "#PWR0132" H 9500 3375 50  0001 C CNN
F 1 "VCC" H 9517 3698 50  0000 C CNN
F 2 "" H 9500 3525 50  0001 C CNN
F 3 "" H 9500 3525 50  0001 C CNN
	1    9500 3525
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR0133
U 1 1 5EBEC765
P 9500 2900
F 0 "#PWR0133" H 9500 2750 50  0001 C CNN
F 1 "VCC" H 9517 3073 50  0000 C CNN
F 2 "" H 9500 2900 50  0001 C CNN
F 3 "" H 9500 2900 50  0001 C CNN
	1    9500 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9500 2900 9650 2900
Wire Wire Line
	9500 3525 9650 3525
$Comp
L Device:Buzzer BZ1
U 1 1 5EAE4647
P 3625 3500
F 0 "BZ1" H 3850 3500 50  0000 C CNN
F 1 "Buzzer" H 3875 3425 50  0000 C CNN
F 2 "Buzzer_Beeper:Buzzer_TDK_PS1240P02BT_D12.2mm_H6.5mm" V 3600 3600 50  0001 C CNN
F 3 "~" V 3600 3600 50  0001 C CNN
	1    3625 3500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4800 3300 4225 3300
$Comp
L power:GNDPWR #PWR0134
U 1 1 5EAEC2D3
P 3800 4200
F 0 "#PWR0134" H 3800 4000 50  0001 C CNN
F 1 "GNDPWR" H 3804 4046 50  0001 C CNN
F 2 "" H 3800 4150 50  0001 C CNN
F 3 "" H 3800 4150 50  0001 C CNN
	1    3800 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5EAF0A3E
P 4550 3200
F 0 "R1" V 4475 3200 50  0000 C CNN
F 1 "330" V 4550 3200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 4480 3200 50  0001 C CNN
F 3 "~" H 4550 3200 50  0001 C CNN
	1    4550 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 3200 4800 3200
$Comp
L Device:LED D1
U 1 1 5EAF4736
P 3875 3200
F 0 "D1" H 3868 3325 50  0000 C CNN
F 1 "LED" H 3868 3325 50  0001 C CNN
F 2 "LED_THT:LED_D3.0mm" H 3875 3200 50  0001 C CNN
F 3 "~" H 3875 3200 50  0001 C CNN
	1    3875 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4025 3200 4400 3200
$Comp
L power:GNDPWR #PWR0135
U 1 1 5EAFC6E3
P 3650 3200
F 0 "#PWR0135" H 3650 3000 50  0001 C CNN
F 1 "GNDPWR" H 3654 3046 50  0001 C CNN
F 2 "" H 3650 3150 50  0001 C CNN
F 3 "" H 3650 3150 50  0001 C CNN
	1    3650 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 3200 3725 3200
Wire Wire Line
	1725 3250 1725 3325
Wire Wire Line
	1725 4500 1725 4600
$Comp
L Device:R_POT_Small R_P1
U 1 1 5EB07ECB
P 2300 2950
F 0 "R_P1" V 2103 2950 50  0000 C CNN
F 1 "1k" V 2194 2950 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266W_Vertical" H 2300 2950 50  0001 C CNN
F 3 "~" H 2300 2950 50  0001 C CNN
	1    2300 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	2125 2950 2200 2950
Wire Wire Line
	2300 3075 2300 3050
Wire Wire Line
	2300 3075 2425 3075
$Comp
L Device:CP_Small C_P1
U 1 1 5EB0FCDA
P 2425 3225
F 0 "C_P1" H 2513 3271 50  0000 L CNN
F 1 "100uF" H 2513 3180 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 2425 3225 50  0001 C CNN
F 3 "~" H 2425 3225 50  0001 C CNN
	1    2425 3225
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0136
U 1 1 5EB1036C
P 2425 3375
F 0 "#PWR0136" H 2425 3175 50  0001 C CNN
F 1 "GNDPWR" H 2429 3221 50  0001 C CNN
F 2 "" H 2425 3325 50  0001 C CNN
F 3 "" H 2425 3325 50  0001 C CNN
	1    2425 3375
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 3375 2425 3325
Wire Wire Line
	2425 3125 2425 3075
Connection ~ 2425 3075
Wire Wire Line
	2425 3075 2475 3075
$Comp
L Device:R_POT_Small R_V1
U 1 1 5EB19018
P 2300 4200
F 0 "R_V1" V 2103 4200 50  0000 C CNN
F 1 "1,7k" V 2194 4200 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266W_Vertical" H 2300 4200 50  0001 C CNN
F 3 "~" H 2300 4200 50  0001 C CNN
	1    2300 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 4200 2125 4200
Wire Wire Line
	2300 4350 2300 4300
Wire Wire Line
	2300 4350 2425 4350
$Comp
L Device:CP_Small C_V1
U 1 1 5EB2171F
P 2425 4500
F 0 "C_V1" H 2513 4546 50  0000 L CNN
F 1 "10uF" H 2513 4455 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 2425 4500 50  0001 C CNN
F 3 "~" H 2425 4500 50  0001 C CNN
	1    2425 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0137
U 1 1 5EB22523
P 2425 4650
F 0 "#PWR0137" H 2425 4450 50  0001 C CNN
F 1 "GNDPWR" H 2429 4496 50  0001 C CNN
F 2 "" H 2425 4600 50  0001 C CNN
F 3 "" H 2425 4600 50  0001 C CNN
	1    2425 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 4400 2425 4350
Connection ~ 2425 4350
Wire Wire Line
	2425 4350 2475 4350
Wire Wire Line
	2425 4600 2425 4650
Wire Notes Line
	500  2250 3025 2250
Wire Notes Line
	500  3550 3025 3550
Text Notes 10400 2775 0    50   ~ 0
Servo Valve IN\n Futabe S3003
Text Notes 10400 3400 0    50   ~ 0
Servo Valve OUT\n Futabe S3003
Wire Notes Line
	8800 2100 8800 4000
Wire Notes Line
	8800 4000 11000 4000
Text Notes 9475 800  0    50   Italic 0
Pas sur circuit imprimé
Text Notes 1275 5125 0    50   ~ 0
Bornier Supplémentaire
$Comp
L Connector_Generic:Conn_01x03 J_SA4
U 1 1 5EB193E1
P 2075 5400
F 0 "J_SA4" H 2075 5200 50  0000 C CNN
F 1 "Conn_01x03" H 1993 5266 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2075 5400 50  0001 C CNN
F 3 "~" H 2075 5400 50  0001 C CNN
	1    2075 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	2275 5400 2525 5400
$Comp
L Connector_Generic:Conn_01x03 J_SA5
U 1 1 5EB1F1FC
P 2075 5850
F 0 "J_SA5" H 2075 5650 50  0000 C CNN
F 1 "Conn_01x03" H 1993 5716 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2075 5850 50  0001 C CNN
F 3 "~" H 2075 5850 50  0001 C CNN
	1    2075 5850
	-1   0    0    1   
$EndComp
Wire Wire Line
	2275 5850 2525 5850
$Comp
L Connector_Generic:Conn_01x01 J_SA8
U 1 1 5EB22891
P 2075 6250
F 0 "J_SA8" H 1993 6117 50  0000 C CNN
F 1 "Conn_01x01" H 1993 6116 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 2075 6250 50  0001 C CNN
F 3 "~" H 2075 6250 50  0001 C CNN
	1    2075 6250
	-1   0    0    1   
$EndComp
Wire Wire Line
	2275 6250 2525 6250
$Comp
L Connector_Generic:Conn_01x01 J_SA9
U 1 1 5EB2619E
P 2075 6475
F 0 "J_SA9" H 1993 6342 50  0000 C CNN
F 1 "Conn_01x01" H 1993 6341 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 2075 6475 50  0001 C CNN
F 3 "~" H 2075 6475 50  0001 C CNN
	1    2075 6475
	-1   0    0    1   
$EndComp
Wire Wire Line
	2275 6475 2525 6475
$Comp
L Connector_Generic:Conn_01x01 J_SIO4
U 1 1 5EB29A64
P 2700 6100
F 0 "J_SIO4" H 2618 5967 50  0000 C CNN
F 1 "Conn_01x01" H 2618 5966 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 2700 6100 50  0001 C CNN
F 3 "~" H 2700 6100 50  0001 C CNN
	1    2700 6100
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 6100 3175 6100
$Comp
L Connector_Generic:Conn_01x01 J_SIO1
U 1 1 5EB2D408
P 2700 5400
F 0 "J_SIO1" H 2618 5267 50  0000 C CNN
F 1 "Conn_01x01" H 2618 5266 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 2700 5400 50  0001 C CNN
F 3 "~" H 2700 5400 50  0001 C CNN
	1    2700 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 5400 3175 5400
$Comp
L Connector_Generic:Conn_01x01 J_SIO2
U 1 1 5EB30FCD
P 2700 5625
F 0 "J_SIO2" H 2618 5492 50  0000 C CNN
F 1 "Conn_01x01" H 2618 5491 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 2700 5625 50  0001 C CNN
F 3 "~" H 2700 5625 50  0001 C CNN
	1    2700 5625
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 5625 3175 5625
$Comp
L Connector_Generic:Conn_01x01 J_SIO3
U 1 1 5EB34AFE
P 2700 5850
F 0 "J_SIO3" H 2618 5717 50  0000 C CNN
F 1 "Conn_01x01" H 2618 5716 50  0001 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 2700 5850 50  0001 C CNN
F 3 "~" H 2700 5850 50  0001 C CNN
	1    2700 5850
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 5850 3175 5850
Wire Notes Line
	3025 3500 3025 2300
Wire Notes Line
	3025 3575 3025 4975
Wire Notes Line
	500  5000 3275 5000
Wire Notes Line
	500  6575 3275 6575
Wire Wire Line
	4800 5000 4400 5000
Wire Wire Line
	4800 5100 4400 5100
Wire Wire Line
	6800 5300 7175 5300
Wire Wire Line
	6800 5200 7175 5200
Wire Wire Line
	4800 3600 4425 3600
Wire Wire Line
	4800 3700 4425 3700
Wire Wire Line
	4800 3800 4425 3800
Wire Wire Line
	4800 3900 4425 3900
Text Label 2325 5400 0    50   ~ 0
SA4
Text Label 2325 5850 0    50   ~ 0
SA5
Text Label 2325 6250 0    50   ~ 0
SA8
Text Label 2325 6475 0    50   ~ 0
SA9
Text Label 2975 5400 0    50   ~ 0
SIO1
Text Label 2975 5625 0    50   ~ 0
SIO2
Text Label 2975 5850 0    50   ~ 0
SIO3
Text Label 2975 6100 0    50   ~ 0
SIO4
Text Label 4475 3600 0    50   ~ 0
SIO1
Text Label 4475 3700 0    50   ~ 0
SIO2
Text Label 4475 3800 0    50   ~ 0
SIO3
Text Label 4475 3900 0    50   ~ 0
SIO4
Text Label 4450 5000 0    50   ~ 0
SA4
Text Label 4450 5100 0    50   ~ 0
SA5
Text Label 6825 5300 0    50   ~ 0
SA8
Text Label 6825 5200 0    50   ~ 0
SA9
$Comp
L Connector_Generic:Conn_01x04 J_GND1
U 1 1 5EBC0340
P 650 5575
F 0 "J_GND1" H 568 5242 50  0000 C CNN
F 1 "Conn_01x04" H 568 5241 50  0001 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-4_P5.08mm" H 650 5575 50  0001 C CNN
F 3 "~" H 650 5575 50  0001 C CNN
	1    650  5575
	-1   0    0    1   
$EndComp
Wire Wire Line
	850  5375 900  5375
Wire Wire Line
	900  5375 900  5475
Wire Wire Line
	900  5675 850  5675
Wire Wire Line
	850  5575 900  5575
Connection ~ 900  5575
Wire Wire Line
	900  5575 900  5675
Wire Wire Line
	850  5475 900  5475
Connection ~ 900  5475
Wire Wire Line
	900  5475 900  5525
$Comp
L power:GNDPWR #PWR0138
U 1 1 5EBE14AD
P 1025 5550
F 0 "#PWR0138" H 1025 5350 50  0001 C CNN
F 1 "GNDPWR" H 1029 5396 50  0001 C CNN
F 2 "" H 1025 5500 50  0001 C CNN
F 3 "" H 1025 5500 50  0001 C CNN
	1    1025 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1025 5550 1025 5525
Wire Wire Line
	1025 5525 900  5525
Connection ~ 900  5525
Wire Wire Line
	900  5525 900  5575
$Comp
L Connector_Generic:Conn_01x04 J_5V1
U 1 1 5EBE6C28
P 1200 5575
F 0 "J_5V1" H 1118 5242 50  0000 C CNN
F 1 "Conn_01x04" H 1118 5241 50  0001 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-4_P5.08mm" H 1200 5575 50  0001 C CNN
F 3 "~" H 1200 5575 50  0001 C CNN
	1    1200 5575
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 5375 1450 5375
Wire Wire Line
	1450 5375 1450 5475
Wire Wire Line
	1450 5675 1400 5675
Wire Wire Line
	1400 5575 1450 5575
Connection ~ 1450 5575
Wire Wire Line
	1450 5575 1450 5675
Wire Wire Line
	1400 5475 1450 5475
Connection ~ 1450 5475
Wire Wire Line
	1450 5475 1450 5525
$Comp
L power:+5V #PWR0139
U 1 1 5EBEE13C
P 1625 5475
F 0 "#PWR0139" H 1625 5325 50  0001 C CNN
F 1 "+5V" H 1640 5648 50  0000 C CNN
F 2 "" H 1625 5475 50  0001 C CNN
F 3 "" H 1625 5475 50  0001 C CNN
	1    1625 5475
	1    0    0    -1  
$EndComp
Wire Wire Line
	1625 5475 1625 5525
Wire Wire Line
	1625 5525 1450 5525
Connection ~ 1450 5525
Wire Wire Line
	1450 5525 1450 5575
$Comp
L Connector_Generic:Conn_01x04 J_3V3
U 1 1 5EBF57C6
P 650 6200
F 0 "J_3V3" H 568 5867 50  0000 C CNN
F 1 "Conn_01x04" H 568 5866 50  0001 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-4_P5.08mm" H 650 6200 50  0001 C CNN
F 3 "~" H 650 6200 50  0001 C CNN
	1    650  6200
	-1   0    0    1   
$EndComp
Wire Wire Line
	850  6000 900  6000
Wire Wire Line
	900  6000 900  6100
Wire Wire Line
	900  6300 850  6300
Wire Wire Line
	850  6200 900  6200
Connection ~ 900  6200
Wire Wire Line
	900  6200 900  6300
Wire Wire Line
	850  6100 900  6100
Connection ~ 900  6100
Wire Wire Line
	900  6100 900  6150
Wire Wire Line
	1075 6100 1075 6150
Wire Wire Line
	1075 6150 900  6150
Connection ~ 900  6150
Wire Wire Line
	900  6150 900  6200
$Comp
L power:+3.3V #PWR0140
U 1 1 5EBFDD45
P 1075 6100
F 0 "#PWR0140" H 1075 5950 50  0001 C CNN
F 1 "+3.3V" H 950 6250 50  0000 L CNN
F 2 "" H 1075 6100 50  0001 C CNN
F 3 "" H 1075 6100 50  0001 C CNN
	1    1075 6100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J_VCC1
U 1 1 5EC06CDE
P 1275 6200
F 0 "J_VCC1" H 1193 5867 50  0000 C CNN
F 1 "Conn_01x04" H 1193 5866 50  0001 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-4_P5.08mm" H 1275 6200 50  0001 C CNN
F 3 "~" H 1275 6200 50  0001 C CNN
	1    1275 6200
	-1   0    0    1   
$EndComp
Wire Wire Line
	1475 6000 1525 6000
Wire Wire Line
	1525 6000 1525 6100
Wire Wire Line
	1525 6300 1475 6300
Wire Wire Line
	1475 6200 1525 6200
Connection ~ 1525 6200
Wire Wire Line
	1525 6200 1525 6300
Wire Wire Line
	1475 6100 1525 6100
Connection ~ 1525 6100
Wire Wire Line
	1525 6100 1525 6150
Wire Wire Line
	1700 6100 1700 6150
Wire Wire Line
	1700 6150 1525 6150
Connection ~ 1525 6150
Wire Wire Line
	1525 6150 1525 6200
$Comp
L power:VCC #PWR0141
U 1 1 5EC0FD1B
P 1700 6100
F 0 "#PWR0141" H 1700 5950 50  0001 C CNN
F 1 "VCC" H 1717 6273 50  0000 C CNN
F 2 "" H 1700 6100 50  0001 C CNN
F 3 "" H 1700 6100 50  0001 C CNN
	1    1700 6100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 JS_5
U 1 1 5EB5F4AF
P 9925 4600
F 0 "JS_5" H 9625 4550 50  0000 C CNN
F 1 "Conn_01x02" H 9843 4366 50  0001 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 9925 4600 50  0001 C CNN
F 3 "~" H 9925 4600 50  0001 C CNN
	1    9925 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	10125 4500 10125 4350
Connection ~ 10125 4350
Wire Wire Line
	10125 4600 10125 4700
Wire Wire Line
	10125 4700 9875 4700
Connection ~ 9875 4700
$Comp
L Connector_Generic:Conn_01x02 JC_5
U 1 1 5EB6FC56
P 9950 5825
F 0 "JC_5" H 9650 5775 50  0000 C CNN
F 1 "Conn_01x02" H 9868 5591 50  0001 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 9950 5825 50  0001 C CNN
F 3 "~" H 9950 5825 50  0001 C CNN
	1    9950 5825
	-1   0    0    1   
$EndComp
Wire Wire Line
	10150 5725 10275 5725
Wire Wire Line
	10275 5725 10275 5600
Wire Wire Line
	10275 5550 10125 5550
Connection ~ 10125 5550
Wire Wire Line
	10150 5825 10150 5900
Connection ~ 9875 5900
NoConn ~ 6800 2600
NoConn ~ 6800 2700
NoConn ~ 6800 2800
NoConn ~ 6800 2900
NoConn ~ 6800 3100
NoConn ~ 6800 3200
NoConn ~ 6800 3300
NoConn ~ 6800 3400
NoConn ~ 6800 3500
NoConn ~ 6800 3600
NoConn ~ 6800 3700
NoConn ~ 6800 3800
NoConn ~ 6800 3900
NoConn ~ 6800 4000
NoConn ~ 6800 4100
NoConn ~ 6800 4500
NoConn ~ 6800 4600
NoConn ~ 6800 4700
NoConn ~ 6800 4900
NoConn ~ 4800 4000
NoConn ~ 4800 4200
NoConn ~ 4800 4300
NoConn ~ 4800 4400
NoConn ~ 4800 4500
NoConn ~ 4800 2600
Wire Wire Line
	2400 2950 2475 2950
Wire Wire Line
	2475 2950 2475 3075
Connection ~ 2475 3075
Wire Wire Line
	2475 3075 2925 3075
Wire Wire Line
	2400 4200 2475 4200
Wire Wire Line
	2475 4200 2475 4350
Connection ~ 2475 4350
Wire Wire Line
	2475 4350 2950 4350
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5EC9ED69
P 10400 5550
F 0 "#FLG0101" H 10400 5625 50  0001 C CNN
F 1 "PWR_FLAG" H 10400 5723 50  0000 C CNN
F 2 "" H 10400 5550 50  0001 C CNN
F 3 "~" H 10400 5550 50  0001 C CNN
	1    10400 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 5550 10400 5600
Wire Wire Line
	10400 5600 10275 5600
Connection ~ 10275 5600
Wire Wire Line
	10275 5600 10275 5550
Wire Wire Line
	9875 5900 10150 5900
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5ECB38FE
P 10400 4225
F 0 "#FLG0102" H 10400 4300 50  0001 C CNN
F 1 "PWR_FLAG" H 10400 4398 50  0000 C CNN
F 2 "" H 10400 4225 50  0001 C CNN
F 3 "~" H 10400 4225 50  0001 C CNN
	1    10400 4225
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 4225 10400 4300
Wire Wire Line
	10400 4300 10125 4300
Connection ~ 10125 4300
Wire Wire Line
	10125 4300 10125 4350
NoConn ~ 6800 3000
$Comp
L power:+5V #PWR0106
U 1 1 5EB596F6
P 6925 4800
F 0 "#PWR0106" H 6925 4650 50  0001 C CNN
F 1 "+5V" H 6940 4973 50  0000 C CNN
F 2 "" H 6925 4800 50  0001 C CNN
F 3 "" H 6925 4800 50  0001 C CNN
	1    6925 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 4800 6925 4800
Wire Notes Line
	3275 5000 3275 6550
$Comp
L power:GNDPWR #PWR0142
U 1 1 5EB5DC6B
P 2350 5500
F 0 "#PWR0142" H 2350 5300 50  0001 C CNN
F 1 "GNDPWR" H 2354 5346 50  0001 C CNN
F 2 "" H 2350 5450 50  0001 C CNN
F 3 "" H 2350 5450 50  0001 C CNN
	1    2350 5500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0143
U 1 1 5EB5EE49
P 2350 5275
F 0 "#PWR0143" H 2350 5125 50  0001 C CNN
F 1 "+3.3V" H 2225 5425 50  0000 L CNN
F 2 "" H 2350 5275 50  0001 C CNN
F 3 "" H 2350 5275 50  0001 C CNN
	1    2350 5275
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5275 2350 5300
Wire Wire Line
	2350 5300 2275 5300
Wire Wire Line
	2350 5500 2275 5500
$Comp
L power:GNDPWR #PWR0144
U 1 1 5EB72F89
P 2350 5950
F 0 "#PWR0144" H 2350 5750 50  0001 C CNN
F 1 "GNDPWR" H 2354 5796 50  0001 C CNN
F 2 "" H 2350 5900 50  0001 C CNN
F 3 "" H 2350 5900 50  0001 C CNN
	1    2350 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5950 2275 5950
$Comp
L power:+3.3V #PWR0145
U 1 1 5EB7D126
P 2525 5725
F 0 "#PWR0145" H 2525 5575 50  0001 C CNN
F 1 "+3.3V" H 2400 5875 50  0000 L CNN
F 2 "" H 2525 5725 50  0001 C CNN
F 3 "" H 2525 5725 50  0001 C CNN
	1    2525 5725
	1    0    0    -1  
$EndComp
Wire Wire Line
	2525 5725 2525 5750
Wire Wire Line
	2525 5750 2275 5750
Wire Wire Line
	1825 1000 1825 625 
Wire Wire Line
	1925 1000 1925 625 
Text Label 1825 950  1    50   ~ 0
IO6
Text Label 1925 950  1    50   ~ 0
IO1
Wire Wire Line
	4800 2700 4200 2700
Text Label 4250 2700 0    50   ~ 0
IO1
Text Label 4250 3100 0    50   ~ 0
IO6
Wire Wire Line
	4800 3100 4200 3100
NoConn ~ 4800 2800
$Comp
L Transistor_FET:BS170 Q?
U 1 1 5EB4B1A8
P 3900 3850
F 0 "Q?" H 4105 3896 50  0000 L CNN
F 1 "BS170" H 4105 3805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4100 3775 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BS/BS170.pdf" H 3900 3850 50  0001 L CNN
	1    3900 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 4050 3800 4200
Wire Wire Line
	3725 3600 3800 3600
Wire Wire Line
	3800 3600 3800 3650
Wire Wire Line
	4100 3850 4225 3850
Wire Wire Line
	4225 3850 4225 3300
$Comp
L power:+5V #PWR?
U 1 1 5EB76E8B
P 3875 3400
F 0 "#PWR?" H 3875 3250 50  0001 C CNN
F 1 "+5V" H 3890 3573 50  0000 C CNN
F 2 "" H 3875 3400 50  0001 C CNN
F 3 "" H 3875 3400 50  0001 C CNN
	1    3875 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	3875 3400 3725 3400
$EndSCHEMATC