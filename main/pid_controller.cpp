    
/********************************************************
 * PID using PID library
 * Daniel Payne
 *
 ********************************************************/

#include <PID_v1.h>
#include <Arduino.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=0.22, Ki=0.0, Kd=0.19;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void PIDsetup(double In)
{
  //initialize the variables we're linked to
  Input = In;
  Setpoint = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  //limit range of output to motor
  myPID.SetOutputLimits(55.90,170);
  //set sample time , 15 milliseconds
  myPID.SetSampleTime(15);
  //tell PID to increase in response when input is above setpoint
  myPID.SetControllerDirection(REVERSE);
}

double PIDloop(double In)
{
  Input = In; 
  myPID.Compute();
  return Output;
}
