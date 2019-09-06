/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         CarRun.c
* @author       xiaozhen
* @version      V1.0
* @date         2018.10.18
* @brief         CarRun
* @details
* @par History  
*
*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

//Define the pins of the motor
#define L_Motor_PIN1 1
#define L_Motor_PIN2 2 
#define R_Motor_PIN1 15
#define R_Motor_PIN2 14

/**
* Function       setup
* @author        liusen
* @date          2017.07.25
* @brief         Initial configuration
* @param[in]     void
* @retval        void
* @par History   no
*/
void setup()
{
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
    delay(2000);
    while(1)
    {
       run(1000);    
       delay(1000);
       back(1000);
       delay(1000);
       left(1000);
       delay(1000);
       right(1000);
       delay(1000);
       spin_left(1000);
       delay(1000);
       spin_right(1000);
       delay(1000);
       brake();
       delay(1000);
    }
}

