/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         A_light.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.19
* @brief        RGB light is off when there is light, RGB light is on when there is no light
* @details
* @par History  
*
*/
#include <Adafruit_NeoPixel.h>    //Library file
#define PIN 5                       //Define the pins of the RGB lamp
#define MAX_LED 8                   //8 RGB lights in the robot car
#define LightSensor A6              //Define the pins of the Lightsensor

int LightValue = 0 ;                //Define variables to save the data collected by the photo-resistor
Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );
uint8_t i = 0;   
uint32_t color_on = strip.Color(255,255,255);   //Green,Red,Blue
uint32_t color_off = strip.Color(0,0,0);        //Green,Red,Blue

/*Initialization settings*/
void setup()
{
  strip.begin();          
  strip.show();   
  pinMode(LightSensor, INPUT);   
  Serial.begin(115200);
  pinMode(4,OUTPUT);
  digitalWrite(4,0);  //Pin 4 is the pin of the color recognition sensor searchlight  
  /* In order to reduce the load of the power supply, 
  * we initialize the searchlight of the color recognition sensor when it is initialized 
  * (this is not necessary when the color recognition sensor is used) 
  */                        
}

/*Mian function*/
void loop()
{
     LightValue = analogRead(LightSensor);
     Serial.println(LightValue);  //Look at the printed number by the serial port and cover the photoresistor to obtain the threshold.
     if (LightValue > 300)        //Set the threshold to 300. When it is greater than 300 (the RGB light is on when there is no light)
     {
        strip.setPixelColor(i, color_on);  
        strip.show(); 
     } 
   else if(LightValue < 300)
    {
        strip.setPixelColor(i, color_off);  
        strip.show(); 
    }  
}




