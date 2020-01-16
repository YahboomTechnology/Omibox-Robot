/*****************
LED.cpp

******************/

#include"YahBoom_BatCar.h"



/* #define INPUT 0x0 #define OUTPUT 0x1 #define INPUT_PULLUP 0x2 */ 
/*****************************************************************/ /*LED控制*/ 
YahBoom_BatCar_LED::YahBoom_BatCar_LED(byte pin, byte PinMode)   //构造函数 
{ 
		pinName = pin;
		pinMode(pinName, PinMode);
		digitalWrite(pinName, LOW);
}

YahBoom_BatCar_LED::~YahBoom_BatCar_LED()
{
    digitalWrite(pinName, LOW);
    pinMode(pinName, INPUT);
} 

void YahBoom_BatCar_LED::LED_ON(byte PinNum)
{
		digitalWrite(PinNum, HIGH);
}

void YahBoom_BatCar_LED::LED_OFF(byte PinNum)
{
		digitalWrite(PinNum, LOW);
}

void YahBoom_BatCar_LED::LED_Breath(byte PinNum)
{
		for (int i = 0; i < 255; i++)
  	{
	    analogWrite(PinNum, i);
	    delay(7);
  	}
	  delay(10);
	  for (int i = 255; i > 0; i--)
	  {
	    analogWrite(PinNum, i);
	    delay(7);
	  }		
}

/*****************************************************************/



/******************************************************************/

/*蜂鸣器控制*/
YahBoom_BatCar_Beep::YahBoom_BatCar_Beep(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
   	digitalWrite(pinName, HIGH);
}

YahBoom_BatCar_Beep::~YahBoom_BatCar_Beep()
{
		digitalWrite(pinName, HIGH);
    pinMode(pinName, INPUT);
} 

void YahBoom_BatCar_Beep::BEEP_SetFreDelay(int Fre, int ms)
{
		analogWrite(pinName, Fre);//PWM比例0~255调速，左右轮差异略增减
		delay(ms);
}

void YahBoom_BatCar_Beep::BEEP_ON(byte PinNum)
{

		digitalWrite(PinNum, LOW);
}

void YahBoom_BatCar_Beep::BEEP_OFF(byte PinNum)
{

		digitalWrite(PinNum, HIGH);
}

/*********************************************************************/

/******************************************************************/

/*按键*/
YahBoom_BatCar_Button::YahBoom_BatCar_Button(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
}

YahBoom_BatCar_Button::~YahBoom_BatCar_Button()
{
} 

int YahBoom_BatCar_Button::Get_Button_State(byte PinNum)
{

		return digitalRead(PinNum);
}


/*********************************************************************/

/******************************************************************/

/*巡线*/
YahBoom_BatCar_BlackLine::YahBoom_BatCar_BlackLine(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
}

YahBoom_BatCar_BlackLine::~YahBoom_BatCar_BlackLine()
{
} 

int YahBoom_BatCar_BlackLine::Senser_State_L(byte PinNum)
{

	return digitalRead(PinNum);
}

int YahBoom_BatCar_BlackLine::Senser_State_R(byte PinNum)
{

	return digitalRead(PinNum);
}

/*********************************************************************/

/******************************************************************/

/*红外避障*/
YahBoom_BatCar_IRAvoid::YahBoom_BatCar_IRAvoid(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
}

YahBoom_BatCar_IRAvoid::~YahBoom_BatCar_IRAvoid()
{
} 

int YahBoom_BatCar_IRAvoid::Senser_State_L(byte PinNum)
{

	return digitalRead(PinNum);
}

int YahBoom_BatCar_IRAvoid::Senser_State_R(byte PinNum)
{

	return digitalRead(PinNum);
}

/*********************************************************************/

/******************************************************************/

/*小车运动*/
YahBoom_BatCar_Motor::YahBoom_BatCar_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack, byte pLEn, byte pREn)
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

YahBoom_BatCar_Motor::~YahBoom_BatCar_Motor()
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

