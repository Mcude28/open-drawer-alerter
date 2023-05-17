/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/michaelude/EE1301/IOT_project/Bunny/src/OpenDrawerAlerter.ino"
/*
 * Project Drawer Alarmer
 * Description: Alarm to stop pesky intruders from looking through items in a drawer.
 * Author: Ashley Olson, Doua Vue, Michael Ude
 * Date: 05/03/22
 * ude00003, vue00158, olso9404
 * Spring 2022
 * IOT lab final project
 */
#include "Particle.h"
#include "neopixel.h"
#include "cstdlib"
void setup();
void loop();
int turn_off_alarm(String input_string);
int Reset(String input_string);
#line 13 "/Users/michaelude/EE1301/IOT_project/Bunny/src/Bunny.ino"
enum alarm_on {
  ON,
  OFF,
};
alarm_on mode = ON;
int light_data;
int ledState = FALSE;
long unsigned int nextTime;
int PIXEL_PIN = D4;
int PIXEL_COUNT = 9;
int PIXEL_TYPE = WS2812;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
void setColor(int &red, int &green, int &blue);
void alarm(bool AlarmOn);
int speakerPin = D0;
unsigned long int  ToggleTime = 100;
bool AlarmOn = true;
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Particle.variable("alarm-on", AlarmOn);
  Particle.function("turn_off_alarm",turn_off_alarm);
  Particle.function("AlarmReset", Reset);
  strip.begin();
  Serial.begin(9600);
  noTone(speakerPin);
  pinMode(D7, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  if (mode == ON){
    noTone(speakerPin);
    light_data = analogRead(A1);
      if (millis() >= nextTime){
        ledState = !ledState;
        digitalWrite(D7, ledState);

      Serial.print("My Data is: ");
      Serial.print(light_data);
      Serial.println(";");
      nextTime += 500;
        if (light_data < 1500.0 && AlarmOn == true){//maybe make this true and prior have a function that changes the enum mode to off making the bool fales
          alarm(AlarmOn);
        }
    } 
  }

  else if (mode == OFF){
      for(int pixel =0; pixel<8; pixel++) {   
        strip.setPixelColor(pixel, strip.Color(0, 0, 0));
        strip.show();
      }
      
    }
}

void setColor(int &red, int &green, int &blue){//returns the value of the colors (random values between 0-255)
  red = rand() % 256;
  green = rand() % 256;
  blue = rand() % 256;
}
int turn_off_alarm(String input_string){//sets the mode to off and makes the variable false
    if(input_string == "off"){
      mode = OFF;
      AlarmOn = false;
    }
    return 1;
  }
  void alarm(bool AlarmOn){//this publishes to the coloud and allows the alarm to repeatedly flicker and make a noise
    unsigned long int startTime = millis();
    tone(speakerPin, 880, 0);
    while (ToggleTime < startTime && AlarmOn == true){


      for (int pixel = 0; pixel < 8; pixel++){
        int red, green, blue;
        setColor(red, green, blue);
        strip.setPixelColor(pixel, strip.Color(red, green, blue));
        strip.show();
      }

    ToggleTime+=100;

  }

  
}
int Reset(String input_string){//This allows the mode to be turned back on and the variavle to be set to true for the program to be reset by the user
  if(input_string == "on"){
    mode = ON;
    AlarmOn = true;

  }

  return 0;
}