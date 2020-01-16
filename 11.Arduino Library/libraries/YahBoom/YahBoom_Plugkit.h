/*******************
YahBoom_Plugkit.h
*******************/

#ifndef _YAHBOOM_Plugkit_H__
#define _YAHBOOM_Plugkit_H__

//����Arduino����ͷ�ļ�
#include<Arduino.h> 
#include<dht11.h>              //��ʪ��
#include<Servo.h> 			   //���
#include <IRremote.h>          //����
#include <Wire.h>              //IIC           
#include <Adafruit_GFX.h>	   //oledͼ�ο�
#include <Adafruit_SSD1306.h>  //oled
// #include <Adafruit_NeoPixel.h>

/*RGB��ģ��*/
class YahBoom_Plugkit_RGB
{
	private:
        byte pinNameR, pinNameG, pinNameB;
          
	public:
		YahBoom_Plugkit_RGB(byte pin1, byte pin2, byte pin3, byte PinMode);	 //���캯��                  
		~YahBoom_Plugkit_RGB();    //��������
		// void RGB_Init();
		void RGB_OFF();
		void RGB_Control(int pinR_OnOff, int pinG_OnOff, int pinB_OnOff);
		void RGB_Contrl_PWM(int pinRValue, int pinGValue, int pinBValue);
		void YahBoom_Plugkit_RGB::LED_Breath(byte pinName);
};

/*���ط�����*/
class YahBoom_Plugkit_Buzzer
{
	private:
		byte pin;

	public:
          
		YahBoom_Plugkit_Buzzer(byte pinname);   //���캯��         
		~YahBoom_Plugkit_Buzzer();  //��������

		/*����������*/
		void setBuzzer_Tone(uint16_t frequency, uint32_t duration);
		void music_Play(uint8_t  v_song, uint8_t v_repeat);
		void birthday();
		void childhood();
		void fenshuajiang();
		void wanghouyusheng();
		void huanlesong();
		void yuemayangbian();
		void guangdongaiqinggushi();
		void shishangzhiyoumamahao();
		void rangwomendangqishuangjiang();
		void xinnianhao();
		void xiaoxingxing();
		void liangzhilaohu();
};

/*����ģ��*/
class YahBoom_Plugkit_Button
{
	private:
		byte pinName; 
		
	public:
          
		YahBoom_Plugkit_Button(byte pin);   //���캯��         
		~YahBoom_Plugkit_Button();  //��������

		/*������ȡ*/
		bool Get_Button_State();

};

/*��λ��ģ��*/
class YahBoom_Plugkit_Potentiometer
{
	private:
		byte pinName;    
		 
	public:
          
		YahBoom_Plugkit_Potentiometer(byte pin);   //���캯��         
		~YahBoom_Plugkit_Potentiometer();  //��������
		void YahBoom_Plugkit_Potentiometer_Init();
		/*��λ����ȡ*/
		int Get_Potentiometer_value();

};

/*ҡ��ģ��*/
class YahBoom_Plugkit_Rocker
{
	private:
		byte pinName; 
		 
	public:
          
		YahBoom_Plugkit_Rocker(byte pin);   //���캯��         
		~YahBoom_Plugkit_Rocker();  //��������

		/*ҡ��ֵ��ȡ*/
		void YahBoom_Plugkit_Rocker_Init();
		int Get_Rocker_State();

};

/*���С����*/
class YahBoom_Plugkit_FAN
{
	private:
		byte pinName;

	public:
          
		YahBoom_Plugkit_FAN(byte pin);   //���캯��         
		~YahBoom_Plugkit_FAN();  //��������

		void YahBoom_Plugkit_FAN_Init();//��ʼ������
		void SetFanSpeed(int speed);//���Ʒ���ת��    //������Ը�ɭ������ֵ������int speed = ���ȵ�����ٶȻ���д0��������ľ��������и���ֵ

};

/*���*/
class YahBoom_Plugkit_Servo
{
	private:
		byte pinName;
		Servo myservo; 
		
	public:
          
		YahBoom_Plugkit_Servo(byte pin);   //���캯��         
		~YahBoom_Plugkit_Servo();  //��������
		void YahBoom_Plugkit_Servo_Init();//��ʼ������
		void SetServoAngle(int ServoPos);
		void ServoGearRotating(int pos1, int pos2, int time);//���ת������

};