void YahBoom_BatCar_Motor::Run(int speed, int delay_ms)
{
	digitalWrite(pinLeftEn, HIGH);  // 左电机使能
  	digitalWrite(pinRightEn, HIGH);  // 右电机使能

  	digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	
}

void YahBoom_BatCar_Motor::Back(int speed, int delay_ms)
{
	digitalWrite(pinLeftEn, HIGH);  // 左电机使能
  	digitalWrite(pinRightEn, HIGH);  // 右电机使能

  	digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, HIGH);  //10 in4 0   
	analogWrite(pinLeftBack, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, HIGH);// 9 in1 0
	analogWrite(pinRightBack, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	

}

void YahBoom_BatCar_Motor::Left(int speed, int delay_ms)
{
	digitalWrite(pinLeftEn, HIGH);  // 左电机使能
  	digitalWrite(pinRightEn, HIGH);  // 右电机使能

  	digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, 0);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	

}

void YahBoom_BatCar_Motor::Right(int speed, int delay_ms)
{

	digitalWrite(pinLeftEn, HIGH);  // 左电机使能
  	digitalWrite(pinRightEn, HIGH);  // 右电机使能

  	digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, 0);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	
}

void YahBoom_BatCar_Motor::Stop(int speed, int delay_ms)
{
	digitalWrite(pinLeftEn, LOW);  // 左电机使能
  	digitalWrite(pinRightEn, LOW);  // 右电机使能

  	digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, 0);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, 0);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	

}

void YahBoom_BatCar_Motor::SpinLeft(int speed, int delay_ms)
{

	digitalWrite(pinLeftEn, HIGH);  // 左电机使能
  	digitalWrite(pinRightEn, HIGH);  // 右电机使能

  	digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, HIGH);  //10 in4 0   
	analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);
}

void YahBoom_BatCar_Motor::SpinRight(int speed, int delay_ms)
{

	digitalWrite(pinLeftEn, HIGH);  // 左电机使能
  	digitalWrite(pinRightEn, HIGH);  // 右电机使能

  	digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, HIGH);// 9 in1 0
	analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);
}

void YahBoom_BatCar_Motor::LeftMotor(int direction, int speed)
{
	

	if(direction == 1) //前进
	{
		digitalWrite(pinLeftEn, HIGH);  // 左电机使能
		digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, LOW);  //10 in4 0   
		analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减
	}
	else if (direction == 2) //后退
	{
		digitalWrite(pinLeftEn, HIGH);  // 左电机使能
		digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, HIGH);  //10 in4 0   
		analogWrite(pinLeftBack, speed);//PWM比例0~255调速，左右轮差异略增减
	}
	else //停止
	{
		digitalWrite(pinLeftEn, LOW);  // 左电机使能
		digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	}
}

void YahBoom_BatCar_Motor::RightMotor(int direction, int speed)
{


	if(direction == 1) //前进
	{
		digitalWrite(pinRightEn, HIGH);  // 左电机使能
		digitalWrite(pinRightGo, HIGH);  // 右电机前进 6 in3 1
		digitalWrite(pinRightBack, LOW);  //10 in4 0   
		analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	}
	else if (direction == 2) //后退
	{
		digitalWrite(pinRightEn, HIGH);  // 左电机使能
		digitalWrite(pinRightGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinRightBack, HIGH);  //10 in4 0   
		analogWrite(pinRightBack, speed);//PWM比例0~255调速，左右轮差异略增减
	}
	else //停止
	{
		digitalWrite(pinRightEn, LOW);  // 左电机使能
		digitalWrite(pinRightGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinRightBack, LOW);  //10 in4 0   
	}
	
}
  	

/*********************************************************************/
/*亚博智能AR传感器套件
/*********************************************************************/
/*蜂鸣器控制*/
YahBoom_ARSensor_Beep::YahBoom_ARSensor_Beep(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
   	digitalWrite(pinName, LOW);
}

YahBoom_ARSensor_Beep::~YahBoom_ARSensor_Beep()
{
		digitalWrite(pinName, LOW);
    pinMode(pinName, INPUT);
} 

