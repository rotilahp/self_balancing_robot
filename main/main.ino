/*******************************************
 * 
 * Daniel Payne's Amazing Self Balancing Robot with Android App controls
 * 8/6/2019
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

double MPUdata = 0;   //complimentary angle from accelerometer IMU
int interval = 15; //1 second between loops
double Out;   //pid output
boolean forward = true;
double MPUrotvel = 0;
int inByte;

double previousMillis;
double currentMillis;

void setup(){
    Serial.begin(9600);  
    motorSetup();
    setMotorSpeed(0,0); //Motor will start moving at 70. 70 - 225 
    MPUsetup();
    PIDsetup(0);

    //timer for bluetooth
    previousMillis = millis();
}
void loop(){
  /**********************
   * ACCELEROMETER/GYROSCOPE
   * RAW DATA -> COMPLIMENTARY ANGLE
   ********************/
  MPUdata = MPUloop();  //Gets complimentary angle in degrees
 
  
  //ROTATIONAL VELOCITY
  MPUrotvel =sq(0.917185*2.0*9.8*0.1524*(1.0 - cos(MPUdata*PI/180.0))/0.00884422);

  /***************
   * WHICH WAY IS ROBOT TILTING!?!?!
   * Figures out if robot is falling forward or backwards
   ******************/
  if (MPUdata > 0){           //forward or reverse tilt
      forward = true;
      MPUdata = MPUdata*-1;
  }
  else {
      forward = false;
  }
  /***************
   * PID CONTROLLER
   * Tries to return back to setpoint which is angle of 0
   * Set to provide more power the further away from 0 the angle becomes
   ***********************/
  //inputValue = map(MPUrotvel, 0,9,0,120);
  Out = PIDloop(MPUrotvel);         //Places velocity into PIDloop, setpoint being 0. 
  if (Out < 56){                    //Motor doesnt really work well below this value
      Out = 0;
  }
  /***************
   * MOTOR CONTROLLER
   ******************/
  setMotorSpeed(Out,Out);         //set motor speed to what PID controller is outputting. Want less speed for little tilt, more speed for big tilt
  if (forward == true){           //is the robot falling forward or reverse direction
      moveForward();
  }
  else {
      moveBackward();
  }
   /***************
   * Bluetooth Module HC-05
   * Works off of Rx and Tx pins, ez pz
   * default baud rate of 9600
   * ez just use Serial stuff
   ***************/
   currentMillis = millis();
   if ((currentMillis - previousMillis) > 1000){
        previousMillis = currentMillis;
        Serial.print(String(MPUdata,4));   //Sends angle
        Serial.print(",");                 //comma seperates string on android app
        Serial.print("60");                //Sends Temperature   
   }
  
  if (Serial.available() > 0) {
        inByte = Serial.read();
        inByte=inByte-48;     //converts it to ASCII
    
        if (inByte==0)
        {
        //no input
        }
        if (inByte==1)
        {
        //1 for forward  
        }
        if (inByte==2)
        {
        //2 is left  
        }
        if (inByte==3)
        {
        //3 is right
        }
        if (inByte==4)
        {
        //4 is reverse  
        }
    }
  // DELAY
  delay(interval);
}
