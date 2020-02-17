#include <Wire.h>
const int MPU_addr = 0x68;
float Acc_X, Acc_Y, Acc_Z;
float An_X, An_Y, An_Z;
float Gy_X, Gy_Y, Gy_Z;
float rad_deg=180/3.1415926535897932384626433832795;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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

  An_X=(atan((Acc_X)/sqrt(pow((Acc_Y),2)+pow((Acc_Z),2)))*rad_deg);
  An_Y=(atan((Acc_Y)/sqrt(pow((Acc_X),2)+pow((Acc_Z),2)))*rad_deg);
  An_Z=(atan((Acc_Z)/sqrt(pow((Acc_Y),2)+pow((Acc_X),2)))*rad_deg);

  
  Serial.print("Ax = "); Serial.print(Acc_X);
  Serial.print(" | Ay = "); Serial.print(Acc_Y);
  Serial.print(" | Az = "); Serial.print(Acc_Z);
  Serial.print("  An_X = "); Serial.print(An_X);
  Serial.print(" | An_Y = "); Serial.print(An_Y);
  Serial.print(" | An_Z = "); Serial.println(An_Z);
  delay(500);
}
