#include <SoftwareSerial.h>
SoftwareSerial BT(11,3); //MODULE HC-06 SLAVE
int ENA=9;
int ENB=10;
int IN1=4;
int IN2=5;
int IN3=6;
int IN4=7;
char dir;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ENA,OUTPUT); // Configurer
  pinMode(ENB,OUTPUT); // les broches
  pinMode(IN1,OUTPUT); // comme sortie
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  BT.begin(9600);
  delay(500);
  
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner
  digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (BT.available()) {
    dir=char(BT.read());
     if (dir=='N'){ //HC06 LIT POSITION NEUTRE
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       analogWrite(ENA,0);
       analogWrite(ENB,0);
     }
     else if (dir=='A'){ //HC06 LIT AVANCER
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       analogWrite(ENA,255);
       analogWrite(ENB,255);
     }
     else if (dir=='D'){ //HC06 LIT AVANCER DROITE
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       analogWrite(ENA,255);
       analogWrite(ENB,100);
     }
     else if (dir=='G'){ //HC06 LIT AVANCER GAUCHE
       digitalWrite(IN1,LOW);
       digitalWrite(IN1,HIGH);
       digitalWrite(IN1,HIGH);
       digitalWrite(IN1,LOW);
       analogWrite(ENA,100);
       analogWrite(ENB,255);
     }
     else if (dir=='R'){ //HC06 LIT RECULER
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       analogWrite(ENA,255);
       analogWrite(ENB,255);
     }
     else if (dir=='L'){ //HC06 LIT RECULER GAUCHE
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       analogWrite(ENA,100);
       analogWrite(ENB,255);
     }
     else if (dir=='W'){ //HC06 LIT RECULER DROITE
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       analogWrite(ENA,255);
       analogWrite(ENB,100);
   } 
 }

 while (Serial.available()){
  BT.write(char(Serial.read()));
 }
 
}
