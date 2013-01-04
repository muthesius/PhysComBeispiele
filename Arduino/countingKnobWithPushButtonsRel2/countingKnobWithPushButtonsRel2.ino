/*
inspired by circuits at home
http://www.circuitsathome.com/mcu/reading-rotary-encoder-on-arduino
*/

const int encPinA = A2;                           // rotary encoder pin A
const int encPinB = A3;                           // rotary encoder pin B
int encALast;

int theNumber = 0;
int sendNumber = -1;
const int maxNumber = 255;
int val; 
int segments[7] = {11,12,6,7,8,10,9};       // pins, the segments are attached to

int buttonUpPin = A4;                        // pin, where the push button UP is connected
int buttonDownPin = A5;                      // pin, where the push button DOWN is connected
int buttonUpState;
int buttonDownState;
int lastButtonUpState;
int lastButtonDownState;


byte seven_seg_segments[16][7] = { 
  {1,1,1,1,1,1,0},  // = 0
  {0,1,1,0,0,0,0},  // = 1
  {1,1,0,1,1,0,1},  // = 2
  {1,1,1,1,0,0,1},  // = 3
  {0,1,1,0,0,1,1},  // = 4
  {1,0,1,1,0,1,1},  // = 5
  {1,0,1,1,1,1,1},  // = 6
  {1,1,1,0,0,0,0},  // = 7
  {1,1,1,1,1,1,1},  // = 8
  {1,1,1,1,0,1,1},  // = 9
  {1,1,1,0,1,1,1},  // = A
  {0,0,1,1,1,1,1},  // = B
  {1,0,0,1,1,1,0},  // = C
  {0,1,1,1,1,0,1},  // = D
  {1,0,0,1,1,1,1},  // = E
  {1,0,0,0,1,1,1}   // = F
};

byte leds_segments[16][4] = { 
  {1,1,1,1},  // = 0
  {1,1,1,0},  // = 1
  {1,1,0,1},  // = 2
  {1,1,0,0},  // = 3
  {1,0,1,1},  // = 4
  {1,0,1,0},  // = 5
  {1,0,0,1},  // = 6
  {1,0,0,0},  // = 7
  {0,1,1,1},  // = 8
  {0,1,1,0},  // = 9
  {0,1,0,1},  // = A
  {0,1,0,0},  // = B
  {0,0,1,1},  // = C
  {0,0,1,0},  // = D
  {0,0,0,1},  // = E
  {0,0,0,0}   // = F
};

void setup() {    
  Serial.begin(9600);                    // starts serial communication
  //pinMode(encPinA, INPUT);                    // set rotary encoder A pin as input
  //pinMode(encPinB, INPUT);                    // set rotary encoder B pin as input  
  //digitalWrite(encPinA, HIGH);                // switches internal drop down resistors on
  //digitalWrite(encPinB, HIGH);                // switches internal drop down resistors on

  //pinMode(buttonUpPin,INPUT);
  //pinMode(buttonDownPin, INPUT);
  
  for (int i=0; i<7; i++){
    pinMode(segments[i], OUTPUT);           // sets the seven segment outputs
  }
}

void sevenSegWrite(int digit) {  // write a number to a seven segment digit
  for (int i = 0; i < 7; i++) {          
    if (seven_seg_segments[digit][i] == 1){  // segment connected to ground leads to 0 instead of 1  
      digitalWrite(segments[i], LOW);
    } 
    else {
      digitalWrite(segments[i], HIGH);
    }
  }
}

void ledsWrite(int digit) {
  for (int i = 0; i < 4; i++) {          
    if (leds_segments[digit][i] == 1){  
      digitalWrite(segments[i], LOW);
    } 
    else {
      digitalWrite(segments[i], HIGH);
    }
  }  
}

void showNumber(){                                 // show the number

    if (sendNumber != theNumber) {
    byte toBeSend = theNumber;
    Serial.write(toBeSend);
    sendNumber = theNumber;
    }

    int ergebnis = theNumber&0x0f;
    if (ergebnis>-1){
      //sevenSegWrite(ergebnis);
      ledsWrite(ergebnis);
      delayMicroseconds(10);
    } else {
      //sevenSegWrite(0);
      ledsWrite(0);
      delayMicroseconds(10);
    }
}

void nextNumber() {
      theNumber++;
      if (theNumber>maxNumber) theNumber=0;
}

void prevNumber() {
      theNumber--;
      if (theNumber<0) theNumber=maxNumber;
}

void loop() {
  // read rotary encoder
  int encPinAState = digitalRead(encPinA);
  int encPinBState = digitalRead(encPinB);  
  
  if (encALast!=encPinAState){
    if ((encPinAState==HIGH)&&(encPinBState==HIGH)) {
      nextNumber();
    }
    if ((encPinAState==HIGH)&&(encPinBState==LOW)) {
      prevNumber();
    }
  }
  
  encALast=encPinAState;
  
  buttonUpState = digitalRead(buttonUpPin);
  // compare the buttonState to its previous state
  if (buttonUpState != lastButtonUpState) {
    // if the state has changed, increment the counter
    if (buttonUpState == HIGH) {
      // if the current state is HIGH then the button wend from off to on:
      nextNumber();
    } 
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonUpState = buttonUpState;
  
  buttonDownState = digitalRead(buttonDownPin);
  // compare the buttonState to its previous state
  if (buttonDownState != lastButtonDownState) {
    // if the state has changed, increment the counter
    if (buttonDownState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      prevNumber();
      //Serial.println("dec");
    } 
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonDownState = buttonDownState;
  showNumber();
  
  ////////////////////// integration of snippet taken from PhysicalPixel example
  
    if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    byte incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      nextNumber();
    } 
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      prevNumber();
    }
  }
  
  delay(5);
}
