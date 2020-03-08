//Programme pour la voiture dans les 6 directions + le programme avec la voiture retournée + les mouvements optionnels
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial BT(11,3); //MODULE HC-06 SLAVE
//Ports moteur
int ENA=9;
int ENB=10;
int IN1=4;
int IN2=5;
int IN3=6;
int IN4=7;
char dir;
float i;
//Variable accéléromètre
const int MPU_addr = 0x68;
float Acc_X, Acc_Y, Acc_Z;
float An_X, An_Y, An_Z;
float rad_deg=180/3.1415926535897932384626433832795;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Configuration ports moteur
  pinMode(ENA,OUTPUT); // Configurer
  pinMode(ENB,OUTPUT); // les broches
  pinMode(IN1,OUTPUT); // comme sortie
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  //Bluetooth
  BT.begin(38400);
  delay(500);
  //Initialisation sens moteur
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner
  digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //Accéléromètre
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Wire.beginTransmission(0x68);
  Wire.write(0x1c);
  Wire.write(B00000000);
  Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,7*2,true);
  Acc_X=(Wire.read()<<8|Wire.read())/2048;
  Acc_Y=(Wire.read()<<8|Wire.read())/2048;
  Acc_Z=(Wire.read()<<8|Wire.read())/2048;
  
  //An_X=(atan((Acc_X)/sqrt(pow((Acc_Y),2)+pow((Acc_Z),2)))*rad_deg);
  //An_Y=(atan((Acc_Y)/sqrt(pow((Acc_X),2)+pow((Acc_Z),2)))*rad_deg);
  An_Z=(atan((Acc_Z)/sqrt(pow((Acc_Y),2)+pow((Acc_X),2)))*rad_deg);
  while (BT.available()) {
     dir=BT.read();
     if (An_Z>0){
       if (dir=='N'){ //HC06 LIT POSITION NEUTRE
        for(i=255; i>0;i-=10){
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
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,LOW);
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,i);
         analogWrite(ENB,i-145);
        }
       }
       else if (dir=='G'){ //HC06 LIT AVANCER GAUCHE
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,LOW);
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,i-145);
         analogWrite(ENB,i);
        }
       }
       else if (dir=='R'){ //HC06 LIT RECULER
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,HIGH);
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,i);
         analogWrite(ENB,i);
        }
       }
       else if (dir=='L'){ //HC06 LIT RECULER GAUCHE
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,HIGH);
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,i-145);
         analogWrite(ENB,i);
        }
       }
       else if (dir=='W'){ //HC06 LIT RECULER DROITE
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,HIGH);
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,i);
         analogWrite(ENB,i-145);
        }
       } 
    }
    else if (An_Z<=0){
      if (dir=='N'){ //HC06 LIT POSITION NEUTRE
        for(i=255; i>0;i-=10){
         digitalWrite(IN1,HIGH);
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,i);
         analogWrite(ENB,i);
        }
       }
       else if (dir=='A'){ //HC06 LIT AVANCER
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,HIGH);
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,i);
         analogWrite(ENB,i);
        }
       }
       else if (dir=='G'){ //HC06 LIT AVANCER GAUCHE
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,HIGH);
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,i);
         analogWrite(ENB,i-145);
        }
       }
       else if (dir=='D'){ //HC06 LIT AVANCER DROITE
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,HIGH);
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,i-145);
         analogWrite(ENB,i);
        }
       }
       else if (dir=='R'){ //HC06 LIT RECULER
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,LOW);
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,i);
         analogWrite(ENB,i);
        }
       }
       else if (dir=='L'){ //HC06 LIT RECULER GAUCHE
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,LOW);
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,i-145);
         analogWrite(ENB,i);
        }
       }
       else if (dir=='W'){ //HC06 LIT RECULER DROITE
        for(i=0; i<256;i+=10){
         digitalWrite(IN1,LOW);
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,i);
         analogWrite(ENB,i-145);
        }
       }
    }
    if (dir=='F'){
      for(i=0; i<256 ; i+=10){
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        analogWrite(ENA,i);
        analogWrite(ENB,i);
      }
      delay(1500);
    }

} 
}
