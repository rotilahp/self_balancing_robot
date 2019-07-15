/*******************************************
 * 
 * Daniel Payne's Amazing Self Balancing Robot with Android App controls
 * 7/11/2019
 * dpayne.us
 * danielgatesf@gmail.com
 * 
 *********************************************/

#include "l298n_motor_controller.h"
#include "bluetooth.h"
#include "mpu_acc_and_gyro.h"
#include "pid_controller.h"

double MPUdata = 0;
int interval = 15; //1 second between loops
double Out;
boolean forward = true;

void setup(){
    Serial.begin(115200);  
    motorSetup();
    setMotorSpeed(0,0); //Motor will start moving at 70. 70 - 225 
    MPUsetup();
    PIDsetup(0);
}
void loop(){
  MPUdata = MPUloop();      //Gets complimentary angle in degrees, double
  Serial.print("Angle: ");
  Serial.println(MPUdata);
  
  if (MPUdata < 0){           //forward or reverse tilt
      forward = false;
  }
  else {
      forward = true;
      MPUdata = MPUdata*-1;
  }
  
  Out = PIDloop(MPUdata);         //Places angle in PIDloop, setpoint being 0. 
  Serial.print("PID Output: ");
  Serial.println(Out);            //Motor controller starts to work around 70. So trying to get PID controller to have an output between 70-255 when there is tilt
  
  setMotorSpeed(Out,Out);         //set motor speed to what PID controller is outputting. Want less speed for little tilt, more speed for big tilt
  if (forward = true){
      moveForward();
  }
  else {
      moveBackward();
  }
  
  delay(interval);
}
