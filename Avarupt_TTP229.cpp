#include "Avarupt_TTP229.h"


void Avarupt_TTP229::updateData(){
  getTTP229data(&aa,&bb);//get the data from the TTP229 as two bytes, Most Significant Byte being aa
  prevPosition = position;//the current position is about to be updated so set it as the previous position
  position = calculatePosition();
  
  //Because touchDetected has not been updatated yet, we can use it as a check to see if there has been a change during this updateData sequence
  if(position!=0&&!touchDetected){
	pressPosition = position;//If there is at least one button pressed and touchDetected hasn't been set yet, update the pressed position
  }
  touchDetected = position!=0; //Update touchDetected so that it is useful later
  
  if(touchDetected){//If there was a touch detected, check for wammy movement and update the wammy position
	wammyPosition += (position-pressPosition)/(8*multiplier);//this needs to be a specific multiplier
  }
  
  if(prevPosition!=0 && position!=0){//If the last two updates contain at least one button pressed in each one
	rotaryPosition += round(multiplier*(position-prevPosition)); //change the rotaryPosition by the difference times a multiplier
  }
}
 

double Avarupt_TTP229::calculatePosition(){//This function calculates the position using a weighted average
  double average = 0;
  int n = 0; 
  for(int i = 0; i<8; i++){
    
    average+=bitRead(bb,i)*i;
    if(bitRead(bb,i)!=0){
      n++;
    }
    average+=bitRead(aa,i)*(i+8);
    if(bitRead(aa,i)!=0){
      n++;
    }
  }
  if(n==0){
    return 0;
  }
  return (average/n)+1;
}

void Avarupt_TTP229::showByteData(){//Utility function for displaying the bytes to the serial output
  Serial.print("data TTP229 = ");
  printByte(aa);
  printByte(bb);
  Serial.println(";");
}

void Avarupt_TTP229::getTTP229data(byte *a, byte *b)//This function gets the data from the TTP229
{
  Wire.requestFrom(TTP229_LSF, 2);    // request 6 bytes from slave device #2
  int dataN = 0;
  while(Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read();    // receive a byte as character
    if (dataN == 0) 
		*a = c;
    if (dataN == 1) 
		*b = c;
    dataN++;
  }
}

void Avarupt_TTP229::printByte (byte bytePrint) {//This just prints off a byte
   for (unsigned int mask = 0x80; mask; mask >>= 1) {
       if (mask & bytePrint) {
           Serial.print('1');
       }
       else {
           Serial.print('0');
       }
   }
}