#define OLED_RESET 11
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 32
#define LOGO16_GLCD_WIDTH 128

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

/*OLED*/
class YahBoom_Plugkit_Oled
{
	private:
		   
	public:
		
		 YahBoom_Plugkit_Oled();   //���캯�� 
		 ~YahBoom_Plugkit_Oled();  //��������
		void YahBoom_Plugkit_Oled_Init();
		void YahBoom_Plugkit_Oled_clear();
		void YahBoom_Plugkit_Oled_display();
		void YahBoom_Plugkit_Oled_drawPixel(uint8_t x,uint8_t y);
		void YahBoom_Plugkit_Oled_drawLine(uint8_t x,uint8_t y,uint8_t x1,uint8_t y1);
		void YahBoom_Plugkit_Oled_character(int fontsize, int character_x, int character_y, const char *str);
		void YahBoom_Plugkit_Oled_number(int fontsize, int number_x, int number_y, unsigned long int num);
		
		void testdrawcircle(uint16_t x, uint16_t y);
		void testdrawtriangle();
		void testdrawrect(uint16_t x, uint16_t y);
		void testdrawroundrect(uint16_t x, uint16_t y);
		void testdrawheart(uint16_t x, uint16_t y);
		void testdrawstar(uint16_t x, uint16_t y);
		void testdrawright(uint16_t x, uint16_t y);
		void testdrawerror(uint16_t x, uint16_t y);
		void testdrawhouse(uint16_t x, uint16_t y);
		void testdrawboat(uint16_t x, uint16_t y);
		void testdrawumbrella(uint16_t x, uint16_t y);
		void testdrawsmile(uint16_t x, uint16_t y);
		void testdrawcry(uint16_t x, uint16_t y);
		void testdrawnote(uint16_t x, uint16_t y);
		void testdrawxhr(uint16_t x, uint16_t y);
		void testdrawpkq(uint16_t x, uint16_t y);
		void testdrawhmbb(uint16_t x, uint16_t y);
		void testdrawxzpq(uint16_t x, uint16_t y);
		
		void YahBoom_Plugkit_Oled_staticPicture(uint16_t x1, uint16_t y1, uint8_t v_spic);
		
		void testfillrect();
		void testfilltriangle();
		void testfillroundrect();
		void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h);	
		void harichord(int frame);
		void customanimation();
		
		void YahBoom_Plugkit_Oled_movePicture(uint8_t v_mode);
		
		void scrollright(int time);
		void scrollleft(int time);
		void scrolldiagright(int time);
		void scrolldiagleft(int time); 
		void YahBoom_Plugkit_Oled_moveStr(const char *str, uint8_t v_mode, int t);
		void YahBoom_Plugkit_Oled_dynamicPicture(uint8_t v_spic, uint8_t v_mode, int t);
		void YahBoom_Plugkit_Oled_Sensordata(int fontsize, int character_x, int character_y, const char *str, int sensordata);
};

/*�������*/
class YahBoom_Plugkit_IRrecv
{
	private:          
		byte pinname;

		
	public:
		unsigned long last;
		decode_results results; // ���ڴ洢�������Ķ���
		int last_receive_number;
		int receive_number;
		IRrecv irrecv = IRrecv(12);
		
		YahBoom_Plugkit_IRrecv(byte v_pinname);   //���캯��         
		~YahBoom_Plugkit_IRrecv();  //��������

		void YahBoom_Plugkit_IRrecv_Init();//��ʼ������
		int IR_Deal();//���غ�����յ���ֵ
		  
};

/*����������*/
class YahBoom_Plugkit_VoiceSensor
{
	private:
		byte pinName;
          
	public:
          
		YahBoom_Plugkit_VoiceSensor(byte pin);   //���캯��         
		~YahBoom_Plugkit_VoiceSensor();  //��������

		void YahBoom_Plugkit_VoiceSensor_Init();//��ʼ������
		int get_VoiceSensor();  //��ȡ����AD 0-1023

};

/*����������*/
class YahBoom_Plugkit_LightSensor
{
	private:
		byte pinName;
          
	public:
          
		YahBoom_Plugkit_LightSensor(byte pin);   //���캯��         
		~YahBoom_Plugkit_LightSensor();  //��������

