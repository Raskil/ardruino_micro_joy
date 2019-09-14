#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  4, 0,                  // Button Count, Hat Switch Count
  false, false, false,   // No X, Y and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

unsigned long refrehRate = 15; // The refresh Rate between sonsor chekking in ms.
                               // lower value means faster refresh.

// reversebutton state inverts the signal processing (signal means no button is pressed
// no signal means button is pressed).                               
int reverseButtonState[4] = {false, true, false, false};

// if debug is true, the device will send the button information to the serial port
// can be viewed with the serial monitor in arduino IDE.
bool debugMode = false;
String debugMessage = "";

const int pinToButtonMap = 9; // Constant that maps the phyical pin to the joystick button. a value of 0 for example
                                // Means button 0 is wired to PIN 9, button 1 to PIN 10, etc.

int lastButtonState[4] = {0,0,0,0};

void setup() {
  if(debugMode)
  {
     Serial.begin(9600);
  }
  
  // Initialize Button Pins
  pinMode(pinToButtonMap, INPUT_PULLUP);
  pinMode(pinToButtonMap + 1, INPUT_PULLUP);
  pinMode(pinToButtonMap + 2, INPUT_PULLUP);
  pinMode(pinToButtonMap + 3, INPUT_PULLUP);

  Joystick.begin();

}


void loop() {
   // Read pin values
  for (int index = 0; index < 4; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (reverseButtonState[index]) 
    {
      currentButtonState = !currentButtonState;
    }
    if(debugMode)
    {
     debugMessage = "";
     debugMessage = "BtnNr.:" + (String)index;
     debugMessage = debugMessage + " State: ";
     debugMessage = debugMessage + (String)currentButtonState;
     debugMessage = debugMessage + "\r\n";
     Serial.print(debugMessage);
    }
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(refrehRate);
}
