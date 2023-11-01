/*
The purpose of this code is to allow the Arduino to use the
generic serial output of vixen lights to control 5 channels of LEDs.
Author: Matthew Strange
Created: 14 October 2010
Modifier: Ben Towner
Modified: 19-OCT-2010
Changes: Addition of 20 Digital On/Off Channels - Setup for Arduino Mega 2560
 
*/
#include <FastLED.h> 
#define NUM_LEDS 150         // Enter the number of pixels i.e. No. of LEDS x 3

CRGB leds[NUM_LEDS]; 




 
//setup the pins/ inputs & outputs
void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<WS2811, 2, GRB>(leds, 0, 50).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<WS2811, 3, GRB>(leds, 50, 100).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<WS2811, 4, GRB>(leds, 100, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  128 );
 
  
}
 
void loop()
{  // 5 channels are coming in to the Arduino
 // Set some counter / temporary storage variables
  int cnt;
  unsigned int num_leds;
  unsigned int d1, d2, d3;



     // Begin an endless loop to receive and process serial data
  for(;;) {
    // Set a counter to 0.  This couter keeps track of the pixel colors received.
    cnt = 0;
    //Begin waiting for the header to be received on the serial bus
    //1st character
    while(!Serial.available());
      if(Serial.read() != '>') {
        continue;
        }
    //second character
    while(!Serial.available());
      if(Serial.read() != '>') {
        continue;
        }
    //get the first digit from the serial bus for the number of pixels to be used
    while(!Serial.available());
      d1 = Serial.read();
    //get the second digit from the serial bus for the number of pixels to be used
    while(!Serial.available());
      d2 = Serial.read();
    //get the third digit from the serial bus for the number of pixels to be used
    while(!Serial.available());
      d3 = Serial.read();
    //get the end of the header
    while(!Serial.available());
      if(Serial.read() != '<') {
        continue;
        }
    while(!Serial.available());
      if(Serial.read() != '<') {
        continue;
        }

       // calculate the number of pixels based on the characters provided in the header digits
    num_leds = (d1-'0')*100+(d2-'0')*10+(d3-'0');
    // ensure the number of pixels does not exceed the number allowed
    if(num_leds > NUM_LEDS) {
      continue;
      }
     // Let the FastLED library know how many pixels we will be addressing
    FastLED.addLeds<WS2811, 2, GRB>(leds,0 , 50);
    FastLED.addLeds<WS2811, 3, GRB>(leds,50, 100);
    FastLED.addLeds<WS2811, 4, GRB>(leds,100, num_leds);
  
    
    // Loop through each of the pixels and read the values for each color
    do {
      while(!Serial.available());
        leds[cnt].r = Serial.read();
        
      while(!Serial.available());
        leds[cnt].g = Serial.read();
       
      while(!Serial.available());
        leds[cnt++].b = Serial.read();
        
      } 
    while(--num_leds);

    
    // Tell the FastLED Library it is time to update the strip of pixels
    FastLED.show();  
   
   }
}
