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
#define ARDUINO_USB_MODE 0
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

const int buttonPin = 0;

int state = 0;              // 0=up, 1=down, 2=left, 3=right, 4=space
bool lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Keyboard.begin();
  USB.begin();
  delay(500);
}

void loop() {
  bool currentState = digitalRead(buttonPin);
  
  if (lastState == HIGH && currentState == LOW) {
    state = (state + 1) % 5;
    
    switch (state) {
      case 0: Keyboard.write(KEY_UP_ARROW);    break;
      case 1: Keyboard.write(KEY_DOWN_ARROW);  break;
      case 2: Keyboard.write(KEY_LEFT_ARROW);  break;
      case 3: Keyboard.write(KEY_RIGHT_ARROW); break;
      case 4: Keyboard.write(KEY_SPACE);       break;
    }
    
    delay(200);
  }
  
  lastState = currentState;
  delay(10);
}
#endif /* ARDUINO_USB_MODE */
