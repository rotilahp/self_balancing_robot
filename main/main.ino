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
#include <math.h>

double MPUdata = 0;
int interval = 15; //1 second between loops
double Out;
boolean forward = true;
double MPUrotvel = 0;

void setup(){
    Serial.begin(115200);  
    motorSetup();
    setMotorSpeed(0,0); //Motor will start moving at 70. 70 - 225 
    MPUsetup();
    PIDsetup(0);
}
void loop(){
  MPUdata = MPUloop()-5.5;  //Gets complimentary angle in degrees, double to int
  Serial.print("Angle: ");
  Serial.println(MPUdata);
  
  MPUrotvel =sq(0.917185*2.0*9.8*0.1524*(1.0 - cos(MPUdata*PI/180.0))/0.00884422);
  Serial.print("Rotational Velocity: ");
  Serial.println(MPUrotvel);
  /***************
   * Figures out if robot is falling forward or backwards
   */
  if (MPUdata > 0){           //forward or reverse tilt
      forward = true;
      MPUdata = MPUdata*-1;
  }
  else {
      forward = false;
  }
  /***************
   * Sends data to PID, PID gives us an output value
   */
  //inputValue = map(MPUrotvel, 0,9,0,120);
  Out = PIDloop(MPUrotvel);         //Places velocity into PIDloop, setpoint being 0. 
  Serial.print("PID Output: ");
  Serial.println(Out);            //Motor controller starts to work around 70. So trying to get PID controller to have an output between 70-255 when there is tilt

  if (Out < 56){                  //Motor doesnt really work well below this value
      Out = 0;
  }
  /***************
   * Send PID output to motor controller for movement
   */
  
  setMotorSpeed(Out,Out);         //set motor speed to what PID controller is outputting. Want less speed for little tilt, more speed for big tilt
  if (forward == true){         //is the robot falling forward or reverse direction
      moveForward();
  }
  else {
      moveBackward();
  }
  
  delay(interval);
}
