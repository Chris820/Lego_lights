/* Device setup */
#include "Adafruit_TLC59711.h"
#include <SPI.h>
#define NUM 1 // Define the number of boards chained
#define clock 2
#define data 3
Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM, clock, data);

/* The steady function */
void steady(uint8_t chan, uint8_t lev) {
  if(1 < lev > 128) lev = 64;
  uint16_t pwm = (256 * (2 * lev))-1;
  tlc.setPWM(chan, pwm);
  tlc.write();
}

/* The flickering function */
/* Returns a random integer between dMin and dMax, used as a delay */
int flicker(uint8_t chan, uint8_t lev, uint8_t range = 16, int dmin = 20, int dmax = 100) {
  if(1 < lev > 128) lev = 128;
  if(1 < range > lev) range = lev;
  int rlev = random((lev/range), lev);
  uint16_t pwm = (256 * (2 * rlev))-1;
  int rd = random(dmin,dmax);
  tlc.setPWM(chan, pwm);
  tlc.write();
  return rd;
}

/* Helper: Returns a random integer between min and max  */
int random(int min, int max) {
   return min + rand() % (( max + 1 ) - min);
}

/* Variables used for the Millis pseudo-multithreading */
unsigned long flickerAIter = 0;
unsigned long flickerADelay = 10;
unsigned long flickerBIter = 0;
unsigned long flickerBDelay = 10;
unsigned long flickerCIter = 0;
unsigned long flickerCDelay = 10;
unsigned long flickerDIter = 0;
unsigned long flickerDDelay = 10;

/*************************************************** 
* Steady LEDs can be defined in the setup function
* 
*   steady(channel, level);
*   
*     Channnel is the LED channel number
*     Level is a integer between 1-128, sets brightness
*     
****************************************************/
void setup() {
  tlc.begin();

  /* 1 - Olivander's - Under stairs */
  steady(1, 32);

  /* 3 - Olivander's - Overheads */
  steady(3, 28);
  
  /* 4 - Scribulus - Overheads */
  steady(4, 52);
  
  /* 5 - Scribulus - Desk lamp */
  steady(5, 32);
  
  /* 6 - Olivander's - Desk lamp */
  steady(6, 20);
  
  /* 8 - Olivander's - Window lanterns */
  steady(8, 100);
  
  /* 9 - Scribulus - Window display */
  steady(9, 52);
  
  /* 10 - Scribulus - Bottle */
  steady(10, 2);
  
  tlc.write();
}

void loop() {
  unsigned long Millis = millis();
  /*************************************************** 
  * The flickering LEDs are set within a loop
  * 
  *   flicker(channel, level, range, delayMin, delayMax);
  *   
  *     Channnel is the LED channel number
  *     Level is a integer between 1-128, sets brightness
  *     (Optional) Range. An integer less than Level. Sets the intensity of the flickering. Smaller number is a more subtle flicker. Larger number is more noticeable. Default = 16
  *     (Optional) DelayMin. Default = 20. 
  *     (Optional) DelayMax. Default = 100.
  * 
  ****************************************************/
  /* 0 - Olivander's - Ground floor candle */
  if (Millis - flickerAIter > flickerADelay) {
    flickerAIter = Millis;
    flickerADelay = flicker(0, 22, 8);
  }
  /* 2 - Scribulus - Street lamp and fireplace 1 */
  if (Millis - flickerBIter > flickerBDelay) {
    flickerBIter = Millis;
    flickerBDelay = flicker(2, 64, 8);
  }
    /* 7 - Olivander's - Upper floor candle */
  if (Millis - flickerCIter > flickerCDelay) {
    flickerCIter = Millis;
    flickerCDelay = flicker(7, 26, 8);
  }
  /* 11 - Scribulus - Fireplace 2 */
  if (Millis - flickerDIter > flickerDDelay) {
    flickerDIter = Millis;
    flickerDDelay = flicker(11, 96);
  }
  
} /* End the loop */
