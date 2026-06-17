/*
  KeyboardAndMouseControl

  Hardware:
  - five pushbuttons attached to D12, D13, D14, D15, D0

  The mouse movement is always relative. This sketch reads four pushbuttons, and
  uses them to set the movement of the mouse.

  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the mouse commands.

  created 15 Mar 2012
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardAndMouseControl
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
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"
USBHIDMouse Mouse;
USBHIDKeyboard Keyboard;


void setup() {  // initialize the buttons' inputs:

  Serial.begin(115200);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
  USB.begin();
}

void loop() {

  Keyboard.write('u');
  Mouse.move(0, -40);
  delay(2000);
}
#endif /* ARDUINO_USB_MODE */
