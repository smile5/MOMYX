/***************************************************************************
  Copyright 2020 X Galtier - Marc Pleyber - Orphee Cugat - Mickael Brunello
  FROM ORIGINAL MUR-PROJECT LECLUBSANDWICH
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
// nous devons fixer nos consignes en cm H20 donc en hPa = de 5 à 40 hPa
// le capteur renvoie l'info en Volts, sortie max Capteur 5V pour 100 hPa
// (le teensy analog input 3V3 max donc maxi lisible 70 hPa) 

#include <Servo.h>
#include <Wire.h>

//bibliotheque specifique Teensy (a partir de maintenant on peut plus utiliser un autre carte)
#include <ADC.h>
#include <ADC_util.h>

ADC *adc = new ADC(); // adc object dedans 2 adc:  
// adc0 pour les capteurs (filtres)
// adc1 pour les potards (non filtres +rapide)
//--------------------------------------------------------------------------------------------

// declaration fonction
void print_Consigne_Interface_Graphique();
void print_Valeurs();
void get_PID_From_Uart();
void process_Consigne();
float Calcul_PID(float consigne,float sensor,bool init_val);
void updateSensors();
void sature_Position_Valve_In(int position);
void sature_Position_Valve_Out(int position);
float mesure_Flow_Venturi();
void offset_Capteurs();

// ou/et comment imprimer les Valeurs  =1 plot_valeur; =2 print_valeur;  =0 interface graphique
#define PRINT_WHERE 1   // 0 GUI,  1 TRACEUR,  2 MONITOR

// Parametre regulation:
float coeff_P=4;    // constante proportionnelle
float coeff_I=5; // constante de temps integration
float coeff_D=0.1 ; // constante de temps derivee

// definition des constantes
#define VALVE_IN_MAX 100 //valeur fermeture VALVE VTT
#define VALVE_IN_MIN 0 // valeur ouverture VALVE VTT
#define VALVE_OUT_MAX 100  // ouverture VALVE d'expiration (boisseau triangle)
#define VALVE_OUT_MIN 0    // fermeture VALVE d'expiration (boisseau triangle)
#define RATIO_VALVE_INOUT 1.5 // (VALVE_IN_MAX-VALVE_IN_MIN)/(VALVE_OUT_MAX-VALVE_OUT_MIN)

// limites alarmes Pression Diff
#define MIN_DIFF_PRESS 100.  // mini  300 Pa = 3 hPa = 3 cmH2O 
#define MAX_DIFF_PRESS 4000. // maxi 4000 Pa = 40 hPa = 40 cmH2O

#define STATE_IDLE 0 // etat attente 
#define STATE_PEAK 1 // cycle en cours et etat = generation peak
#define STATE_INSPIRATION_PLATEAU 2 // cycle/etat = gene plateau inspiratoire
#define STATE_EXPIRATION_PLATEAU 3  // cycle/etat = gene plateau expiratoire

#define CAPTEUR_SAMP_TIME 20
#define POTENTIO_SAMP_TIME 50
#define GUI_SAMP_TIME 100

// definition variables Globales
Servo inValve;  // servomoteur entree turbine => patient
Servo outValve; // servomoteur sortie patient => room
int servo_in,servo_out; // angles servos

unsigned char etat=STATE_IDLE; // etat courant de la machine à etats

float pression_Patient_Relative; // pression relative du patient (hPa)

// Potentiometer and Servo pins
int inValvePin = 2;     // Pin for input Valve  => REMISES 2 & 3 COMME MUR
int outValvePin = 3;    // Pin for Output Valve => REMISES 2 & 3 COMME MUR
int Led = 5;            // future neopixel Led for user feedback
int Buzzer = 6 ;            // Alarm Buzzer 
int btn_Maintenance = 7;    // sets all valves to 0° for maintaince
int btn_PressureCal = 8;    // closes outputValve and opens Input Valve for maximum pressure calibration

// Lecture input potars valeurs analogiques 0 à 3V3
// => pattes Teensy A0 A1 A2 A3 (A6 = capteur MPXV5010/5004, A7 = capteur MPXV5010)

float pot_A0,pot_A1,pot_A2,pot_A3,venturi_A6,pression_A7;
float pot_A0_old,pot_A1_old,pot_A2_old,pot_A3_old,venturi_A6_old,pression_A7_old;
float cycle,ratio;

float debit_l_m,volume_ml,debit; // debit en l/min - volume en ml - debit en m3/s
//float venturi_maxi,venturi_neg; //ancienne calib capteurs
//float pression_maxi,pression_neg;
int venturi_offset,pression_offset;

// different timers in our breathing cycle
unsigned long temps_cycle = 3000;  // duree totale cycle (ms)
unsigned long temps_peak = 0;       // duree peak  (ms) PAS IMPLEMENTEE
unsigned long temps_plateauIns = 0; // duree plateau inspiration (ms)
unsigned long temps_plateauExp = 0; // duree plateau expiration  (ms)
float consigne_Inspi=20;             // consigne de départ plateau Inspire (hPa) 
float consigne_Expi=6;              // consigne de départ plateau Exprire (hPa)
//
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

// variable pour loop
unsigned long var_stock_temp_cycle=0;
unsigned long var_stock_temp_capteur=0;
unsigned long var_stock_temp_potentio=0;
unsigned long var_stock_temp_gui=0,var_stock_temp_volume=0,now=0;
float consigne;
int cptserial = 0;
char buffer[64];
int servo_angle,servo_max;

// sauvegarde valeur PID
float err_int=0;
float last_erreur=0;
unsigned long last_time=0;

//                                     MAIN LOOP
void setup() {
  pinMode(btn_Maintenance, INPUT_PULLUP); // configure entree Bouton
  pinMode(btn_PressureCal, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT); // configure Voyant
  pinMode(Buzzer, OUTPUT);    // configure Buzzer
  digitalWrite(Buzzer, LOW);  // Chut j'ai dit
  Serial.begin(115200);       // initialisation port serie (utile pour comm: data + courbe )
 
  // CONFIG Specifique ADC Teensy
  pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(venturi_A6, INPUT);
	pinMode(pression_A7, INPUT);
	adc->adc0->setAveraging(16); // set number of averages
    adc->adc0->setResolution(16); // set bits of resolution
	adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED_16BITS); // change the conversion speed
	adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED); // change the sampling speed
//	adc->adc1->setAveraging(1); // set number of averages
//    adc->adc1->setResolution(10); // set bits of resolution
//	adc->adc1->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED_16BITS); // change the conversion speed
//	adc->adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED); // change the sampling speed
	//	
	
  inValve.attach(inValvePin);
  outValve.attach(outValvePin);
  // au démarrage on tripote les vannes :
  outValve.write(VALVE_OUT_MIN);  // valve OUT OPEN
  delay (300);             // 
  inValve.write(VALVE_IN_MAX);    // valve IN CLOSED
  delay (300);
  
  inValve.write(VALVE_IN_MIN);    // valve IN  OPEN 	
  var_stock_temp_volume=0;
  etat=STATE_IDLE;	

//ROUTINE CALIBRATION OFFSET	
		  outValve.write(VALVE_OUT_MIN);  // valve OUT OPEN
          inValve.write(VALVE_IN_MAX);    // valve IN CLOSED
          delay(1000);
		  // pression & débit nuls, on peut calibrer l'offset du capteu venturi pour le MAP
	      offset_Capteurs() ;
		  delay(100);
}


void print_Potentiometre()
{
	bool change=false;
    if(abs(pot_A0-pot_A0_old)>100)  // vario cycle 100 ms
    {
      pot_A0_old=pot_A0;
      cycle=pot_A0;
      Serial.print("(durée=");  
      Serial.print(int(pot_A0/100.)/10.); // durée du cycle en sec
      Serial.print(")");  
      temps_cycle=(unsigned long)cycle;
      temps_plateauIns=(unsigned long)(cycle*ratio); // NB I/E n'est pas I/cycle ! I/E = ratio/(1-ratio)
      temps_plateauExp=temps_cycle-temps_plateauIns;
	  change=true;
    }
    if(abs(pot_A1-pot_A1_old)>0.02)  // vario ratio 2%
    {
      pot_A1_old=pot_A1;
      ratio=pot_A1;
      temps_plateauIns=(unsigned long)(cycle*ratio);
      temps_plateauExp=temps_cycle-temps_plateauIns;
	  change=true;
    }
    if(abs(pot_A2-pot_A2_old)>0.2) // vario Inspi 0.2 cm
    {
      pot_A2_old=pot_A2;
      consigne_Inspi=pot_A2;
	  change=true;
    }
    if(abs(pot_A3-pot_A3_old)>0.2)  // vario expi 0,2 cm
    {
      pot_A3_old=pot_A3;
      consigne_Expi=pot_A3;
	  change=true;
    }
#if PRINT_WHERE==1
    plot_valeurs();     //  TRACEUR
#elif PRINT_WHERE==2
    print_Valeurs();  //  TABLEAU
#else 
	if(change==true)
    	print_Consigne_Interface_Graphique();
#endif    

}


void updateSensors()
{
  unsigned char i;
//  read Diff Sensor analog, lecture 3V3 maxi (5V pour range max 100 hPa)
        pression_A7=adc->adc0->analogRead(A7)-pression_offset;  // press diff patient, on tiens compte de l'offset du capteur
    pression_A7=map(pression_A7, 0, 65535, 0, 7333);  // Mapping pour Pression MPXV5010
    pression_Patient_Relative = pression_A7/100.;
	
  if ((pression_Patient_Relative <= MIN_DIFF_PRESS) || (pression_Patient_Relative >= MAX_DIFF_PRESS)) {
    digitalWrite(Buzzer, HIGH);
  }
  else
  {
    digitalWrite(Buzzer, LOW);
  }
}

void loop() {
	
/*      if(init_val==true)
    {
        inValve.write(80);              // au tout début on met de la pression pour gagner en temps de montée
        outValve.write(130);            // 
    }
*/ 
	
  // Lire capteur a intervalles reguliers (20ms => 50Hz env) 
  // attention pas tres precis depend du temps de boucle
  if (CAPTEUR_SAMP_TIME < (millis() - var_stock_temp_capteur)) {
    // sample time before reading the sensor for a regular interval
    var_stock_temp_capteur=millis();
    updateSensors();
	if(etat==STATE_EXPIRATION_PLATEAU)
	{
		now=micros();
  		debit=mesure_Flow_Venturi();	// en m3/s
 	  	debit_l_m=debit*60000.0;        // en litre/min
  		volume_ml+= debit*((float)(now-var_stock_temp_volume));	// volume en ml
  		var_stock_temp_volume=now;  
	}
	if(etat!= STATE_IDLE)
	{
  // Calcul du correcteur PID ici a chaque fois qu'on lit les capteurs  
     servo_angle=Calcul_PID(consigne,pression_Patient_Relative,false); 
  // calcul angle servo_in et servo out 
	  servo_in=(int)((float)RATIO_VALVE_INOUT*servo_angle);
	  servo_out=(int)(servo_angle);
    sature_Position_Valve_Out(servo_out);   /////////    
    sature_Position_Valve_In(VALVE_IN_MAX-servo_in);   ////
        }
  }
	
  if(POTENTIO_SAMP_TIME< (millis() - var_stock_temp_potentio)) {
    // sample time before reading the sensor for a regular interval
    var_stock_temp_potentio=millis();
    lire_Potentiometre();
    print_Potentiometre();
  }
