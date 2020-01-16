 /*****************
YahBoom_Roboduino.cpp
******************/

#include"./YahBoom_Roboduino.h"
#include "avr/pgmspace.h"
#include "./RGBLed.h"

#define RGB_OFF  0

enum enMusic
	{
		enBirthday=1,
		Ode=2,
		Star=3,
		MerryChristmas=4,
  		Bingo=5
	};

#define G5 392
#define A6 440
#define B7 494
#define c1 525
#define d2 587
#define e3 659
#define f4 698
#define g5 784
#define a6 880
#define b7 988
#define C1 1047
#define D2 1175
#define E3 1319
#define F4 1397
#define GG5 1568
#define AA6 1769
#define g4 392
#define c5 523
#define a4 440
#define d5 587
#define e5 659
#define b4 494
#define c6 1047
#define d6 1175
#define b5 988
#define a5 880
#define g5 784
#define e6 1319
#define f6 1397
#define a5 880
#define f5 698


const PROGMEM  int ODe[70][2]
{
	{e3,2},{e3,2},{f4,2},{g5,2},{g5,2},{f4,2},{e3,2},{d2,2},{c1,2},{c1,2},{d2,2},{e3,2},{e3,3},{d2,1},{d2,4},
	{e3,2},{e3,2},{f4,2},{g5,2},{g5,2},{f4,2},{e3,2},{d2,2},{c1,2},{c1,2},{d2,2},{e3,2},{d2,3},{c1,1},{c1,4},
	{d2,2},{d2,2},{e3,2},{c1,2},{d2,2},{e3,1},{f4,1},{e3,2},{c1,2},
	{d2,2},{e3,1},{f4,1},{e3,2},{d2,2},{c1,2},{d2,2},{G5,2},
	{e3,2},{e3,2},{f4,2},{g5,2},{g5,2},{f4,2},{e3,2},{d2,2},{c1,2},{c1,2},{d2,2},{e3,2},{d2,3},{c1,1},{c1,4},
};


const PROGMEM  int BIrthday[25][2]
{
	{G5,2},{A6,2},{G5,2},{c1,2},{B7,4},
	{G5,2},{A6,2},{G5,2},{d2,2},{c1,4},
	{G5,2},{g5,2},{e3,2},{c1,2},{B7,2},{A6,2},
	{f4,2},{e3,2},{c1,2},{d2,2},{c1,2}
};


const PROGMEM  int STar[42][2]
{
	{c1,2},{c1,2},{g5,2},{g5,2},{a6,2},{a6,2},{g5,4},
	{f4,2},{f4,2},{e3,2},{e3,2},{d2,2},{d2,2},{c1,4},
	{g5,2},{g5,2},{f4,2},{f4,2},{e3,2},{e3,2},{d2,4},
	{g5,2},{g5,2},{f4,2},{f4,2},{e3,2},{e3,2},{d2,4},
	{c1,2},{c1,2},{g5,2},{g5,2},{a6,2},{a6,2},{g5,4},
	{f4,2},{f4,2},{e3,2},{e3,2},{d2,2},{d2,2},{c1,4},
};

const PROGMEM  int MErryChristmas[36][2]  
{
  {g5,1},{g5,1},{c6,2},{c6,1},{d6,1},{c6,1},{b5,1},{a5,2},{a5,2},{0,2},
  {a5,1},{a5,1},{d6,2},{d6,1},{e6,1},{d6,1},{c6,1},{b5,2},{g5,2},{0,2},
  {g5,1},{g5,1},{e6,2},{e6,1},{f6,1},{e6,1},{d6,1},{c6,2},{a5,2},{0,2},
  {g5,1},{g5,1},{a5,1},{d6,1},{b5,1},{c6,2}
};

const PROGMEM  int BIngo[39][2]   
{
  {g4,1},{c5,1},{c5,1},{c5,1},{g4,1},{a4,1},{a4,1},{g4,1},{g4,1},
  {c5,1},{c5,1},{d5,1},{d5,1},{e5,2},{c5,1},{0,1},
  {e5,2},{e5,2},{f5,1},{f5,1},{f5,2},{d5,2},{d5,2},{e5,1},{e5,1},{e5,2},
  {c5,2},{c5,2},{d5,1},{d5,1},{d5,1},{c5,1},{b4,1},{g4,1},{a4,1},{b4,1},{c5,2},{c5,1},{c5,1}
};


