/*******************
YahBoom_4WD.h

*******************/

#ifndef _YAHBOOM_4WDCAR_H__
#define _YAHBOOM_4WDCAR_H__

//����Arduino����ͷ�ļ�
#include<Arduino.h> 



/*LED*/
class YahBoom_4WD_LED
{
     private:
          byte pinName;

     public:
          
          YahBoom_4WD_LED(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_4WD_LED();  //��������

          /*LED����*/

          void LED_ON(byte PinNum);
          void LED_OFF(byte PinNum);


};

/*FAN*/
class YahBoom_4WD_FAN
{
     private:
          byte pinName;

     public:
          
          YahBoom_4WD_FAN(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_4WD_FAN();  //��������

          /*FAN����*/
          void FAN_ON(byte PinNum);
          void FAN_OFF(byte PinNum);

};

/*RGB����LED*/
class YahBoom_4WD_RGBLED
{
     private:
          byte pinNameR, pinNameG, pinNameB;

     public:
          
          YahBoom_4WD_RGBLED(byte pin1, byte pin2, byte pin3, byte PinMode);   //���캯��         
          ~YahBoom_4WD_RGBLED();  //��������

          /*LED����*/
					void RGB_Contrl(int pinR_OnOff, int pinG_OnOff, int pinB_OnOff);
					void RGB_Contrl_PWM(int pinRValue, int pinGValue, int pinBValue);

};

class YahBoom_4WD_CloudServo
{
     private:
          byte pinName;

     public:
          
          YahBoom_4WD_CloudServo(byte pin1, byte PinMode);   //���캯��         
          ~YahBoom_4WD_CloudServo();  //��������

          /*�����̨����*/
					void CloudServo_Contrl(int v_iDegree, int v_iDelayTime);

};

/*������*/
class YahBoom_4WD_Beep
{
     private:
          byte pinName;

     public:
          
          YahBoom_4WD_Beep(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_4WD_Beep();  //��������

          /*����������*/
          void BEEP_SetFreDelay(int Fre, int ms);
          void BEEP_ON(byte PinNum);
          void BEEP_OFF(byte PinNum);

};


/*��ť*/
class YahBoom_4WD_Button
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_Button(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_4WD_Button();  //��������

          /*������ȡ*/
          int Get_Button_State(byte pin);

};

/*Ѳ��*/
class YahBoom_4WD_BlackLine
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_BlackLine(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_4WD_BlackLine();  //��������

          /*��Ѳ��1,2��ȡ*/
          int Senser_State_L1(byte pin);
          int Senser_State_L2(byte pin);
          /*��Ѳ��1,2��ȡ*/
          int Senser_State_R1(byte pin);
          int Senser_State_R2(byte pin);
};

/*�������*/
class YahBoom_4WD_IRAvoid
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_IRAvoid(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_4WD_IRAvoid();  //��������

          /*����϶�ȡ*/
          int Senser_State_L(byte pin);
          
          /*�ұ��϶�ȡ*/
          int Senser_State_R(byte pin);

};

/*Ѱ��*/
class YahBoom_4WD_LightFind
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_LightFind(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_4WD_LightFind();  //��������

          /*�������ȡ*/
          int Senser_State_L(byte pin);
          
          /*�ҹ�����ȡ*/
          int Senser_State_R(byte pin);

};

/*��ɫ������*/
class YahBoom_4WD_ColorGet
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_4WD_ColorGet(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_4WD_ColorGet();  //��������

          /*��ȡ��ɫADֵ*/
          int Senser_get_value(byte pin);
};

/*С���˶�*/
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
          
          YahBoom_4WD_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack, byte pLEn, byte pREn);   //���캯��         
          ~YahBoom_4WD_Motor();  //��������

          /*С������״̬*/
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