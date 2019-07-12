#include <Arduino.h>

#define inputA1 15
#define inputA2 18
#define inputB1 4
#define inputB2 5
#define enA 13
#define enB 13


void setup() {
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

void loop() {
  setMotorSpeed(200,200);
  moveForward();

}
