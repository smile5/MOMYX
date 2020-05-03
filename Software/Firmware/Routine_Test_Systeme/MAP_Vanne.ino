/***************************************************************************
  Copyright 2020 X Galtier - Orphee Cugat
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
***************************************************************************/

//          AVERTISSEMENT UNITE PRESSIONS
// 1 atmosphère = 1013 hecto Pascal = 10 m d'eau = 1000 cm H2O
// 1 hecto Pascal = 1 cm H2O
// les réanimateurs travaillent entre 5 et 40 cm H2O
// le capteur renvoie l'info en Volts (masi 3V3 analogpin, capteur 5V pour 100 hPa)
  // capteur MPXV5010 Pdiff normalisée à 100hPa avec :
  // Pmaxi = 10000 Pa à sortie max 5010 mV
  // Pmini = négative
  // Volt = a.Pa + b
  // Patmo zéro: signal 260 mV => b = 260 (Attention elle varie parfois et ça bouscule les coeffs a et b ci dessous)
  // 5010 = a.10000 + 260 => a = (5010-260)/10000 = 0,500
  // entrée Arduino limitée à 3V3 = 3300 mV
  // donc P maxi mesurable (3300-260)/0,500 = 6080 Pa pour 1023 digit au MAP
  // tension à P atmo (0 relatif) = 260 mV
  // donc Pression à 0 V = -260/0,500 = -520 Pa pour 0 digit au MAP

#include <Servo.h>
#include <Wire.h>

//bibliotheque specifique Teensy (a partir de maintenant on peut plus utiliser un autre carte)
#include <ADC.h>
#include <ADC_util.h>

ADC *adc = new ADC(); // adc object dedans 2 adc:  
  
#define VALVE_IN_MAX 85 //valeur fermeture Vanne IN (90 fermé total)
#define VALVE_IN_MIN 0 // valeur ouverture Vanne IN (ouverte)
#define VALVE_OUT_MAX 180   // valeur Maxi vanne OUT
#define VALVE_OUT_MIN 0     // valeur Mini (ouverte)

void updateSensors();
int venturi_offset,pression_offset;
float pression_A7;
void offset_Capteurs();

Servo inValve;  // servomoteur entree air => patient
Servo outValve;  // servomoteur sortie patient => room

int inValvePin = 2;     // Pin for input Valve
int outValvePin = 3;    // Pin for Output Valve
float sens_A7;
unsigned long i;

void setup() {
  Serial.begin(115200);       // initialisation port serie (utile pour comm: data + courbe )
  
  // pinMode(venturi_A6, INPUT);
  pinMode(pression_A7, INPUT);
  adc->adc0->setAveraging(16); // set number of averages
  adc->adc0->setResolution(16); // set bits of resolution
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED_16BITS); // change the conversion speed
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED); // change the sampling speed
 
  inValve.attach(inValvePin);
  outValve.attach(outValvePin);
  
offset_Capteurs();
}

void loop() {
  
  	if (i>VALVE_OUT_MAX) i=VALVE_OUT_MIN;
    outValve.write(i);
    delay (700);
    pression_A7=adc->adc0->analogRead(A7)-pression_offset;  // press diff patient, on tiens compte de l'offset du capteur
    pression_A7=map(pression_A7, 0, 65535, 0, 7333);  // Mapping pour Pression MPXV5010

 /*   { // PLOT LES COURBES PRESSION/ANGLE
      Serial.print(abs(i)/10.);    // angle
      Serial.print(',');
      Serial.println(pression_A7/100.);    // pression mesurée
     }
*/
{ // IMPRIME LES DONNEES ANGLE/PRESSION
      Serial.print(i);
      Serial.print(" ; ");     
      Serial.println(pression_A7);
      } 

   i=i+2;         // 1-2-5 ou 10
   	}

void offset_Capteurs()
{
unsigned char i;
// valves IN fermée, valve OUT ouverte, on élimine la pression dans le circuit
          outValve.write(VALVE_OUT_MIN);  // valve OUT OPEN
          inValve.write(VALVE_IN_MAX);    // valve IN CLOSED
          delay(3000); // et on laisse tomber la pression

  for(i=0;i<64;i++)
  {
//      venturi_offset+=adc->adc0->analogRead(A6); 
      pression_offset+=adc->adc0->analogRead(A7); 
    delay(10);
  }
//  venturi_offset=venturi_offset/64;
  pression_offset=pression_offset/64;
 //Serial.print("(VentOff=");
 //Serial.print(venturi_offset);
 Serial.print("Pa)");
 Serial.print("(PressOff=");
 Serial.print(pression_offset);
 Serial.print("Pa)"); 

 inValve.write(VALVE_IN_MIN);    // valve IN OPEN
} 
