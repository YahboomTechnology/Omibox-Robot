/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         IR_contorl.c
* @author       xiaozhen
* @version      V1.0
* @date         2017.08.02
* @brief        IR_contorl
* @details
* @par History  
*
*/

#include <Adafruit_NeoPixel.h>       //Library file
#include <Adafruit_PWMServoDriver.h>
#include <LedControl.h>               //Library file
#include <Wire.h>
#include "./IRremote.h"
uint8_t i;    

#define ON  1       
#define OFF 0       

#define run_car     '1'
#define back_car    '2'
#define left_car    '3'
#define right_car   '4'
#define stop_car    '0'

enum {
  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enTLEFT,
  enTRIGHT
} enCarState;
int g_modeSelect = 0;              //0 is the default state;

#define PIN 5                      //Define the pins of the RGB lamp
#define MAX_LED 8                  //8 RGB lights on the robot car

Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );

#define L_Motor_PIN1 1      
#define L_Motor_PIN2 2
#define R_Motor_PIN1 15
#define R_Motor_PIN2 14

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

int buzzer = 6;

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
byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};//Smile
byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};//Standard expression   
byte heart[8] = {0x00,0x66,0xff,0xff,0x7E,0x3C,0x18,0x00};//Heart
byte Music[8] = {0x7f,0x7f,0x41,0x41,0x41,0xc3,0xc3,0x00};//Music
LedControl lc=LedControl(DIN,CLK,CS,NUM);

//IR control
int RECV_PIN = A3; 
IRrecv irrecv(RECV_PIN);
decode_results results; 
unsigned long last = millis();

int Speed = 1000;   
int g_carstate = enSTOP; 
int g_colorlight = 0;


/**
* Function       setup
* @author        liusen
* @date          2017.08.02
* @brief         Initial configuration
* @param[in]     void
* @retval        void
* @par History   no
*/
void setup()
{
   pwm.begin();
   pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
   pinMode(4,OUTPUT);
   digitalWrite(4,0);  //Pin 4 is the pin of the color recognition sensor searchlight  
   /* In order to reduce the load of the power supply, 
   * we initialize the searchlight of the color recognition sensor when it is initialized 
   * (this is not necessary when the color recognition sensor is used) 
   */                    
   pinMode(buzzer, OUTPUT); 
   lc.shutdown(0,false);       
   lc.setIntensity(0,1);       
   lc.shutdown(1,false);       
   lc.setIntensity(1,1);       
   lc.clearDisplay(0);         
   strip.begin();           
   strip.show();  
   digitalWrite(buzzer, HIGH);    
   Serial.begin(115200);	
  irrecv.enableIRIn();    //Initialize infrared decoding
  pinMode(RECV_PIN, INPUT_PULLUP);     //Set the IR receive pin to input and internal pull-up mode
}


/**
* Function       run
* @author        liusen
* @date          2017.07.25
* @brief         advance
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void run(int Speed)
{
    pwm.setPWM(L_Motor_PIN1, 0, Speed);
    pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, Speed);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}

/**
* Function       back
* @author        liusen
* @date          2017.07.25
* @brief         back
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void back(int Speed)
{
    pwm.setPWM(L_Motor_PIN1, 0, 0);
    pwm.setPWM(L_Motor_PIN2, 0, Speed);
    
    pwm.setPWM(R_Motor_PIN1, 0, 0);
    pwm.setPWM(R_Motor_PIN2, 0, Speed);
}

/**
* Function       brake
* @author        liusen
* @date          2017.07.25
* @brief         brake
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void brake()
{
    pwm.setPWM(L_Motor_PIN1, 0, 0);
    pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, 0);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}
/**
* Function       left
* @author        liusen
* @date          2017.07.25
* @brief         left(Left wheel stop, Right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void left(int Speed)
{
    pwm.setPWM(L_Motor_PIN1, 0, 0);
    pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, Speed);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}/**
* Function       right
* @author        liusen
* @date          2017.07.25
* @brief         right(Right wheel stop, left wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void right(int Speed)
{
    pwm.setPWM(L_Motor_PIN1, 0, Speed);
    pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, 0);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}

/**
* Function       spin_left
* @author        liusen
* @date          2017.07.25
* @brief         spin_left spin_left(left wheel back, right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void spin_left(int Speed)
{
   pwm.setPWM(L_Motor_PIN1, 0, 0);
   pwm.setPWM(L_Motor_PIN2, 0, Speed);
    
    pwm.setPWM(R_Motor_PIN1, 0, Speed);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}
/**
* Function       spin_right
* @author        liusen
* @date          2017.07.25
* @brief         spin_right spin_right(left wheel advance, right wheel back)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void spin_right(int Speed)
{
   pwm.setPWM(L_Motor_PIN1, 0, Speed);
   pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, 0);
    pwm.setPWM(R_Motor_PIN2, 0, Speed);
}


/**
* Function       whistle
* @author        liusen
* @date          2017.07.25
* @brief         whistle
* @param[in1]    void
* @retval        void
* @par History   no
*/

