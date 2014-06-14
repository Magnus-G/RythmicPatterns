// Written by: Magnus Gyllensward

#include "drumPatterns.h";

const int clkIn = 2;           // the digital (clock) input
const int digPin[2] = {3,4};  // the digital output pins
const int pinOffset = 5;       // the first DAC pin (from 5-12)
const int trigTime = 10;       // triggers are 10 ms.
volatile int clkState = LOW;
// int loops = 0;

////////////////////////////////////////////////////////////

// randomization/probability
int randValueSubtract = 1023;
int randValueAdd = 1023;

////////////////////////////////////////////////////////////

// for the on/off switch on clock in
int inputIsHigh = 0;
int digState[2] = {LOW, LOW};  // start with both set low

////////////////////////////////////////////////////////////

// counting drumloops. see drums.h for all drum patterns
int drumLoops = 0;
int drumDivision[6] = {1, 2, 4, 8, 16, 32};    

int sixth = 0;
int seventh = 0;
int eighth = 0;

////////////////////////////////////////////////////////////

int isThisATrigger[noOfDrumSteps] = {1,1,1,1,1,1,1};
int anslagEveryOther[noOfDrumSteps] = {1,1,1,1,1,1,1};

////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  
  // set up the digital (clock) input
  pinMode(clkIn, INPUT);
  
  // set up the digital outputs
  for (int i=0; i<2; i++) {
    pinMode(digPin[i], OUTPUT);
    digitalWrite(digPin[i], LOW);
  }
  
  // set up the 8-bit DAC output pins
  for (int i=0; i<8; i++) {
    pinMode(pinOffset+i, OUTPUT);
    digitalWrite(pinOffset+i, LOW);
  }
  
  attachInterrupt(0, isr, RISING);
}

////////////////////////////////////////////////////////////

void loop() {  
            
  // go through drum matrix
  for (int column=1; column<17; column++) { // temporal. start with first beat point...
    for (int row=1; row<noOfDrumSteps; row++) { // vertical, outputs. start with output 0...

      // will the program run for this column?
      randValueSubtract = random(0, 1023);
      if (randValueSubtract > analogRead(2)) {
        
        // set drumProgram
        int drumProgram = (analogRead(0) / (1023/noOfDrumPrograms)); if (drumProgram > 0) {  drumProgram--; } // deal with zero indexing on addressing the array vs the integer declared to set the number.
        
        // the hit
        if (drums[drumProgram][row-1][column-1] == 1) {
          digitalWrite(pinOffset+(row-1), 1);
        }

        // the 1 or 0 from the pattern is added to isThisATrigger
        isThisATrigger[row-1] = drums[drumProgram][row-1][column-1]; // give isThisATrigger a 1 or 0 depending on hit or not

        // a 1 is added to isThisATrigger anyway... maybe
        randValueAdd = random(0, 1023);
        if (randValueAdd < analogRead(3)) {
          digitalWrite(pinOffset+(row-1), 1);
          isThisATrigger[row-1] = 1;
        }
        
        // check if gate should be turned off or kept open
        if (isThisATrigger[row-1] == 1) { // if this is a hit
          if (anslagEveryOther[row-1] == 1) { // if the indicator variable shows 1
            digitalWrite(pinOffset+(row-1), LOW);  // turn gate off
            digitalWrite(pinOffset+(row-1), HIGH);  // turn gate on 
            digitalWrite(pinOffset+(row-1), LOW);  // turn gate off
            anslagEveryOther[row-1] = 0; // indicator value set to 0 to indicate that the last hit turned gate off... so next one should keep it on and not go through this loop
          }
          else {
            anslagEveryOther[row-1] = 1; // so that next time there will be a turning off 
          }
        }         
      }
    }
    delay(1023 - analogRead(1)); // delay after each beat == bpm
  }
      
  // extra hits, outside of the drum program
  drumLoops++;
    
  // controls the on/off for the sixth output
  if (drumLoops % 2 == 0) {
    digitalWrite(pinOffset+(5), HIGH);
    delay(1);
    
    if (sixth == 1) {
      digitalWrite(pinOffset+(5), LOW);
      sixth = 0;
    }
    else {
      sixth = 1;
    }
  }
  
  // controls the on/off for the seventh output
  if (drumLoops % 4 == 0) {
    digitalWrite(pinOffset+(6), HIGH);
    delay(1);
    
    if (seventh == 1) {
      digitalWrite(pinOffset+(6), LOW);
      seventh = 0;
    }
    else {
      seventh = 1;
    }
  }  
  
  // controls the on/off for the eighth output
  if (drumLoops % 5 == 0) {
    digitalWrite(pinOffset+(7), HIGH);
    delay(1);
    
    if (eighth == 1) {
      digitalWrite(pinOffset+(7), LOW);
      eighth = 0;
    }
    else {
      eighth = 1;
    }
  }  
} // end loop

//  =================== convenience routines ===================
//  isr() - quickly handle interrupts from the clock input
//  ------------------------------------------------------
void isr()
{
  // Note: you don't want to spend a lot of time here, because
  // it interrupts the activity of the rest of your program.
  // In most cases, you just want to set a variable and get
  // out.
  clkState = HIGH;
}

//  dacOutput(byte) - deal with the DAC output
//  -----------------------------------------
void dacOutput(byte v)
{
  PORTB = (PORTB & B11100000) | (v >> 3);
  PORTD = (PORTD & B00011111) | ((v & B00000111) << 5);
}

//  ===================== end of program =======================
