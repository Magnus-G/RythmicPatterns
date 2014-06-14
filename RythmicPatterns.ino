#include "drumPatterns.h";

const int clkIn = 2;           // the digital (clock) input
const int digPin[2] = {3,4};  // the digital output pins
const int pinOffset = 5;       // the first DAC pin (from 5-12)
const int trigTime = 10;       // triggers are 10 ms.

int const noOfDrumPrograms = 1;
int const noOfColumns = 16;
int const noOfRows = 16;

//  variables for interrupt handling of the clock input
volatile int clkState = LOW;
int loops = 0;

// randomization/probability
int randValue = 1023;

// for the on/off switch on clock in
int inputIsHigh = 0;
int digState[2] = {LOW, LOW};  // start with both set low

// counting drumloops. see drums.h for all drum patterns
int drumLoops = 0;
int drumDivision[6] = {1, 2, 4, 8, 16, 32};    

int anslag[noOfColumns] = {1,1,1,1,1,1,1};
int anslagEveryOther[noOfColumns] = {1,1,1,1,1,1,1};

int thereWillBeATrigger = 0;

int sixth = 0;
int seventh = 0;
int eighth = 0;

////////////////////////////////////////////////

int gateOpenOnThisRow[noOfRows] = {1, 1, 1, 1, 1};

////////////////////////////////////////////////

//  ==================== start of setup() ======================

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

//  ==================== start of loop() =======================
void loop() {  
          
    // go through drum matrix
    for (int row=0; row<noOfRows; row++) { // temporal. start with first beat point...
      for (int column=0; column<noOfColumns; column++) { // vertical, outputs. start with output 0...

          // set drumProgram
          int drumProgram = (analogRead(0) / (1023/noOfDrumPrograms)); if (drumProgram > 0) {  drumProgram--; } // deal with zero indexing on addressing the array vs the integer declared to set the number.

          // if pattern shows a hit. open gate
          if (drums[drumProgram][column][row] == 1) {
            thereWillBeATrigger = 1;
          }

          // Set random numbers for potential addition
          int randValueAdditions = random(0, 1023);
          if (randValueAdditions < analogRead(2)) {   
            thereWillBeATrigger = 1;
          }

          // Set random numbers for potential subtraction
          int randValueSubtractions = random(0, 1023);
          if (randValueSubtractions < analogRead(3)) {   
            thereWillBeATrigger = 0;
          }

          // TRIGGER

          if (thereWillBeATrigger == 1) {
            digitalWrite(pinOffset + column, 0);
            digitalWrite(pinOffset + column, 1);
            thereWillBeATrigger = 0;

            if (gateOpenOnThisRow[row] == 1) {
              digitalWrite(pinOffset + row, 0);
              gateOpenOnThisRow[row] = 0;
            }

            else {
              gateOpenOnThisRow[row] = 1;
            }
          }
        } // gone through all columns
        delay(1023 - analogRead(1)); // delay after each beat == bpm
      }
      
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
