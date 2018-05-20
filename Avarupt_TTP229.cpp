#include "Avarupt_TTP229.h"


void Avarupt_TTP229::updateData() {
	getTTP229data(&aa, &bb);//get the data from the TTP229 as two bytes, Most Significant Byte being aa
	prevPosition = position;//the current position is about to be updated so set it as the previous position
	position = calculatePosition();

	//Falling Edge Touch detection
	if (position == 0 && touchDetected) {
		if (!pressDetected && !swipeDetected && millis() - touchMillis < LONG_PRESS_MILLI_THRESHOLD) {
			pressDetected = true;
			canDoublePress = true;
			if (canDoublePress &&previousPressTimestamp + DOUBLE_PRESS_MILLIS >= millis()) {
				canDoublePress = false;
				if (onDoublePressFunction != NULL)
					(*onDoublePressFunction)();
			}
			else {
				previousPressTimestamp = millis();
				if (onPressFunction != NULL) {
					(*onPressFunction)();
				}
			}
		}
		if (onReleaseFunction != NULL) {
			(*onReleaseFunction)();
		}
	}

	//Rising Edge Touch Detection
	//Because touchDetected has not been updatated yet, we can use it as a check to see if there has been a change during this updateData sequence
	if (position != 0 && !touchDetected) {
		pressPosition = position;

		if (onTouchFunction != NULL) {
			(*onTouchFunction)();
		}
		totalDistance = 0;
		touchMillis = millis();
		longTouchDetected = false;
		swipeDetected = false;
		pressDetected = false;
		canLongTouch = true;

	}
	touchDetected = position != 0; //Update touchDetected so that it is useful later



	if (touchDetected) {
		if (!longTouchDetected && millis() - touchMillis > LONG_PRESS_MILLI_THRESHOLD ) {
			if (canLongTouch) {
				longTouchDetected = true;
				canDoublePress = false;
				canLongTouch = false;
				if (onLongPressFunction != NULL) {
					(*onLongPressFunction)();
					previousPressTimestamp = 0;
				}
			}
			//else if(!swipeDetected){
			//	swipeHelper();
			//}
			
		}
		if (!swipeDetected && millis() - touchMillis < SWIPE_MILLI_THRESHOLD&&abs(position - pressPosition)/((millis() - touchMillis)/1000+1)>=SWIPE_VELOCITY_THRESHOLD){ ///*totalDistance*/abs(position-pressPosition) > SWIPE_DISTANCE_THRESHOLD) {
			swipeHelper();
			//Serial.println();
		}
	}

	if (canLongTouch && position!=0&& abs(position - pressPosition) > LONG_PRESS_DISTANCE_THRESHOLD) {
		canLongTouch = false;
	}






}

void Avarupt_TTP229::swipeHelper() {
	swipeDetected = true;
	canDoublePress = false;
	if (onSwipeFunction != NULL)
		(*onSwipeFunction)(prevPosition > pressPosition);
}

double Avarupt_TTP229::calculatePosition() {//This function calculates the position using a weighted average
	double average = 0;
	int n = 0;
	for (int i = 0; i < 8; i++) {

		average += bitRead(bb, i)*i;
		if (bitRead(bb, i) != 0) {
			n++;
		}
		average += bitRead(aa, i)*(i + 8);
		if (bitRead(aa, i) != 0) {
			n++;
		}
	}
	if (n == 0) {
		return 0;
	}
	return (average / n) + 1;
}

void Avarupt_TTP229::showByteData() {//Utility function for displaying the bytes to the serial output
	Serial.print("data TTP229 = ");
	printByte(aa);
	printByte(bb);
	Serial.println(";");
}

void Avarupt_TTP229::getTTP229data(byte *a, byte *b)//This function gets the data from the TTP229
{
	Wire.requestFrom(TTP229_LSF, 2);    // request 6 bytes from slave device #2
	int dataN = 0;
	while (Wire.available())    // slave may send less than requested
	{
		char c = Wire.read();    // receive a byte as character
		if (dataN == 0)
			*a = c;
		if (dataN == 1)
			*b = c;
		dataN++;
	}
}

void Avarupt_TTP229::printByte(byte bytePrint) {//This just prints off a byte
	for (unsigned int mask = 0x80; mask; mask >>= 1) {
		if (mask & bytePrint) {
			Serial.print('1');
		}
		else {
			Serial.print('0');
		}
	}
}
