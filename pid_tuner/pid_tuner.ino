#import <Wire.h>
#import <stdlib.h>
void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

char address = 1;

double pterm = 0;
double iterm = 0;
double dterm = 0;
double speed = 0;

long last_update = 0;
void loop()
{
  switch(Serial.read()){
  case 'P':
    update_tuning(&pterm);
    break;
  case 'I':
    update_tuning(&iterm);
    break;
  case 'D':
    update_tuning(&dterm);
    break;
  case 'S':
    update_tuning(&speed);
    break;
  case 'T':
    if(address == 1){
      address = 2;
    } else {
      address = 1;
    }
    Serial.print("New Address: ");
    Serial.println(address);
    break;
  case ' ':
    Wire.beginTransmission(address);
    Wire.write(5); //ESTOP
    Wire.endTransmission();
    Serial.println("****ESTOP****");
  }
  Wire.beginTransmission(address);
  Wire.write(6);
  Wire.endTransmission();
  delay(10);
}
void update_tuning(double * target){
  char buffer[100];
  int buffer_index = 0;
  while(buffer_index < 100){
    while(!Serial.available()){
      Wire.beginTransmission(address);
      Wire.write(6);
      Wire.endTransmission();
      delay(10);
    }
    buffer[buffer_index] = Serial.read();
    if(buffer[buffer_index] == '$'){
      break;
    }
    ++buffer_index;

  }
  if(buffer_index != 100){
    buffer[buffer_index] = 0;
    double parse_out = strtod(buffer, NULL);
    *target = parse_out;
  }
  Serial.print("Got: ");
  Serial.print(*target);
  Wire.beginTransmission(address);
  if(target == &pterm){
    Wire.write(1);
    Serial.println(" pterm");
  }
  if(target == &iterm){
    Wire.write(2);
    Serial.println(" iterm");
  }
  if(target == &dterm){
    Wire.write(3);
    Serial.println(" dterm");
  }
  if(target == &speed){
    Wire.write(0);
    Serial.println(" speed");
  }
  Wire.write((byte *)target, 4);
  Wire.endTransmission();
}
