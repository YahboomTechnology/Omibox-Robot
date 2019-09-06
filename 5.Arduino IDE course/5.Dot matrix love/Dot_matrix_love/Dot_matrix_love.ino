/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         Dot_matrix_love.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.19
* @brief        Two love patterns are flashed at intervals of 1 second on the dot matrix, three times.
*               Then the pattern LOVE is displayed  2 second.
* @details
* @par History  
*
*/
#include <LedControl.h>               //Library file
#include <Adafruit_NeoPixel.h>       //Library file
#define PIN 5                          //Define the pins of the RGB lamp
#define MAX_LED 8                      //8 RGB lights in the robot 

Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );
uint8_t i;   

/*Define the pins of the Dot matrix */
#define DIN 9
#define CS  10
#define CLK 11
#define NUM 2                   
#define ADD true
#define SUB false


/* Customize the pattern displayed by the dot matrix, 
Note:
The high level lights up, and each dot matrix has 8 rows and 8 columns.
For example: byte test[1] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
Indicates that the dot matrix is on full screen.
For example: byte test[2] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
Indicates that the dot matrix is off full screen.
The following are examples of dot patterns, and users can design their own patterns.
*/
byte e[8]=     {0x7C,0x7C,0x60,0x7C,0x7C,0x60,0x7C,0x7C};     //E
byte d[8]=     {0x78,0x7C,0x66,0x66,0x66,0x66,0x7C,0x78};     //D
byte u[8]=     {0x66,0x66,0x66,0x66,0x66,0x66,0x7E,0x7E};     //U
byte c[8]=     {0x7E,0x7E,0x60,0x60,0x60,0x60,0x7E,0x7E};     //C
byte eight[8]= {0x7E,0x7E,0x66,0x7E,0x7E,0x66,0x7E,0x7E};     //8
byte s[8]=     {0x7E,0x7C,0x60,0x7C,0x3E,0x06,0x3E,0x7E};     //S
byte dot[8]=   {0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18};     //.
byte o[8]=     {0x7E,0x7E,0x66,0x66,0x66,0x66,0x7E,0x7E};     //O
byte m[8]=     {0xE7,0xFF,0xFF,0xDB,0xDB,0xDB,0xC3,0xC3};     //M
byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};   //Smile
byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};   //Standard expression  
byte test1[8] = { 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};   //Full screen is on
byte test2[8] =  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};   //Full screen is off
byte heart[8] = {0x00,0x66,0xff,0xff,0x7E,0x3C,0x18,0x00};    //Heart
byte WORD_LO[8] = {0x8E,0x8A,0x8A,0x8A,0x8A,0x8A,0x8A,0xEE};  //LO
byte WORD_VE[8] = {0xAE,0xA8,0xA8,0xA8,0xAE,0xA8,0xA8,0x4E};  //LO
LedControl lc=LedControl(DIN,CLK,CS,NUM);

/*Initialization settings*/ 
void setup()
{
   lc.shutdown(0,false);       //At startup, the MAX72XX is in power saving mode
   lc.setIntensity(0,1);       //Set the brightness to the maximum
   lc.shutdown(1,false);       //At startup, the MAX72XX is in power saving mode
   lc.setIntensity(1,1);       //Set the brightness to the maximum
   lc.clearDisplay(0);         
   strip.begin();           
   strip.show();  
   pinMode(4,OUTPUT);
   digitalWrite(4,0);         //Pin 4 is the pin of the color recognition sensor searchlight  
  /* In order to reduce the load of the power supply, 
  * we initialize the searchlight of the color recognition sensor when it is initialized 
  * (this is not necessary when the color recognition sensor is used) 
  */             
}

/*Dot matrix display LO */
void printByte_LO(byte character [])
{
     int i = 0;
     for(i=0;i<8;i++)                 
     {
          lc.setRow(0,i,character[i]);   //0 represents the first matrix (the dot matrix on the left)
      }
}

/*Dot matrix display VE*/
void printByte_VE(byte character [])   
{
    int i = 0;
    for(i=0;i<8;i++)                 
    {
         lc.setRow(1,i,character[i]);   //1 represents the second matrix (the dot matrix on the right)
    }
}

/*Two dot matrix display heart*/
void printByte_heart(byte character [])
{
    int i = 0;
    for(i=0;i<8;i++)                
    {
         lc.setRow(0,i,character[i]);
         lc.setRow(1,i,character[i]);
    }
}

/*Two dot matrix clear display*/
void printByte_CLEAR(byte character [])
{
    int i = 0;
    for(i=0;i<8;i++)                
    {
         lc.setRow(1,i,character[i]); 
         lc.setRow(0,i,character[i]);   
    }
}

/*Main function*/
void loop()
{
    int m = 0;
    for(m=0; m<3; m++)     //Two hearts are displayed at intervals of 1 second on the dot matrix, three times,
    {
    printByte_heart(heart);    
    delay(1000);
    printByte_CLEAR(test2);
    delay(1000);
    }
    printByte_LO(WORD_LO); //the pattern LOVE is displayed  2 second.
    printByte_VE(WORD_VE);
    delay(2000);
}
 

