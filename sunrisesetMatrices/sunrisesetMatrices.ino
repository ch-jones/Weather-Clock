#include <LedControl.h>   //include LEDControl library

/*
 Matrix One >
 pin 7 is connected to the DataIn 
 pin 6 is connected to the CLK 
 pin 5 is connected to LOAD(/CS)
 Using one single MAX7219 per LedControl/Matrix.

 e.g. LedControl lc=LedControl(DataIn, CLK, CS, # of MAX7219 per Matrix)
 */
 
LedControl lc1=LedControl(7,6,5,1);
LedControl lc3=LedControl(3,6,5,1);

unsigned long delaytime=500;    //set delay between display updates

void setup() {
  //LED Matrix 1
  lc1.shutdown(0,false);  //Wake up MAX7219 (in power-saving mode on startup)
  lc1.setIntensity(0,8);  //Set the brightness
  lc1.clearDisplay(0);    //Clear the display

  //LED Matrix 2
  lc3.shutdown(0,false);  //Wake up MAX7219 (in power-saving mode on startup)
  lc3.setIntensity(0,8);  //Set the brightness
  lc3.clearDisplay(0);    //Clear the display
}

void loop() { 
  sunrise();
  sunset();
}

void sunrise() {
  //Byte data for sunrise animation
  byte a[8]= {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00111100,
    B01111110,
    B11111111
  };
  byte b[8]= {
    B00000000,
    B00000000,
    B00000000,
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111
  };
  byte c[8]= {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100
  };
  byte d[8]= {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };
  

  //Display icon with delay
  lc1.setRow(0,0,a[0]);
  lc1.setRow(0,1,a[1]);
  lc1.setRow(0,2,a[2]);
  lc1.setRow(0,3,a[3]);
  lc1.setRow(0,4,a[4]);
  lc1.setRow(0,5,a[5]);
  lc1.setRow(0,6,a[6]);
  lc1.setRow(0,7,a[7]);
  lc1.setRow(0,8,a[8]);
  delay(delaytime);
  lc1.setRow(0,0,b[0]);
  lc1.setRow(0,1,b[1]);
  lc1.setRow(0,2,b[2]);
  lc1.setRow(0,3,b[3]);
  lc1.setRow(0,4,b[4]);
  lc1.setRow(0,5,b[5]);
  lc1.setRow(0,6,b[6]);
  lc1.setRow(0,7,b[7]);
  lc1.setRow(0,8,b[8]);
  delay(delaytime);
  lc1.setRow(0,0,c[0]);
  lc1.setRow(0,1,c[1]);
  lc1.setRow(0,2,c[2]);
  lc1.setRow(0,3,c[3]);
  lc1.setRow(0,4,c[4]);
  lc1.setRow(0,5,c[5]);
  lc1.setRow(0,6,c[6]);
  lc1.setRow(0,7,c[7]);
  lc1.setRow(0,8,c[8]);
  delay(delaytime);
  lc1.setRow(0,0,d[0]);
  lc1.setRow(0,1,d[1]);
  lc1.setRow(0,2,d[2]);
  lc1.setRow(0,3,d[3]);
  lc1.setRow(0,4,d[4]);
  lc1.setRow(0,5,d[5]);
  lc1.setRow(0,6,d[6]);
  lc1.setRow(0,7,d[7]);
  lc1.setRow(0,8,d[8]);
  delay(delaytime);
}

void sunset() {
  //Byte data for sunset animation
  byte a[8]= {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100
  };
  byte b[8]= {
    B00000000,
    B00000000,
    B00000000,
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111
  };
  byte c[8]= {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00111100,
    B01111110,
    B11111111
  };
  byte d[8]= {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };

  //Display icon with delay
  lc3.setRow(0,0,a[0]);
  lc3.setRow(0,1,a[1]);
  lc3.setRow(0,2,a[2]);
  lc3.setRow(0,3,a[3]);
  lc3.setRow(0,4,a[4]);
  lc3.setRow(0,5,a[5]);
  lc3.setRow(0,6,a[6]);
  lc3.setRow(0,7,a[7]);
  lc3.setRow(0,8,a[8]);
  delay(delaytime);
  lc3.setRow(0,0,b[0]);
  lc3.setRow(0,1,b[1]);
  lc3.setRow(0,2,b[2]);
  lc3.setRow(0,3,b[3]);
  lc3.setRow(0,4,b[4]);
  lc3.setRow(0,5,b[5]);
  lc3.setRow(0,6,b[6]);
  lc3.setRow(0,7,b[7]);
  lc3.setRow(0,8,b[8]);
  delay(delaytime);
  lc3.setRow(0,0,c[0]);
  lc3.setRow(0,1,c[1]);
  lc3.setRow(0,2,c[2]);
  lc3.setRow(0,3,c[3]);
  lc3.setRow(0,4,c[4]);
  lc3.setRow(0,5,c[5]);
  lc3.setRow(0,6,c[6]);
  lc3.setRow(0,7,c[7]);
  lc3.setRow(0,8,c[8]);
  delay(delaytime);
  lc3.setRow(0,0,d[0]);
  lc3.setRow(0,1,d[1]);
  lc3.setRow(0,2,d[2]);
  lc3.setRow(0,3,d[3]);
  lc3.setRow(0,4,d[4]);
  lc3.setRow(0,5,d[5]);
  lc3.setRow(0,6,d[6]);
  lc3.setRow(0,7,d[7]);
  lc3.setRow(0,8,d[8]);
  delay(delaytime);
}
