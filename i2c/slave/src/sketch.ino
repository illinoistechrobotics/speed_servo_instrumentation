#include <Wire.h>
#define ADDRESS_PIN 13

void receive(int incoming);
void writeVoltage();
void setParam(int incoming, volatile double * dest);
void setParam(int incoming, volatile int * dest);

volatile int test_int = 0;
volatile double test_double = 0;

void setup(){
  pinMode(ADDRESS_PIN, INPUT);
  Serial.begin(9600);
  int address = 1;
  Serial.print("Address: ");
  Serial.println(address);
  Wire.begin(address);
  Wire.onReceive(receive);
  Wire.onRequest(writeVoltage);
}

void loop(){
  delay(100);
  Serial.print(test_int,BIN);
  Serial.print('\t');
  Serial.println(test_double);
}

void receive(int incoming){
  if(incoming == sizeof(int)){
    test_int = Wire.read() + (Wire.read() << 8);
  }
  if(incoming == sizeof(double)){
    byte buff[4];
    for(int i = 0; i<sizeof(double); ++i){
      buff[i] = Wire.read();
    }
    test_double = *((double*)(buff));
  }
}

void writeVoltage(){
  Wire.write(analogRead(A0));
}
