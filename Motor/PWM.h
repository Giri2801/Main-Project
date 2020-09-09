#include <time.h> 
#include "pwm_driver.h"
#include"../defines.h"
#define Mode int
#define FORWARD 0
#define RIGHT 1
#define LEFT 2 
#define SPEED                 // write some constant
#define ANGULAR_VELOCITY      // write some constant




//supporting functions
void initializeMotor();
void rotate(Angle angle, bool leftorright);
void go_straight(Distance distance);

//additional function 
void Run(int module_number,int time);

//PWM_0 :
//        Input1,Input3 of L293D motordriver is given high ("So that both Motors rotate in clockwise")
//PWM_1 :
//        Input1,Input4 of L293D motordriver is given high ("")
//PWM_2 :
//        Input2,Input4 of L293D motordriver is given high ("")

//https://www.instructables.com/id/L293D-Motor-Driver/