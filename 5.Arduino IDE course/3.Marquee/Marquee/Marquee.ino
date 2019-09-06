/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         Marquee.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.18
* @brief        Marquee
* @details
* @par History  
*
*/
#include <Adafruit_NeoPixel.h>                      //Library file
#define PIN 5                                         //Define the pins of the RGB lamp
#define MAX_LED 8                                     //8 RGB lights in the robot car
Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );
uint8_t i0=0,i1=1,i2=2,i3=3,i4=4,i5=5,i6=6,i7=7;      //"i" indicates the serial number of the RGB lamp                      

/*Main function*/
void setup()
{
  strip.begin();          
  strip.show();     
  pinMode(4,OUTPUT);
  digitalWrite(4,0);    //Pin 4 is the pin of the color recognition sensor searchlight  
  /* In order to reduce the load of the power supply, 
  * we initialize the searchlight of the color recognition sensor when it is initialized 
  * (this is not necessary when the color recognition sensor is used) 
  */     
}     

/*Main function*/
void loop()
{
       delay(100);
       strip.setPixelColor(i0, strip.Color(255,0,0));   //No.0 RGB light is green
       strip.show();
       strip.setPixelColor(i0, strip.Color(0,0,0));     //No.0 RGB light is off
       strip.show();
       delay(100);
       strip.setPixelColor(i1, strip.Color(0,255,0));   //No.1 RGB light is red
       strip.show();
       strip.setPixelColor(i1, strip.Color(0,0,0));     //No.1 RGB light is off
       strip.show();
       delay(100);
       strip.setPixelColor(i2, strip.Color(0,0,255));
       strip.show();
       strip.setPixelColor(i2, strip.Color(0,0,0));
       strip.show();
       delay(100);
       strip.setPixelColor(i3, strip.Color(255,255,0));
       strip.show();
       strip.setPixelColor(i3, strip.Color(0,0,0));
       strip.show();
       delay(100);
       strip.setPixelColor(i4, strip.Color(0,255,255));
       strip.show();
       strip.setPixelColor(i4, strip.Color(0,0,0));
       strip.show();
       delay(100);
       strip.setPixelColor(i5, strip.Color(255,0,255));
       strip.show();
       strip.setPixelColor(i5, strip.Color(0,0,0));
       strip.show();
       delay(100);
       strip.setPixelColor(i6, strip.Color(255,255,255));
       strip.show();
       strip.setPixelColor(i6, strip.Color(0,0,0));
       strip.show();
       delay(100);
       strip.setPixelColor(i7, strip.Color(255,0,0));
       strip.show();
       strip.setPixelColor(i7, strip.Color(0,0,0));
       strip.show(); 
       delay(100);         
}
