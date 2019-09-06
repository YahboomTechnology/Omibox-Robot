   
#include "./YahBoom_OMIBOX.h"

#define run_car     '1'
#define back_car    '2'
#define left_car    '3'
#define right_car   '4'
#define spin_left_car '5'
#define spin_right_car '6'
#define stop_car    '0'

#define ON 1           
#define OFF 0          

enum {
  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enTLEFT,
  enTRIGHT
} enCarState;


int IncomingByte = 0;             //Received data byte
String InputString = "";          //Used to store received content
boolean NewLineReceived = false;  //Previous data end mark
boolean StartBit  = false;        //Agreement start mark
String ReturnTemp = "";           //Store return value

int g_CarState = enSTOP;         
int g_oldcarState = 11;
unsigned long g_uptimes = 10000; //Automatic reporting interval
int g_Mode = 0;                   //1：Water light  2：Marquee 3：Breathlight  4：Tracking  5：Avoid  6：follow  7：Vioce  8：Close
int g_MusicMode = 0;              //1：Play 2：pause 
int g_SoundsSelect = 1;           
const unsigned char music_max[5] = {21,36,39,42,70};   
char matrixdata[16] = {0};
int g_ReportMode = 1;             
static int Breath_a=0;
static int Brightness=0;
int bluetooth_value = 0;
int prve_mode = 0;      
int curr_mode = 0;      
int carry_out = 0;      
int light_mode = 0;      

/*运动*/
YahBoom_OMIBOX_MotorServo cMotor;
YahBoom_OMIBOX_Button cButton;
YahBoom_OMIBOX_Matrix cMatrix;
YahBoom_OMIBOX_RGBLED cRGB(8, 5);
YahBoom_OMIBOX_Buzzer cBuzzer(6);
YahBoom_OMIBOX_Voltage cVoltage(A2);
YahBoom_OMIBOX_LightSensor cLightSensor(A6);
YahBoom_OMIBOX_Color cColor;
YahBoom_OMIBOX_TrackLine cTrack(7, 8);
YahBoom_OMIBOX_IRAvoid cIR(A0, A1);
YahBoom_OMIBOX_VoiceSensor cVoiceSensor(A7);
unsigned char picBuffer[16];
unsigned char *picTemp;

