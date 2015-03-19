#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(9600);
}

double speed = 12345;
double term = 65432.0;
void loop(){
  delay(500);

  //test speed setting
  Wire.beginTransmission(1);
  Wire.write(0); // inform the controller that we are setting speed
  Wire.write((byte *)&speed, sizeof(double));
  Wire.endTransmission();
  speed++;

  delay(10);

  for(int i = 1; i < 4; ++i){
    Wire.beginTransmission(1);
    Wire.write(i); // pterm
    Wire.write((byte *)&term, sizeof(double));
    Wire.endTransmission();
    term-= 1.0;
  }
  
}
