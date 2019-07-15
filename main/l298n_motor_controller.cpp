/*******************************************
l298n Motor Controller Code
Written by Daniel Payne
7/11/2019

l298n has ability to run two motors, this code uses two motors

There are 3 control inputs per motor
the enable pins which turns on the motor and allows you to control the speed via pmw
- motor controller accepts pmw in range of 0 - 255. Use 70 as minimum pmw value for movement

the input pins, in1 in2 is for first motor in3 in4 is for second motor

motors moves forward when pins are set as such:
in2,in4 = high in1,in3 = low 

switch the order and motors move in reverse

*******************************************/

#include <Arduino.h>

#define inputA1 15
#define inputA2 18
#define inputB1 4
#define inputB2 5
#define enA 13
#define enB 13

void motorSetup() {
    //Each motor requires 3 pins, enable, in1, in2
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(inputA1, OUTPUT);
    pinMode(inputA2, OUTPUT);
    pinMode(inputB1, OUTPUT);
    pinMode(inputB2, OUTPUT);
    
}

void setMotorSpeed(int pmwOutputA,int pmwOutputB){
    //Send PMW signal to l298n enable pin
    //Value ranges from 0 to 255
    //pmw should be > 70 for movement
    //use the map(value, 0, max value, 0, 255) to make things fit the 0 to 255 range
    digitalWrite(enA,pmwOutputA);
    digitalWrite(enB,pmwOutputB);
}

void moveForward(){
    // Set forward direction
    //Motor A
    digitalWrite(inputA1, LOW);
    digitalWrite(inputA2, HIGH);
    //Motor B
    digitalWrite(inputB1, LOW);
    digitalWrite(inputB2, HIGH);
}

void moveBackward(){
    // Set reverse direction
    //Motor A
    digitalWrite(inputA1, HIGH);
    digitalWrite(inputA2, LOW);
    //Motor B
    digitalWrite(inputB1, HIGH);
    digitalWrite(inputB2, LOW);
}

void moveLeft(){
    //Motor B forward
    digitalWrite(inputB1, LOW);
    digitalWrite(inputB2, HIGH);
}
void moveRight(){
    //Motor A forward
    digitalWrite(inputA1, LOW);
    digitalWrite(inputA2, HIGH);
}
