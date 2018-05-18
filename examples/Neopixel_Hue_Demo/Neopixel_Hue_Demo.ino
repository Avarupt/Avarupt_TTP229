#include <Avarupt_TTP229.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6  //The pin that the neopixel should be connected to
#define NUMPIXELS      44 //The number of neopixels there are. In this case, it should be the same as the number of TTP229 pins (16)

//#define SWIPE_CONTROL
#define WAMMY_CONTROL

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Avarupt_TTP229 sensor; //Create the default TTP229 sensor

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
 sensor.updateData();//This is called to poll the ttp229 sensor every loop
 //sensor.showByteData();//Outputs the updated values of each pin to the serial monitor
//int position = round(sensor.getPosition())-1; //Gets the current position of your finger(basically a weighted average)
                                              //.getPosition returns a value from 0-16 (0 meaning that no finger is detected)
                                              //thus it must be mapped to 0-15. Round just converts it from double precision to an int
  //pixels.clear();//Clear any pixels that were previously displayed.
  #ifdef WAMMY_CONTROL
  for(int i = 0; i<NUMPIXELS; i++){ 
    pixels.setPixelColor(i, Wheel(sensor.getWammyPosition()+(byte)(i*(255/(float)NUMPIXELS/2))));
  }
  #endif
  #ifdef SWIPE_CONTROL
  for(int i = 0; i<NUMPIXELS; i++){ 
    pixels.setPixelColor(i, Wheel(sensor.getRotaryPosition()+(byte)(i*(255/(float)NUMPIXELS/2))));
  }
  #endif
  pixels.show();//update the display
}

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
