/*******************
YahBoom_BatCar.h

*******************/

#ifndef _YAHBOOM_BATCAR_H__
#define _YAHBOOM_BATCAR_H__

//����Arduino����ͷ�ļ�
#include<Arduino.h>  


/*LED*/
class YahBoom_BatCar_LED
{
     private:
          byte pinName;

     public:
          
          YahBoom_BatCar_LED(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_BatCar_LED();  //��������

          /*LED����*/

          void LED_ON(byte PinNum);
          void LED_OFF(byte PinNum);
					void LED_Breath(byte PinNum);


};

/*������*/
class YahBoom_BatCar_Beep
{
     private:
          byte pinName;

     public:
          
          YahBoom_BatCar_Beep(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_BatCar_Beep();  //��������

          /*����������*/
          void BEEP_SetFreDelay(int Fre, int ms);
          void BEEP_ON(byte PinNum);
          void BEEP_OFF(byte PinNum);

};


/*��ť*/
class YahBoom_BatCar_Button
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_BatCar_Button(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_BatCar_Button();  //��������

          /*������ȡ*/
          int Get_Button_State(byte pin);

};

/*Ѳ��*/
class YahBoom_BatCar_BlackLine
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_BatCar_BlackLine(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_BatCar_BlackLine();  //��������

          /*��Ѳ�߶�ȡ*/
          int Senser_State_L(byte pin);
          /*��Ѳ�߶�ȡ*/
          int Senser_State_R(byte pin);

};

/*�������*/
class YahBoom_BatCar_IRAvoid
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_BatCar_IRAvoid(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_BatCar_IRAvoid();  //��������

          /*��Ѳ�߶�ȡ*/
          int Senser_State_L(byte pin);
          
          /*��Ѳ�߶�ȡ*/
          int Senser_State_R(byte pin);

};

/*С���˶�*/
class YahBoom_BatCar_Motor
{
     private:
          byte pinLeftGo;
          byte pinLeftBack;
          byte pinRightGo;
          byte pinRightBack;

          byte pinLeftEn;
          byte pinRightEn;
          
     public:
          
          YahBoom_BatCar_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack, byte pLEn, byte pREn);   //���캯��         
          ~YahBoom_BatCar_Motor();  //��������

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


/*�ǲ�����AR�������׼�*/
/*������*/
class YahBoom_ARSensor_Beep
{
     private:
          byte pinName;

     public:
          
          YahBoom_ARSensor_Beep(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_ARSensor_Beep();  //��������

          /*����������*/
          void BEEP_SetFreDelay(int Fre, int ms);
          void BEEP_ON(byte PinNum);
          void BEEP_OFF(byte PinNum);

};

/*1λ�����*/
class YahBoom_ARSensor_SMG1
{
		private:
			int a;  // ����IO��7 ���������a��
			int b;  // ����IO��6 ���������b��
			int c;  // ����IO��5 ���������c��
			int d; // ����IO��11 ���������d��
			int e; // ����IO��10 ���������e��
			int f;  // ����IO��8 ���������f��
			int g;  // ����IO��9���������g��
			int dp; // ����IO��4 ���������С�����
          
    public:
          
      YahBoom_ARSensor_SMG1();   //���캯��         
      ~YahBoom_ARSensor_SMG1();  //��������
			
			void digital_0(void);
			void digital_1(void);
			void digital_2(void);
			void digital_3(void);
			void digital_4(void);
			void digital_5(void);
			void digital_6(void);
			void digital_7(void);
			void digital_8(void);
			void digital_9(void);
			
      void SMG1_DisPlay(char v_cNum); 
         
};
/*4λ�����*/
class YahBoom_ARSensor_SMG4
{
          
    public:
          
      YahBoom_ARSensor_SMG4();   //���캯��         
      ~YahBoom_ARSensor_SMG4();  //��������
			void Display(unsigned char com, unsigned char num);

      void SMG4_DisPlay(int v_iNum); 
         
};

/*������ť*/
class YahBoom_ARSensor_TouchBtn
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_ARSensor_TouchBtn(byte pin, byte PinMode);   //���캯��         
          ~YahBoom_ARSensor_TouchBtn();  //��������

          /*������ȡ*/
          int Get_Button_State(byte pin);

};


/*8*8����*/
class Yahboom_ARsenser_Lattice
{
		private:
			int R[8];
			int C[8];
		public:

			Yahboom_ARsenser_Lattice();
			~Yahboom_ARsenser_Lattice();
			
			void Display(int Row, unsigned char temp);

	
	
	
	
};


//AR����С��
/*С���˶�*/
class YahBoom_ARCar_Motor
{
     private:
          byte pinLeftGo;
          byte pinLeftBack;
          byte pinRightGo;
          byte pinRightBack;
          
     public:
          
          YahBoom_ARCar_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack);   //���캯��         
          ~YahBoom_ARCar_Motor();  //��������

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