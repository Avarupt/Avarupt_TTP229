/*********************************************
*Programmer: Caleb Marting
*5/20/2018
*Description:This is an example file for the slider portion of the Avarupt_TTP229 library
*Program Features:
*   Touch events will be displayed over serial
*   A fast swipe to the left or right will start the LED's in their respective direction
*   A regular movement will move the LED's proportionally
*   A long press (500 ms) changes the multiplier for that swipe only (a long press also causes the strip to flash when activated
*   A double tap will flip the colors!
*********************************************/
#include <Avarupt_TTP229.h>
#include <Adafruit_NeoPixel.h>
#include <Slider.h>

#define PIN            6  //The pin that the neopixel should be connected to
#define NUMPIXELS      44 //The number of neopixels there are. In this case, it should be the same as the number of TTP229 pins (16)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Avarupt_TTP229 sensor; //Create the default TTP229 sensor

//Create the slider (regular swipe multiplier, should there be a long touch multiplier, and the long touch multiplier
Slider slider(10,true,3);

//Helper Vars
bool swiped = false;
bool swipedLeft = false;
byte swipedPosition = 0;
uint8_t sign = 1;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  
  //These add the touch events functions to the slider
  slider.setOnTouch(&OnTouch);
  slider.setOnRelease(&OnRelease);
  slider.setOnDoublePress(&OnDoublePress);
  slider.setOnLongPress(&OnLongPress);
  slider.setOnSwipe(&OnSwipe);
}

void loop() {
  //this must be done once per loop, This library is (unfortunately) not based on interrupts yet. please do at the beginning to avoid strange behaviour
  slider.Poll();

  for(int i = 0; i<NUMPIXELS; i++){ 
    pixels.setPixelColor(i, Wheel(sign*(slider.getCurrentPosition()+swipedPosition+(byte)(i*(255/(float)NUMPIXELS/2)))));
  }
  pixels.show();//update the display

  //if they swiped, change the swiped colors in their respective directions
  if(swiped){
    if(swipedLeft){
      swipedPosition++;
    }
    else{
      swipedPosition--;
    }
  }
}

//the functions used in the touch events functions
void OnLongPress(){
  Serial.println("**LONG PRESSED");
    for(int i = 0; i<NUMPIXELS; i++){ 
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();//update the display

  delay(10);

  }
void OnSwipe(bool isLeft){
  Serial.print("**SWIPED "); Serial.println(isLeft?"\"LEFT\"":"\"RIGHT\"");
  swiped = true;
  swipedLeft = isLeft;
}
void OnTouch(){
  Serial.println("TOUCHED");
  swiped = false;
}

void OnPress(){Serial.println("**PRESSED");}
void OnRelease(){Serial.println("RELEASED");}
void OnDoublePress(){
  Serial.println("**DOUBLE PRESSED");
  sign *= -1;
  }

//Helper function for pretty rainbows
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