if (stringComplete) {
	get_PID_From_Uart(); // permet de recuperer les valeurs des coeff PID
    //process_Consigne(); //A GARDER POUR LA SUITE ECRAN
  }
 
  switch (etat)
  {
    case STATE_IDLE:
      // On sort de l'etat de veille si les consignes sont realistes
      if((temps_cycle<11990)&&(consigne_Inspi>10)&&(consigne_Expi>1))
        {
          etat=STATE_INSPIRATION_PLATEAU;
          Calcul_PID(0.0,0.0,true); // useless si ce n'est RAZ PID (notamment le I)
//ROUTINE CALIBRATION OFFSET	          
		  outValve.write(VALVE_OUT_MIN);  // valve OUT OPEN
          inValve.write(VALVE_IN_MAX);    // valve IN CLOSED
          delay(1000);
		  // pression & débit nuls, on peut calibrer l'offset du capteu venturi pour le MAP
	      offset_Capteurs() ;
		  delay(100);
        }
      break;
    case STATE_INSPIRATION_PLATEAU:


		  
	  if(millis()-var_stock_temp_cycle>=temps_plateauIns)
      {
        consigne=consigne_Expi;
        etat=STATE_EXPIRATION_PLATEAU;
        var_stock_temp_cycle=millis();
        digitalWrite(LED_BUILTIN, LOW);
		volume_ml=0; // RAZ volume_ml
      }
      break;
    case STATE_EXPIRATION_PLATEAU:


   
      if(millis()-var_stock_temp_cycle>=temps_plateauExp)
      {
        consigne= consigne_Inspi;
        etat=STATE_INSPIRATION_PLATEAU;
        var_stock_temp_cycle=millis();    
        digitalWrite(LED_BUILTIN, HIGH);  
		volume_ml=0; // RAZ volume_ml
      }
      break;
  }
  // Print Value for monitoring 
  
  if(etat!=STATE_IDLE)
  {
    #if PRINT_WHERE==0
    if(GUI_SAMP_TIME< (millis() - var_stock_temp_gui)) {
    // sample time before reading the sensor for a regular interval
    var_stock_temp_gui=millis();

    Serial.print("!P");
    Serial.print(pression_Patient_Relative);
    Serial.println('*'); 
    Serial.print("!c");
    Serial.print(consigne);
    Serial.println('*');
    }
#endif
 }
  if(temps_cycle>11990)
  {
    etat=STATE_IDLE;    
//ROUTINE CALIBRATION OFFSET	
	      outValve.write(VALVE_OUT_MIN);  // valve OUT OPEN
          inValve.write(VALVE_IN_MAX);    // valve IN CLOSED
          delay(1000);
		  // pression & débit nuls, on peut calibrer l'offset du capteu venturi pour le MAP
	      offset_Capteurs() ;
		  delay(100);
  }
}
void sature_Position_Valve_In(int position)
{
    // Saturation commande sortie PID   
    // on veut saturer la sortie entre 0 et VALVE_OUT_MAX, 
    // si position > MAX alors VALVE = VALVE_OUT_MAX, si position <0 alors VALVE=0
  	// sinon si position est comprise entre les deux VALVE = position
	
	  if (position>VALVE_IN_MAX) 
      {                                         
        inValve.write(VALVE_IN_MAX);          //   |
      }                                         //   |  
      else if (position<VALVE_IN_MIN)          //   |
      {                                         //   |
        inValve.write(VALVE_IN_MIN);          //    >  si erreur augmente on ferme la VALVE...
      }                                         //   |    donc un - devant servo angle
      else                                      //   |
      {                                         //   |
        inValve.write(position);               //   |
      }   
}

