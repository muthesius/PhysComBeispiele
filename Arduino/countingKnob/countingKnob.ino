/*
  Physical Computing – Interfacedesign Muthesius Kunsthochschule Kiel

  Dreh-Encoder trifft 7-Segmentanzeige

  Komments will bi in Inglish!
*/


// The common counter:
int counter = 0;

// Pins and state for the rotary encoder
const int encA = 4;
const int encB = 5;
int lastA,lastB;


// pins, the segments are attached to
int segments[7] = {6,7,8,9,10,11,12};

// Number of gits stored in the seven_seg_segments array:
const int NUM_DIGITS = 10;
byte seven_seg_segments[NUM_DIGITS][7] = {
  {1,1,1,1,1,1,0},  // = 0
  {0,0,1,1,0,0,0},  // = 1
  {1,1,0,1,1,0,1},  // = 2
  {0,1,1,1,1,0,1},  // = 3
  {0,0,1,1,0,1,1},  // = 4
  {0,1,1,0,1,1,1},  // = 5
  {1,1,1,0,1,1,1},  // = 6
  {0,0,1,1,1,0,0},  // = 7
  {1,1,1,1,1,1,1},  // = 8
  {0,1,1,1,1,1,1},  // = 9
};


void displayNumber(int number) {
  int digit = constrain(number,0,NUM_DIGITS);
  for (int i = 0; i < 7; i++) {
    if (seven_seg_segments[digit][i] == 1){
      digitalWrite(segments[i], HIGH);
    }
    else {
      digitalWrite(segments[i], LOW);
    }
  }
}


void setup() {
  Serial.begin(9600);

  // Setup for the rotary encoder:
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);

  // Sets up the seven segment as outputs
  for (int i=0; i<7; i++){
    pinMode(segments[i], OUTPUT);
    digitalWrite(segments[i], LOW);
  }
  
  displayNumber(counter);
}

void loop(){
  int a = digitalRead(encA);
  int b = digitalRead(encB);

  if ( lastA == LOW &&  a == HIGH ) {
    if ( b == LOW ) {
      Serial.print("UP\t");
      counter++;
    } else {
      Serial.print("DOWN\t");
      counter--;
    }

    if ( counter > 9 ) counter = 0;
    if ( counter < 0 ) counter = 9;

    Serial.print("Counter:\t");
    Serial.println(counter);
    displayNumber(counter);
  }

  lastA = a;

  delay(5);
}
