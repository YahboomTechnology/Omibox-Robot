/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         smile_and_cry.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.19
* @brief        press the green button, the dot matrix displays a crying expression, 
*               press the red button, and the dot matrix displays a smile.
* @details
* @par History  
*
*/

#include <LedControl.h>               //Library file
#include <Adafruit_NeoPixel.h>       //Library file
#define PIN 5                         //Define the pins of the RGB lamp
#define MAX_LED 8                     //8 RGB lights in the robot car.

Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );
#define key1  2     //Define the pin of key1(red button)
#define key2  3     //Define the pin of key2(green button)

/*Define the pin of the dot matrix*/
#define DIN 9
#define CS  10
#define CLK 11
#define NUM 2                    
#define ADD true
#define SUB false

//int val1;
//int val2;

byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};//Smile
byte Cry[8]= {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};//Crying
LedControl lc=LedControl(DIN,CLK,CS,NUM);

/*Initialization settings*/
void setup()
{
     pinMode(key1,INPUT);       
     pinMode(key2,INPUT);       
     lc.shutdown(0,false);       
     lc.setIntensity(0,1);       
     lc.shutdown(1,false);       
     lc.setIntensity(1,1);       
     lc.clearDisplay(0);        
     strip.begin();             
     strip.show(); 
     Serial.begin(115200);  
     pinMode(4,OUTPUT);
     digitalWrite(4,0);   //Pin 4 is the pin of the color recognition sensor searchlight  
    /* In order to reduce the load of the power supply, 
    * we initialize the searchlight of the color recognition sensor when it is initialized 
    * (this is not necessary when the color recognition sensor is used) 
    */                   
}

/*Button detection*/
int key_scan()   
{
  if(digitalRead(key1) == 0 || digitalRead(key2) == 0)
  {
    if(digitalRead(key1) == 0)
    {
      delay(10);
      if(digitalRead(key1) == 0)
      {
       Serial.println("key1 down");
       while(digitalRead(key1) == 0);
        return 1;
      }
      else 
      {
        Serial.println("error");
      }
    }
    else{
      delay(10);
      if(digitalRead(key2) == 0)
      {
       Serial.println("key2 down");
       while(digitalRead(key2) == 0);
        return 2;
      }
      else
      {
        Serial.println("error"); 
      }
    }
  }
 return 0;
} 
 
/*Two dot matrix display functions*/
void printByte(byte character [])
{
    int i = 0;
    for(i=0;i<8;i++)                
    {
         lc.setRow(0,i,character[i]);
         lc.setRow(1,i,character[i]);
    }
}

/*Main function*/
void loop()
{
   int val = 0;
   val = key_scan( );

   if(val==2)       //Determine whether the button Key2 is pressed,when the button is pressed the crying is displayed.
    {
        printByte(Cry); 
        Serial.println("2"); 
    } 
    else if(val==1)    //Determine whether the button Key2 is pressed,when the button is pressed the smile is displayed.
    {
        printByte(smile);
        Serial.println("1");
    } 
}

