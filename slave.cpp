#include <Keypad.h> //Keypad Bibliothek einbinden
int state=0;
char P1='1';char P2='2';char P3='3';char P4='4'; //Zahlen des Codes eingeben
char C1,C2,C3,C4; //Code wird gespeichert
const byte COLS=4; //4 Spalten
const byte ROWS=4; //4 Reihen
int z1=0,z2,z3,z4; //Variablen zum Freischalten des Codes
char hexakeys[ROWS][COLS]={
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'}, 
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
  }; 

byte colPins[COLS]={2,3,4,5};  //Definition der Pins für die 4 Spalten
byte rowPins[ROWS]={6,7,8,9};  //Definition der Pins für die 4 Reihen

char Taste; //Variable für die gedrückte taste

Keypad mykeypad=Keypad(makeKeymap(hexakeys),rowPins, colPins,ROWS,COLS); //keypad wird mit mykeypad angesprochen

void setup() {
  Serial.begin(9600); //Beginn serielle Kommunikation
  }

void loop() {
  if(Serial.available()>0){ //Wenn Daten empfangen werden
  state=Serial.read(); //Daten auslesen
 }
  Anfang: // Hierher wird mit goto gesprungen
Taste = mykeypad.getKey(); //gedrückte Taste auslesen
if (Taste) //Wenn eine Taste gedrückt wurde...
 
 {
  if (Taste=='*') // Wenn die "*" Taste gedrückt wurde ist der Automat gesperrt
   {
   delay(3000); //Drei Sekunden warten
   
   z1=0; z2=1; z3=1; z4=1; // Zugang zur ersten Zeicheneingabe freischalten
   goto Anfang;
   }
   if (Taste=='#') // Wenn die Rautetaste gedrückt wurde...
   {
   if (C1==P1&&C2==P2&&C3==P3&&C4==P4) //Eingegebenen Code überprüfen
   {
   Serial.write('x'); //Wenn Code richtig, x Senden
   }
   else // ist das nicht der Fall...
   {
   
   Serial.write('y'); //y senden
   
   z1=0; z2=1; z3=1; z4=1; // Der Zugang für die erste Zeicheneingabe wird wieder freigeschaltet
   goto Anfang; 
   }
  }
// Ab hier werden die Zeichen an der richtigen Position gespeichert
  if (z1==0) // Wenn das erste Zeichen noch nicht gespeichert wurde...
  {
  C1=Taste; 
  z1=1; z2=0; z3=1; z4=1; // Zugang zur zweiten Zeicheneingabe freischalten
  goto Anfang;
  }
 
  if (z2==0) // Wenn das zweite Zeichen noch nicht gespeichert wurde...
  {
  C2=Taste; 
  z1=1; z2=1; z3=0; z4=1; // Zugang zur dritten Zeicheneingabe freischalten
  goto Anfang;
  }

  if (z3==0) // Wenn das dritte Zeichen noch nicht gespeichert wurde...
  {
  C3=Taste; 
  z1=1; z2=1; z3=1; z4=0; // Zugang zur vierten Zeicheneingabe freischalten
  goto Anfang;
  }
  
  if (z4==0) // Wenn das vierte Zeichen noch nicht gespeichert wurde...
  {
  C4=Taste; 
  z1=1; z2=1; z3=1; z4=1; // Zugang zur weiteren Zeicheneingabe sperren
  
  }
 }
  }
