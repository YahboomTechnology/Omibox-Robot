/*******************
YahBoom_4WD.h

*******************/

#ifndef _YAHBOOM_4WDCAR_H__
#define _YAHBOOM_4WDCAR_H__

//导入Arduino核心头文件
#include<Arduino.h> 



/*LED*/
class YahBoom_4WD_LED
{
     private:
          byte pinName;

     public:
          
          YahBoom_4WD_LED(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_4WD_LED();  //析构函数

          /*LED控制*/

          void LED_ON(byte PinNum);
          void LED_OFF(byte PinNum);


};

/*FAN*/
class YahBoom_4WD_FAN
{
     private:
          byte pinName;

     public:
          
          YahBoom_4WD_FAN(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_4WD_FAN();  //析构函数

          /*FAN控制*/
          void FAN_ON(byte PinNum);
          void FAN_OFF(byte PinNum);

};

/*RGB——LED*/
class YahBoom_4WD_RGBLED
{
     private:
          byte pinNameR, pinNameG, pinNameB;

     public:
          
          YahBoom_4WD_RGBLED(byte pin1, byte pin2, byte pin3, byte PinMode);   //构造函数         
          ~YahBoom_4WD_RGBLED();  //析构函数

          /*LED控制*/
					void RGB_Contrl(int pinR_OnOff, int pinG_OnOff, int pinB_OnOff);
					void RGB_Contrl_PWM(int pinRValue, int pinGValue, int pinBValue);

};

class YahBoom_4WD_CloudServo
{
     private:
          byte pinName;

     public:
          
          YahBoom_4WD_CloudServo(byte pin1, byte PinMode);   //构造函数         
          ~YahBoom_4WD_CloudServo();  //析构函数

          /*舵机云台控制*/
					void CloudServo_Contrl(int v_iDegree, int v_iDelayTime);

};

/*蜂鸣器*/
class YahBoom_4WD_Beep
{
     private:
          byte pinName;

     public:
          
          YahBoom_4WD_Beep(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_4WD_Beep();  //析构函数

          /*蜂鸣器控制*/
          void BEEP_SetFreDelay(int Fre, int ms);
          void BEEP_ON(byte PinNum);
          void BEEP_OFF(byte PinNum);

};


/*按钮*/
class YahBoom_4WD_Button
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_Button(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_4WD_Button();  //析构函数

          /*按键读取*/
          int Get_Button_State(byte pin);

};

/*巡线*/
class YahBoom_4WD_BlackLine
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_BlackLine(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_4WD_BlackLine();  //析构函数

          /*左巡线1,2读取*/
          int Senser_State_L1(byte pin);
          int Senser_State_L2(byte pin);
          /*右巡线1,2读取*/
          int Senser_State_R1(byte pin);
          int Senser_State_R2(byte pin);
};

/*红外避障*/
class YahBoom_4WD_IRAvoid
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_IRAvoid(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_4WD_IRAvoid();  //析构函数

          /*左避障读取*/
          int Senser_State_L(byte pin);
          
          /*右避障读取*/
          int Senser_State_R(byte pin);

};

/*寻光*/
class YahBoom_4WD_LightFind
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_LightFind(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_4WD_LightFind();  //析构函数

          /*左光敏读取*/
          int Senser_State_L(byte pin);
          
          /*右光敏读取*/
          int Senser_State_R(byte pin);

};

/*颜色传感器*/
class YahBoom_4WD_ColorGet
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_ColorGet(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_4WD_ColorGet();  //析构函数

          /*读取颜色AD值*/
          int Senser_get_value(byte pin);
};

/*小车运动*/
class YahBoom_4WD_Motor
{
     private:
          byte pinLeftGo;
          byte pinLeftBack;
          byte pinRightGo;
          byte pinRightBack;

          byte pinLeftEn;
          byte pinRightEn;
          
     public:
          
          YahBoom_4WD_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack, byte pLEn, byte pREn);   //构造函数         
          ~YahBoom_4WD_Motor();  //析构函数

          /*小车运行状态*/
          void Run(int speed = 255, int delay_ms = 0);
          void Back(int speed = 255, int delay_ms = 0);
          void Left(int speed = 255, int delay_ms = 0);
          void Right(int speed = 255, int delay_ms = 0);
          void SpinLeft(int speed = 255, int delay_ms = 0);
          void SpinRight(int speed = 255, int delay_ms = 0);
          void Stop(int speed = 0, int delay_ms = 0);

          void LeftMotor(int direction = 0, int speed = 255);
          void RightMotor(int direction = 0, int speed = 255);


};


#endif