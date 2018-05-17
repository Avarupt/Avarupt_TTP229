#include "Avarupt_TTP229.h"


void Avarupt_TTP229::updateData(){
  getTTP229data(&aa,&bb);
  position = calculatePosition();
}
 

double Avarupt_TTP229::calculatePosition(){
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

void Avarupt_TTP229::showByteData(){
  Serial.print("data TTP229 = ");
  printByte(aa);
  printByte(bb);
  Serial.println(";");
}

void Avarupt_TTP229::getTTP229data(byte *a, byte *b)
{
  Wire.requestFrom(TTP229_LSF, 2);    // request 6 bytes from slave device #2
  int dataN = 0;
  while(Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read();    // receive a byte as character
    if (dataN == 0) *a = c;
    if (dataN == 1) *b = c;
    dataN++;
  }
}

void Avarupt_TTP229::printByte (byte bytePrint) {
   for (unsigned int mask = 0x80; mask; mask >>= 1) {
       if (mask & bytePrint) {
           Serial.print('1');
       }
       else {
           Serial.print('0');
       }
   }
}
