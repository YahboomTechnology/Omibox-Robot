#include <Adafruit_NeoPixel.h>
#define PIN 5          //Define the pins of the RGB lamp
#define MAX_LED 8      //8 RGB lights in the robot car

int beep = 6;         //Define the pins of the buzzer
int i = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );
int val;
int voice = A7;       //Define the pins of the Voice sensor


/*Initialization settings*/
void setup()
{
  Serial.begin(115200);
  pinMode(voice, INPUT);
  pinMode(beep,OUTPUT);    
  strip.begin();           
  strip.show();           
  pinMode(4,OUTPUT);
  digitalWrite(4,0); //Pin 4 is the pin of the color recognition sensor searchlight  
  /* In order to reduce the load of the power supply, 
  * we initialize the searchlight of the color recognition sensor when it is initialized 
  * (this is not necessary when the color recognition sensor is used) 
  */                     
}

void beep_on()
{
  for(i=0;i<50;i++)
      {
          digitalWrite(beep,HIGH);//sound
          delay(3);
          digitalWrite(beep,LOW);//no sound
          delay(1);
      }  
}

/*Main function*/
void loop()
{
  
  val =analogRead(voice);
  //Serial.println("start");
  //Serial.println("1234");
  Serial.println(val);   //Print out the value output by the photo sensor by the serial port
  if (val > 500)          //Determine if the received data value meets the scope
  {
      beep_on();  
  }
  //Serial.println("end");
}
