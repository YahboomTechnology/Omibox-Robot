/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         Breathing_light.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.19
* @brief        Breathing_ligh
* @details
* @par History  
*
*/
#include <Adafruit_NeoPixel.h>     //Library file
#define PIN 5                        //Define the pins of the RGB lamp
#define MAX_LED 8                    //8 RGB lights in the robot car
Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );
uint8_t brightness = 0;             //Brightness of RGB light
uint8_t fadeAmount = 1;             //Increment in brightness change
uint8_t i=0;                        //"i" indicates the serial number of the RGB lamp   

/*Initialization settings*/
void setup()
{
  strip.begin();          
  strip.show();   
  pinMode(4,OUTPUT);
  digitalWrite(4,0);  //Pin 4 is the pin of the color recognition sensor searchlight  
  /* In order to reduce the load of the power supply, 
  * we initialize the searchlight of the color recognition sensor when it is initialized 
  * (this is not necessary when the color recognition sensor is used) 
  */             
}

/*Main function*/
void loop() 
{
   for(i=0;i<MAX_LED;i++)
   {
   strip.setPixelColor(i, brightness, 0, 0);  //All RGB light is green
   strip.show();
    }
   brightness = brightness + fadeAmount;
   if (brightness <= 0 || brightness >=100)  //The brightness of RGB lamps varies from 1 to 100.
   fadeAmount = -fadeAmount ; 
   delay(20);
}
