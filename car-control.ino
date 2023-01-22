#include <Fuzzy.h>

/* Engelden Kaçan Araç */
int sure = 0;
int mesafe = 0;

const int trig_pin = 3; 
const int echo_pin = 2;  
const int sag_enable = 11;    // ENABLE A
const int sag_ileri = 10;     // INPUT 1
const int sag_geri = 9;       // INPUT 2
const int sol_ileri = 8;      // INPUT 3
const int sol_geri = 7;       // INPUT 4
const int sol_enable = 6;     // ENABLE B


const int ottocoupler = 4;  // ottocoupler pin

void setup(){
  pinMode(trig_pin, OUTPUT); 
  pinMode(echo_pin, INPUT ); 
  pinMode(sag_ileri, OUTPUT); 
  pinMode(sag_geri, OUTPUT);
  pinMode(sol_ileri, OUTPUT);
  pinMode(sol_geri, OUTPUT);
  pinMode(sag_enable, OUTPUT);
  pinMode(sol_enable, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(trig_pin, HIGH); 
  delayMicroseconds(10);   
  digitalWrite(trig_pin, LOW);
  sure = pulseIn(echo_pin, HIGH);
  mesafe = (sure / 2) / 29.1;
  Serial.println(mesafe);

  if (mesafe < 20 && mesafe >5) {  // mesafe 20 cm den küçükse
    /* motorlar kitlenerek araç durdurulur */
    digitalWrite(sag_ileri, LOW); 
    digitalWrite(sag_geri, LOW);
    digitalWrite(sol_ileri, LOW);
    digitalWrite(sol_geri, LOW);
    delay(500);
    
    /* araç geriye doğru hareket ettirilir */
    digitalWrite(sag_ileri, LOW);
    digitalWrite(sag_geri, HIGH);
    digitalWrite(sol_ileri, LOW);
    digitalWrite(sol_geri, HIGH);
    analogWrite(sag_enable, 100); // motor hızları 200 PWM
    analogWrite(sol_enable, 100);
    delay(500);
    
    /* araç sola döndürülür */
    digitalWrite(sag_ileri, HIGH);
    digitalWrite(sag_geri, LOW);
    digitalWrite(sol_ileri, LOW);
    digitalWrite(sol_geri, HIGH);
    analogWrite(sag_enable, 200); // motor hızları 200 PWM
    analogWrite(sol_enable, 200);
    delay(500);
  }

  else { // mesafe 20 cm den büyükse
    /* araç ileri gitsin */
    digitalWrite(sag_ileri, HIGH);
    digitalWrite(sag_geri, LOW);
    digitalWrite(sol_ileri, HIGH);
    digitalWrite(sol_geri, LOW);
    analogWrite(sag_enable, 100); // motor hızları 255 PWM
    analogWrite(sol_enable, 100);  
  }
}
