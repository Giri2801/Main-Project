#include"PWM.h"

void delay(int milli_seconds) 
{  
    clock_t start_time = clock(); 
    while (clock() < (start_time + milli_seconds)) 
        ; 
}


//https://components101.com/l293d-pinout-features-datasheet

void initializeMotor(){
    pwm_configure(PWM_0, 0xffff, 0xff, 0x01, false);
    pwm_configure(PWM_1, 0xffff, 0xff, 0x01, false);
    pwm_configure(PWM_2, 0xffff, 0xff, 0x01, false);
}

int getmodule(Mode mode){
  if(mode == FORWARD){
      return PWM_0;
  }
  else if(mode== RIGHT){
      return PWM_1;
  }
  else if(mode== LEFT){
      return PWM_2;
  }
}


void Run(int module_number,int time)
{     
    pwm_start(module_number,2);
    delay(time);
    pwm_stop(module_number);
}

void go_straight(Distance distance)   // distance in millimetres
{
    int time = (distance*(1.0))/(SPEED);
    int module_number = getmodule( FORWARD );
    Run( module_number,time );
}


void rotate(Angle angle,bool leftorright)  // left means boolean is true, otherwise false
{
   int time = (angle/ANGULAR_VELOCITY);
   int module_number;
   if(leftorright){
      module_number = getmodule(LEFT);
   }
   else {
      module_number = getmodule( RIGHT );
   }
   Run( module_number,time );
}

