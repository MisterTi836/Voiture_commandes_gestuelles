#include <SoftwareSerial.h>
SoftwareSerial BT(11,3); //MODULE HC-06 SLAVE
int ENA=9;
int ENB=10;
int IN1=4;
int IN2=5;
int IN3=6;
int IN4=7;
char dir;
float i;
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
    dir=BT.read();
     if (dir=='N'){ //HC06 LIT POSITION NEUTRE
      for(i=255; i<0;i-=10){
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       analogWrite(ENA,i);
       analogWrite(ENB,i);
      }
     }
     else if (dir=='A'){ //HC06 LIT AVANCER
      for(i=0; i<256;i+=10){
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       analogWrite(ENA,i);
       analogWrite(ENB,i);
      }
     }
     else if (dir=='D'){ //HC06 LIT AVANCER DROITE
      for(i=0; i<0;i+=10){
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       analogWrite(ENA,i);
       analogWrite(ENB,i-145);
      }
     }
     else if (dir=='G'){ //HC06 LIT AVANCER GAUCHE
      for(i=0; i<0;i+=10){
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       analogWrite(ENA,i-145);
       analogWrite(ENB,i);
      }
     }
     else if (dir=='R'){ //HC06 LIT RECULER
      for(i=0; i<0;i+=10){
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       analogWrite(ENA,i);
       analogWrite(ENB,i);
      }
     }
     else if (dir=='L'){ //HC06 LIT RECULER GAUCHE
      for(i=0; i<0;i+=10){
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       analogWrite(ENA,i-145);
       analogWrite(ENB,i);
      }
     }
     else if (dir=='W'){ //HC06 LIT RECULER DROITE
      for(i=0; i<0;i+=10){
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       analogWrite(ENA,i);
       analogWrite(ENB,i-145);
      }
   } 
 }

 while (Serial.available()){
  BT.write(char(Serial.read()));
 }
 
}
