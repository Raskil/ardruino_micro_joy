#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  4, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // No X, Y and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

unsigned long refrehRate = 50; // The refresh Rate between sonsor chekking in ms.
int reverseButtonState[4] = {false, true, false, false};
// Last state of the button
int lastButtonState[4] = {0,0,0,0};

void setup() {
  // Initialize Button Pins
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  Joystick.begin();
  }

// Constant that maps the phyical pin to the joystick button. Means button 0 is wired to PIN 9, button 1 to PIN 10, etc.
const int pinToButtonMap = 9;


void loop() {
  // Read pin values
  for (int index = 0; index < 4; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (reverseButtonState[index]) 
    {
      currentButtonState = !currentButtonState;
    }
    //String debugMessage = "BtnNr." + index;
    //debugMessage = debugMessage + " State: ";
    //debugMessage = debugMessage + currentButtonState;
    //Serial.print(debugMessage);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(refrehRate);
}
