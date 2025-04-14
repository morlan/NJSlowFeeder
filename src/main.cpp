#include <Arduino.h>
#include <Button.h> //uh, buttons
#include "driver/rtc_io.h" //deepsleep

//GPIOs
const int MotorPin = 13;
const int buttonUPpin = 5;
const int buttonDOWNpin = 4; 

//deepsleep/wake defines, using EXT0 cause internal pullup power domain is needed.
#define BUTTON_PIN_BITMASK(GPIO) (1ULL << GPIO)  // 2 ^ GPIO_NUMBER in hex
#define WAKEUP_GPIO              GPIO_NUM_5     // Only RTC IO are allowed

//motor variables
float MotorVoltage = 1.5;
float BusVoltage = 3.3;
int MotorUpdateTime = 500; //millisecond
int setMotorVoltage(int, float, float);

//Loop/Sleep Variables
u_long PrevUpdateTime = 0;
u_long SleepTimeoutTracker = 0;
int SleepTimeoutTime = 60000; //milliseconds


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

//deepsleep related
/*
  Method to print the reason by which ESP32
  has been awaken from sleep
*/
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:     Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1:     Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER:    Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP:      Serial.println("Wakeup caused by ULP program"); break;
    default:                        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

void setup() {
  //motor configs
  pinMode(13, OUTPUT);
  analogWriteFrequency(20000);
  
  //start serial for ButtonDebug
  Serial.begin(115200);
  Serial.println("Serial Start");

  print_wakeup_reason();

  // Assign callback functions
  //buttonUP.pressHandler(onPress);
  //buttonUP.clickHandler(onClick);
  buttonUP.releaseHandler(onRelease);
  buttonUP.holdHandler(onHold, 1000); // must be held for at least 1000 ms to trigger

  //buttonDOWN.pressHandler(onPress);
  //buttonDOWN.clickHandler(onClick);
  buttonDOWN.releaseHandler(onRelease);
  buttonDOWN.holdHandler(onHold, 1000); // must be held for at least 1000 ms to trigger

  PrevUpdateTime = millis();
  SleepTimeoutTracker = PrevUpdateTime;

}

void loop() {
  int updatetimebool = ((millis() - PrevUpdateTime) > MotorUpdateTime);
  if((millis() - SleepTimeoutTracker) > SleepTimeoutTime){
      //begin going to sleep :)
      esp_sleep_enable_ext0_wakeup(WAKEUP_GPIO, 1);  //1 = High, 0 = Low
      // Configure pullup/downs via RTCIO to tie wakeup pins to inactive level during deepsleep.
      rtc_gpio_pullup_dis(WAKEUP_GPIO);
      rtc_gpio_pulldown_en(WAKEUP_GPIO);
      Serial.println("Going to sleep now");
      esp_deep_sleep_start();
      Serial.println("If you see this, no you didn't");
  }
  
  buttonUP.process();
  buttonDOWN.process();
  if(buttonUP.buttonstatus != 0 || buttonDOWN.buttonstatus != 0){ SleepTimeoutTracker = millis();} //delay sleep
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
    setMotorVoltage(MotorPin, BusVoltage, MotorVoltage=2.1);
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
