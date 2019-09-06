/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         Tracking.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.18
* @brief        Tracking
* @details
* @par History  
*
*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

#define L_Motor_PIN1 1
#define L_Motor_PIN2 2
#define R_Motor_PIN1 15
#define R_Motor_PIN2 14

//Tracking pin definition
//TrackSensorLeftPin TrackSensorRightPin
//     L1                 R1               
const int TrackSensorLeftPin  =  7;  //Define the left tracking sensor pin (XJ1)
const int TrackSensorRightPin =  8;  //Define the right tracking sensor pin (XJ2)

int TrackSensorLeftValue; //Define variables to save the data collected by the tracking sensor
int TrackSensorRightValue;

/**
* Function       setup
* @author        Danny
* @date          2017.07.25
* @brief         Initial configuration
* @param[in]     void
* @retval        void
* @par History   no
*/
void setup()
{
  pinMode(TrackSensorLeftPin, INPUT);
  pinMode(TrackSensorRightPin, INPUT);

  digitalWrite(TrackSensorLeftPin, HIGH);
  digitalWrite(TrackSensorRightPin, HIGH);
   Serial.begin(115200);    
   Serial.println("1234");  
   pwm.begin();
   pwm.setPWMFreq(50);    // Analog servos run at ~60 Hz updates
   pinMode(4,OUTPUT);
  digitalWrite(4,0);  //Pin 4 is the pin of the color recognition sensor searchlight  
   /* In order to reduce the load of the power supply, 
   * we initialize the searchlight of the color recognition sensor when it is initialized 
   * (this is not necessary when the color recognition sensor is used) 
   */                     
}

/**
* Function       run
* @author        liusen
* @date          2017.07.25
* @brief         advance
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void run(int Speed)
{
    pwm.setPWM(L_Motor_PIN1, 0, Speed);
    pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, Speed);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}

/**
* Function       back
* @author        liusen
* @date          2017.07.25
* @brief         back
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void back(int Speed)
{
    pwm.setPWM(L_Motor_PIN1, 0, 0);
    pwm.setPWM(L_Motor_PIN2, 0, Speed);
    
    pwm.setPWM(R_Motor_PIN1, 0, 0);
    pwm.setPWM(R_Motor_PIN2, 0, Speed);
}

/**
* Function       brake
* @author        liusen
* @date          2017.07.25
* @brief         brake
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void brake()
{
    pwm.setPWM(L_Motor_PIN1, 0, 0);
    pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, 0);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}

/**
* Function       left
* @author        liusen
* @date          2017.07.25
* @brief         left(Left wheel stop, Right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void left(int Speed)
{
    pwm.setPWM(L_Motor_PIN1, 0, 0);
    pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, Speed);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}

/**
* Function       right
* @author        liusen
* @date          2017.07.25
* @brief         right(Right wheel stop, left wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void right(int Speed)
{
    pwm.setPWM(L_Motor_PIN1, 0, Speed);
    pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, 0);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}

/**
* Function       spin_left
* @author        liusen
* @date          2017.07.25
* @brief         spin_left spin_left(left wheel back, right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void spin_left(int Speed)
{
   pwm.setPWM(L_Motor_PIN1, 0, 0);
   pwm.setPWM(L_Motor_PIN2, 0, Speed);
    
    pwm.setPWM(R_Motor_PIN1, 0, Speed);
    pwm.setPWM(R_Motor_PIN2, 0, 0);
}

/**
* Function       spin_right
* @author        liusen
* @date          2017.07.25
* @brief         spin_right spin_right(left wheel advance, right wheel back)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   no
*/
void spin_right(int Speed)
{
   pwm.setPWM(L_Motor_PIN1, 0, Speed);
   pwm.setPWM(L_Motor_PIN2, 0, 0);
    
    pwm.setPWM(R_Motor_PIN1, 0, 0);
    pwm.setPWM(R_Motor_PIN2, 0, Speed);
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief        
* @param[in]     void
* @retval        void
* @par History   no
*/
void loop()
{
  //Tracking module indicator is on when no black line is detected, and the port level is HIGH.
  //Tracking module indicator is off when black line is detected, and the port level is LOW.
  TrackSensorLeftValue  = digitalRead(TrackSensorLeftPin);
  TrackSensorRightValue = digitalRead(TrackSensorRightPin);
  //2-channel tracking pin level status
  // 1 1  
  if ( TrackSensorLeftValue == HIGH && TrackSensorRightValue == HIGH) 
  {
    run(800);
    //delay(80);
  }
  //2-channel tracking pin level status
  // 1 0       
  else if ( TrackSensorLeftValue == LOW && TrackSensorRightValue == HIGH )
  {
    spin_left(800);
   //delay(80);
  }
  //2-channel tracking pin level status
  // 0 1  
  else if ( TrackSensorLeftValue == HIGH && TrackSensorRightValue == LOW)
  {
    spin_right(800);
    //delay(80);
  }
    //2-channel tracking pin level status
    // 0 0 
    else if ( TrackSensorLeftValue == LOW && TrackSensorRightValue == LOW)
  {
     brake();
  }
}


