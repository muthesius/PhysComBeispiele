/*
  _____       .__  __         .__                
_/ ____\______|__|/  |________|__| ____    ____  
\   __\\_  __ \  \   __\___   /  |/    \  / ___\ 
 |  |   |  | \/  ||  |  /    /|  |   |  \/ /_/  >
 |__|   |__|  |__||__| /_____ \__|___|  /\___  / 
                             \/       \//_____/  
          __                 __                  __   .__  __   
  _______/  |______ ________/  |_  ___________  |  | _|__|/  |_ 
 /  ___/\   __\__  \\_  __ \   __\/ __ \_  __ \ |  |/ /  \   __\
 \___ \  |  |  / __ \|  | \/|  | \  ___/|  | \/ |    <|  ||  |  
/____  > |__| (____  /__|   |__|  \___  >__|    |__|_ \__||__|  
     \/            \/                 \/             \/         

Example      RGB LED Fader
Autor        Stefan Hermann
Date         16.06.2011

Description  This example lets you fade through the colors of a RGB LED.

*/

int LEDGreen=9;
int LEDBlue=10;
int LEDRed=11;


int sensorPin=A0;
int val;

void setup(){
  Serial.begin(9600);
  pinMode(LEDRed,OUTPUT);
  pinMode(LEDGreen,OUTPUT);
  pinMode(LEDBlue,OUTPUT);  
}

int maxVal = 150;

void loop(){
  
  val=map(analogRead(sensorPin),0,1023,0,900);
  Serial.println(val);
  if (val<150) {
    analogWrite(LEDRed,maxVal);
    analogWrite(LEDBlue,255); 
    analogWrite(LEDGreen,255);    
  } else if (val<300) {
    analogWrite(LEDRed,map(val,150,300,maxVal,255));
    analogWrite(LEDBlue,map(val,150,300,255,maxVal)); 
    analogWrite(LEDGreen,255);
  } else if (val<450) {
    analogWrite(LEDRed,255);
    analogWrite(LEDBlue,maxVal); 
    analogWrite(LEDGreen,255);  
  } else if (val<600) {
    analogWrite(LEDRed,255);
    analogWrite(LEDBlue,map(val,450,600,maxVal,255)); 
    analogWrite(LEDGreen,map(val,450,600,255,maxVal));
  } else if (val<750) {
    analogWrite(LEDRed,255);
    analogWrite(LEDBlue,255); 
    analogWrite(LEDGreen,maxVal);  
  } else if (val<=900) {
    analogWrite(LEDRed,map(val,750,900,255,maxVal));
    analogWrite(LEDBlue,255); 
    analogWrite(LEDGreen,map(val,750,900,maxVal,255));
  }
  delay(10);
}


