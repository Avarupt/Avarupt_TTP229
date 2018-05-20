#ifndef SLIDER_H
#define SLIDER_H
#include "Avarupt_TTP229.h"


class Slider : public Avarupt_TTP229{
public:
	Slider(float mult = 8, bool longPressChangeMultiplier = true, float longPressMultiplier=.2) :multiplier(mult),longPressChangeSensitivity(longPressChangeMultiplier), changedMultiplier(longPressChangeMultiplier) {
		currentPosition = 0;

	}
	void Poll();
	byte getCurrentPosition() {
		return round(currentPosition);
	};
private:
	float multiplier;
	float changedMultiplier;
	bool longPressChangeSensitivity;
	float currentPosition;
	void(*onPressFunction)(void);//This function pointer returns void, takes in no arguments, and is called onPressFunction

};



#endif