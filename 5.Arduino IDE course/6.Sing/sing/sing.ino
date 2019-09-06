/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         Dot_matrix_love.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.19
* @brief        The buzzer plays music, and the music pattern is displayed on the dot matrix
* @details
* @par History  
*
*/
#include <Wire.h>                   //Library file
#include <LedControl.h>

/*Define the pins of the Dot matrix  */
#define DIN 9
#define CS  10
#define CLK 11
#define PIN 4                     
#define ADD true
#define SUB false

/*Define the pitch in the score*/
#define BL1 248
#define BL2 278
#define BL3 294
#define BL4 330
#define BL5 371
#define BL6 416
#define BL7 467

#define B1 495
#define B2 556
#define B3 624
#define B4 661
#define B5 742
#define B6 833
#define B7 935

#define BH1 990
#define BH2 1112
#define BH3 1178
#define BH4 1322
#define BH5 1484
#define BH6 1665
#define BH7 1869

#define NTC1 262
#define NTC2 294
#define NTC3 330
#define NTC4 350
#define NTC5 393
#define NTC6 441
#define NTC7 495

#define NTCL1 131
#define NTCL2 147
#define NTCL3 165
#define NTCL4 175
#define NTCL5 196
#define NTCL6 221
#define NTCL7 248

#define NTCH1 525
#define NTCH2 589
#define NTCH3 661
#define NTCH4 700
#define NTCH5 786
#define NTCH6 882
#define NTCH7 990

#define NTD0 -1
#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556

#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278

#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 1112

#define NTE1 330
#define NTE2 350
#define NTE3 393
#define NTE4 441
#define NTE5 495
#define NTE6 556
#define NTE7 624

#define NTEL1 165
#define NTEL2 175
#define NTEL3 196
#define NTEL4 221
#define NTEL5 248
#define NTEL6 278
#define NTEL7 312

#define NTEH1 661
#define NTEH2 700
#define NTEH3 786
#define NTEH4 882
#define NTEH5 990
#define NTEH6 1112
#define NTEH7 1248

int buzzer=6;      //Set the buzzer pin
int i = 0;
byte Music[8] = {0x7f,0x7f,0x41,0x41,0x41,0xc3,0xc3,0x00};
LedControl lc=LedControl(DIN,CLK,CS,PIN);


//Ode
int tune[]=                 
{
NTC3, NTC3, NTC4, NTC5, NTC5, NTC4, NTC3, NTC2, NTC1, NTC1, NTC2, NTC3, NTC3,NTC2, NTC2, 
 NTC3, NTC3, NTC4, NTC5, NTC5, NTC4, NTC3, NTC2, NTC1, NTC1, NTC2, NTC3, NTC2, NTC1, NTC1,
NTC2, NTC2, NTC3,NTC1, NTC2, NTC3, NTC4, NTC3, NTC1, NTC2, NTC3, NTC4, NTC3, NTC2,

NTC1, NTC2, NTCL5, NTC3, NTC3, NTC3, NTC4, NTC5, NTC5, NTC4, NTC3, NTC4, NTC2, NTC1, NTC1, NTC2, NTC3, 
 NTC2, NTC1,NTC1,
};

float durt[]= 
{
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1,
0.5, 0.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0.5, 1, 1, 1, 1, 2, 0.5, 0.5,
};

//Happy Birthday
/*
int tune[]=                 
{
NTC5, NTC5, NTC6, NTC5, NTCH1, NTC7, 
NTC5, NTC5, NTC6, NTC5, NTCH2, NTCH1, 
NTC5, NTC5, NTCH5, NTCH3, NTCH1, NTC7, NTC6, 
NTCH4, NTCH4, NTCH3, NTCH1, NTCH2, NTCH1,
};
float durt[]=                   
{
0.5, 0.5, 1, 1, 1, 2,
 0.5, 0.5, 1, 1, 1, 2,
 0.5, 0.5, 1, 1, 1, 1, 2,
 0.5, 0.5, 1, 1, 1, 2,
};
*/


void PlayTest()
{
 int length = sizeof(tune)/sizeof(tune[0]);   
 for(int x=0; x < length;x++)
  {
    tone(buzzer,tune[x]);
    delay(500*durt[x]);   /*This is used to adjust the delay according to the beat. 
                            The 500 parameter can be adjusted by yourself. In this music,
                            500 is more suitable.*/
    noTone(buzzer);
  }
  
}

/*Dot matrix display Music pattern*/
void printByte_Music(byte character [])
{
     int i = 0;
     for(i=0;i<8;i++)                 
     {
          lc.setRow(0,i,character[i]);   //1 represents the second dot matrix, and 0 represents the first dot matrix
          lc.setRow(1,i,character[i]);   
      }
}

/*initialization setting*/
void setup() 
{ 
     pinMode(buzzer,OUTPUT);     
     lc.shutdown(0,false);       
     lc.setIntensity(0,1);       
     lc.shutdown(1,false);       
     lc.setIntensity(1,1);       
     lc.clearDisplay(0);         
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
         printByte_Music(Music); 
         PlayTest();    
}

