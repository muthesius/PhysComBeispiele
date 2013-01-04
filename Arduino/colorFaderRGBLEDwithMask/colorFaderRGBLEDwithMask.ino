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

int masterGreen=9;
int masterBlue=10;
int masterRed=11;

int LEDGreen=3;
int LEDBlue=5;
int LEDRed=6;
int greenMask = 0xfc;
int blueMask = 0xf8;
int redMask = 0xf8;

int sensorPin=A0;
int val;

void setup(){
  Serial.begin(9600);
  pinMode(LEDRed,OUTPUT);
  pinMode(LEDGreen,OUTPUT);
  pinMode(LEDBlue,OUTPUT);  
  pinMode(masterRed,OUTPUT);
  pinMode(masterGreen,OUTPUT);
  pinMode(masterBlue,OUTPUT);  
}

void loop(){
  
  val=map(analogRead(sensorPin),0,1024,0,900);
  Serial.println(val);
  if (val<150) {
    analogWrite(LEDRed,0 & redMask);
    analogWrite(LEDBlue,255 & blueMask); 
    analogWrite(LEDGreen,255 & greenMask);    
    analogWrite(masterRed,0);
    analogWrite(masterBlue,255); 
    analogWrite(masterGreen,255);    
  } else if (val<300) {
    analogWrite(LEDRed,map(val,150,300,0,255) & redMask);
    analogWrite(LEDBlue,map(val,150,300,255,0) & blueMask); 
    analogWrite(LEDGreen,255 & greenMask);
    analogWrite(masterRed,map(val,150,300,0,255));
    analogWrite(masterBlue,map(val,150,300,255,0)); 
    analogWrite(masterGreen,255);
  } else if (val<450) {
    analogWrite(LEDRed,255 & redMask);
    analogWrite(LEDBlue,0 & blueMask); 
    analogWrite(LEDGreen,255 & greenMask);  
    analogWrite(masterRed,255);
    analogWrite(masterBlue,0); 
    analogWrite(masterGreen,255);  
  } else if (val<600) {
    analogWrite(LEDRed,255 & redMask);
    analogWrite(LEDBlue,map(val,450,600,0,255) & blueMask); 
    analogWrite(LEDGreen,map(val,450,600,255,0) & greenMask);
    analogWrite(masterRed,255);
    analogWrite(masterBlue,map(val,450,600,0,255)); 
    analogWrite(masterGreen,map(val,450,600,255,0));
  } else if (val<750) {
    analogWrite(LEDRed,255 & redMask);
    analogWrite(LEDBlue,255 & blueMask); 
    analogWrite(LEDGreen,0 & greenMask);  
    analogWrite(masterRed,255);
    analogWrite(masterBlue,255); 
    analogWrite(masterGreen,0);  
  } else if (val<900) {
    analogWrite(LEDRed,map(val,750,900,255,0) & redMask);
    analogWrite(LEDBlue,255 & blueMask); 
    analogWrite(LEDGreen,map(val,750,900,0,255) & greenMask);
    analogWrite(masterRed,map(val,750,900,255,0));
    analogWrite(masterBlue,255); 
    analogWrite(masterGreen,map(val,750,900,0,255));
  }
  delay(10);
}