void sature_Position_Valve_Out(int position)
{
    // Saturation commande sortie PID   
    // on veut saturer la sortie entre 0 et VALVE_OUT_MAX, 
    // si position > MAX alors VALVE = VALVE_OUT_MAX, si position <0 alors VALVE=0
	  // sinon si position est comprise entre les deux VALVE = position
	
	  if (position>VALVE_OUT_MAX) 
      {                                         
        outValve.write(VALVE_OUT_MAX);          //   |
      }                                         //   |  
      else if (position<VALVE_OUT_MIN)          //   |
      {                                         //   |
        outValve.write(VALVE_OUT_MIN);          //    >  si erreur augmente on ferme la VALVE...
      }                                         //   |    donc un - devant servo angle
      else                                      //   |
      {                                         //   |
        outValve.write(position);               //   |
      }   
}


void lire_Potentiometre()
{
  adc->adc0->setAveraging(1); // set number of averages	to 1 for lecture potards
	
  pot_A0=map(adc->adc0->analogRead(A0), 0, 65535, 12000, 1000);        // cycle 1000 à 12000 millisec (en tournant à droite 5 à 60 cycles/min)
  pot_A1=map(adc->adc0->analogRead(A1), 0, 65535, 2000, 5000)/10000.0; // ratio Insp/Cycle 0,2 à 0,5 : voir NB ci-dessous, y'a une nuance !
  pot_A2=map(adc->adc0->analogRead(A2), 0, 65535, 1000, 3000)/100.0;   // inspi 15 à 30 cmH2O (30 au lieu de 40 tant qu'on n'a pas la bonne turbine)
  pot_A3=map(adc->adc0->analogRead(A3), 0, 65535, 300, 1600)/100.0;    // expi 3 à 16 cmH2O
  // ATTENTION le ratio affiché c'est le ratio insp/cycle et non pas I/E (Insp/Exp)
  // les réa pensent en ratio I/E de 1/4 à 1/1
  // MAIS comme Cycle = Insp + Exp, alors Insp/Cycle = 20 à 50%
  // DONC le potard donne direct 20 à 50% du cycle puisque le calculateur pense en insp/cycle
  // il faudra PLUS TARD demander au potard de donner et afficher le vrai I/E et non I/cycle, et de rajouter une ligne de calcul
  
	adc->adc0->setAveraging(16); // set number of averages to 16 pour capteurs pression	
}

