#include <SoftwareSerial.h>
const int RX = 11;
const int TX = 3;
SoftwareSerial BlueT(RX,TX);
char data;
int x=0;
int y=0;
// Moteur gauche
int ENA=9;
int IN1=4;
int IN2=5;
int PMWG=0;

// Moteur Droite
int ENB=10;
int IN3=6;
int IN4=7;
int PMWD=0;

bool etat=0;
int i=0;
int dir=1;//0=gauche,1=tt droit,2=droite
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  BlueT.begin(9600);
  delay(500);
  //Moteur
  pinMode(ENA,OUTPUT); // Configurer
  pinMode(ENB,OUTPUT); // les broches
  pinMode(IN1,OUTPUT); // comme sortie
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner
  digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner
  // Direction du Moteur A
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  // Direction du Moteur B
  // NB: en sens inverse du moteur
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (BlueT.available()){
    data = BlueT.read();
    x = BlueT.parseInt();
    if (x<255){
      dir = 0;
    }
    else if (x>255){
       dir=2;
    }
    else{
      dir=1;
    }
    data =BlueT.read();
    y=BlueT.parseInt();
    if (y>255 && dir==0){
      PMWG=-y+x;
      PMWD=255-y;
      etat=1; 
    }
    else if (y>255 && dir==2){
      PMWG=255-y;
      PMWD=511-y-x;
      etat=1;
    }
    else if (y>255 && dir==1){
      PMWG=y-256;
      PMWD=y-256;
      etat=1;
    }
    else if (y<255 && dir==0){
      PMWG=y-511+x;
      PMWD=y-256; 
      etat=0;
    }
    else if (y<255 && dir==2) {
      PMWG=y-256;
      PMWD=y-x;
      etat=0;
    }
    else if (y<255 && dir==1){
      PMWG=255-y;
      PMWD=255-y;
      etat=0;
    }
    else if (y==255||y==256){
      PMWD=0;
      PMWG=0;
    }
    else{
      Serial.println("Rien ne va");
    }
    PMWG*=0.5;
    PMWD*=0.5;
    digitalWrite(IN1,not etat);
    digitalWrite(IN2,etat);
    digitalWrite(IN4,not etat);
    digitalWrite(IN3,etat);
    Serial.println(etat);
    Serial.println(dir);
    Serial.println(PMWG);
    Serial.println(PMWD);
    analogWrite(ENA,PMWG);
    analogWrite(ENB,PMWD);
    Serial.println(y);
  }
}
