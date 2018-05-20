#ifndef SLIDER_H
#define SLIDER_H
#include "Avarupt_TTP229.h"


class Slider : public Avarupt_TTP229{
public:
	Slider(float mult=2):multiplier(mult) {
		pressPosition = 0;
		currentPosition = 0;
		onPressFunction = NULL;
	}
	void Poll();
	byte getCurrentPosition() { return (byte)(fmod(currentPosition, 256)); };
	void setOnPressCallbackFunction(void(*ptr2Func)(void)) {
		onPressFunction = ptr2Func;
	};
private:
	float multiplier;
	float pressPosition;
	float currentPosition;
	void(*onPressFunction)(void);//This function pointer returns void, takes in no arguments, and is called onPressFunction

};



#endif