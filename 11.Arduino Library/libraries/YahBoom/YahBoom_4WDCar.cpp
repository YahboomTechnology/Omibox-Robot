/*****************
YahBoom_4WDCar.cpp
******************/

#include"YahBoom_4WDCar.h"




/* #define INPUT 0x0 #define OUTPUT 0x1 #define INPUT_PULLUP 0x2 */ 
/*****************************************************************/ 
/*LED控制*/ 
/*****************************************************************/
YahBoom_4WD_LED::YahBoom_4WD_LED(byte pin, byte PinMode)   //构造函数 
{ 
		pinName = pin;
		pinMode(pinName, PinMode);
		digitalWrite(pinName, LOW);
}

YahBoom_4WD_LED::~YahBoom_4WD_LED()
{
    digitalWrite(pinName, LOW);
    pinMode(pinName, INPUT);
} 

void YahBoom_4WD_LED::LED_ON(byte PinNum)
{
		digitalWrite(PinNum, HIGH);
}

void YahBoom_4WD_LED::LED_OFF(byte PinNum)
{
		digitalWrite(PinNum, LOW);
}
/*****************************************************************/
//风扇
/*****************************************************************/
YahBoom_4WD_FAN::YahBoom_4WD_FAN(byte pin, byte PinMode)   //构造函数 
{ 
		pinName = pin;
		pinMode(pinName, PinMode);
		digitalWrite(pinName, LOW);
}

YahBoom_4WD_FAN::~YahBoom_4WD_FAN()
{
    digitalWrite(pinName, LOW);
    pinMode(pinName, INPUT);
} 

void YahBoom_4WD_FAN::FAN_ON(byte PinNum)
{
		digitalWrite(PinNum, LOW);
}

void YahBoom_4WD_FAN::FAN_OFF(byte PinNum)
{
		digitalWrite(PinNum, HIGH);
}

/*****************************************************************/
/*七彩LED控制*/ 
/*****************************************************************/ 

YahBoom_4WD_RGBLED::YahBoom_4WD_RGBLED(byte pin1, byte pin2, byte pin3, byte PinMode)   //构造函数 
{ 
		pinNameR = pin1; 
		pinNameG = pin2; 
		pinNameB = pin3;
		pinMode(pinNameR, PinMode);
		pinMode(pinNameG, PinMode);
		pinMode(pinNameB, PinMode);
		digitalWrite(pinNameR, LOW);
		digitalWrite(pinNameG, LOW);
		digitalWrite(pinNameB, LOW);
}

YahBoom_4WD_RGBLED::~YahBoom_4WD_RGBLED()
{
		digitalWrite(pinNameR, LOW);
		digitalWrite(pinNameG, LOW);
		digitalWrite(pinNameB, LOW);
    pinMode(pinNameR, INPUT);
		pinMode(pinNameG, INPUT);
		pinMode(pinNameB, INPUT);
} 

void YahBoom_4WD_RGBLED::RGB_Contrl(int pinR_OnOff, int pinG_OnOff, int pinB_OnOff)
{
		digitalWrite(pinNameR, pinR_OnOff);
		digitalWrite(pinNameG, pinG_OnOff);
		digitalWrite(pinNameB, pinB_OnOff);
}

void YahBoom_4WD_RGBLED::RGB_Contrl_PWM(int pinRValue, int pinGValue, int pinBValue)
{
		analogWrite(pinNameR, pinRValue);
		analogWrite(pinNameG, pinGValue);
		analogWrite(pinNameB, pinBValue);
}
/*****************************************************************/
/*舵机云台*/
/*****************************************************************/
YahBoom_4WD_CloudServo::YahBoom_4WD_CloudServo(byte pin1, byte PinMode)   //构造函数 
{ 
		pinName = pin1; 
		pinMode(pinName, PinMode);
		digitalWrite(pinName, LOW);
}

YahBoom_4WD_CloudServo::~YahBoom_4WD_CloudServo()
{
		digitalWrite(pinName, LOW);
    pinMode(pinName, INPUT);
} 