void Display_clear()   
{
  picTemp = new unsigned char[16]{
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
  ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
  memcpy(picBuffer,picTemp,16);
  free(picTemp);
  cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
}

void Display_eye()   
{
  picTemp = new unsigned char[16]{
  0x38,0x1c,0x7c,0x3e,0xfe,0x7f,0xe6,0x73
  ,0xe6,0x73,0xfe,0x7f,0x7c,0x3e,0x38,0x1c};
  memcpy(picBuffer,picTemp,16);
  free(picTemp);
  cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
}

void Display_Tracking()  
{
  picTemp = new unsigned char[16]{
  0x0,0x0,0x1c,0x0,0x22,0x4,0x41,0x4
  ,0x41,0x4,0x41,0x4,0x40,0x88,0x0,0x70};
  memcpy(picBuffer,picTemp,16);
  free(picTemp);
  cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
}

void Display_Avoid()   
{
  picTemp = new unsigned char[16]{
  0x20,0x0,0x11,0x80,0x6b,0x80,0x65,0x80
  ,0x0,0x1c,0x1d,0x1c,0x1c,0x80,0x8,0x7c};
  memcpy(picBuffer,picTemp,16);
  free(picTemp);
  cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
}

void Display_Follow()   
{
  picTemp = new unsigned char[16]{
  0x0,0x0,0x0,0x10,0x31,0xfb,0x48,0x13
  ,0xfc,0x83,0x49,0xfb,0x0,0x80,0x0,0x0};
  memcpy(picBuffer,picTemp,16);
  free(picTemp);
  cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
}

void Display_Color()   
{
  picTemp = new unsigned char[16]{
  0x3f,0xfc,0x43,0xc2,0x83,0xc1,0xe0,0xf
  ,0xe0,0xf,0x83,0xc1,0x43,0xc2,0x3f,0xfc};
  memcpy(picBuffer,picTemp,16);
  free(picTemp);
  cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
}

void Display_Voice()   
{
  picTemp = new unsigned char[16]{
  0x0,0xa0,0x1,0xc0,0x2,0x80,0xc,0xe0
  ,0xc,0xe0,0x2,0x80,0x1,0xc0,0x0,0xa0};
  memcpy(picBuffer,picTemp,16);
  free(picTemp);
  cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
}

void Init_All()
{
    unsigned char picBuffer[16];
    unsigned char *picTemp;

    cMatrix.YahBoom_OMIBOX_Matrix_Init();
    cRGB.RGBLED_Init();
    cRGB.RGBLED_Show_All(0,0,0);  
    picTemp = new unsigned char[16]{
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
    ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
    memcpy(picBuffer,picTemp,16);
    free(picTemp);
    cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);  
    cMotor.YahBoom_OMIBOX_MotorServo_Init();
    cColor.YahBoom_OMIBOX_Color_Init(); 
    cTrack.YahBoom_OMIBOX_TrackLine_Init();
    cIR.YahBoom_OMIBOX_IRAvoid_Init();
    cVoiceSensor.YahBoom_OMIBOX_VoiceSensor_Init();
    cColor.PowerSwith(0);
}

void setup()
{

    Serial.begin(115200);
    Init_All(); 
    cMatrix.LED_ShowStrroll("OMIBOX", 1, 0);
    cMatrix.Move_picture(5, 200);
    cMatrix.Move_picture(5, 200);
    cRGB.RGBLED_Show_Color(0,255,0,0);
    cBuzzer.setBuzzer_Tone(523, 1);
    cRGB.RGBLED_Show_Color(1,0,255,0);
    cBuzzer.setBuzzer_Tone(587, 1);
    cRGB.RGBLED_Show_Color(2,0,0,255);
    cBuzzer.setBuzzer_Tone(659, 1);
    cRGB.RGBLED_Show_Color(3,255,255,0);
    cBuzzer.setBuzzer_Tone(698, 1);
    cRGB.RGBLED_Show_Color(4,255,0,255);
    cBuzzer.setBuzzer_Tone(784, 1);
    cRGB.RGBLED_Show_Color(5,0,255,255);
    cBuzzer.setBuzzer_Tone(880, 1);
    cRGB.RGBLED_Show_Color(6,255,255,255);
    cBuzzer.setBuzzer_Tone(988, 1);
    cRGB.RGBLED_Show_Color(7,255,0,0);
    cRGB.RGBLED_Show_All(0,0,0);
    
}

void SendAutoUp()
{
  g_uptimes --;
  if (g_uptimes == 0)
  {
     
    String returntemp;
  
    char temp[5]={0};
  
    float voltage = cVoltage.get_Voltage();
    memset(temp, 0x00, sizeof(temp));
    dtostrf(voltage, 1, 2, temp);  
    String VT = temp;
  
    if(g_ReportMode == 2)
    {
      cColor.PowerSwith(1);
      if(cColor.YahBoom_OMIBOX_Identify_Color(1) == true)
      {
        returntemp = "$09" + VT +",1" + "#";
      }
      else if(cColor.YahBoom_OMIBOX_Identify_Color(2) == true)
      {
        returntemp = "$09" + VT +",2" + "#";
      }
      else if(cColor.YahBoom_OMIBOX_Identify_Color(3) == true)
      {
        returntemp = "$09" + VT +",3" + "#";
      }
      else if(cColor.YahBoom_OMIBOX_Identify_Color(4) == true)
      {
        returntemp = "$09" + VT +",4" + "#";
      }
      else
      {
        returntemp = "$09" + VT +",0" + "#";
      }
    }
    else
    {
      cColor.PowerSwith(0);
      returntemp = "$09" + VT +",0" + "#";      
    }
    Serial.print(returntemp); 
  }
  
  if (g_uptimes == 0)
      g_uptimes = 10000;
}

void Start_Music()  
{
    cBuzzer.setBuzzer_Tone(349, 2);
    cBuzzer.setBuzzer_Tone(440, 2);
    cBuzzer.setBuzzer_Tone(523, 2);
}

int g_num = 0;

void bluetooth_ctrl()
{
    if( 0 == bluetooth_value )
    {
      if (NewLineReceived)
      {
        //Display_clear();
        //Display_eye();
        curr_mode = 0;
        cMotor.Stop(255, 0);
        serial_data_parse();  
      }
      if(g_CarState != g_oldcarState)
      {
        g_oldcarState = g_CarState;
        if(g_Mode == 0)
        {
          switch (g_CarState)
          {
            case enSTOP: cMotor.Stop(255, 0); break;
            case enRUN: cMotor.Run(255, 0); break;
            case enLEFT: cMotor.Left(255, 0); break;
            case enRIGHT: cMotor.Right(255, 0); break;
            case enBACK: cMotor.Back(255, 0); break;
            case enTLEFT: cMotor.SpinLeft(255, 0); break;
            case enTRIGHT: cMotor.SpinRight(255, 0); break;
            default: cMotor.Stop(255, 0); break;
          }
        }
      }
      else //if(g_Mode != 0 )
      {
        switch(g_Mode)
        {
          case 0:  SendAutoUp();break;  
          case 1:  Mode_WaterLED_Func(); break;
          case 2:  Mode_HorseLED_Func(); break;
          case 3:  Mode_chameleon_Func();cColor.PowerSwith(1); break;
          case 4:  Mode_TrackLine_Func(); break;
          case 5:  Mode_Avoid_Func(); break;
          case 6:  Mode_Fllow_Func(); break;
          case 7:  Mode_VoiceCtrl_Func();break;
          case 8:  Mode_Close_Func();cColor.PowerSwith(0); break;
           
        }
      }
  
      
      if(g_MusicMode == 1) 
      {
          if(g_SoundsSelect != 0 )
          {
              switch(g_SoundsSelect)
              {
                case 1: cBuzzer.music_Play(1, g_num);break;
                case 2: cBuzzer.music_Play(2, g_num);break;
                case 3: cBuzzer.music_Play(3, g_num);break;
                case 4: cBuzzer.music_Play(4, g_num);break;
                case 5: cBuzzer.music_Play(5, g_num);break;  
              }
              g_num++;
              if(g_num >= music_max[g_SoundsSelect - 1])
              {
                g_num = 0;
                g_MusicMode = 2; 
              }
          }
          
      }
      else   
      {        
          SendAutoUp();
      }
  }
}


void Mode_Breath_light()
{

  cRGB.RGBLED_Show_All(Brightness,Brightness,Brightness);
  delay(10);
  if(Breath_a == 0)
  {
    Brightness=Brightness + 1;
    if(Brightness == 150)
    {
      Breath_a=1;
    }
  }
  if(Breath_a == 1)
  {
    Brightness=Brightness - 1;
    if(Brightness == 0)
    {
      Breath_a=0;
    }
  }
}  


void Mode_VoiceCtrl_Func_1()
{
  cMatrix.Static_picture(1);
  if(cVoiceSensor.get_VoiceSensor() > 400)
  {
    cBuzzer.setBuzzer_Tone(523, 2);
    //cMatrix.Static_picture(8);
    cMatrix.Move_picture(6, 0);
    for( int x1 = 0; x1 < 10; x1++)
    {
      if ((x1 % 2) == 0) {
        cMotor.LeftMotor(1, 50);
        cMotor.RightMotor(2, 50);
        delay(50);
      } else {
        cMotor.LeftMotor(2, 50);
        cMotor.RightMotor(1, 50);
        delay(50);
      }
    }
    cMotor.LeftMotor(2, 50);
    cMotor.RightMotor(2, 50);
    delay(300);
    cMotor.Stop(255, 0);
  }  
}

void loop()
{

    bluetooth_ctrl();
    if(cButton.Get_Button_State(2))
    {
        delay(10);
        if(cButton.Get_Button_State(2))
        {
          while (cButton.Get_Button_State(2));
          if(light_mode == 0)
          {
            g_Mode = 0;
            curr_mode++;
            if (6 == curr_mode) 
            {
              curr_mode = 1;  
            }
            if ( curr_mode != 4)
            {
              cColor.PowerSwith(0);
              cRGB.RGBLED_Show_All(0,0,0);
            }
            carry_out = 0;
            cMotor.Stop(255, 0);
            Start_Music();
          }
        }
    }
    else if(cButton.Get_Button_State(3))  
    {
        delay(10);
        if(cButton.Get_Button_State(3))
        {
          while (cButton.Get_Button_State(3));
          if(light_mode == 0)
          {
            carry_out = 1;
          }
        }
    }
    else if(analogRead(A6) > 950)  
    {
        light_mode = 1;
        bluetooth_value = 1;
        cColor.PowerSwith(0);
        cMotor.Stop(255, 0);
        curr_mode = 0;
    }
    else if(analogRead(A6) <= 950) 
    {
        bluetooth_value = 0;
        if (1 == light_mode)
        {
          Display_eye();
          cRGB.RGBLED_Show_All(0,0,0);
          curr_mode = prve_mode;
          g_Mode = 0;
        }
        light_mode = 0;
    }
    
    if (curr_mode == 1)
    {
      if (carry_out == 1)
      {
        Mode_TrackLine_Func();
      }
      else 
      {
        Display_Tracking();  
      }
    } 
    else if (curr_mode == 2) 
    {
      if (carry_out == 1) 
      {
         Mode_Avoid_Func();
      }
      else 
      {
        Display_Avoid(); 
      }
    } 
    else if (curr_mode == 3) 
    {
      if (carry_out == 1) 
      {
         Mode_Fllow_Func();   
      }
      else 
      {
        Display_Follow(); 
      }
    } 
    else if (curr_mode == 4) 
    {
      if (carry_out == 1) 
      {
         Mode_chameleon_Func();  
      }
      else 
      {
        Display_Color(); 
      }
    } 
    else if (curr_mode == 5) 
    {
      if (carry_out == 1) 
      {
         Mode_VoiceCtrl_Func_1();  
      }
      else 
      {
        Display_Voice();
      }
    } 
    else if (light_mode == 1)    
    {
        bluetooth_value = 1;
        cColor.PowerSwith(0);
        picTemp = new unsigned char[16]{
        0x0,0x1c,0x3,0xc8,0x0,0x9c,0xf9,0x0
        ,0x13,0xc0,0x20,0x0,0x40,0x0,0xf8,0x0};
         memcpy(picBuffer,picTemp,16);
        free(picTemp);
        cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
        Mode_Breath_light();
    }

}
/**
* Function       CMD_Sport_Fun
* @author        liusen
* @date          2019.02.27
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void CMD_Sport_Func(unsigned char str)
{
  
  switch (str)
  {
    case run_car:   g_CarState = enRUN;  break;
    case back_car:  g_CarState = enBACK;  break;
    case left_car:  g_CarState = enLEFT;  break;
    case right_car: g_CarState = enRIGHT;  break;
    case spin_left_car: g_CarState = enTLEFT;  break;
    case spin_right_car: g_CarState = enTRIGHT;  break;
    case stop_car:  g_CarState = enSTOP;  break;
    default: g_CarState = enSTOP; break;
  }
}


void CMD_Matrix_Show_Func()
{
   int X, Y, state;
   X = (InputString[3] - 0x30)*10 + (InputString[4] - 0x30);
   Y = (InputString[5] - 0x30)*10 + (InputString[6] - 0x30);
   state = (InputString[7] - 0x30);
   cMatrix.LED_Display(X, Y, state);
}


void CMD_Matrix_Picture_Func(uint8_t static_or_move, uint8_t index)
{
  if(static_or_move == 1 && index < 7)
  {
    cMatrix.Move_picture(index, 500);
    
  }
  else if(static_or_move == 2 && index < 10)
  {
    cMatrix.Static_picture(index);
  }
  else
  {
    unsigned char picBuffer[16];
    unsigned char *picTemp;  
    picTemp = new unsigned char[16]{
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
    ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
    memcpy(picBuffer,picTemp,16);
    free(picTemp);
    cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer); 
  }
}


void CMD_Servo_Func()
{
  uint8_t index, pos;
  index = InputString[3] - 0x30;
  pos = (InputString[4] - 0x30)*100 + (InputString[5] - 0x30)*10 + (InputString[6]-0x30);
  if(index < 5 && pos <= 180)
    cMotor.SetServoAngle(index,pos);
}


void CMD_RGB_Func()
{
  
    uint8_t num=0, Red=0, Green=0, Blue=0;
    String temp = "";
    temp = InputString.substring(3, 13);
    //Serial.println(temp);
   
    num = temp[0] - 0x30;
    Red = (temp[1] - 0x30)*100 + (temp[2] - 0x30)*10 + (temp[3]-0x30);
    Green = (temp[4] - 0x30)*100 + (temp[5] - 0x30)*10 + (temp[6]-0x30);
    Blue = (temp[7] - 0x30)*100 + (temp[8] - 0x30)*10 + (temp[9]-0x30);
    //Serial.println("Hello:" + R);
    
    if(num == 8)
    {
      cRGB.RGBLED_Show_All(Red,Green,Blue);
    }
    else
    {
      cRGB.RGBLED_Show_All(0,0,0);
      cRGB.RGBLED_Show_Color(num, Red, Green, Blue);
    }
    
}

void CMD_BEEP_Func(uint8_t state)
{
    if(state == 1)
      cBuzzer.setBuzzer_Tone(262, 1);
    else
      cBuzzer.setBuzzer_Tone(0, 8);
}


void CMD_Music_Func()
{
    uint8_t tonenum, button;
    tonenum = InputString[3] - 0x30;
    button =  InputString[4];
    
    switch(tonenum)
    {
      case 1: 
      {
        switch(button)
        {
          case '1': cBuzzer.setBuzzer_Tone(131, 1);break;
          case '2': cBuzzer.setBuzzer_Tone(147, 1);break;
          case '3': cBuzzer.setBuzzer_Tone(165, 1);break;
          case '4': cBuzzer.setBuzzer_Tone(175, 1);break;
          case '5': cBuzzer.setBuzzer_Tone(196, 1);break;
          case '6': cBuzzer.setBuzzer_Tone(220, 1);break;
          case '7': cBuzzer.setBuzzer_Tone(247, 1);break;
          case '8': cBuzzer.setBuzzer_Tone(262, 1);break;
          case 'a': cBuzzer.setBuzzer_Tone(139, 1);break;
          case 'b': cBuzzer.setBuzzer_Tone(156, 1);break;
          case 'c': cBuzzer.setBuzzer_Tone(185, 1);break;
          case 'd': cBuzzer.setBuzzer_Tone(208, 1);break;
          case 'e': cBuzzer.setBuzzer_Tone(233, 1);break; 
        }
      }break;
      case 2: 
      {
        switch(button)
        {
          case '1': cBuzzer.setBuzzer_Tone(262, 1);break;
          case '2': cBuzzer.setBuzzer_Tone(294, 1);break;
          case '3': cBuzzer.setBuzzer_Tone(330, 1);break;
          case '4': cBuzzer.setBuzzer_Tone(349, 1);break;
          case '5': cBuzzer.setBuzzer_Tone(392, 1);break;
          case '6': cBuzzer.setBuzzer_Tone(440, 1);break;
          case '7': cBuzzer.setBuzzer_Tone(494, 1);break;
          case '8': cBuzzer.setBuzzer_Tone(523, 1);break;
          case 'a': cBuzzer.setBuzzer_Tone(277, 1);break;
          case 'b': cBuzzer.setBuzzer_Tone(311, 1);break;
          case 'c': cBuzzer.setBuzzer_Tone(370, 1);break;
          case 'd': cBuzzer.setBuzzer_Tone(415, 1);break;
          case 'e': cBuzzer.setBuzzer_Tone(466, 1);break; 
        }
      }break;
      case 3:  
      {
        switch(button)
        {
          case '1': cBuzzer.setBuzzer_Tone(523, 1);break;
          case '2': cBuzzer.setBuzzer_Tone(587, 1);break;
          case '3': cBuzzer.setBuzzer_Tone(659, 1);break;
          case '4': cBuzzer.setBuzzer_Tone(698, 1);break;
          case '5': cBuzzer.setBuzzer_Tone(784, 1);break;
          case '6': cBuzzer.setBuzzer_Tone(880, 1);break;
          case '7': cBuzzer.setBuzzer_Tone(988, 1);break;
          case '8': cBuzzer.setBuzzer_Tone(1047, 1);break;
          case 'a': cBuzzer.setBuzzer_Tone(554, 1);break;
          case 'b': cBuzzer.setBuzzer_Tone(622, 1);break;
          case 'c': cBuzzer.setBuzzer_Tone(740, 1);break;
          case 'd': cBuzzer.setBuzzer_Tone(831, 1);break;
          case 'e': cBuzzer.setBuzzer_Tone(932, 1);break; 
        }
      }break;
    }  
}

//Music selection mode
void CMD_Sound_Func()
{
    if(InputString[4] == 'R')
    {
         g_MusicMode = 1;
    }
    else if(InputString[4] == 'P')
    {
         g_MusicMode = 2;  
    }
    else
    {
        g_SoundsSelect = (InputString[3] - 0x30)*10 + (InputString[4] - 0x30);
        g_num = 0;
    }
     
}

//Mode select
void CMD_Mode_Func(int Mode)
{
    g_Mode = Mode;
    if(g_Mode != 8)
      Start_Music();
}

//ReportMode
void CMD_ReportMode_Func(int Mode)
{
  g_ReportMode = Mode;
}


void Mode_WaterLED_Func()
{
    cRGB.RGBLED_Show_Color(0,255,0,0);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(1,0,255,0);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(2,0,0,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(3,255,0,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(4,0,255,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(5,255,255,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(6,255,255,0);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(7,0,0,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_All(0, 0, 0);
    delay(0.2*1000);  
}


void Mode_HorseLED_Func()
{
    cRGB.RGBLED_Show_Color(0,255,0,0);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(0, 0, 0, 0);
    cRGB.RGBLED_Show_Color(1,0,255,0);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(1, 0, 0, 0);
    cRGB.RGBLED_Show_Color(2,0,0,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(2, 0, 0, 0);
    cRGB.RGBLED_Show_Color(3,255,0,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(3, 0, 0, 0);
    cRGB.RGBLED_Show_Color(4,0,255,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(4, 0, 0, 0);
    cRGB.RGBLED_Show_Color(5,255,255,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(5, 0, 0, 0);
    cRGB.RGBLED_Show_Color(6,0,255,255);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(6, 0, 0, 0);
    cRGB.RGBLED_Show_Color(7,255,0,0);
    delay(0.2*1000);
    cRGB.RGBLED_Show_Color(7, 0, 0, 0);
    delay(0.2*1000);
}


void Mode_chameleon_Func()
{
    cColor.PowerSwith(1);
    cRGB.RGBLED_Show_All(cColor.ReturnRedValue(),cColor.ReturnGreenValue(),cColor.ReturnBlueValue());
}

void Mode_TrackLine_Func()
{
   unsigned char picBuffer[16];
   unsigned char *picTemp;
   if((cTrack.Senser_State_L(0) && cTrack.Senser_State_R(0)))
   {
      picTemp = new unsigned char[16]{
      0x38,0x1c,0x7c,0x3e,0xfe,0x7f,0xba,0x5d
      ,0x82,0x41,0x82,0x41,0x44,0x22,0x38,0x1c};
      memcpy(picBuffer,picTemp,16);
      free(picTemp);
      cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
      cMotor.LeftMotor(1, 60);
      cMotor.RightMotor(1, 60);
    }
    if((cTrack.Senser_State_L(1) && cTrack.Senser_State_R(0)))
    {
      picTemp = new unsigned char[16]{
      0x38,0x1c,0x44,0x22,0x8e,0x47,0x9e,0x4f
      ,0x9e,0x4f,0x8e,0x47,0x44,0x22,0x38,0x1c};
      memcpy(picBuffer,picTemp,16);
      free(picTemp);
      cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
      cMotor.LeftMotor(2, 40);
      cMotor.RightMotor(1, 60);
    }
    if((cTrack.Senser_State_L(0) && cTrack.Senser_State_R(1)))
    {
      picTemp = new unsigned char[16]{
      0x38,0x1c,0x44,0x22,0xe2,0x71,0xf2,0x79
      ,0xf2,0x79,0xe2,0x71,0x44,0x22,0x38,0x1c};
      memcpy(picBuffer,picTemp,16);
      free(picTemp);
      cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
      cMotor.LeftMotor(1, 60);
      cMotor.RightMotor(2, 40);
    }
    if((cTrack.Senser_State_L(1) && cTrack.Senser_State_R(1)))
    {
      picTemp = new unsigned char[16]{
      0x0,0x0,0x40,0x2,0x60,0x6,0x30,0xc
      ,0x18,0x18,0x7c,0x3e,0x7c,0x3e,0x0,0x0};
      memcpy(picBuffer,picTemp,16);
      free(picTemp);
      cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
      cMotor.LeftMotor(1, 0);
      cMotor.RightMotor(1, 0);
    }
}

void Mode_Avoid_Func()
{
  unsigned char picBuffer[16];
  unsigned char *picTemp;
  if((cIR.Senser_State_L() && cIR.Senser_State_R()))
  {
    picTemp = new unsigned char[16]{
    0x0,0x0,0xc0,0x3,0x60,0x6,0x30,0xc
    ,0x18,0x18,0xfc,0x3f,0xfc,0x3f,0x0,0x0};
    memcpy(picBuffer,picTemp,16);
    free(picTemp);
    cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
    cMotor.LeftMotor(1, 70);
    cMotor.RightMotor(2, 70);
  }
  else
  {
    if(cIR.Senser_State_L())
    {
      picTemp = new unsigned char[16]{
      0x38,0x1c,0x44,0x22,0x8e,0x47,0x9e,0x4f
      ,0x9e,0x4f,0x8e,0x47,0x44,0x22,0x38,0x1c};
      memcpy(picBuffer,picTemp,16);
      free(picTemp);
      cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
      cMotor.LeftMotor(1, 50);
      cMotor.RightMotor(2, 50);
    }
    else
    {
      if(cIR.Senser_State_R())
      {
        picTemp = new unsigned char[16]{
        0x38,0x1c,0x44,0x22,0xe2,0x71,0xf2,0x79
        ,0xf2,0x79,0xe2,0x71,0x44,0x22,0x38,0x1c};
        memcpy(picBuffer,picTemp,16);
        free(picTemp);
        cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
        cMotor.LeftMotor(2, 50);
        cMotor.RightMotor(1, 50);
      }
      else
      {
        picTemp = new unsigned char[16]{
        0x38,0x1c,0x7c,0x3e,0xfe,0x7f,0xba,0x5d
        ,0x82,0x41,0x82,0x41,0x44,0x22,0x38,0x1c};
        memcpy(picBuffer,picTemp,16);
        free(picTemp);
        cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
        cMotor.LeftMotor(1, 50);
        cMotor.RightMotor(1, 50);
      }
    }
  }
}

void Mode_Fllow_Func()
{
    unsigned char picBuffer[16];
    unsigned char *picTemp;
    if((cIR.Senser_State_L() && cIR.Senser_State_R()))
    {
      picTemp = new unsigned char[16]{
      0x0,0x0,0x0,0x0,0x6c,0x36,0xfe,0x7f
      ,0xfe,0x7f,0x7c,0x3e,0x38,0x1c,0x10,0x8};
      memcpy(picBuffer,picTemp,16);
      free(picTemp);
      cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
      cMotor.LeftMotor(1, 50);
      cMotor.RightMotor(1, 50);
    }
    else
    {
      if(cIR.Senser_State_L())
      {
        picTemp = new unsigned char[16]{
        0x38,0x1c,0x44,0x22,0x8e,0x47,0x9e,0x4f
        ,0x9e,0x4f,0x8e,0x47,0x44,0x22,0x38,0x1c};
        memcpy(picBuffer,picTemp,16);
        free(picTemp);
        cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
        cMotor.LeftMotor(2, 50);
        cMotor.RightMotor(1, 50);
      }
      else
      {
        if(cIR.Senser_State_R())
        {
          picTemp = new unsigned char[16]{
          0x38,0x1c,0x44,0x22,0xe2,0x71,0xf2,0x79
          ,0xf2,0x79,0xe2,0x71,0x44,0x22,0x38,0x1c};
          memcpy(picBuffer,picTemp,16);
          free(picTemp);
          cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
          cMotor.LeftMotor(1, 50);
          cMotor.RightMotor(2, 50);
        }
        else
        {
          picTemp = new unsigned char[16]{
          0x38,0x1c,0x7c,0x3e,0xfe,0x7f,0xba,0x5d
          ,0x82,0x41,0x82,0x41,0x44,0x22,0x38,0x1c};
          memcpy(picBuffer,picTemp,16);
          free(picTemp);
          cMatrix.YahBoom_OMIBOX_Matrix_Show(picBuffer);
          cMotor.Stop(255, 0);
        }
      }
    }
}

void Mode_VoiceCtrl_Func()
{
  cMatrix.Static_picture(1);
  if(cVoiceSensor.get_VoiceSensor() > 400)
  {
    cBuzzer.setBuzzer_Tone(523, 2);
    cMatrix.Static_picture(8);
    cMotor.Run(100, 1000);
    cMotor.Stop(255, 0);
  }  
}

void Mode_Close_Func()
{
  g_Mode = 0;
  cMotor.Stop(255, 0);
  cBuzzer.setBuzzer_Tone(392, 2);
  cBuzzer.setBuzzer_Tone(249, 2);
  cMatrix.Move_picture(1, 0);
}


int htoi(char s[])  
{  
    int i;  
    int n = 0;  
    if (s[0] == '0' && (s[1]=='x' || s[1]=='X'))  
    {  
        i = 2;  
    }  
    else  
    {  
        i = 0;  
    }  
    for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >='A' && s[i] <= 'Z');++i)  
    {  
        if (tolower(s[i]) > '9')  
        {  
            n = 16 * n + (10 + tolower(s[i]) - 'a');  
        }  
        else  
        {  
            n = 16 * n + (tolower(s[i]) - '0');  
        }  
    }  
    return n;  
}  

void CMD_Matrix_Refrush_Func()
{
    char line = InputString[3];
    char hexstr[2] = {0};
    int num = 0;
    //matrixdata[] = ;
    switch(line)
    {
      case '1': 
      {
        for(int i = 0; i < 4; i++)
        {
          hexstr[0] = InputString[4 + i*2];
          hexstr[1] = InputString[4 + i*2 + 1];
          sscanf(hexstr,"%x",&num);
          matrixdata[i] = num;
        }
      }break;
      case '2':
      {
        for(int i = 0; i < 4; i++)
        {
          hexstr[0] = InputString[4 + i*2];
          hexstr[1] = InputString[4 + i*2 + 1];
          sscanf(hexstr,"%x",&num);
          matrixdata[i+4] = num;
        }
      }break;
      case '3':
      {
        for(int i = 0; i < 4; i++)
        {
          hexstr[0] = InputString[4 + i*2];
          hexstr[1] = InputString[4 + i*2 + 1];
          sscanf(hexstr,"%x",&num);
          matrixdata[i+8] = num;
        }
      }break;
      case '4': 
      {
        for(int i = 0; i < 4; i++)
        {
          hexstr[0] = InputString[4 + i*2];
          hexstr[1] = InputString[4 + i*2 + 1];
          sscanf(hexstr,"%x",&num);
          matrixdata[i+12] = num;
        }
       
        cMatrix.YahBoom_OMIBOX_Matrix_Show(matrixdata);
        memset(matrixdata, 0x00, 16);
      }break;
      
    }  
}

/**
* Function       serial_data_parse
* @author        liusen
* @date          2019.02.27
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void serial_data_parse()
{
  //Serial.println(InputString);

  char cmd = InputString[2];
  char state = InputString[3];
  switch(cmd)
  {
    case '1': CMD_Sport_Func(state);break;                                             //Movement
    case '2': CMD_Matrix_Show_Func();break;                                           
    case '3': CMD_Matrix_Picture_Func(state - 0x30, InputString[4] - 0x30);break;      //Display dynamic emoticons
    case '4': CMD_Servo_Func();break;                                                  //control servo
    case '5': CMD_RGB_Func(); break;                                                   //RGB lights
    case '6': CMD_BEEP_Func(state - 0x30);break;                                       //Whistle
    case '7': CMD_Music_Func();break;                                                  //Play music
    case '8': CMD_Sound_Func(); break;                                                 //Music selection play and pause
    case '9': CMD_ReportMode_Func(state - 0x30); break;                                //Reporting mode
    case 'A': CMD_Mode_Func(state - 0x30);break;                                       //Mode select
    case 'B': CMD_Matrix_Refrush_Func();break;                                         //Lattice dynamic refresh
  } 
  InputString = "";                     //Clear serial data
  NewLineReceived = false;
  return;
  
}
/**
* Function       serialEvent
* @author        liusen
* @date          2019.02.27
* @brief         
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/

void serialEvent()
{
  while (Serial.available())
  {
    IncomingByte = Serial.read();
    if ( StartBit == false && IncomingByte == '$')
    {
      StartBit = true;
    }
    if (StartBit == true)
    {
      InputString += (char) IncomingByte;
    }
    if (IncomingByte == '#')
    {
      NewLineReceived = true;
      StartBit = false;
    }
  }
}

