#include <Wire.h> //BIBLIOTHEQUE WIRE POUR L'ACCELEROMETRE

const int MPU_addr = 0x68;
float Acc_X, Acc_Y, Acc_Z;
float Gy_X, Gy_Y, Gy_Z;
float An_X, An_Y, An_Z;
float rad_deg=180/3.1415926535897932384626433832795;
float Tmp;

#include <SoftwareSerial.h> //BIBLIOTHEQUE BLUETOOTH
SoftwareSerial BT(11,3); //MODULE HC-05 MASTER

void setup() {
  // put your setup code here, to run once:
  //PARTIE BLUETOOTH
  Serial.begin(9600);
  Serial.println("Bonjour -Pret pour les commandes AT");
  BT.begin(38400);

  //PARTIE ACCELEROMETRE
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
  //ON RECUPERE LES DONNEES DE L'ACCELEROMETRE
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,7*2,true);
  Acc_X=(Wire.read()<<8|Wire.read())/2048;
  Acc_Y=(Wire.read()<<8|Wire.read())/2048;
  Acc_Z=(Wire.read()<<8|Wire.read())/2048;
  
  Tmp = Wire.read() << 8 | Wire.read();  
  
  Gy_X = Wire.read() << 8 | Wire.read();  
  Gy_Y = Wire.read() << 8 | Wire.read();  
  Gy_Z = Wire.read() << 8 | Wire.read(); 

  An_X=(atan((Acc_X)/sqrt(pow((Acc_Y),2)+pow((Acc_Z),2)))*rad_deg);
  An_Y=(atan((Acc_Y)/sqrt(pow((Acc_X),2)+pow((Acc_Z),2)))*rad_deg);
  An_Z=(atan((Acc_Z)/sqrt(pow((Acc_Y),2)+pow((Acc_X),2)))*rad_deg);
  
  Serial.print(" | Ax = "); Serial.print(Acc_X);
  Serial.print(" | Ay = "); Serial.print(Acc_Y);
  Serial.print(" | Az = "); Serial.println(Acc_Z);
  
  //Serial.print(" | Gy_X = "); Serial.print(Gy_X);
  //Serial.print(" | Gy_Y = "); Serial.print(Gy_Y);
  //Serial.print(" | Gy_Z = "); Serial.print(Gy_Z);

  //Serial.print(" | An_X = "); Serial.print(An_X);
  //Serial.print(" | An_Y = "); Serial.print(An_Y);
  //Serial.print(" | An_Z = "); Serial.println(An_Z);
  
  delay(500);

  //COMMUNCATION AVEC LE MODULE HC-05
  while (BT.available()) {
    if (Acc_X<90 && Acc_Y<10){
      BT.write('N'); //POSITION NEUTRE
      Serial.println('N');
    }
    else if(Acc_X<10 && Acc_Y<-10){
      BT.write('A'); //AVANCER
      Serial.println('A');
    }
    else if(Acc_X<-10 && Acc_Y<-10){
      BT.write('D'); //AVANCER DROITE
      Serial.println('D');
    }
    else if(Acc_X>10 && Acc_Y<-10){
      BT.write('G'); //AVANCER GAUCHE
      Serial.println('G');
    }
    else if(Acc_X<10 && Acc_Y>10){
      BT.write('R'); //RECULER
      Serial.println('R');
    }
     else if(Acc_X<-10 && Acc_Y>10){
      BT.write('W'); //RECULER DROITE
      Serial.println('W');
    }
     else if(Acc_X>10 && Acc_Y>10){
      BT.write('L'); //RECULER GAUCHE
      Serial.println('L');
    }
   }

   while (Serial.available()){
    Serial.print(char(BT.read())); } 

}
