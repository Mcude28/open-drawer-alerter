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

enum alarm_on {//this allows us to have on mode or off mode where we can have a function change one variavle and the it'll go through a different set of code for our device to work
  ON,
  OFF,
};
/*these intializaitons allow us to automatically turn the alarm on with the mode being set to ON,
however, if the mode were to turn off, these intialztions would be changed to allow the alarm to stop
blaring.
*/
alarm_on mode = ON;

int light_data;
int ledState = FALSE;
bool AlarmOn = true;
void alarm (bool AlarmOn);
/*The set of the following intializtions initalizes the lights and the pins 
on our circuit ot the type, amount, and where the voltage is going to be outputted
*/
int PIXEL_PIN = D4;
int PIXEL_COUNT = 8;
int PIXEL_TYPE = WS2812;
Adafruit_NeoPixel strip = Adafruit_NeoPixel (PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
void setColor (int &red, int &green, int &blue);

int speakerPin = D0;//initalizes where the voltage on the speakier is comming from
long unsigned int nextTime;//timers
unsigned long int  ToggleTime = 100;

// setup() runs once, when the device is first turned on.
void setup () {
  // Put initialization like pinMode and begin functions here.
  Particle.variable ("alarm-on", AlarmOn);//variable to communicate to the cloud weather the alarm is on or off
  Particle.function ("turn_off_alarm",turn_off_alarm);//this is how the IFTTT will turn off the alarm through a button
  Particle.function ("AlarmReset", Reset);//this allows the IFTTT to reset the alarm and turn it back on when the conditions are met

  strip.begin ();

  Serial.begin (9600);
  noTone (speakerPin);//funciton to set up the speaker
  pinMode (D7, OUTPUT);//this reads the loop and makes the sound how we want it
  nextTime = millis () + 1000;
}

// loop() runs over and over again, as quickly as it can execute.
void loop () {
  // The core of your code will likely live here.
  if (mode == ON){
    noTone (speakerPin);
    light_data = analogRead (A1);

    if (millis () >= nextTime) {
      ledState =!ledState;
      digitalWrite (D7, ledState);//this allows us to show that the code is running through the photon allowing the test light to flash

      Serial.print ("My Data is: ");
      Serial.print (light_data);//with this we can test to see how the light is being read in the terminal
      Serial.println (";");
      nextTime += 500;

      if (light_data < 1500.0 && AlarmOn == true) {
        alarm (AlarmOn);//send us to the funtion that allows the light to turn on and the alarm to go off
      }
    } 
  }

  else if (mode == OFF) {
    for (int pixel = 0; pixel < PIXEL_COUNT; pixel++) {   //this will set each of the lights to turn off and stops it from from going through the loop and setting off the alarm
      strip.setPixelColor (pixel, strip.Color(0, 0, 0));
      strip.show ();
    }    
  }
}

void setColor (int &red, int &green, int &blue) {    //returns the value of the colors (random values between 0-255)
  red = rand () % 256;
  green = rand () % 256;
  blue = rand () % 256;
}

int turn_off_alarm(String input_string) {   //sets the mode to off and makes the variable false
    if (input_string == "off") {
      mode = OFF;
      AlarmOn = false;
    }

    return 1;
  }

  void alarm (bool AlarmOn) {    //this publishes to the coloud and allows the alarm to repeatedly flicker and make a noise
    unsigned long int startTime = millis ();
    tone (speakerPin, 880, 0);// assigns the place where the voltage comes from, hertz, and duration

    while (ToggleTime < startTime && AlarmOn == true) {//this is the portion that sets each of the lights to the random values
      for (int pixel = 0; pixel < PIXEL_COUNT; pixel++) {
        int red, green, blue;
        setColor (red, green, blue);
        strip.setPixelColor (pixel, strip.Color(red, green, blue));
        strip.show ();
      }

    ToggleTime += 100;
  }
}

int Reset (String input_string) {    //This allows the mode to be turned back on and the variavle to be set to true for the program to be reset by the user
  if (input_string == "on") {
    mode = ON;
    AlarmOn = true;
  }

  return 0;
}