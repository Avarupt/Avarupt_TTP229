#ifndef BENDER_H
#define BENDER_H
#include "Avarupt_TTP229.h"

//class Avarupt_TTP229;

class Bender : public Avarupt_TTP229{
public:
	Bender(float mult=2):multiplier(mult) {
		pressPosition = 0;
		currentPosition = 0;
		
	}
	void Poll();
	byte getCurrentPosition() { return (byte)(fmod(currentPosition, 256)); };

private:
	float multiplier;
	float pressPosition;
	float currentPosition;
	
};



#endif