void plot_valeurs()
{
//     Serial.print(pot_A2);      // P Insp
//      Serial.print(',');
//      Serial.print(pot_A3);      // PEP
//      Serial.print(',');
        Serial.print(consigne);    // consigne qui basule de A2 (insp) à A3 (PEP)
        Serial.print(',');
  /*    Serial.print(servo_in/10.);    // angle du servo_in
      Serial.print(',');
      Serial.print(servo_out/10.);    // angle du servo_out
      Serial.print(',');
   */
      Serial.print(pression_Patient_Relative);  // pression Patient cmH2O ou hPa
      Serial.print(',');
 //     Serial.print(venturi_A6/100.);  // pression Patient en Pa/100. = cmH2O ou hPa
   /* Serial.print(',');
      Serial.print(debit_l_m);    // debit en litre/min
	    Serial.print(',');
      Serial.print(volume_ml/10.);    // volume en ml/10. = cl (car en ml trop grand pour écran)
     */
      Serial.println(',');
      }

void print_Valeurs()
{
      Serial.print(etat);              // IDLE INSP EXP
      Serial.print(" (durée ");  
      Serial.print(int(pot_A0/1000.)); // durée du cycle en sec
      Serial.print("sec @I/cycle ");
      Serial.print(int(pot_A1*100));   // ratio Insp/Cycle
      Serial.print("%) (Insp/Exp: ");
      Serial.print(int(pot_A2));       // insp
      Serial.print("/");            
      Serial.print(int(pot_A3));       // exp
      Serial.print("cm) [Réel ");
      Serial.print(int(pression_A7));  // pression patient
      Serial.print("cm]");
      Serial.println('*');
} 

