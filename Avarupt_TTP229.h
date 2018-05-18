#ifndef AVARUPT_TTP229_H
#define AVARUPT_TTP229_H

#include "Arduino.h"
#include "Wire.h"

#define TTP229_LSF 0x57 // Device address (the addressing without the R/W bit) -> 01010111 = 57

class Avarupt_TTP229{
  public:
    Avarupt_TTP229(){
      aa=0;
      bb=0;
      position = 0;
	  prevPosition = 0;
	  rotaryPosition = 0;
	  wammyPosition = 0;
	  multiplier = 2;
	  Wire.begin();
    }
	
	//I need to class and objectize all of my wammy position and rotary position things
	
    byte getMostSignificantByte(){return aa;};
    byte getLeastSignificantByte(){return bb;};
	byte getRotaryPosition(){return rotaryPosition;};
    byte getWammyPosition(){return (byte)(fmod(wammyPosition,256));}; // objectize, add "max velocity" to protect against epilepsy
    double getPosition(){return position;};
	bool isTouchDetected(){return touchDetected;};
    void showByteData();
    void updateData();
  private:
    byte aa;
    byte bb;
	float multiplier;//Rename this variable to be more specific
    float position;
	byte rotaryPosition;
	float wammyPosition;
	float prevPosition;
	
	bool touchDetected;
	float pressPosition;
    void getTTP229data(byte *a, byte *b);
    void printByte (byte bytePrint);
    double calculatePosition();
};

#endif