/*****************************************************************/
/*LOGO RGB*/ 
/*****************************************************************/ 

YahBoom_Roboduino_LOGORGB::YahBoom_Roboduino_LOGORGB()          //Constructor
{ 
	pwm = Adafruit_PWMServoDriver(0x40); 
}

YahBoom_Roboduino_LOGORGB::~YahBoom_Roboduino_LOGORGB()
{

} 

void YahBoom_Roboduino_LOGORGB::LOGORGB_Init()
{
	pwm.begin();
	pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void YahBoom_Roboduino_LOGORGB::LOGORGB_Show_Color()  //Power on start breathibg light
{
	const int LOGORGB_pin = 7;      //Logo RGB connect to LED7 of PCA9685 chip
	for (int b = 0; b < 255; b += 5)
	{
		int newb = map(b, 0, 255, 0, 4095);
		pwm.setPWM(LOGORGB_pin, 0, newb);
		delay(40);
	}
}

void YahBoom_Roboduino_LOGORGB::LOGORGB_Close()  //Close LogoRGB
{
	const int LOGORGB_pin = 7;      //Logo RGB connect to LED7 of PCA9685 chip
	pwm.setPWM(LOGORGB_pin, 0, 0);

}


/*****************************************************************/
/*Onboard RGB*/ 
/*****************************************************************/ 

YahBoom_Roboduino_OnboardRGB::YahBoom_Roboduino_OnboardRGB(byte max_led, byte pinname)   //Constructor
{ 
	strip = Adafruit_NeoPixel(max_led, pinname, NEO_RGB + NEO_KHZ800 );   //Only one onboard RGB and it connect to Pin6 of Uno board
}

YahBoom_Roboduino_OnboardRGB::~YahBoom_Roboduino_OnboardRGB()
{

} 

void YahBoom_Roboduino_OnboardRGB::OnboardRGB_Init()
{
	strip.begin();           
	strip.show(); 
}

void YahBoom_Roboduino_OnboardRGB::OnboardRGB_Show_Color(uint8_t v_Red, uint8_t v_Green, uint8_t v_Blue)  //set color of Onboard RGB
{
	uint32_t color = strip.Color(v_Green, v_Red, v_Blue );
	strip.setPixelColor(0, color);  //Only one onboard RGB
	strip.show();
}

void YahBoom_Roboduino_OnboardRGB::OnboardRGB_setBrightness(uint8_t b)  //set brightness of Onboard RGB
{
	strip.setBrightness(b);
    strip.show();
}

void YahBoom_Roboduino_OnboardRGB::OnboardRGB_OFF()   //Close Onboard RGB
{
	strip.setPixelColor(0, 0, 0, 0 );  //Only one onboard RGB
	strip.show();
}


/*****************************************************************/
/*Ultrasonic RGB*/   
YahBoom_Roboduino_UltrasonicRGB::YahBoom_Roboduino_UltrasonicRGB(byte pinname, byte max_led)   
{ 
	mRgb = RGBLed(pinname,max_led);  //Two Ultrasonic RGB connect to Pin11 of Uno board
	
}

YahBoom_Roboduino_UltrasonicRGB::~YahBoom_Roboduino_UltrasonicRGB()
{

} 

void YahBoom_Roboduino_UltrasonicRGB::UltrasonicRGB_Init()
{
	pinMode(pinname,OUTPUT); 
}

void YahBoom_Roboduino_UltrasonicRGB::UltrasonicRGB_Show_Color(byte Num,uint8_t v_Red, uint8_t v_Green, uint8_t v_Blue)  //set color of UltrasonicRGB 
{
	mRgb.setColor(Num, v_Green, v_Red, v_Blue); 
    mRgb.show();
}

void YahBoom_Roboduino_UltrasonicRGB::UltrasonicRGB_Show_All(uint8_t v_Red, uint8_t v_Green, uint8_t v_Blue)  
{
	mRgb.setColor(0, v_Green, v_Red, v_Blue); //0 means that all the RGB lights of the ultrasonic module are illuminated.
    mRgb.show();
}


void YahBoom_Roboduino_UltrasonicRGB::UltrasonicRGB_OFF()//Close all Ultrasonic RGB 
{
	mRgb.setColor(0, RGB_OFF); 
    mRgb.show();
}


/*****************************************************************/
/*Motor and Servo*/
//I2C PCA9685
YahBoom_Roboduino_MotorServo::YahBoom_Roboduino_MotorServo()
{
	pwm = Adafruit_PWMServoDriver(0x40); 
}

YahBoom_Roboduino_MotorServo::~YahBoom_Roboduino_MotorServo()
{

} 

void YahBoom_Roboduino_MotorServo::YahBoom_Roboduino_MotorServo_Init()
{
	pwm.begin();
	pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}


/*Servo*/
void YahBoom_Roboduino_MotorServo::SetServoPos(int num, int value)
{
    // 50hz: 20,000 us
    long us = (value * 1800.0 / 180 + 600); // 0.6 ~ 2.4 
    long pwmvalue = us * 4096 / 20000;
    pwm.setPWM(num, 0, pwmvalue);
}

void YahBoom_Roboduino_MotorServo::SetServoAngle(int num, int value)
{
	switch(num)
	{
		case 1: SetServoPos(0, value);break;   //S1 connect to LED0 of PCA9685 
		case 2: SetServoPos(1, value);break;   //S2 connect to LED1 of PCA9685
		case 3: SetServoPos(2, value);break;   //S3 connect to LED2 of PCA9685
		case 4: SetServoPos(3, value);break;   //S4 connect to LED3 of PCA9685
	}
}

/*Motor*/
void YahBoom_Roboduino_MotorServo::Advance(int speed, int delay_ms)     //advance
{
	speed = map(speed, 0, 255, 0, 4095);
	pwm.setPWM(10, 0, speed); //Right front wheel Forward 
  	pwm.setPWM(11, 0, 0);
  	pwm.setPWM(8, 0, speed); //Right rear wheel Forward 
  	pwm.setPWM(9, 0, 0);

  	pwm.setPWM(13, 0, speed); //Left front wheel Forward 
  	pwm.setPWM(12, 0, 0);
  	pwm.setPWM(15, 0, speed); //Left rear wheel Forward 
  	pwm.setPWM(14, 0, 0);	
	delay(delay_ms);
}

void YahBoom_Roboduino_MotorServo::Back(int speed, int delay_ms)   //back
{
	speed = map(speed, 0, 255, 0, 4095);
  	pwm.setPWM(10, 0, 0);
  	pwm.setPWM(11, 0, speed); //Right front wheel Reverse
  	pwm.setPWM(8, 0, 0);
  	pwm.setPWM(9, 0, speed);  //Right rear wheel Reverse

  	pwm.setPWM(13, 0, 0);
  	pwm.setPWM(12, 0, speed);  //Left front wheel Reverse
  	pwm.setPWM(15, 0, 0);
  	pwm.setPWM(14, 0, speed);  //Left rear wheel Reverse	
	delay(delay_ms);
}

void YahBoom_Roboduino_MotorServo::Left(int speed, int delay_ms)   //turn left
{
	speed = map(speed, 0, 255, 0, 4095);
  	pwm.setPWM(10, 0, speed);     //Right front wheel Reverse
  	pwm.setPWM(11, 0, 0);
  	pwm.setPWM(8, 0, speed);      //Right rear wheel Reverse
  	pwm.setPWM(9, 0, 0);      

  	pwm.setPWM(13, 0, 0);         //Left front wheel Stop
  	pwm.setPWM(12, 0, 0);
  	pwm.setPWM(15, 0, 0);
  	pwm.setPWM(14, 0, 0);	
	delay(delay_ms);
}

void YahBoom_Roboduino_MotorServo::Right(int speed, int delay_ms)  //turn right
{
	speed = map(speed, 0, 255, 0, 4095);
	pwm.setPWM(10, 0, 0);        //Right front wheel Stop
  	pwm.setPWM(11, 0, 0);
  	pwm.setPWM(8, 0, 0);
  	pwm.setPWM(9, 0, 0);

  	pwm.setPWM(13, 0, speed);    //Left front wheel Reverse
  	pwm.setPWM(12, 0, 0);
  	pwm.setPWM(15, 0, speed);    //Left rear wheel Reverse
  	pwm.setPWM(14, 0, 0);
	delay(delay_ms);
}

void YahBoom_Roboduino_MotorServo::Stop(int speed, int delay_ms)   //stop
{
	speed = map(speed, 0, 255, 0, 4095);	
	pwm.setPWM(8, 0, 0);    //Right front wheel Stop
  	pwm.setPWM(9, 0, 0);
  	pwm.setPWM(11, 0, 0);
  	pwm.setPWM(10, 0, 0);

  	pwm.setPWM(12, 0, 0);   //Left front wheel Stop
  	pwm.setPWM(13, 0, 0);
  	pwm.setPWM(14, 0, 0);
  	pwm.setPWM(15, 0, 0);	
	delay(delay_ms);
}

void YahBoom_Roboduino_MotorServo::SpinLeft(int speed, int delay_ms)   //spin left
{
	speed = map(speed, 0, 255, 0, 4095);
	pwm.setPWM(10, 0, speed);      //Right front wheel Forword
  	pwm.setPWM(11, 0, 0);
  	pwm.setPWM(8, 0, speed);       //Right rear wheel Forword
  	pwm.setPWM(9, 0, 0);

  	pwm.setPWM(13, 0, 0);
  	pwm.setPWM(12, 0, speed);      //Left front wheel Back
  	pwm.setPWM(15, 0, 0);
  	pwm.setPWM(14, 0, speed);      //Left rear wheel Back
  	delay(delay_ms);
}

void YahBoom_Roboduino_MotorServo::SpinRight(int speed, int delay_ms)  //spin right
{
	speed = map(speed, 0, 255, 0, 4095);
  	pwm.setPWM(10, 0, 0);
  	pwm.setPWM(11, 0, speed);    //Right front wheel Back
  	pwm.setPWM(8, 0, 0);
  	pwm.setPWM(9, 0, speed);     //Right rear wheel Back

  	pwm.setPWM(13, 0, speed);    //Left front wheel Forword
  	pwm.setPWM(12, 0, 0);
  	pwm.setPWM(15, 0, speed);    //Left rear wheel Forword
  	pwm.setPWM(14, 0, 0);
	delay(delay_ms);
}

void YahBoom_Roboduino_MotorServo::MotorSpeed(int left_speed, int right_speed)   //control speed of left and right motor
{
		int Lspeed = 0, Rspeed = 0;
		if(left_speed < 0)   //When input speed of left motor is less than 0, left motor reverse
		{
			Lspeed = abs(left_speed);
			Lspeed = map(Lspeed, 0, 255, 0, 4095);
			pwm.setPWM(13, 0, 0);
  			pwm.setPWM(12, 0, Lspeed);  //Left front wheel Reverse
  			pwm.setPWM(15, 0, 0);
  			pwm.setPWM(14, 0, Lspeed);  //Left rear wheel Reverse	
		}
		else         //When input speed of left motor is greater than 0, left motor forward
		{
			Lspeed = abs(left_speed);
			Lspeed = map(Lspeed, 0, 255, 0, 4095);
			pwm.setPWM(13, 0, Lspeed); //Left front wheel Forward 
  			pwm.setPWM(12, 0, 0);
  			pwm.setPWM(15, 0, Lspeed); //Left rear wheel Forward 
 			pwm.setPWM(14, 0, 0);	
		}
		if(right_speed < 0)   //When input speed of right motor is less than 0, right motor reverse
		{
			Rspeed = abs(right_speed);
			Rspeed = map(Rspeed, 0, 255, 0, 4095);
			pwm.setPWM(10, 0, 0);
  			pwm.setPWM(11, 0, Rspeed);    //Right front wheel Reverse
  			pwm.setPWM(8, 0, 0);
  			pwm.setPWM(9, 0, Rspeed);     //Right rear wheel Reverse
		}
		else           //When input speed of right motor is greater than 0, right motor forward
		{
			Rspeed = abs(right_speed);
			Rspeed = map(Rspeed, 0, 255, 0, 4095);
			pwm.setPWM(10, 0, Rspeed);      //Right front wheel Forword
  			pwm.setPWM(11, 0, 0);
  			pwm.setPWM(8, 0, Rspeed);       //Right rear wheel Forword
  			pwm.setPWM(9, 0, 0);	
		}	
		
}

void YahBoom_Roboduino_MotorServo::LeftMotor(int direction, int speed)   //control the direction and speed of rotation of left motor
{
	speed = map(speed, 0, 255, 0, 4095);
	if(direction == 1) //forward
	{
		pwm.setPWM(13, 0, speed);    //Left front wheel Forword
  		pwm.setPWM(12, 0, 0);
  		pwm.setPWM(15, 0, speed);    //Left rear wheel Forword
  		pwm.setPWM(14, 0, 0);	
	}
	else if (direction == 2) //forward
	{
		pwm.setPWM(13, 0, 0);
  		pwm.setPWM(12, 0, speed);      //Left front wheel Reverse
  		pwm.setPWM(15, 0, 0);
  		pwm.setPWM(14, 0, speed);      //Left rear wheel Reverse
	}
	else //stop
	{
		pwm.setPWM(12, 0, 0);   //Left front wheel Stop
  		pwm.setPWM(13, 0, 0);
  		pwm.setPWM(14, 0, 0);
  		pwm.setPWM(15, 0, 0);	
	}
}

void YahBoom_Roboduino_MotorServo::RightMotor(int direction, int speed)   //control the direction and speed of rotation of right motor
{

   speed = map(speed, 0, 255, 0, 4095);
	if(direction == 1) //forward
	{
		pwm.setPWM(10, 0, speed);      //Right front wheel Forword
  		pwm.setPWM(11, 0, 0);
  		pwm.setPWM(8, 0, speed);       //Right rear wheel Forword
  		pwm.setPWM(9, 0, 0);		
	}
	else if (direction == 2) //forward
	{
		pwm.setPWM(10, 0, 0);
  		pwm.setPWM(11, 0, speed);      //Left front wheel Reverse
  		pwm.setPWM(8, 0, 0);
  		pwm.setPWM(9, 0, speed);      //Left rear wheel Reverse	
	}
	else //stop
	{
		pwm.setPWM(8, 0, 0);    //Right front wheel Stop
  		pwm.setPWM(9, 0, 0);
  		pwm.setPWM(11, 0, 0);
  		pwm.setPWM(10, 0, 0);
	}
	
}
  	

/*****************************************************************/
/*Buzzer*/
/******************************************************************/
//Buzzer connect to Pin10 of Uno board
YahBoom_Roboduino_Beep::YahBoom_Roboduino_Beep(byte v_pinname)
{
	pinname = v_pinname;
}

YahBoom_Roboduino_Beep::~YahBoom_Roboduino_Beep()
{
	
}  

void YahBoom_Roboduino_Beep::YahBoom_Roboduino_Beep_Init()
{
    pinMode(pinname, OUTPUT);
}  

void YahBoom_Roboduino_Beep::setBuzzer_Tone(uint16_t frequency, uint32_t duration)
{
	int period = 1000000L / frequency;//1000000L
  	int pulse = period / 2;
	
  	for (long i = 0; i < duration * 200000L; i += period) 
  	{
		digitalWrite(pinname, 1);
    	delayMicroseconds(pulse);
    	digitalWrite(pinname, 0);
    	delayMicroseconds(pulse);
  	}
  	if(frequency==0)
  	delay(230*duration);	
	delay(20);
} 

void YahBoom_Roboduino_Beep::birthday()   
{
	int j;
	
	for(j=0;j<21;j++)
	{
		setBuzzer_Tone(pgm_read_word_near(&BIrthday[j][0]), pgm_read_word_near(&BIrthday[j][1]));	
	}
}

void YahBoom_Roboduino_Beep::ode()    
{
	int j;
	for(j=0;j<70;j++)
	{
		setBuzzer_Tone(pgm_read_word_near(&ODe[j][0]), pgm_read_word_near(&ODe[j][1]));	
	}
	
}

void YahBoom_Roboduino_Beep::star()  
{
	int j;
	for(j=0;j<42;j++)
	{
		setBuzzer_Tone(pgm_read_word_near(&STar[j][0]), pgm_read_word_near(&STar[j][1]));	
	}
}


void YahBoom_Roboduino_Beep::merryChristmas()  
{
	int j;
	for(j=0;j<36;j++)
	{
		setBuzzer_Tone(pgm_read_word_near(&MErryChristmas[j][0]), pgm_read_word_near(&MErryChristmas[j][1]));	
	}
}


void YahBoom_Roboduino_Beep::bingo()  
{
	int j;
	for(j=0;j<39;j++)
	{
		setBuzzer_Tone(pgm_read_word_near(&BIngo[j][0]), pgm_read_word_near(&BIngo[j][1]));	
	}
}


void YahBoom_Roboduino_Beep::music_Play(uint8_t v_song, uint8_t v_repeat)
{
	switch(v_song)
	{ 
		case enBirthday:
		{
			do
			{
				birthday();
			}
			while(v_repeat-1);					
			break;
		}
		case Ode:
		{
			do
			{
				ode();
			}
			while(v_repeat-1);					
			break;
		}
		case Star:
		{
			do
			{
				star();
			}
			while(v_repeat-1);					
			break;
		}
		case MerryChristmas:
		{
			do
			{
				merryChristmas();
			}
			while(v_repeat-1);					
			break;
		}
		case Bingo:
		{
			do
			{
				bingo();
			}
			while(v_repeat-1);					
			break;
		}
	}
}

/*********************************************************************/

/*Button*/    
/*********************************************************************/
//Button connect Pin7 of Uno board
YahBoom_Roboduino_Button::YahBoom_Roboduino_Button(byte v_pinname)
{
	pinname = v_pinname;
}

YahBoom_Roboduino_Button::~YahBoom_Roboduino_Button()
{
} 

void YahBoom_Roboduino_Button::YahBoom_Roboduino_Button_Init()
{	
	pinMode(pinname, INPUT);
} 

bool YahBoom_Roboduino_Button::Get_Button_State()      //Determine if the button is pressed
{
	int temp = 1;
	while (digitalRead(pinname));  
	while (!digitalRead(pinname))        //When the button press
	{
		delay(10);                    //delay 10ms
		if (digitalRead(pinname)  ==  LOW)//The second time to determine whether the button is pressed
		{    
			delay(10);   
			while (!digitalRead(pinname));  //Test whether the key is released    
			temp = 0;
		}    
	}
	if(temp == 0)
		return true;
	else
		return false;
}
/*********************************************************************/


/*Tracking module*/
/*********************************************************************/
//Output the analog value detected by the 3-channel Tracking sensor

YahBoom_Roboduino_Tracking::YahBoom_Roboduino_Tracking(byte v_pinname0, byte v_pinname1, byte v_pinname2)
{
	pinname0 = v_pinname0;
	pinname1 = v_pinname1;
	pinname2 = v_pinname2;
}

YahBoom_Roboduino_Tracking::~YahBoom_Roboduino_Tracking()
{
} 

void YahBoom_Roboduino_Tracking::YahBoom_Roboduino_Tracking_Init()
{
	pinMode(pinname0, INPUT);   //A0
	pinMode(pinname1, INPUT);   //A1
	pinMode(pinname2, INPUT);   //A2
} 

//Method 1:analog value
int YahBoom_Roboduino_Tracking::ReturnLTrackingValue()
{  
	int val_LTrackingSenser = 0;
	val_LTrackingSenser = analogRead(pinname2);   //A2 corresponds to left tracking sensor.
	return val_LTrackingSenser;
}

int YahBoom_Roboduino_Tracking::ReturnMTrackingValue()
{
	int val_MTrackingSenser = 0;
	val_MTrackingSenser = analogRead(pinname1);   //A1 corresponds to middle tracking sensor.
	return val_MTrackingSenser;
}

int YahBoom_Roboduino_Tracking::ReturnRTrackingValue()
{ 
	int val_RTrackingSenser = 0;
	val_RTrackingSenser = analogRead(pinname0);   //A0 corresponds to right tracking sensor.
	return val_RTrackingSenser;
}

//Method 2:digital value
//state: black:1, white:2
bool YahBoom_Roboduino_Tracking::LTracking_Senser_State(int state, int threshold)
{
	int val_LSenser = 0;
	int val = 0;
	val_LSenser = analogRead(pinname2);
	if(val_LSenser >= threshold)
		val = 1;
	else 
		val = 2;	
	if (state == val)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
//Method 2:digital value
//state: black:1, white:2
bool YahBoom_Roboduino_Tracking::MTracking_Senser_State(int state, int threshold)
{

	int val_MSenser = 0;
	int val = 0;
	val_MSenser = analogRead(pinname1);
	if(val_MSenser >= threshold)
		val = 1;
	else 
		val = 2;	
	if (state == val)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//Method 2:digital value
//state: black:1, white:2
bool YahBoom_Roboduino_Tracking::RTracking_Senser_State(int state, int threshold)
{

	int val_RSenser = 0;
	int val = 0;
	val_RSenser = analogRead(pinname0);
	if(val_RSenser >= threshold)
		val = 1;
	else 
		val = 2;	
	if (state == val)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*********************************************************************/
/*Ultrasonic module*/
//Ultrasonic function connect Pin12 of Uno board
YahBoom_Roboduino_Ultrasonic::YahBoom_Roboduino_Ultrasonic(byte v_pinname)
{
	pinname = v_pinname;
}

YahBoom_Roboduino_Ultrasonic::~YahBoom_Roboduino_Ultrasonic()
{
} 



float YahBoom_Roboduino_Ultrasonic::ReturnUltrasonicDistanceValue()  //Get distance
{  
	float distance = 0;
	pinMode(pinname,OUTPUT); 
	digitalWrite(pinname, LOW);
	delayMicroseconds(2);
	digitalWrite(pinname, HIGH);
	delayMicroseconds(10);
	digitalWrite(pinname, LOW);

	pinMode(pinname, INPUT);
	delayMicroseconds(50);
	distance = pulseIn(pinname, HIGH) / 58.00;

	return distance;
}

/*********************************************************************/


/*IR */
/******************************************************************/
//IR function connect A3 of Uno board

YahBoom_Roboduino_IRrecv::YahBoom_Roboduino_IRrecv(byte v_pinname)      
{
	last = millis();
	receive_number=0;
	pinname = v_pinname;
}

YahBoom_Roboduino_IRrecv::~YahBoom_Roboduino_IRrecv()
{
	
}

void YahBoom_Roboduino_IRrecv::YahBoom_Roboduino_IRrecv_Init()
{
	irrecv.enableIRIn();           //Initialize infrared decoding
	pinMode(pinname, INPUT_PULLUP);     //Set the IR_pin(A3) as input mode and internal pull-up mode2
	Serial.println("start1");
	
}
int YahBoom_Roboduino_IRrecv::IR_Deal()
{
	//int receive_number=0;
	//Serial.println("start2");
	if (irrecv.decode(&results))
	{
		//Serial.println("start3");
		Serial.println(results.value,HEX);
		switch (results.value)
		{
			case 0X00FF00FF: receive_number = 1;  break;
			case 0X00FF807F: receive_number = 4;  break;//
			case 0X00FF40BF: receive_number = 2;  break;
			case 0X00FF20DF: receive_number = 6;  break;//
			case 0X00FFA05F: receive_number = 3;  break;
			case 0X00FF609F: receive_number = 7;  break;//
			case 0X00FF10EF: receive_number = 8;  break;
			case 0X00FF906F: receive_number = 5;  break;//
			case 0X00FF50AF: receive_number = 9;  break;
			case 0X00FF30CF: receive_number = 10;  break;
			case 0X00FFB04F: receive_number = 12;  break;
			case 0X00FF708F: receive_number = 11;  break;
			case 0X00FF08F7: receive_number = 13;  break;
			case 0X00FF8877: receive_number = 14;  break;
			case 0X00FF48B7: receive_number = 15;  break;
			case 0X00FF28D7: receive_number = 16;  break;
			case 0X00FFA857: receive_number = 17;  break;
			case 0X00FF6897: receive_number = 18;  break;
			case 0X00FF18E7: receive_number = 19;  break;
			case 0X00FF9867: receive_number = 20;  break;
			case 0X00FF58A7: receive_number = 21;  break;
			//case 0xFFFFFFFF: receive_number = last_receive_number;	 break;
			default: break;
		}
		// 
		//last_receive_number = receive_number;
		last = millis();
		irrecv.resume(); // receive the next code
		//Serial.println(receive_number,DEC);
		// return receive_number; 
		//last_receive_number = receive_number;
	}

	/*if(receive_number==num)
	{
		last_receive_number = receive_number;
		//receive_number = 0;
		return 1;
	}

	else
	{
		last_receive_number = 0;
		return 0; 
	}*/
	else if (millis() - last > 120)
	{
		receive_number = 0;
		last = millis();
		//	 return 0;
	}
		return receive_number; 
}
 


/***Hardware initialization***/
YahBoom_Roboduino::YahBoom_Roboduino()
{
	pwm = Adafruit_PWMServoDriver(0x40); 
}

YahBoom_Roboduino::~YahBoom_Roboduino()
{
	
}

void YahBoom_Roboduino::YahBoom_Roboduino_Init()
{
	pwm.begin();
	pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates
	for (int i = 0; i < 16; i++)
	{
		pwm.setPWM(i, 0, 0);
	}

} 