void print_Consigne_Interface_Graphique()
{
      Serial.print('!');
      Serial.print('C');
      Serial.print(cycle);
      Serial.println('*');
      Serial.print('!');
      Serial.print('R');
      Serial.print(ratio);
      Serial.println('*');
      Serial.print('!');
      Serial.print('I');
      Serial.print(consigne_Inspi);
      Serial.println('*');
      Serial.print('!');
      Serial.print('E');
      Serial.print(consigne_Expi);
      Serial.println('*');
}
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. 
  This routine is run between each time loop() runs, so using delay inside loop 
  can delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is an asterix ;-) , 
    // set a flag so the main loop can do something about it:
    if (inChar == '*') {
      stringComplete = true;
    }
  }
}

void get_PID_From_Uart() // NE PAS EFFACER NI MODIFIER !!! on s'en servire plus tard
{
  String temp_String = "";
  char index_Start,index_Stop,index_temp1,index_temp2;
  index_Start=inputString.indexOf('!');
  index_Stop=inputString.indexOf('*');
  if((index_Start>=0)&&(index_Stop>=0))
    temp_String =inputString.substring(index_Start,index_Stop);
  if(temp_String!=""){
    index_Start=temp_String.indexOf('p'); // coeff P
    index_Stop=temp_String.indexOf('i');  // coeff I
    index_temp1=temp_String.indexOf('d'); // coeff D
    if(index_Start !=-1)
      coeff_P=temp_String.substring(index_Start+1,index_Stop).toFloat();
    if(index_Stop !=-1)
      coeff_I=temp_String.substring(index_Stop+1,index_temp1).toFloat();
    if(index_temp1 !=-1)
      coeff_D=temp_String.substring(index_temp1+1).toFloat();
    inputString="";
  }
}


