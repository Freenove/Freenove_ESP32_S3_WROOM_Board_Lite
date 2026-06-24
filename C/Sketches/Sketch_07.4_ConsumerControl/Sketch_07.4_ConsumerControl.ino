#define ARDUINO_USB_MODE 0
#ifndef ARDUINO_USB_MODE
#error This ESP32 SoC has no Native USB interface
#elif ARDUINO_USB_MODE == 1
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include "USB.h"
#include "USBHIDConsumerControl.h"
USBHIDConsumerControl ConsumerControl;

const int buttonPin = 0;

int state = 0;  // 0=vol+, 1=vol-, 2=bright+, 3=bright-
bool lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  ConsumerControl.begin();
  USB.begin();
  delay(500);
}

void loop() {
  bool currentState = digitalRead(buttonPin);
  
  if (lastState == HIGH && currentState == LOW) {
    state = (state + 1) % 4;
    
    switch (state) {
      case 0: ConsumerControl.press(CONSUMER_CONTROL_VOLUME_INCREMENT); break;
      case 1: ConsumerControl.press(CONSUMER_CONTROL_VOLUME_DECREMENT); break;
      case 2: ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_INCREMENT); break;
      case 3: ConsumerControl.press(CONSUMER_CONTROL_BRIGHTNESS_DECREMENT); break;
    }
    ConsumerControl.release();
    
    delay(200);
  }
  
  lastState = currentState;
  delay(10);
}
#endif /* ARDUINO_USB_MODE */