void YahBoom_ARSensor_Beep::BEEP_SetFreDelay(int Fre, int ms)
{
		analogWrite(pinName, Fre);//PWM比例0~255调速，左右轮差异略增减
		delay(ms);
}

void YahBoom_ARSensor_Beep::BEEP_ON(byte PinNum)
{

		digitalWrite(PinNum, HIGH);
}

void YahBoom_ARSensor_Beep::BEEP_OFF(byte PinNum)
{

		digitalWrite(PinNum, LOW);
}

/*1位数码管*/

YahBoom_ARSensor_SMG1::YahBoom_ARSensor_SMG1()
{
	int i;
	a = 7;  // 数字IO口7 连接数码管a段
	b = 6;  // 数字IO口6 连接数码管b段
	c = 5;  // 数字IO口5 连接数码管c段
	d = 11; // 数字IO口11 连接数码管d段
	e = 10; // 数字IO口10 连接数码管e段
	f = 8;  // 数字IO口8 连接数码管f段
	g = 9;  // 数字IO口9 连接数码管g段
	dp = 4; // 数字IO口4 连接数码管小数点段
	
	for (i = 4; i <= 11; i++)
    pinMode(i, OUTPUT); //设置4-11为输出口
}

YahBoom_ARSensor_SMG1::~YahBoom_ARSensor_SMG1()
{
	int i;
	for (i = 4; i <= 11; i++)
    digitalWrite(i, LOW); //设置4-11为低
	for (i = 4; i <= 11; i++)
    pinMode(i, INPUT); //设置4-11为输出口
}
void YahBoom_ARSensor_SMG1::digital_0(void) //显示数字0 abcdef
{
  unsigned char j;
  digitalWrite(d, HIGH); //点亮d段
  digitalWrite(e, HIGH); //点亮e段
  for (j = 5; j <= 8; j++) //abcf
    digitalWrite(j, HIGH);

  digitalWrite(g, LOW);  //灭g
  digitalWrite(dp, LOW); //小数点不点亮
}
void YahBoom_ARSensor_SMG1::digital_1(void) //显示数字1
{
  unsigned char j;
  digitalWrite(c, HIGH); //点亮c段
  digitalWrite(b, HIGH); //点亮b段
  for (j = 7; j <= 11; j++) //7~11口相应段拉低：a,f,g,e,d
    digitalWrite(j, LOW);
  digitalWrite(dp, LOW); //小数点不点亮
}
void YahBoom_ARSensor_SMG1::digital_2(void) //显示数字2
{
  unsigned char j;
  digitalWrite(b, HIGH);
  digitalWrite(a, HIGH);
  for (j = 9; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(c, LOW);
  digitalWrite(f, LOW);
}
void YahBoom_ARSensor_SMG1::digital_3(void) //显示数字3
{
  unsigned char j;
  digitalWrite(g, HIGH);
  digitalWrite(d, HIGH);
  for (j = 5; j <= 7; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(f, LOW);
  digitalWrite(e, LOW);
}
void YahBoom_ARSensor_SMG1::digital_4(void) //显示数字4
{
  digitalWrite(c, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(a, LOW);
  digitalWrite(e, LOW);
  digitalWrite(d, LOW);
}
void YahBoom_ARSensor_SMG1::digital_5(void) //显示数字5
{
  unsigned char j;
  for (j = 7; j <= 9; j++)
    digitalWrite(j, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(b, LOW);
  digitalWrite(e, LOW);
}
void YahBoom_ARSensor_SMG1::digital_6(void) //显示数字6
{
  unsigned char j;
  for (j = 7; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(b, LOW);
}
void YahBoom_ARSensor_SMG1::digital_7(void) //显示数字7
{
  unsigned char j;
  for (j = 5; j <= 7; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
  for (j = 8; j <= 11; j++)
    digitalWrite(j, LOW);
}
void YahBoom_ARSensor_SMG1::digital_8(void) //显示数字8
{
  unsigned char j;
  for (j = 5; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
}

void YahBoom_ARSensor_SMG1::digital_9(void) //显示数字9
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}
void YahBoom_ARSensor_SMG1::SMG1_DisPlay(char v_cNum)
{
		switch (v_cNum)
    {
      //case '.' : digital_dian(); break;
      case 0 : digital_0(); break;
      case 1 : digital_1(); break;
      case 2 : digital_2(); break;
      case 3 : digital_3(); break;
      case 4 : digital_4(); break;
      case 5 : digital_5(); break;
      case 6 : digital_6(); break;
      case 7 : digital_7(); break;
      case 8 : digital_8(); break;
      case 9 : digital_9(); break;
      default: break;
    }
}

/*4位数码管*/
#define SEG_A 2  //Arduino Pin2--->SegLed Pin11
#define SEG_B 3  //Arduino Pin3--->SegLed Pin7
#define SEG_C 4  //Arduino Pin4--->SegLed Pin4
#define SEG_D 5  //Arduino Pin5--->SegLed Pin2
#define SEG_E 6  //Arduino Pin6--->SegLed Pin1
#define SEG_F 7  //Arduino Pin7--->SegLed Pin10
#define SEG_G 8  //Arduino Pin8--->SegLed Pin5    
#define SEG_H 9  //Arduino Pin9--->SegLed Pin3

#define COM1 10  //Arduino Pin10--->SegLed Pin12
#define COM2 11  //Arduino Pin11--->SegLed Pin9
#define COM3 12  //Arduino Pin12--->SegLed Pin8
#define COM4 13  //Arduino Pin13--->SegLed Pin6
unsigned char table[10][8] =
{
  {0,	0,	1,	1,	1,	1,	1,	1},			//0
  {0,	0,	0,	0,	0,	1,	1,	0},			//1
  {0,	1,	0,	1,	1,	0,	1,	1},			//2
  {0,	1,	0,	0,	1,	1,	1,	1},			//3
  {0,	1,	1,	0,	0,	1,	1,	0},			//4
  {0,	1,	1,	0,	1,	1,	0,	1},			//5
  {0,	1,	1,	1,	1,	1,	0,	1},			//6
  {0,	0,	0,	0,	0,	1,	1,	1},			//7
  {0,	1,	1,	1,	1,	1,	1,	1},			//8
  {0,	1,	1,	0,	1,	1,	1,	1}			//9
};

YahBoom_ARSensor_SMG4::YahBoom_ARSensor_SMG4()
{	
  pinMode(SEG_A, OUTPUT);		//设置为输出引脚
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_H, OUTPUT);

  pinMode(COM1, OUTPUT);
  pinMode(COM2, OUTPUT);
  pinMode(COM3, OUTPUT);
  pinMode(COM4, OUTPUT);
}

YahBoom_ARSensor_SMG4::~YahBoom_ARSensor_SMG4()
{
  pinMode(SEG_A, INPUT);		//设置为输入引脚
  pinMode(SEG_B, INPUT);
  pinMode(SEG_C, INPUT);
  pinMode(SEG_D, INPUT);
  pinMode(SEG_E, INPUT);
  pinMode(SEG_F, INPUT);
  pinMode(SEG_G, INPUT);
  pinMode(SEG_H, INPUT);

  pinMode(COM1, INPUT);
  pinMode(COM2, INPUT);
  pinMode(COM3, INPUT);
  pinMode(COM4, INPUT);
}

void YahBoom_ARSensor_SMG4::Display(unsigned char com, unsigned char num)
{
  digitalWrite(SEG_A, LOW);			//去除余晖
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_C, LOW);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_H, LOW);

  switch (com)						//选通位选
  {
    case 1:
      digitalWrite(COM1, LOW);		//选择位1
      digitalWrite(COM2, HIGH);
      digitalWrite(COM3, HIGH);
      digitalWrite(COM4, HIGH);
      break;
    case 2:
      digitalWrite(COM1, HIGH);
      digitalWrite(COM2, LOW);		//选择位2
      digitalWrite(COM3, HIGH);
      digitalWrite(COM4, HIGH);
      break;
    case 3:
      digitalWrite(COM1, HIGH);
      digitalWrite(COM2, HIGH);
      digitalWrite(COM3, LOW);		//选择位3
      digitalWrite(COM4, HIGH);
      break;
    case 4:
      digitalWrite(COM1, HIGH);
      digitalWrite(COM2, HIGH);
      digitalWrite(COM3, HIGH);
      digitalWrite(COM4, LOW);		//选择位4
      break;
    default: break;
  }

  digitalWrite(SEG_A, table[num][7]);			//a查询码值表
  digitalWrite(SEG_B, table[num][6]);
  digitalWrite(SEG_C, table[num][5]);
  digitalWrite(SEG_D, table[num][4]);
  digitalWrite(SEG_E, table[num][3]);
  digitalWrite(SEG_F, table[num][2]);
  digitalWrite(SEG_G, table[num][1]);
  digitalWrite(SEG_H, table[num][0]);
}

void YahBoom_ARSensor_SMG4::SMG4_DisPlay(int v_iNum)
{
	int smg4[4];
	smg4[0] = v_iNum / 1000;
	smg4[1] = v_iNum % 1000 / 100;
	smg4[2] = v_iNum % 100 / 10;
	smg4[3] = v_iNum % 10;
	
	for (int i = 1; i <= 4; i++)
  {
    switch (smg4[i-1])
    {
      case 0 : Display(i, 0); break;
      case 1 : Display(i, 1); break;
      case 2 : Display(i, 2); break;
      case 3 : Display(i, 3); break;
      case 4 : Display(i, 4); break;
      case 5 : Display(i, 5); break;
      case 6 : Display(i, 6); break;
      case 7 : Display(i, 7); break;
      case 8 : Display(i, 8); break;
      case 9 : Display(i, 9); break;
      default: break;
    }
  }
}

/*********************************************************************/

/******************************************************************/

/*按键*/
YahBoom_ARSensor_TouchBtn::YahBoom_ARSensor_TouchBtn(byte pin, byte PinMode)
{
    pinName = pin;
   	pinMode(pinName, PinMode);
}

YahBoom_ARSensor_TouchBtn::~YahBoom_ARSensor_TouchBtn()
{
} 

int YahBoom_ARSensor_TouchBtn::Get_Button_State(byte PinNum)
{
		
		int touchval = analogRead(PinNum); //读取A0口的电压值并赋值到touchval
	  if (touchval > 500)
	  {
	    return 1;	
	  }
	  else
	  {
	    return 0;
	  }
}

/*点阵*/
	
Yahboom_ARsenser_Lattice::Yahboom_ARsenser_Lattice()
{
	
	R[0] =2; R[1] =3; R[2] =4; R[3] =5; R[4] =A3; R[5] =A2; R[6] =A1; R[7] =A0;
	C[0] =6; C[1] =7; C[2] =8; C[3] =9; C[4] =10; C[5] =11; C[6] =12; C[7] =13;
	for (int i = 0; i < 8; i++)
  {
    pinMode(R[i], OUTPUT);
    pinMode(C[i], OUTPUT);
  }
}

Yahboom_ARsenser_Lattice::~Yahboom_ARsenser_Lattice()
{
	for (int i = 0; i < 8; i++)
  {
    pinMode(R[i], INPUT);
    pinMode(C[i], INPUT);
  }	
}

void Yahboom_ARsenser_Lattice::Display(int Row, unsigned char temp)   //显示函数
{
	
    unsigned char data[8] = {0};
    digitalWrite(R[Row], HIGH); //选通第c列

    //循环
    for (int c = 0; c < 8; c++)
    {  
      data[c] = ((temp>>(7-c))&0x01);
      data[c] = ((data[c] == 0)?1:0);
     
      digitalWrite(C[c], data[c]);
    }
    delay(1);
   
    digitalWrite(R[Row], LOW);
    for (int i = 0; i < 8; i++)
    {
    	digitalWrite(C[i], HIGH);    
    }	
    
}

//AR车

/*小车运动*/
YahBoom_ARCar_Motor::YahBoom_ARCar_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack)
{
    pinLeftGo = pLGo;
    pinLeftBack = pLBack;
    pinRightGo = pRGo;
    pinRightBack = pRBack;


   	pinMode(pinLeftGo, OUTPUT);
   	pinMode(pinLeftBack, OUTPUT);
   	pinMode(pinRightGo, OUTPUT);
   	pinMode(pinRightBack, OUTPUT);

}

YahBoom_ARCar_Motor::~YahBoom_ARCar_Motor()
{

		digitalWrite(pinLeftGo, LOW);
   	digitalWrite(pinLeftBack, LOW);
   	digitalWrite(pinRightGo, LOW);
   	digitalWrite(pinRightBack, LOW);


		pinMode(pinLeftGo, INPUT);
   	pinMode(pinLeftBack, INPUT);
   	pinMode(pinRightGo, INPUT);
   	pinMode(pinRightBack, INPUT);

} 

void YahBoom_ARCar_Motor::Run(int speed, int delay_ms)
{


  	digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, LOW);  //10 in4 0   
		analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减

		digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
		digitalWrite(pinRightBack, LOW);// 9 in1 0
		analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
		delay(delay_ms);	
}

void YahBoom_ARCar_Motor::Back(int speed, int delay_ms)
{

  	digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, HIGH);  //10 in4 0   
	analogWrite(pinLeftBack, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, HIGH);// 9 in1 0
	analogWrite(pinRightBack, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	

}

void YahBoom_ARCar_Motor::Left(int speed, int delay_ms)
{


  	digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, 0);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	

}

