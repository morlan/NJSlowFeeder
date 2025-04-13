#include <Arduino.h>
#include <Button.h>

//GPIOs
const int MotorPin = 13;
const int buttonUPpin = 5;
const int buttonDOWNpin = 4; 
//motor variables

float MotorVoltage = 1.5;
float BusVoltage = 3.3;
int MotorUpdateTime = 500; //millisecond
u_long PrevUpdateTime = 0;

int setMotorVoltage(int, float, float);


//Button Variables

int buttonUPPrevState = 0; //0 = inactive, 1 = held, 2 = click
int buttonDOWNPrevState = 0; //0 = inactive, 1 = held, 2 = click
//Button configs
Button buttonUP = Button(buttonUPpin, BUTTON_PULLDOWN, true, 50);
Button buttonDOWN = Button(buttonDOWNpin, BUTTON_PULLDOWN, true, 50);
//Button Callbacks
// void onPress(Button& b){
// 	Serial.print("onPress: ");
// 	Serial.println(b.pin);
// 	//digitalWrite(13,HIGH);
// }

// void onClick(Button& b){
// 	Serial.print("onClick: ");
// 	Serial.println(b.pin);
// 	//digitalWrite(13,HIGH);
// }

void onRelease(Button& b){
	Serial.print("onRelease: ");
	Serial.println(b.pin);
	if(b.buttonstatus == 0){
    Serial.print("Click: ");
   	Serial.println(b.pin);
    b.buttonstatus = 2;
  }
  else if(b.buttonstatus == 1){
    Serial.print("HoldRelease: ");
   	Serial.println(b.pin);
    b.buttonstatus = 0;
  }
  
  else {
    Serial.print("Unhandled pin triggered - release");
    Serial.println(b.buttonstatus);
  }
}

void onHold(Button& b){
	Serial.print("Held: ");
	Serial.println(b.pin);
  b.buttonstatus = 1;
  
}

void setup() {
  //motor configs
  pinMode(13, OUTPUT);
  analogWriteFrequency(20000);
  PrevUpdateTime = millis();
  //start serial for ButtonDebug
  Serial.begin(115200);
  Serial.println("Serial Start");
  
  // Assign callback functions
  //buttonUP.pressHandler(onPress);
  //buttonUP.clickHandler(onClick);
  buttonUP.releaseHandler(onRelease);
  buttonUP.holdHandler(onHold, 1000); // must be held for at least 1000 ms to trigger

  //buttonDOWN.pressHandler(onPress);
  //buttonDOWN.clickHandler(onClick);
  buttonDOWN.releaseHandler(onRelease);
  buttonDOWN.holdHandler(onHold, 1000); // must be held for at least 1000 ms to trigger


}

void loop() {
  int updatetimebool = ((millis() - PrevUpdateTime) > MotorUpdateTime);
  
  
  buttonUP.process();
  buttonDOWN.process();
  if(buttonUP.buttonstatus == 1){
    //do hold things
    Serial.println("Doing holdUP");
    if(updatetimebool){
      MotorVoltage = constrain(MotorVoltage + 0.2, 0, BusVoltage);
      Serial.println(MotorVoltage);
      setMotorVoltage(MotorPin, BusVoltage, MotorVoltage);
    }
  }
  else if(buttonUP.buttonstatus == 2){
    //do click things
    Serial.println("Doing clickUP");
    setMotorVoltage(MotorPin, BusVoltage, MotorVoltage=1.5);
    //reset buttonUP state
    buttonUP.buttonstatus = 0;
  }

  if(buttonDOWN.buttonstatus == 1){
    //do hold things
    Serial.println("Doing hold things");
    if(updatetimebool){
      MotorVoltage = constrain(MotorVoltage - 0.2, 0, BusVoltage);
      Serial.println(MotorVoltage);
      setMotorVoltage(MotorPin, BusVoltage, MotorVoltage);
    }
  }
  else if(buttonDOWN.buttonstatus == 2){
    //do click things
    Serial.print("Doing clickDOWN");
    setMotorVoltage(MotorPin, BusVoltage, 0);
    //reset buttonUP state
    buttonDOWN.buttonstatus = 0;
  }
  
  if(updatetimebool){
    PrevUpdateTime = millis();
  }
  delay(10);
}

int setMotorVoltage(int driverPin, float BusVoltage, float MotorVoltage) {
  if(MotorVoltage > BusVoltage){return 1;}
  else{
    int setpoint = (int)((MotorVoltage / BusVoltage) * 255);
    analogWrite(driverPin, setpoint);
    return 0;
  }
}
