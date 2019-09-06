/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         Infrared avoid.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.18
* @brief        Infrared avoid
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

const int AvoidSensorLeft =  A0;   //Define the infrared sensor pin (BZ1) for obstacle avoidance on the left
const int AvoidSensorRight = A1;   //Define the infrared sensor pin (BZ2) for obstacle avoidance on the right

int LeftSensorValue ;              //Define variables to save the data collected by the infrared sensor
int RightSensorValue ;

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
   pinMode(AvoidSensorLeft, INPUT);
   pinMode(AvoidSensorRight, INPUT);

   digitalWrite(AvoidSensorLeft, HIGH);
   digitalWrite(AvoidSensorRight, HIGH);
   Serial.begin(115200);
   Serial.println("1234");
   pwm.begin();
   pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates 
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


void loop()
{ 
    //When an obstacle is encountered, the indicator of the infrared obstacle avoidance module is on, and the port level is HIGH.
    //When an obstacle is not encountered, the indicator of the infrared obstacle avoidance module is off, the port level is LOW
    LeftSensorValue  = digitalRead(AvoidSensorLeft);
    RightSensorValue = digitalRead(AvoidSensorRight);
    if (LeftSensorValue == LOW && RightSensorValue == LOW)
    {
      run(800);  //when obstacles are not detected on both the left and right sides, Call run function 
    }
    else if (LeftSensorValue == HIGH && RightSensorValue == LOW)
    {
      spin_right(650);   //An obstacle was detected on the left, robot car spin right
    }
    else if (RightSensorValue == HIGH && LeftSensorValue == LOW)
    {
      spin_left(650);     //An obstacle was detected on the right, robot car spin left
    }
    else
    {
      spin_right(800);
    }
}