void YahBoom_4WD_CloudServo::CloudServo_Contrl(int v_iDegree, int v_iDelayTime)
{
		for(int i = 15; i > 0; i--)
		{
			int Angle = map(v_iDegree, 0,180, 500,2480);
			digitalWrite(pinName, HIGH);//将舵机接口电平至高
			delayMicroseconds(Angle);//延时脉宽值的微秒数
			digitalWrite(pinName, LOW);//将舵机接口电平至低
			delay(20 - v_iDegree/1000);			
		}
	  
	  delay(v_iDelayTime);
	
}

/*****************************************************************/
/*蜂鸣器控制*/
/******************************************************************/

YahBoom_4WD_Beep::YahBoom_4WD_Beep(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
   	digitalWrite(pinName, HIGH);
}

YahBoom_4WD_Beep::~YahBoom_4WD_Beep()
{
		digitalWrite(pinName, HIGH);
    pinMode(pinName, INPUT);
} 

void YahBoom_4WD_Beep::BEEP_SetFreDelay(int Fre, int ms)
{
		analogWrite(pinName, Fre);//PWM比例0~255调速，左右轮差异略增减
		delay(ms);
}

void YahBoom_4WD_Beep::BEEP_ON(byte PinNum)
{

		digitalWrite(PinNum, LOW);
}

void YahBoom_4WD_Beep::BEEP_OFF(byte PinNum)
{

		digitalWrite(PinNum, HIGH);
}

/*********************************************************************/
/*按键*/
/*********************************************************************/

YahBoom_4WD_Button::YahBoom_4WD_Button(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
}

YahBoom_4WD_Button::~YahBoom_4WD_Button()
{
} 

int YahBoom_4WD_Button::Get_Button_State(byte PinNum)
{

		return digitalRead(PinNum);
}


/*********************************************************************/
/*巡线*/
/*********************************************************************/

YahBoom_4WD_BlackLine::YahBoom_4WD_BlackLine(byte pin, byte PinMode)
{
		pinName = pin; 
   	pinMode(pinName, PinMode);
}

YahBoom_4WD_BlackLine::~YahBoom_4WD_BlackLine()
{
} 

int YahBoom_4WD_BlackLine::Senser_State_L1(byte pin)
{
	return digitalRead(pin);
}

int YahBoom_4WD_BlackLine::Senser_State_L2(byte pin)
{
	return digitalRead(pin);
}

int YahBoom_4WD_BlackLine::Senser_State_R1(byte pin)
{
	return digitalRead(pin);
}

int YahBoom_4WD_BlackLine::Senser_State_R2(byte pin)
{
	return digitalRead(pin);
}

/*********************************************************************/

/*********************************************************************/

/*红外避障*/
YahBoom_4WD_IRAvoid::YahBoom_4WD_IRAvoid(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
}

YahBoom_4WD_IRAvoid::~YahBoom_4WD_IRAvoid()
{
} 

int YahBoom_4WD_IRAvoid::Senser_State_L(byte PinNum)
{

	return digitalRead(PinNum);
}

int YahBoom_4WD_IRAvoid::Senser_State_R(byte PinNum)
{

	return digitalRead(PinNum);
}

/*********************************************************************/
/*寻光*/
/*********************************************************************/

YahBoom_4WD_LightFind::YahBoom_4WD_LightFind(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
}

YahBoom_4WD_LightFind::~YahBoom_4WD_LightFind()
{
} 

int YahBoom_4WD_LightFind::Senser_State_L(byte PinNum)
{

	return digitalRead(PinNum);
}

int YahBoom_4WD_LightFind::Senser_State_R(byte PinNum)
{

	return digitalRead(PinNum);
}

/*********************************************************************/
/*颜色传感器*/
/*********************************************************************/

YahBoom_4WD_ColorGet::YahBoom_4WD_ColorGet(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
}

YahBoom_4WD_ColorGet::~YahBoom_4WD_ColorGet()
{
} 

int YahBoom_4WD_ColorGet::Senser_get_value(byte PinNum)
{
	return analogRead(PinNum);
}


/*********************************************************************/
/*小车运动*/
/*********************************************************************/

YahBoom_4WD_Motor::YahBoom_4WD_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack, byte pLEn, byte pREn)
{
    pinLeftGo = pLGo;
    pinLeftBack = pLBack;
    pinRightGo = pRGo;
    pinRightBack = pRBack;
    pinLeftEn = pLEn;
    pinRightEn = pREn;

   	pinMode(pinLeftGo, OUTPUT);
   	pinMode(pinLeftBack, OUTPUT);
   	pinMode(pinRightGo, OUTPUT);
   	pinMode(pinRightBack, OUTPUT);
   	pinMode(pinLeftEn, OUTPUT);
   	pinMode(pinRightEn, OUTPUT);
}

