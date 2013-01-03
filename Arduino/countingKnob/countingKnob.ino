/*
  Physical Computing – Interfacedesign Muthesius Kunsthochschule Kiel

  Encoder als "counting knob".

  Based on an example from circuits at home
  http://www.circuitsathome.com/mcu/reading-rotary-encoder-on-arduino

*/

// The common counter:
int theNumber = 0;

// Pins and state for the rotary encoder
const int encPinA = 14;                           // rotary encoder pin A
const int encPinB = 15;                           // rotary encoder pin B
int encALast;


// pins, the segments are attached to
int segments[7] = {12,13,3,4,5,10,9};       
// common anode of each digit
int digits[2]   = {7,11};                    

byte seven_seg_segments[10][7] = { 
  {1,1,1,1,1,1,0},  // = 0
  {0,1,1,0,0,0,0},  // = 1
  {1,1,0,1,1,0,1},  // = 2
  {1,1,1,1,0,0,1},  // = 3
  {0,1,1,0,0,1,1},  // = 4
  {1,0,1,1,0,1,1},  // = 5
  {1,0,1,1,1,1,1},  // = 6
  {1,1,1,0,0,0,0},  // = 7
  {1,1,1,1,1,1,1},  // = 8
  {1,1,1,1,0,1,1}   // = 9
};

void setup() {    
  Serial.begin(9600);                    // starts serial communication
  
  // Setup for the rotary encoder:
  pinMode(encPinA, INPUT_PULLUP);
  pinMode(encPinB, INPUT_PULLUP);

  // Sets up the seven segment as outputs
  for (int i=0; i<7; i++){
    pinMode(segments[i], OUTPUT);           
  }

  // Sets up the common anodes as outputs
  for (int i=0; i<2; i++){
    pinMode(digits[i], OUTPUT);             
  }
}


/*
  sevenSegWrite(int thePosition, int digit) is a wrapper function to abstract
  the handling of the segment module.
 */

void sevenSegWrite(int thePosition, int digit) {
  for (int i = 0; i < 7; i++) {          
    if (seven_seg_segments[digit][i] == 1){  
      digitalWrite(segments[i], LOW);
    } 
    else {
      digitalWrite(segments[i], HIGH);
    }
  }
  digitalWrite(digits[thePosition], HIGH);
  delayMicroseconds(200);
  digitalWrite(digits[thePosition], LOW);
  delayMicroseconds(200);
}

/*
  clearDisplay() – Utility function to clear out any previous written
  symbols.
 */
void clearDisplay() {
  for (int i=0; i<5; i++){
    digitalWrite(digits[i], LOW);
  }
}

/*
  showNumber(int number);
 */
void showNumber() {
    char szZahl[1];
    sprintf(szZahl, "%d", theNumber);
    int ergebnis = szZahl[0] - '0';
    if (ergebnis>-1){
      sevenSegWrite(1,ergebnis);
      delayMicroseconds(10);
    } else {
      sevenSegWrite(1,0);
      delayMicroseconds(10);
    }
    delay(1);
    clearDisplay();
}

/*
  The actual Arduino loop function comes last
 */
void loop() {
  // read rotary encoder
  if (encALast!=digitalRead(encPinA)){
    if ((digitalRead(encPinA)==LOW)&&(digitalRead(encPinB)==LOW)) {
      
      theNumber++;
      
      if (theNumber>9) theNumber=0;
    }
    if ((digitalRead(encPinA)==LOW)&&(digitalRead(encPinB)==HIGH)) {
      
      theNumber--;
      
      if (theNumber<0) theNumber=9;
    }
  }
  
  encALast=digitalRead(encPinA);
  
  /*
    TODO clearDisplay and delay(1) really needed?
  */
  clearDisplay();
  showNumber();
  delay(1);
}
