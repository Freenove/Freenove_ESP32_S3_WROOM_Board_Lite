/*
  ButtonMouseControl

  Controls the mouse from five pushbuttons on an Arduino Leonardo, Micro or Due.

  Hardware:
  - five pushbuttons attached to D12, D13, D14, D15, D0

  The mouse movement is always relative. This sketch reads four pushbuttons,
  and uses them to set the movement of the mouse.

  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the mouse commands.

  created 15 Mar 2012
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ButtonMouseControl
*/
#ifndef ARDUINO_USB_MODE
#error This ESP32 SoC has no Native USB interface
#elif ARDUINO_USB_MODE == 1
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include "USB.h"
#include "USBHIDMouse.h"
USBHIDMouse Mouse;

const int buttonPin = 0;
int range = 5000;

int state = 0;              // 0=up, 1=down, 2=left, 3=right, 4=right-click
bool lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Mouse.begin();
  USB.begin();
  delay(500);  // wait for USB to initialize
}

void loop() {
  bool currentState = digitalRead(buttonPin);
  
  // detect falling edge (button press)
  if (lastState == HIGH && currentState == LOW) {
    state = (state + 1) % 5;
    
    switch (state) {
      case 0: Mouse.move(0, -range); break;  // up
      case 1: Mouse.move(0,  range); break;  // down
      case 2: Mouse.move(-range, 0); break;  // left
      case 3: Mouse.move(range, 0); break;   // right
      case 4: Mouse.click(MOUSE_RIGHT); break; // right-click
    }
    
    delay(200);  // debounce
  }
  
  lastState = currentState;
  delay(10);
}
#endif
