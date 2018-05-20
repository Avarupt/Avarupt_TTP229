#include "Bender.h"
#include "Avarupt_TTP229.h"


void Bender::Poll() {
	//bool pressedThisPoll = Avarupt_TTP229::getPosition() != 0 && !Avarupt_TTP229::isTouchDetected();
	bool prevPressed = Avarupt_TTP229::isTouchDetected();
	Avarupt_TTP229::updateData();
	//if (!prevPressed&&Avarupt_TTP229::isTouchDetected()) {
	//	pressPosition = getPosition();
	//}
	if (Avarupt_TTP229::isTouchDetected()) {
		currentPosition+= (Avarupt_TTP229::getPosition() - Avarupt_TTP229::getPressPosition()) / (8 * multiplier);
	}
}