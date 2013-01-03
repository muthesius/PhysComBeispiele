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

int master=6;
int master2=3;
int master3=5;

int led=11;
int led2=10;
int led3=9;

int mask = 0xf8;
int greenMask = 0xfc;
//int mask = 0x1f;
//int greenMask = 0x3f;

int sensorPin=A0;
int val;
int maskVal;
int maskGreenVal;

void setup(){
  Serial.begin(9600);
  //pinMode(led,OUTPUT);
  //pinMode(led2,OUTPUT);
  //pinMode(led3,OUTPUT);
  //pinMode(master,OUTPUT);
  //pinMode(master2,OUTPUT);
  //pinMode(master3,OUTPUT);
}

void loop(){
  
  val=map(analogRead(sensorPin),0,1023,0,255);
  //maskVal=val&mask;
  //maskGreenVal=val&mask;
  
  maskVal=(val>>4);
  maskGreenVal=(val>>3);
  //maskVal=maskVal&0x0f;
  //maskGreenVal=maskGreenVal&0x1f;
  
  Serial.print(val);
  Serial.print("  ");
  Serial.print(maskVal);
  Serial.print("  ");
  Serial.print(maskGreenVal);
  Serial.print(" / ");
  Serial.print(255>>4);
  Serial.print("       ");
  

  val=map(val, 0, 255, 255, 0);
  
  maskVal=map(maskVal, 0, 255>>4, 255, 0);
  maskGreenVal=map(maskGreenVal, 0, 255>>3, 255, 0);
  
  Serial.print(val);
  Serial.print("  ");
  Serial.print(maskVal);
  Serial.print("  ");
  Serial.println(maskGreenVal);
  
  analogWrite(master, val);
  analogWrite(master2, val);
  analogWrite(master3, val);
  analogWrite(led3, maskVal);  // red
  analogWrite(led, maskGreenVal);  // green
  analogWrite(led2, maskVal);  // blue
//  Serial.print(val);
//  Serial.print("  ");
//  Serial.print(maskVal);
//  Serial.println();
//  
  delay(10);
}


