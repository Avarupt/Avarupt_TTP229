#include <Avarupt_TTP229.h>
#include <Adafruit_NeoPixel.h>
#include <Bender.h>
#include <Slider.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6  //The pin that the neopixel should be connected to
#define NUMPIXELS      44 //The number of neopixels there are. In this case, it should be the same as the number of TTP229 pins (16)

#define SWIPE_CONTROL
//#define WAMMY_CONTROL

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Avarupt_TTP229 sensor; //Create the default TTP229 sensor

//Bender bender;
Slider slider(10,true,1);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
//  bender.setOnTouch(&OnTouch);
//  bender.setOnPress(&OnPress);
//  bender.setOnLongPress(&OnLongPress);
//  bender.setOnSwipe(&OnSwipe);
//  bender.setOnRelease(&OnRelease);
//  bender.setOnDoublePress(&OnDoublePress);
  slider.setOnLongPress(&OnLongPress);
}

void loop() {
 //sensor.updateData();//This is called to poll the ttp229 sensor every loop
 //bender.Poll();
 slider.Poll();
  //pixels.clear();//Clear any pixels that were previously displayed.
  #ifdef WAMMY_CONTROL
  for(int i = 0; i<NUMPIXELS; i++){ 
    //pixels.setPixelColor(i, Wheel(sensor.getWammyPosition()+(byte)(i*(255/(float)NUMPIXELS/2))));
    pixels.setPixelColor(i, Wheel(bender.getCurrentPosition()/*+(byte)(i*(255/(float)NUMPIXELS/2))*/));
  }
  #endif
  #ifdef SWIPE_CONTROL
  for(int i = 0; i<NUMPIXELS; i++){ 
    pixels.setPixelColor(i, Wheel(slider.getCurrentPosition()));
  }
  #endif
  pixels.show();//update the display
}

void OnTouch(){Serial.println("TOUCHED");}
void OnPress(){Serial.println("**PRESSED");}
void OnLongPress(){Serial.println("**LONG PRESSED");}
void OnSwipe(bool isLeft){Serial.print("**SWIPED "); Serial.println(isLeft?"\"LEFT\"":"\"RIGHT\"");}
void OnRelease(){Serial.println("RELEASED");}
void OnDoublePress(){Serial.println("**DOUBLE PRESSED");}



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
