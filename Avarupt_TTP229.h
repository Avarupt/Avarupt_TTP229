#ifndef AVARUPT_TTP229_H
#define AVARUPT_TTP229_H

#include "Arduino.h"
#include "Wire.h"

#define TTP229_LSF 0x57 // Device address (the addressing without the R/W bit) -> 01010111 = 57

class Avarupt_TTP229{
  public:
    Avarupt_TTP229(){
      aa=0;
      bb=0;
      position = 0;
	  Wire.begin();
    }
    byte getMostSignificantByte(){return aa;};
    byte getLeastSignificantByte(){return bb;};
    double getPosition(){return position;};
    void showByteData();
    void updateData();
  private:
    byte aa;
    byte bb;
    double position;
    void getTTP229data(byte *a, byte *b);
    void printByte (byte bytePrint);
    double calculatePosition();
};

#endif
