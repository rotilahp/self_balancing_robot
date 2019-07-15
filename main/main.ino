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

double MPUdata = 0;
int interval = 15; //1 second between loops

void setup(){
    Serial.begin(115200);  
    MPUsetup();
}
void loop(){
  MPUdata = MPUloop();
  
  Serial.print("Angle: ");
  Serial.println(MPUdata);
  
  delay(15);
}
