#include <Arduino.h>

#define inputA1 11
#define inputA2 10
#define inputB1 9
#define inputB2 6
#define enA 5
#define enB 3


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
    analogWrite(enA,pmwOutputA);
    analogWrite(enB,pmwOutputB);
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
  setMotorSpeed(55,55);
  moveForward();

}
