#include <Arduino.h>

float MotorVoltage = 1.5;
float BusVoltage = 3.3;

// put function declarations here:
int myFunction(int, int);
int setMotorVoltage(int, float, float);

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  setMotorVoltage(13, BusVoltage, MotorVoltage);
  if(MotorVoltage >= 2.5){ MotorVoltage = 0.2;}
  else{
    MotorVoltage += 0.1;
  }
  delay(1000);
}

int setMotorVoltage(int driverPin, float BusVoltage, float MotorVoltage) {
  if(MotorVoltage > BusVoltage){return 1;}
  else{
    int setpoint = (int)((MotorVoltage / BusVoltage) * 255);
    analogWrite(driverPin, setpoint);
    return 0;
  }
}
