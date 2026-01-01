#include <Wire.h>

#include <Arduino.h>

#include "Constants.hpp"
#include "functions/barometer.hpp"
#include "functions/blink.hpp"
#include "functions/eeprom.hpp"


// Use classes or structs to group related parameters together

// instead of top declaring everything as global functions
// use header files.


// try to declare less global variables. Scope your variables
// to your main looping function or in the function where they are
// needed. This ensures better readibility and maintainability



int butt = 0; // Button state

bool logLock = false;

float starttime; // General Time variable

bool logging = false; // Logging detection

void print();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(serialBaud);
  pinMode(LED, OUTPUT);
  delay(1000);
  while (!Serial) delay(100);

  led(100, 3);

  bmp_temp = bmp.getTemperatureSensor();
  bmp_pressure = bmp.getPressureSensor();
  
  unsigned status;
  status = bmp.begin();
  if (!status) {
    digitalWrite(LED, HIGH);
    while (1){
      delay(20);
    }
  } else {
    led(200, 2);
  }
bmp.setSampling(
      Adafruit_BMP280::MODE_NORMAL,
      Adafruit_BMP280::SAMPLING_X2,
      Adafruit_BMP280::SAMPLING_X4,
      Adafruit_BMP280::FILTER_X4,
      Adafruit_BMP280::STANDBY_MS_1);
  delay(500);

  altZero();

  starttime = millis(); // Initialize gtime with millis()

  adr = 4; // Initialize adr with 4

  float preVar = readFloatFromEEPROM(0);

  if (preVar != 0) {

  }     
  float dZone = millis(); //start deadzone var
  while(1){
      dZone = millis();
      if(analogRead(but)>500){
        //clearEEPROM();
        print();
        logLock = true;
        break;
      }
      else if(dZone > 60000){

            break;
      }
      delay(10);
      
  }

}
void print() {
    delay(5000);
    adr = 4;
    tadr = 8;
      while(analogRead(but) < 500) {
          tadr = adr + 4;
  
          Serial.print(readFloatFromEEPROM(tadr));
          Serial.print(", ");
          Serial.print(readFloatFromEEPROM(adr));
          Serial.print(", ");
          Serial.println(adr);
          delay(25);
          adr += 8;   
          led(20, 1); 
     }
}
// Don't have void functions that work on global variables
// Use parameters and return values instead
// This makes your code easier to understand and maintain
// if this is your main loop, label it as such
void loop() { //main 
  // if your main loop function has its own delay, in a sub-function this 
  // wrecks your iteration rate. Fix this

  float curtime = millis();// finds current time stamp from power on in ms
  float elapsed = (curtime - starttime) / 1000.0; //subtract current time from start time in ms and convert to s
  tadr = adr + 4;// ensure timestamp address is offset
  float filtAlt = altRead(zero);
  if (!logLock) {
    writeFloatToEEPROM(adr, filtAlt); // write
    delay(10); //delay bc idk tbh
    writeFloatToEEPROM(tadr, elapsed);
  }


  Serial.print(readFloatFromEEPROM(tadr));
  Serial.print(", ");
  Serial.print(adr);
  delay(10);
  Serial.print(", ");
  Serial.println(readFloatFromEEPROM(adr));
  // Serial.print(", ");
  // Serial.println(filtAlt);

  if (analogRead(but) > 500) {
    //clearEEPROM();
  }

  adr += 8; //add 8 bytes to compensate for timestamp
  led(20, 1); // flash LED 
}