void whistle()   
{
  for(i=0;i<50;i++)
      {
          digitalWrite(buzzer,HIGH);//sound
          delay(3);//延时
          digitalWrite(buzzer,LOW);//no sound
          delay(1);//延时
      }  
}

/**
* Function       RGB lights
* @author        liusen
* @date          2017.07.25
* @brief         RGB lights
* @param[in1]    void
* @retval        void
* @par History   no
*/
void light(unsigned char gree, unsigned char red, unsigned char blue)
{
      for(i=0;i<MAX_LED;i++)   
      {
        strip.setPixelColor(i, strip.Color(gree, red, blue));  
      }
}

/**
* Function       Dot matrix
* @author        liusen
* @date          2017.07.25
* @brief         RGB lights
* @param[in1]    void
* @retval        void
* @par History   no
*/
void printByte(byte character [])
{
    int i = 0;
    for(i=0;i<8;i++)                
    {
         lc.setRow(0,i,character[i]);
         lc.setRow(1,i,character[i]);
    }
}

/**
* Function       IR_Deal
* @author        liusen
* @date          2017.08.17
* @brief         IR_Deal
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   no
*/
void IR_Deal()
{
  if (irrecv.decode(&results))
  {
    //Serial.println(results.value, HEX);
    //  00FF00FF  power button
    //  00FF30CF   +
    //  00FF708F   -
    //  00FF40BF   light
    //  00FFA05F     beep
    //  00FF807F     advance
    //  00FF20DF     left
    //  00FF00FF     stop
    //  00FF609F     right
    //  00FF906F     back
    //  00FF10EF     spin left
    //  00FF50AF     spin right
    //  00FFB04F     0
    //  00FF08F7     1
    //  00FF8877     2
    //  00FF48B7     3
    //  00FF28D7     4
    //  00FFA857     5
    //  00FF6897     6
    //  00FF18E7     7
    //  00FF9867     8
    //  00FF58A7     9    

    switch (results.value)
    {
      case 0X00FF00FF: light(0,0,0); strip.show();  break;
      case 0x00FF40BF: light(255,255,255); strip.show();  break;
      case 0x00FF08F7: light(255,255,0);strip.show();  break; 
      case 0x00FF8877: light(255,0,255);strip.show();  break; 
      case 0x00FF48B7: light(0,255,255);strip.show();  break;
      case 0x00FF28D7: light(120,200,55);strip.show();  break; 
      case 0x00FF30CF: light(255,0,0); strip.show();  break; 
      case 0x00FFB04F: light(0,255,0); strip.show();  break; 
      case 0x00FF708F: light(0,0,255); strip.show();  break;
      case 0x00FFA857: light(100,100,200);strip.show(); break;  
      case 0x00FFA05F: whistle(); break;       
      
      case 0x00ff18e7: printByte(smile); break;
      case 0x00ff9867: printByte(neutral); break;
      case 0x00ff58a7: printByte(heart); break;
      case 0x00FF6897: printByte(Music);break; 
      
      case 0x00FF807F:  g_carstate = enRUN; break;   
      case 0x00FF20DF:  g_carstate = enLEFT; break;  
      case 0x00FF609F:  g_carstate = enRIGHT; break; 
      case 0x00FF906F:  g_carstate = enBACK; break;  
      case 0x00FF10EF:  g_carstate = enTLEFT; break; 
      case 0x00FF50AF:  g_carstate = enTRIGHT; break;
      default: break; 
      }
     last = millis();
     irrecv.resume(); //Receive the next code
  }
    else if (millis() - last > 120)
   {
       g_carstate = enSTOP;
       last = millis();
   }
}

void loop()
{
  IR_Deal();
  if(g_modeSelect == 0)
  {
    switch (g_carstate)
    {
      //case enSTOP: brake(); break;
      case enRUN: run(1000); break;
      case enLEFT: left(1000); break;
      case enRIGHT: right(1000); break;
      case enBACK: back(1000); break;
      case enTLEFT:spin_left(1000); break;
      case enTRIGHT:spin_right(1000);break;
      default: brake(); break;
    }
  }
}





