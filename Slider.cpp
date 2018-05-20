#include "Slider.h"
#include "Avarupt_TTP229.h"


void Slider::Poll() {

	bool prevPressed = Avarupt_TTP229::isTouchDetected();
	Avarupt_TTP229::updateData();

	if (Avarupt_TTP229::isTouchDetected()&&Avarupt_TTP229::getPrevPosition() != 0 && Avarupt_TTP229::getPosition() != 0) {//If the last two updates contain at least one button pressed in each one

		if (Avarupt_TTP229::isLongPress()) {
			currentPosition -= changedMultiplier*(Avarupt_TTP229::getPrevPosition() - Avarupt_TTP229::getPosition()); //change the rotaryPosition by the difference times a multiplier
		}
		else {
			currentPosition -= multiplier*(Avarupt_TTP229::getPrevPosition() - Avarupt_TTP229::getPosition()); //change the rotaryPosition by the difference times a multiplier
		}

	}
}