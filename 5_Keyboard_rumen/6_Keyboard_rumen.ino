/*
  Keyboard test

  Reads a byte from the serial port, sends a keystroke back.
  The sent keystroke is one higher than what's received, e.g. if you send a,
  you get b, send A you get B, and so forth.

  The circuit:
  - none

  created 21 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardSerial
*/
#include <Arduino.h>
#ifndef ARDUINO_USB_MODE
#error This ESP32 SoC has no Native USB interface
#elif ARDUINO_USB_MODE == 1
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

void setup() {
  // open the serial port:
  Serial.begin(115200);
  // initialize control over the keyboard:
  Keyboard.begin();
  USB.begin();
}

void loop() {

  //按键
  Keyboard.print("hello");
  delay(1000); 

  //回车
  Keyboard.write(KEY_RETURN);
  delay(1000); 
    //组合键
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('v');
  delay(100);
  Keyboard.releaseAll();
  delay(2000);

}
#endif /* ARDUINO_USB_MODE */
