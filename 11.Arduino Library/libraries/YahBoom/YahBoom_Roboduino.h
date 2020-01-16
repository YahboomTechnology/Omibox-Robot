/*******************
YahBoom_Roboduino.h

*******************/

#ifndef _YAHBOOM_Roboduino_H__
#define _YAHBOOM_Roboduino_H__


//Import 
#include <Arduino.h>  
#include <Adafruit_NeoPixel.h>         
#include <Wire.h>                     
#include <Adafruit_PWMServoDriver.h>             
#include <IRremote.h>                 
#include <RGBLed.h>                 

/*LOGORGB*/
class YahBoom_Roboduino_LOGORGB
{
	private:
        Adafruit_PWMServoDriver pwm;
	public:
		YahBoom_Roboduino_LOGORGB();           //Constructor  
		~YahBoom_Roboduino_LOGORGB();          //Destructor
		void LOGORGB_Init();
		void LOGORGB_Show_Color();
		void LOGORGB_Close();  
};

/*Onboard_RGB*/
class YahBoom_Roboduino_OnboardRGB
{
	private:
          byte pinname;
          Adafruit_NeoPixel strip;
	public:
		YahBoom_Roboduino_OnboardRGB(byte max_led, byte pinname);           //Constructor         
		~YahBoom_Roboduino_OnboardRGB();            //Destructor
		void OnboardRGB_Init();
		void OnboardRGB_Show_Color(uint8_t v_Red, uint8_t v_Green, uint8_t v_Blue);
		void OnboardRGB_setBrightness(uint8_t b);
		void OnboardRGB_OFF();
};

/*Ultrasonic_RGB*/
class YahBoom_Roboduino_UltrasonicRGB
{
	private:
	      byte pinname;
		  byte max_led;
		  RGBLed mRgb;
	public:
		YahBoom_Roboduino_UltrasonicRGB(byte pinname, byte max_led);    //Constructor            
		~YahBoom_Roboduino_UltrasonicRGB();            //Destructor    
		void UltrasonicRGB_Init();
		void UltrasonicRGB_Show_Color(byte Num,uint8_t v_Red, uint8_t v_Green, uint8_t v_Blue);
		void UltrasonicRGB_Show_All(uint8_t v_Red, uint8_t v_Green, uint8_t v_Blue) ;
		void UltrasonicRGB_OFF();
};



/*Motor and Servo*/
class YahBoom_Roboduino_MotorServo
{
     private:
          void SetServoPos(int num, int value);
          Adafruit_PWMServoDriver pwm;
     public:
 
          YahBoom_Roboduino_MotorServo();   //Constructor         
          ~YahBoom_Roboduino_MotorServo();    //Destructor 
          void YahBoom_Roboduino_MotorServo_Init(); 
          
          void SetServoAngle(int num, int value); 

          /*Car movement state*/
          void Advance(int speed = 150, int delay_ms = 100) ;
          void Back(int speed = 150, int delay_ms = 100);
          void Left(int speed = 150, int delay_ms = 100);
          void Right(int speed = 150, int delay_ms = 100);
          void SpinLeft(int speed = 150, int delay_ms = 100);
          void SpinRight(int speed = 150, int delay_ms = 100);
          void Stop(int speed = 0, int delay_ms = 100); 
          
          void MotorSpeed(int left_speed = 150, int right_speed = 150 );
          void LeftMotor(int direction = 0, int speed = 150);
          void RightMotor(int direction = 0, int speed = 150);

};


/*Buzzer*/    
//Buzzer connect to Pin10 of Uno board
class YahBoom_Roboduino_Beep
{
	 private:
          byte pinname;
	 public:
          
          YahBoom_Roboduino_Beep(byte v_pinname);   //Constructor            
          ~YahBoom_Roboduino_Beep();  //Destructor
		  void  YahBoom_Roboduino_Beep_Init();
          void setBuzzer_Tone(uint16_t frequency, uint32_t duration);
		  void birthday();
		  void ode();
		  void star();
		  void merryChristmas();
		  void bingo();
          void music_Play(uint8_t  v_song, uint8_t v_repeat);
          

};


/*Button*/
//Button connect to Pin7 of Uno board
class YahBoom_Roboduino_Button
{     
	private:
		byte pinname;
	public:

	YahBoom_Roboduino_Button(byte v_pinname);   //Constructor        
	~YahBoom_Roboduino_Button();    //Destructor
	void YahBoom_Roboduino_Button_Init();
	bool Get_Button_State();       

};

/*Tracking module*/
class YahBoom_Roboduino_Tracking
{       
	private:
		byte pinname0;   //A0
		byte pinname1;   //A1
		byte pinname2;   //A2
	public:
		YahBoom_Roboduino_Tracking(byte v_pinname0, byte v_pinname1, byte v_pinname2);      //Constructor    
		~YahBoom_Roboduino_Tracking();  //Destructor
		void YahBoom_Roboduino_Tracking_Init();

		//Method 1:analog value
		int ReturnLTrackingValue();
		int ReturnMTrackingValue();
		int ReturnRTrackingValue();

		//Method 2:digital value
		bool LTracking_Senser_State(int state, int threshold = 500);
		bool MTracking_Senser_State(int state, int threshold = 500);
		bool RTracking_Senser_State(int state, int threshold = 500);
};

/*Ultrasonic module*/
//Ultrasonic function connect Pin12 of Uno board
class YahBoom_Roboduino_Ultrasonic
{       
	private:
		byte pinname;
	public:

		YahBoom_Roboduino_Ultrasonic(byte v_pinname);         //Constructor        
		~YahBoom_Roboduino_Ultrasonic();  //Destructor
		void YahBoom_Roboduino_Ultrasonic_Init();
		float ReturnUltrasonicDistanceValue();

};

/*IR*/
//IR function connect A3 of Uno board
class YahBoom_Roboduino_IRrecv
{  
	private:
		byte pinname;
	public:            
          unsigned long last;
          decode_results results; 
          int last_receive_number;
          int receive_number;
          IRrecv irrecv = IRrecv(A3);
          
     public:
          
          YahBoom_Roboduino_IRrecv(byte v_pinname);   //Constructor             
          ~YahBoom_Roboduino_IRrecv();  //Destructor
          
          void YahBoom_Roboduino_IRrecv_Init();
          int IR_Deal();
          void init();
};

/*Hardware initialization*/
class YahBoom_Roboduino
{
     private: 
          Adafruit_PWMServoDriver pwm;
     public:
          
          YahBoom_Roboduino();   //Constructor          
          ~YahBoom_Roboduino();  //Destructor

          void YahBoom_Roboduino_Init(); 
};

#endif