void YahBoom_ARCar_Motor::Right(int speed, int delay_ms)
{

  	digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, 0);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	
}

void YahBoom_ARCar_Motor::Stop(int speed, int delay_ms)
{

  	digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, 0);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, 0);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);	

}

void YahBoom_ARCar_Motor::SpinLeft(int speed, int delay_ms)
{
  	digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, HIGH);  //10 in4 0   
	analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, HIGH);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, LOW);// 9 in1 0
	analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);
}

void YahBoom_ARCar_Motor::SpinRight(int speed, int delay_ms)
{

  digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
	digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减

	digitalWrite(pinRightGo, LOW);  // 左电机前进 5 in2 1
	digitalWrite(pinRightBack, HIGH);// 9 in1 0
	analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	delay(delay_ms);
}

void YahBoom_ARCar_Motor::LeftMotor(int direction, int speed)
{
	

	if(direction == 1) //前进
	{
		digitalWrite(pinLeftGo, HIGH);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, LOW);  //10 in4 0   
		analogWrite(pinLeftGo, speed);//PWM比例0~255调速，左右轮差异略增减
	}
	else if (direction == 2) //后退
	{
		digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, HIGH);  //10 in4 0   
		analogWrite(pinLeftBack, speed);//PWM比例0~255调速，左右轮差异略增减
	}
	else //停止
	{
		digitalWrite(pinLeftGo, LOW);  // 右电机前进 6 in3 1
		digitalWrite(pinLeftBack, LOW);  //10 in4 0   
	}
}

void YahBoom_ARCar_Motor::RightMotor(int direction, int speed)
{

	if(direction == 1) //前进
	{
		digitalWrite(pinRightGo, HIGH);  // 右电机前进 6 in3 1
		digitalWrite(pinRightBack, LOW);  //10 in4 0   
		analogWrite(pinRightGo, speed);//PWM比例0~255调速，左右轮差异略增减
	}
	else if (direction == 2) //后退
	{
		digitalWrite(pinRightGo, LOW);  	// 右电机前进 6 in3 1
		digitalWrite(pinRightBack, HIGH);  //10 in4 0   
		analogWrite(pinRightBack, speed);	//PWM比例0~255调速，左右轮差异略增减
	}
	else //停止
	{
		digitalWrite(pinRightGo, LOW);  	// 右电机前进 6 in3 1
		digitalWrite(pinRightBack, LOW);  //10 in4 0   
	}
	
}