		void YahBoom_Plugkit_LightSensor_Init();//��ʼ������
		int get_LightSensor();  //��ȡ����AD 0-1023

};

/*����������*/
class YahBoom_Plugkit_MagnetSensor
{
	private:
		byte pinName;
          
	public:
          
		YahBoom_Plugkit_MagnetSensor(byte pin);   //���캯��         
		~YahBoom_Plugkit_MagnetSensor();  //��������

		void YahBoom_Plugkit_MagnetSensor_Init();//��ʼ������
		int get_MagnetSensor(); //��ȡ����AD 0-1023

};

/*�𶯴�����*/
class YahBoom_Plugkit_ShakeSensor
{
	private:
		// void attachInterrupt (uint8_t interruptNum, void(*)(void)userFunc, int mode);
		byte pinName;
		
	public: 
		YahBoom_Plugkit_ShakeSensor(byte pin);   //���캯��         
		~YahBoom_Plugkit_ShakeSensor();  //��������	
		
		void YahBoom_Plugkit_ShakeSensor_Init();//��ʼ������
		bool get_ShakeSensor(); //��ȡ�жϴ���

};


/*��ɫ������*/
#define RGB_2           0x00
#define ADDR            0x53
#define W_ADDR_L        0x66
#define R_ADDR_L        0x67
//ADDR->High
#define RGB_1           0x01
#define W_ADDR_H        0x98
#define R_ADDR_H        0x99

//Register Address
#define ControlReg_Addr 0x00
#define RGBCON_Addr     0x04

#define ID_Addr         0x06

#define CDATAL_Addr     0x12
#define CDATAH_Addr     0x13

#define RDATAL_Addr     0x10
#define RDATAM_Addr     0x11
#define RDATAH_Addr     0x12

#define GDATAL_Addr     0x0D
#define GDATAM_Addr     0x0E
#define GDATAH_Addr     0x0F

#define BDATAL_Addr     0x13
#define BDATAM_Addr     0x14
#define BDATAH_Addr     0x15
/*  Confi Arg  */
//Control Register 
#define RST             0x00

/*��ɫʶ�𴫸���*/
class YahBoom_Plugkit_Color
{
	private:
		void RGB_Config(void);
		unsigned int Red = 0;
		unsigned int Green  =0;
		unsigned int Blue = 0;
	public:
          
		YahBoom_Plugkit_Color();   //���캯��         
		~YahBoom_Plugkit_Color();  //��������

		void YahBoom_Plugkit_Color_Init(); //��ʼ������
		bool YahBoom_Plugkit_Identify_Color(byte color);//�ж�ʶ�𵽵���ɫ��������ɫ����ѡ�����ɫ�򷵻�true
		void get_ColorSensor();//��ȡ��ɫʶ�𴫸�����⵽��ֵ
		int ReturnRedValue();  //���غ�ɫֵ
		int ReturnGreenValue();//������ɫֵ
		int ReturnBlueValue(); //������ɫֵ

};

/*��ʪ�ȴ�����*/
class YahBoom_Plugkit_HumitureSensor
{
	private:
		byte pinName;
		int chk = 0;
		int tem = 0;
		int hum = 0;
	public:
	
		YahBoom_Plugkit_HumitureSensor(byte pin);  //���캯��   
		~YahBoom_Plugkit_HumitureSensor();  //�������� 

		void YahBoom_Plugkit_HumitureSensor_Init();  //��ʼ������
		// int get_HumitureSensor();  //��ȡ�¶Ⱥ�ʪ��ֵ
		float get_temperature();  //��ȡ�¶�ֵ
		float get_humidity();  //��ȡʪ��ֵ
	 
};

/*������������*/
class YahBoom_Plugkit_UltrasonicSensor
{
	private:
		int Distance = 0;
		byte Echo;
		byte Trig;
	public:
          
		YahBoom_Plugkit_UltrasonicSensor(byte pin1, byte pin2); //���캯��         
		~YahBoom_Plugkit_UltrasonicSensor();  //��������

		void YahBoom_Plugkit_UltrasonicSensor_Init();  //��ʼ������ 
		int get_UltrasonicSensor();  //��ȡ������ֵ

};

#endif