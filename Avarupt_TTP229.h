#ifndef AVARUPT_TTP229_H
#define AVARUPT_TTP229_H

#include "Arduino.h"
#include "Wire.h"
//#include "Bender.h"

#define TTP229_LSF 0x57 // Device address (the addressing without the R/W bit) -> 01010111 = 57
#define LONG_PRESS_MILLI_THRESHOLD 500
#define LONG_PRESS_DISTANCE_THRESHOLD 7
#define DOUBLE_PRESS_MILLIS 300
#define SWIPE_MILLI_THRESHOLD 400

class Avarupt_TTP229{
  public:
    Avarupt_TTP229(){
      aa=0;
      bb=0;
      position = 0;
	  prevPosition = 0;
	  rotaryPosition = 0;
	  multiplier = 2;
	  Wire.begin();
	  touchDetected = 0;
	  onPressFunction = NULL;
	  totalDistance = 0;
	  touchMillis = 0;
	  longTouchDetected = 0;
	  pressDetected = 0;
	  swipeDetected = 0;
	  canDoublePress = false;
	  previousPressTimestamp = 0;
    }
	
    byte getMostSignificantByte(){return aa;};
    byte getLeastSignificantByte(){return bb;};
    double getPosition(){return position;};
	bool isTouchDetected(){return touchDetected;};
    void showByteData();
	void setOnTouch(void(*ptr2Func)(void)) {
		onTouchFunction = ptr2Func;
	};
	void setOnPress(void(*ptr2Func)(void)) {
		onPressFunction = ptr2Func;
	};
	void setOnLongPress(void(*ptr2Func)(void)) {
		onLongPressFunction = ptr2Func;
	};
	void setOnSwipe(void(*ptr2Func)(void)) {
		onSwipeFunction = ptr2Func;
	};
	void setOnRelease(void(*ptr2Func)(void)) {
		onReleaseFunction = ptr2Func;
	};
	void setOnDoublePress(void(*ptr2Func)(void)) {
		onDoublePressFunction = ptr2Func;
	};
protected:
    void updateData();
  private:
    byte aa;
    byte bb;
	float prevPosition;//DO NOT DELETE
	bool touchDetected, longTouchDetected, swipeDetected,pressDetected, canDoublePress;
	
	float totalDistance;
	unsigned long touchMillis;
	unsigned long previousPressTimestamp;
	
	float multiplier;//delete
    float position;
	byte rotaryPosition;//delete
	
    void getTTP229data(byte *a, byte *b);
    void printByte (byte bytePrint);
    double calculatePosition();

	void(*onTouchFunction)(void);//This function pointer returns void, takes in no arguments, and is called onPressFunction
	void(*onPressFunction)(void);//This function pointer returns void, takes in no arguments, and is called onPressFunction
	void(*onLongPressFunction)(void);//This function pointer returns void, takes in no arguments, and is called onPressFunction
	void(*onSwipeFunction)(void);//This function pointer returns void, takes in no arguments, and is called onPressFunction
	void(*onReleaseFunction)(void);//This function pointer returns void, takes in no arguments, and is called onPressFunction
	void(*onDoublePressFunction)(void);//This function pointer returns void, takes in no arguments, and is called onPressFunction
};

#endif