void process_Consigne() // NE PAS EFFACER NI MODIFIER !!! on s'en servire plus tard
{
  String temp_String = "";
  char index_Start,index_Stop,index_temp1,index_temp2;
  index_Start=inputString.indexOf('!');
  index_Stop=inputString.indexOf('*');
  if((index_Start>=0)&&(index_Stop>=0))
    temp_String =inputString.substring(index_Start,index_Stop);
  if(temp_String!=""){
    index_Start=temp_String.indexOf('C'); // durée cycle (ms)
    index_Stop=temp_String.indexOf('R');  // ratio Exp/Insp (fraction)
    index_temp1=temp_String.indexOf('I'); // pression Insp (hPa / cm H2O)
    index_temp2=temp_String.indexOf('E'); // pression Exp  (hPa / cm H2O)
    cycle=temp_String.substring(index_Start+1,index_Stop).toFloat();
    ratio=temp_String.substring(index_Stop+1,index_temp1).toFloat();
    temps_plateauIns=(unsigned long)(ratio*cycle);
    temps_plateauExp=(unsigned long)cycle-temps_plateauIns;
    temps_cycle=temps_plateauIns+temps_plateauExp;
    consigne_Inspi=temp_String.substring(index_temp1+1,index_temp2).toFloat();
    consigne_Expi=temp_String.substring(index_temp2+1).toFloat();
    inputString="";
  }
}

float Calcul_PID(float consigne,float sensor,bool init_val)
{
  
   // Calcul temps de boucle ( devrait etre constant en toute rigueur )
   unsigned long now = micros();
   unsigned long dt = now - last_time;
   float delta_t=(float)dt;
   delta_t=delta_t/1000000.0;   // microseconds => sec
    if(init_val==true)
    {
        err_int=0;
        last_erreur=0;
    }
   //Calcul des erreurs
   float erreur = consigne - sensor;
   err_int += (erreur * delta_t);
   float err_der = (erreur - last_erreur) / delta_t;
  
   //Calcul sortie PID
   float Output = coeff_P * erreur + coeff_I * err_int + coeff_D * err_der;  
   // Memoriser variable pour le prochain pas
   last_erreur = erreur;
   last_time = now;
   return Output;
}

float mesure_Flow_Venturi()
{
#define VENTURI_S0 50.26e-6  // section venturi en entree en m2 phi 8
#define VENTURI_S1 12.56e-6	 // section venturi au col en m2 phi 4
#define RHO        1.2       // densité air kg/m3 
#define S0_CARRE   2.526e-9  // S0² uniquement utile pour alleger tps de calcul Teensy
#define S1_CARRE  157.75e-12 // S1²
#define DEUX_S0_CARRE 5.0526e-9
#define RHO_SURF_DIFF 2.842e-9 // Rho*(S0*S0 -S1*S1)

float debit; // contient debit en m3/s
  venturi_A6=adc->adc0->analogRead(A6)-venturi_offset; // on lit la patte A6 = venturi et on retranche l'offset
  venturi_A6=map(venturi_A6, 0, 65535, 0, 7333);   // on calibre capteur MPXV5010
  // venturi_A6 doit etre en Pa pour les calculs suivants:
  if(venturi_A6>=0)
  {
    debit= VENTURI_S1 * sqrt((DEUX_S0_CARRE*venturi_A6)/(RHO_SURF_DIFF));
  }
  else 
  {
    debit=0;
  }
	//	debit= VENTURI_S1 * sqrt((DEUX_S0_CARRE*venturi_A6)/(RHO_SURF_DIFF));
  return debit; 
}

void offset_Capteurs()
{
unsigned char i;
// valves IN fermée, valve OUT ouverte, on élimine la pression dans le circuit
	        outValve.write(VALVE_OUT_MIN);  // valve OUT OPEN
          inValve.write(VALVE_IN_MAX);    // valve IN CLOSED
          delay(2000); // et on laisse tomber la pression

	for(i=0;i<64;i++)
	{
  		venturi_offset+=adc->adc0->analogRead(A6); 
  		pression_offset+=adc->adc0->analogRead(A7); 
		delay(10);
	}
	venturi_offset=venturi_offset/64;
	pression_offset=pression_offset/64;
 Serial.print("(VentOff=");
 Serial.print(venturi_offset);
 Serial.print("Pa)(PressOff=");
 Serial.print(pression_offset);
 Serial.print("Pa)"); 
} 
