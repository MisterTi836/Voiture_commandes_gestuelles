#include <SoftwareSerial.h>
SoftwareSerial BlueT(11,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  BlueT.begin(9600);
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (BlueT.available()) {
  Serial.print(char(BlueT.read())); }
  while (Serial.available()) {
  BlueT.write(char(Serial.read())); }

  

}