YahBoom_4WD_Motor::~YahBoom_4WD_Motor()
{

		digitalWrite(pinLeftGo, LOW);
   	digitalWrite(pinLeftBack, LOW);
   	digitalWrite(pinRightGo, LOW);
   	digitalWrite(pinRightBack, LOW);
   	digitalWrite(pinLeftEn, LOW);
   	digitalWrite(pinRightEn, LOW);

		pinMode(pinLeftGo, INPUT);
   	pinMode(pinLeftBack, INPUT);
   	pinMode(pinRightGo, INPUT);
   	pinMode(pinRightBack, INPUT);
   	pinMode(pinLeftEn, INPUT);
   	pinMode(pinRightEn, INPUT);
} 

void YahBoom_4WD_Motor::Run(int speed, int delay_ms)
{
	analogWrite(pinLeftEn, speed);  // 左电机使能
  analogWrite(pinRightEn, speed);  // 右电机使能

  digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   

	digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0

	delay(delay_ms);	
}

void YahBoom_4WD_Motor::Back(int speed, int delay_ms)
{
	analogWrite(pinLeftEn, speed);  // 左电机使能
  analogWrite(pinRightEn, speed);  // 右电机使能

  digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, HIGH);  //10 in4 0   

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, HIGH);// 9 in1 0

	delay(delay_ms);	
}

void YahBoom_4WD_Motor::Left(int speed, int delay_ms)
{
	analogWrite(pinLeftEn, 0);  // 左电机使能
  analogWrite(pinRightEn, speed);  // 右电机使能

  digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   

	digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0

	delay(delay_ms);	

}

void YahBoom_4WD_Motor::Right(int speed, int delay_ms)
{

	analogWrite(pinLeftEn, speed);  // 左电机使能
  analogWrite(pinRightEn, 0);  // 右电机使能

  digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	
	delay(delay_ms);	
}

void YahBoom_4WD_Motor::Stop(int speed, int delay_ms)
{
	digitalWrite(pinLeftEn, LOW);  // 左电机使能
  digitalWrite(pinRightEn, LOW);  // 右电机使能

  digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0

	delay(delay_ms);	
}

void YahBoom_4WD_Motor::SpinLeft(int speed, int delay_ms)
{

	analogWrite(pinLeftEn, speed);  // 左电机使能
  analogWrite(pinRightEn, speed);  // 右电机使能

  digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, HIGH);  //10 in4 0   

	digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0

	delay(delay_ms);
}

void YahBoom_4WD_Motor::SpinRight(int speed, int delay_ms)
{

	analogWrite(pinLeftEn, speed);  // 左电机使能
  analogWrite(pinRightEn, speed);  // 右电机使能

  digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, HIGH);// 9 in1 0

	delay(delay_ms);
}

void YahBoom_4WD_Motor::LeftMotor(int direction, int speed)
{
	

	if(direction == 1) //前进
	{
		analogWrite(pinLeftEn, speed);  // 左电机使能
		
		digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	}
	else if (direction == 2) //后退
	{
		analogWrite(pinLeftEn, speed);  // 左电机使能
		digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, HIGH);  //10 in4 0   

	}
	else //停止
	{
		digitalWrite(pinLeftEn, LOW);  // 左电机使能
		digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	}
}

void YahBoom_4WD_Motor::RightMotor(int direction, int speed)
{


	if(direction == 1) //前进
	{
 		analogWrite(pinRightEn, speed);  // 右电机使能
		digitalWrite(pinRightGo, HIGH);  // 右电机前进 6 in3 1
		digitalWrite(pinRightBack, LOW);  //10 in4 0   
	}
	else if (direction == 2) //后退
	{
 		analogWrite(pinRightEn, speed);  // 右电机使能
		digitalWrite(pinRightGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinRightBack, HIGH);  //10 in4 0   
	}
	else //停止
	{
		digitalWrite(pinRightEn, LOW);  // 左电机使能
		digitalWrite(pinRightGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinRightBack, LOW);  //10 in4 0   
	}
	
}
  	

/*********************************************************************/
      


