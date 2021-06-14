/* Device setup */
#include "Adafruit_TLC59711.h"
#include <SPI.h>
#define NUM 2 // Define the number of boards chained
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
* Steady LEDs are be defined in the setup function
* 
*   steady(channel, level);
*   
*     Channnel is the LED channel number
*     Level is a integer between 1-128, sets brightness
*     
****************************************************/
void setup() {
  tlc.begin();

  /* QQS - Second floor chest */
  steady(0, 24);

  /* QQS - Ground floor ceiling */
  steady(1, 64);
  
  /* QQS - Alcove */
  steady(2, 42);

  /* QQS - Minifig in window display */  
  steady(3, 48);

  /* QQS - Second floor ceiling */
  steady(4, 64);
  
  /* QQS -  External lamp */  
  steady(5, 64);
  
  /* Daily Prophet - Camera flash */
  steady(6, 6);

  /* Daily Prophet - Inside */
  steady(7, 45);

  /* Daily Prophet - Alcove */
  steady(8, 24);
  
  /* QQS - Window displays */
  steady(9, 18);

  /* ---- */

  /* Olivander's - Under stairs */
  steady(13, 42);

  /* Olivander's - Overheads */
  steady(15, 28);
  
  /* Scribulus - Overheads */
  steady(16, 52);
  
  /* Scribulus - Desk lamp */
  steady(17, 32);
  
  /* Olivander's - Desk lamp */
  steady(18, 20);
  
  /* Olivander's - Window lanterns */
  steady(20, 100);
  
  /* Scribulus - Window display */
  steady(21, 52);
  
  /* Scribulus - Bottle */
  steady(22, 4);
  
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
  *     (Optional) Range. An integer less than Level. Sets the intensity of the flickering. Default = 16
  *     (Optional) DelayMin. Default = 20. 
  *     (Optional) DelayMax. Default = 100.
  * 
  ****************************************************/
  /* Olivander's - Ground floor candle */
  if (Millis - flickerAIter > flickerADelay) {
    flickerAIter = Millis;
    flickerADelay = flicker(12, 22, 8);
  }
  /* Scribulus - Street lamp and fireplace 1 */
  if (Millis - flickerBIter > flickerBDelay) {
    flickerBIter = Millis;
    flickerBDelay = flicker(14, 64, 8);
  }
  /* Olivander's - Upper floor candle */
  if (Millis - flickerCIter > flickerCDelay) {
    flickerCIter = Millis;
    flickerCDelay = flicker(19, 26, 8);
  }
  /* Scribulus - Fireplace 2 */
  if (Millis - flickerDIter > flickerDDelay) {
    flickerDIter = Millis;
    flickerDDelay = flicker(23, 96);
  }
  
} /* End the loop */
