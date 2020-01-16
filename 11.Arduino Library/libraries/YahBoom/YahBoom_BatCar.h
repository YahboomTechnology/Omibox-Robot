/*******************
YahBoom_BatCar.h

*******************/

#ifndef _YAHBOOM_BATCAR_H__
#define _YAHBOOM_BATCAR_H__

//导入Arduino核心头文件
#include<Arduino.h>  


/*LED*/
class YahBoom_BatCar_LED
{
     private:
          byte pinName;

     public:
          
          YahBoom_BatCar_LED(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_BatCar_LED();  //析构函数

          /*LED控制*/

          void LED_ON(byte PinNum);
          void LED_OFF(byte PinNum);
					void LED_Breath(byte PinNum);


};

/*蜂鸣器*/
class YahBoom_BatCar_Beep
{
     private:
          byte pinName;

     public:
          
          YahBoom_BatCar_Beep(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_BatCar_Beep();  //析构函数

          /*蜂鸣器控制*/
          void BEEP_SetFreDelay(int Fre, int ms);
          void BEEP_ON(byte PinNum);
          void BEEP_OFF(byte PinNum);

};


/*按钮*/
class YahBoom_BatCar_Button
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_BatCar_Button(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_BatCar_Button();  //析构函数

          /*按键读取*/
          int Get_Button_State(byte pin);

};

/*巡线*/
class YahBoom_BatCar_BlackLine
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_BatCar_BlackLine(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_BatCar_BlackLine();  //析构函数

          /*左巡线读取*/
          int Senser_State_L(byte pin);
          /*右巡线读取*/
          int Senser_State_R(byte pin);

};

/*红外避障*/
class YahBoom_BatCar_IRAvoid
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_BatCar_IRAvoid(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_BatCar_IRAvoid();  //析构函数

          /*左巡线读取*/
          int Senser_State_L(byte pin);
          
          /*右巡线读取*/
          int Senser_State_R(byte pin);

};

/*小车运动*/
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
          
          YahBoom_BatCar_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack, byte pLEn, byte pREn);   //构造函数         
          ~YahBoom_BatCar_Motor();  //析构函数

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


/*亚博智能AR传感器套件*/
/*蜂鸣器*/
class YahBoom_ARSensor_Beep
{
     private:
          byte pinName;

     public:
          
          YahBoom_ARSensor_Beep(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_ARSensor_Beep();  //析构函数

          /*蜂鸣器控制*/
          void BEEP_SetFreDelay(int Fre, int ms);
          void BEEP_ON(byte PinNum);
          void BEEP_OFF(byte PinNum);

};

/*1位数码管*/
class YahBoom_ARSensor_SMG1
{
		private:
			int a;  // 数字IO口7 连接数码管a段
			int b;  // 数字IO口6 连接数码管b段
			int c;  // 数字IO口5 连接数码管c段
			int d; // 数字IO口11 连接数码管d段
			int e; // 数字IO口10 连接数码管e段
			int f;  // 数字IO口8 连接数码管f段
			int g;  // 数字IO口9连接数码管g段
			int dp; // 数字IO口4 连接数码管小数点段
          
    public:
          
      YahBoom_ARSensor_SMG1();   //构造函数         
      ~YahBoom_ARSensor_SMG1();  //析构函数
			
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
/*4位数码管*/
class YahBoom_ARSensor_SMG4
{
          
    public:
          
      YahBoom_ARSensor_SMG4();   //构造函数         
      ~YahBoom_ARSensor_SMG4();  //析构函数
			void Display(unsigned char com, unsigned char num);

      void SMG4_DisPlay(int v_iNum); 
         
};

/*触摸按钮*/
class YahBoom_ARSensor_TouchBtn
{
     private:
          byte pinName;
          
     public:
          
          YahBoom_ARSensor_TouchBtn(byte pin, byte PinMode);   //构造函数         
          ~YahBoom_ARSensor_TouchBtn();  //析构函数

          /*按键读取*/
          int Get_Button_State(byte pin);

};


/*8*8点阵*/
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


//AR智能小车
/*小车运动*/
class YahBoom_ARCar_Motor
{
     private:
          byte pinLeftGo;
          byte pinLeftBack;
          byte pinRightGo;
          byte pinRightBack;
          
     public:
          
          YahBoom_ARCar_Motor(byte pLGo, byte pLBack, byte pRGo, byte pRBack);   //构造函数         
          ~YahBoom_ARCar_Motor();  //析构函数

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