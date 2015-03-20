#include <Servo.h>
Servo victor;
void setup()
{
  victor.attach(5);
  victor.writeMicroseconds(1510);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  Serial.begin(9600);
}

void loop()
{
  delay(5000);
  Serial.println("starting");
  digitalWrite(13,HIGH);
  victor.writeMicroseconds(870);
  delay(500);
  victor.writeMicroseconds(2140);
  delay(500);
  victor.writeMicroseconds(1510);
  digitalWrite(13,LOW);
  Serial.println("done");
  while(true){
    delay(1000);
  }
}
