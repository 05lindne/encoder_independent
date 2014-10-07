// @file encoder_independent.ino
// Encoder Functions--------------------------------------------------

//libraries for high performance reads and writes e.g. fastDigitalRead( pin )
#include "SoftSPI.h"

//Encoder specific variables-----------------------
#define encoderPinA 2
#define encoderPinB 8



int encoderInterruptA = 1;


volatile long encoderPos = 1;
volatile long oldPos = 0;


volatile long BSet = 0;


int test =0;

void HandleInterruptA();



void setup(){

  while(!Serial){;}       // needed for Ardiuno Leonardo to wait with executing until terminal is open
  Serial.begin(9600);           // set up Serial library at 9600 bps  
  


  pinMode(encoderPinA, INPUT);      // sets pin A as input
  digitalWrite(encoderPinA, LOW);  // turn on pullup resistors
  pinMode(encoderPinB, INPUT);      // sets pin B as input
  digitalWrite(encoderPinB, LOW);  // turn on pullup resistors
  
  attachInterrupt(encoderInterruptA, HandleInterruptA, RISING);


  Serial.println("Encoder configuration done.");               
}






void loop()
{
  
  // output encoder tick
  if (oldPos != encoderPos) {

    int revolution = encoderPos/4000;
    int encoderTick = encoderPos%4000;

    Serial.print("Encoder Revolution: "); 
    Serial.print(revolution, DEC); 
    Serial.print("\t Encoder Tick: ");
    Serial.print(encoderTick, DEC);
    Serial.print("\t Encoder Position: ");
    Serial.println(encoderPos, DEC);
    Serial.print("\t Test: ");
    Serial.println(test, DEC);
    oldPos = encoderPos;

    test++;
  }

}




void HandleInterruptA (){

  // Test transition; 
  // since the interrupt will only fire on 'rising' 
  // we don't need to read pin A
  BSet = fastDigitalRead(encoderPinB);

  // and adjust counter +1 if A leads B
  encoderPos += BSet ? -1 : +1;

}