int value;
const int rf = 0;
const int led = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogWrite(led,255);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(rf);
  Serial.println(value);
  if (500<value<650){
      analogWrite(led,0);
  }
  if (value>650){
      analogWrite(led,255);
  }
  if (value<500){
      analogWrite(led,120); 
  }
}
