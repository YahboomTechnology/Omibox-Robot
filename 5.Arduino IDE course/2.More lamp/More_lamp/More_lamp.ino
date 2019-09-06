/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         More_lamp.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.18
* @brief        More_lamp
* @details
* @par History  
*
*/

#include <Adafruit_NeoPixel.h>    //Library file
#define PIN 5                       //Define the pins of the RGB lamp
#define MAX_LED 8                   //8 RGB lights in the robot car

Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );
uint8_t i;                            

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
void light()
{
      for(i=0;i<MAX_LED;i++)   //"i" indicates the serial number of the RGB lamp, "color" indicates the color of RGB lamp
      {
        strip.setPixelColor(i, strip.Color(255,0,0));  //8 RGB lights is green
      }
}

/*Main function*/
void loop()
{
       light();  
       strip.show();
}
