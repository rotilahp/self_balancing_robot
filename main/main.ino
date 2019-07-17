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
#include <Arduino.h>

double MPUraw = 0;
int MPUdata = 0;
int interval = 15; //1 second between loops
double Outputraw;
int Out;
boolean forward = true;

void setup(){
    Serial.begin(115200);  
    motorSetup();
    setMotorSpeed(0,0); //Motor will start moving at 70. 70 - 225 
    MPUsetup();
    PIDsetup(0);
}
void loop(){
  MPUraw = MPUloop();      //Gets complimentary angle in degrees, double
  MPUdata = (int)MPUraw;
  Serial.print("Angle: ");
  Serial.println(MPUdata);
  
  if (MPUdata > 0){           //forward or reverse tilt
      forward = true;
      MPUdata = MPUdata*-1;
  }
  else {
      forward = false;
  }
  
  Outputraw = PIDloop(MPUdata);         //Places angle in PIDloop, setpoint being 0. 
  Out = (int)Outputraw;
  Serial.print("PID Output: ");
  Serial.println(Out);            //Motor controller starts to work around 70. So trying to get PID controller to have an output between 70-255 when there is tilt

  if (Out < 45){
      Out = 0;
  }
  setMotorSpeed(Out,Out);         //set motor speed to what PID controller is outputting. Want less speed for little tilt, more speed for big tilt
  if (forward == true){
      moveForward();
      Serial.println("hello??A");
  }
  else {
      moveBackward();
      Serial.println("hello??B");
  }
  
  delay(interval);
}
