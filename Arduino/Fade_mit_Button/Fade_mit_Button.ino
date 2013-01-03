/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int led = 9;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int buttonPin = 2;
int buttonState = HIGH;


// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
} 

// the loop routine runs over and over again forever:
void loop()  { 
  buttonState = digitalRead(buttonPin);

  if ( buttonState == LOW ) {
    brightness = brightness + fadeAmount; // Schritt 1
  } else {
    brightness = brightness - fadeAmount; // Schritt 2
  }
  
  // Schritt 3
  if ( brightness < 0 ) {
    brightness = 0;
  }
  else if ( brightness > 255 ) {
    brightness = 255;
  }
  
  // set the brightness of pin 9:
  analogWrite(led, brightness);    
  
  
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}

