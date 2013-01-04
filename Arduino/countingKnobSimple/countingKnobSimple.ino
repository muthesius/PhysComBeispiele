/*
  Physical Computing – Interfacedesign Muthesius Kunsthochschule Kiel

  Dreh-Encoder auf einfache Weise verwenden.

*/


const int encA = 4;
const int encB = 5;
int lastA,lastB;

int counter = 0;

void setup()
{
  pinMode(encA,INPUT);
  pinMode(encB,INPUT);
  Serial.begin(9600);
}

void loop()
{
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
  }

  lastA = a;

  delay(5);
}
