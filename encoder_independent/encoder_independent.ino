// @file encoder_independent.ino
// Encoder Functions--------------------------------------------------

//libraries for high performance reads and writes e.g. fastDigitalRead( pin )
#include "SoftSPI.h"

//Encoder specific variables-----------------------
#define encoderPinA 2
#define encoderPinB 3
#define encoderPinA1 4 //0 // inverted channels
#define encoderPinB1 5 //1 // inverted channels



// int encoderInterruptA = 0;
// int encoderInterruptB = 1;
int encoderInterruptA = 1;
int encoderInterruptB = 0;

volatile long encoderPos = 1;
volatile long oldPos = 0;
// volatile long encoderRev = 0;
// volatile long oldRev = 0;

volatile long Aold = 0;
volatile long Bnew = 0;
// volatile long A1old = 1; // inverted channels
// volatile long B1new = 1; // inverted channels




int test =0;

void HandleInterruptA();
void HandleInterruptB();


void setup(){

  while(!Serial){;}       // needed for Ardiuno Leonardo to wait with executing until terminal is open
  Serial.begin(9600);           // set up Serial library at 9600 bps  
  

   // Quadrature encoders
  pinMode(encoderPinA, INPUT);      // sets pin A as input
  digitalWrite(encoderPinA, LOW);  // turn on pullup resistors
  pinMode(encoderPinB, INPUT);      // sets pin B as input
  digitalWrite(encoderPinB, LOW);  // turn on pullup resistors
  
  attachInterrupt(encoderInterruptA, HandleInterruptA, CHANGE);
  attachInterrupt(encoderInterruptB, HandleInterruptB, CHANGE);

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







// Interrupt on A changing state
void HandleInterruptA(){

  //heart of the encoder count
  // (Bnew^Aold && B1new^A1old) ? encoderPos++ : encoderPos-- ; // XOR for normal and inverted channels and comparison 
  Bnew^Aold ? encoderPos++ : encoderPos-- ; // XOR for normal and inverted channels and comparison 

  Aold = fastDigitalRead(encoderPinA);
  // A1old = fastDigitalRead(encoderPinA1);

}

// Interrupt on B changing state
void HandleInterruptB(){

  Bnew=fastDigitalRead(encoderPinB);
  // B1new=fastDigitalRead(encoderPinB1);

  //heart of the encoder count
  // (Bnew^Aold && B1new^A1old) ? encoderPos++:encoderPos--;// XOR for normal and inverted channels and comparison
  Bnew^Aold ? encoderPos++:encoderPos--;// XOR for normal and inverted channels and comparison

}


// // Interrupt service routines for the left motor's quadrature encoder
// void HandleInterruptA(){
//   BSet = fastDigitalRead(encoderPinB);
//   ASet = fastDigitalRead(encoderPinA);
//   B1Set = fastDigitalRead(encoderPinB1);
//   A1Set = fastDigitalRead(encoderPinA1);
  
//   if ( (BSet == B1Set) || (ASet == A1Set) ) return;

//   encoderPos+=ParseEncoder();
  
//   APrev = ASet;
//   BPrev = BSet;
// }

// // Interrupt service routines for the right motor's quadrature encoder
// void HandleInterruptB(){
//   // Test transition;
//   BSet = fastDigitalRead(encoderPinB);
//   ASet = fastDigitalRead(encoderPinA);
//   B1Set = fastDigitalRead(encoderPinB1);
//   A1Set = fastDigitalRead(encoderPinA1);

//   if ( (BSet == B1Set) || (ASet == A1Set) ) return;

//   encoderPos+=ParseEncoder();
  
//   APrev = ASet;
//   BPrev = BSet;
// }

// int ParseEncoder(){
//   if(APrev && BPrev){
//     if(!ASet && BSet) return 1;
//     if(ASet && !BSet) return -1;
//   }else if(!APrev && BPrev){
//     if(!ASet && !BSet) return 1;
//     if(ASet && BSet) return -1;
//   }else if(!APrev && !BPrev){
//     if(ASet && !BSet) return 1;
//     if(!ASet && BSet) return -1;
//   }else if(APrev && !BPrev){
//     if(ASet && BSet) return 1;
//     if(!ASet && !BSet) return -1;
//   }
// }