#include "Slider.h"
#include "Avarupt_TTP229.h"


void Slider::Poll() {
	//bool pressedThisPoll = Avarupt_TTP229::getPosition() != 0 && !Avarupt_TTP229::isTouchDetected();
	bool prevPressed = Avarupt_TTP229::isTouchDetected();
	Avarupt_TTP229::updateData();
	if (!prevPressed&&Avarupt_TTP229::isTouchDetected()) {
		pressPosition = getPosition();
		if (onPressFunction != NULL) {
			(*onPressFunction)();
		}
	}
	if (Avarupt_TTP229::isTouchDetected()) {
		currentPosition+= (Avarupt_TTP229::getPosition() - pressPosition) / (8 * multiplier);
	}
}