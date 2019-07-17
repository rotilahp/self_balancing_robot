    
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
double Kp=3.5, Ki=0.0005, Kd=0.00005;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void PIDsetup(double In)
{
  //initialize the variables we're linked to
  Input = In;
  Setpoint = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

double PIDloop(double In)
{
  Input = In;
  myPID.Compute();
  return Output;
}
