/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int photocellSensorPin = A2;    // select the input pin for the potentiometer
int potocellLedPin = 9;      // select the pin for the LED

int temperatureSensorPin = A0;    // select the input pin for the potentiometer
int temperatureLedPin = 10;      // select the pin for the LED

int forceSensorPin = A1;    // select the input pin for the potentiometer
int forceLedPin = 6;      // select the pin for the LED

int distanceSensorPin = A3;    // select the input pin for the potentiometer
int distanceLedPin = 5;      // select the pin for the LED

int potiSensorPin = A4;    // select the input pin for the potentiometer
int potiLedPin = 3;      // select the pin for the LED

int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  //pinMode(potocellLedPin, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(photocellSensorPin);
  Serial.print("photocell: "); 
  Serial.println(sensorValue);  
  sensorValue = map(sensorValue, 0, 900, 0, 255);
  analogWrite(potocellLedPin, sensorValue);
  
  sensorValue = analogRead(temperatureSensorPin);
  sensorValue = sensorValue*0.488; 
  Serial.print("temperature: ");
  Serial.println(sensorValue);  
  sensorValue = map(sensorValue, 25, 32, 00, 255);
  analogWrite(temperatureLedPin, sensorValue);
  
  sensorValue = analogRead(forceSensorPin);
  Serial.print("force: ");
  Serial.println(sensorValue);  
  sensorValue = map(sensorValue, 0, 1000, 20, 255);
  analogWrite(forceLedPin, sensorValue);
  
  sensorValue = analogRead(distanceSensorPin);
  Serial.print("distance: " );
  Serial.print(sensorValue);  
  sensorValue = map(sensorValue, 35, 470, 20, 255);
  Serial.print("/");
  Serial.println(sensorValue);
  analogWrite(distanceLedPin, sensorValue);
  
  sensorValue = analogRead(potiSensorPin);
  Serial.print("poti: " );
  Serial.print(sensorValue);  
  sensorValue = map(sensorValue, 0, 1023, 20, 255);
  Serial.print("/");
  Serial.println(sensorValue);
  analogWrite(potiLedPin, sensorValue);
  
  delay(500);                  
}
