#include <Stepper.h> //Schrittmotor Bibliothek
#include <Servo.h> //Servo Bibliothek
Servo servoklappe; //Servo mit servoklappe ansprechen
const int stepsPerRevolution = 200; //Schritte des Steppers pro Umdrehung
int state = 0;

int richtungA           =12;  //Richtung Motor A an Pin 12
int pwmA                =3;   //Geschwindigkeit Motor A an Pin 3
int bremseA             =9;   //Bremse Motor A an Pin 9
int richtungB           =13;  //Richtung Motor B an Pin 13
int pwmB                =11;  //Geschwindigkeit Motor B an Pin 11
int bremseB             =8;   //Bremse Motor B an Pin 8
int geschwindigkeit     =255; //Maximalgeschwindigkeit

Stepper myStepper(stepsPerRevolution,12,13); //Stepper Library auf 
                                             //Pin 12 und 13 initialisieren

void setup() {
  Serial.begin(9600); //serielle Kommunikation starten
  servoklappe.attach(6); //Servo an Pin 6
  servoklappe.write(180); //Servo auf 180 Grad stellen
  pinMode(richtungA, OUTPUT);   //Richtung A als Output 
  pinMode(richtungB, OUTPUT);   //Richtung B als Output 
  pinMode(bremseA, OUTPUT);     //Bremse A als Output 
  pinMode(bremseB, OUTPUT);     //Bremse B als Output 
  pinMode(pwmA,OUTPUT); //pwmA als Output
  digitalWrite(pwmA, HIGH); //pwmA auf High setzen
  pinMode(pwmA,OUTPUT); //pwmB als Output
  digitalWrite(pwmB, HIGH); //pwmB auf High setzen
  

  myStepper.setSpeed(40); //Geschwindigkeit des Steppers festlegen
  digitalWrite(bremseA, HIGH); //Motor A aus
  digitalWrite(bremseB, HIGH); 
  }

void loop() {
  if(Serial.available()>0) //Wenn Daten empfangen werden
  {
    state=Serial.read(); //Daten auslesen
    Serial.write(state); //Status schreiben
  }
  if (state == 'x') //wenn x empfangen wird
 {
  digitalWrite(bremseA, LOW); //Motor A aus
  digitalWrite(bremseB, LOW);
  delay(1000); //Eine Sekunde warten
  myStepper.step(60); //Stepper 60 Schritte vor
  digitalWrite(bremseA, HIGH); //Motor A aus
  digitalWrite(bremseB, HIGH); 
  delay(1500); //1500ms warten
  servoklappe.write(80); //Servo auf 80 Grad
  delay(4000); //Vier Sekunden warten
  servoklappe.write(180); //Servo auf 180 Grad
  
  state = 0;
 }
 else if (state == 'y') //Wenn y empfangen wird
 {
  digitalWrite(bremseA, HIGH); //Motor aus
  digitalWrite(bremseB, HIGH);
  state=0;
 }
}
