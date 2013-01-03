
// mouseover serial 

// Demonstrates how to send data to the Arduino I/O board, in order to 
// turn ON a light if the mouse is over a square and turn it off 
// if the mouse is not. 

// created 2003-4
// based on examples by Casey Reas and Hernando Barragan
// modified 30 Aug 2011
// by Tom Igoe
// This example code is in the public domain.



import processing.serial.*; 

float boxX;
float boxY;
int boxSize = 20;
boolean mouseOverBox = false;
int readVal = 0;
PFont font;

Serial port;

void setup() {
  size(400, 200);
  boxX = width/3.0;
  boxY = height/2.0;
  rectMode(RADIUS); 
  font = loadFont("FreeSans-48.vlw");
  textFont(font, 48);

  // List all the available serial ports in the output pane. 
  // You will need to choose the port that the Arduino board is 
  // connected to from this list. The first port in the list is 
  // port #0 and the third port in the list is port #2. 
  println(Serial.list()); 

  // Open the port that the Arduino board is connected to (in this case #0) 
  // Make sure to open the port at the same speed Arduino is using (9600bps) 
  port = new Serial(this, Serial.list()[0], 9600);
}

boolean containsMouse() {
  return (mouseX > boxX-boxSize && mouseX < boxX+boxSize && mouseY > boxY-boxSize && mouseY < boxY+boxSize);
}

void draw() 
{ 

  background(0);

  if ( port.available() > 0) {  // If data is available,
    readVal = port.read();         // read it and store it in val
    println("moin");
  }

  //println(readVal);

  // Test if the cursor is over the box 
  if (containsMouse() && !mouseOverBox) {
    mouseOverBox = true;  
    // draw a line around the box and change its color:
    stroke(255); 
    fill(readVal*16);
    // send an 'H' to indicate mouse is over square:
    port.write('H');
  } 
  else {
    // return the box to it's inactive state:
    stroke(153);
    fill(readVal*16);
    // send an 'L' to turn the LED off: 
    //port.write('L');      
    //mouseOverBox = false;
  }

  if (!containsMouse() && mouseOverBox) {
    mouseOverBox = false;
  }
  
  //if (containsMouse() && 

  // Draw the box
  rect(boxX, boxY, boxSize, boxSize);
  
  fill(255);
  String numberText;
  numberText = binary(readVal, 4)+ "B  0x" + hex(readVal, 1) + "  " + str(readVal);
  text(numberText, 10, 50);
}

//void mouseClicked() {
//  println("mouseClicked"+mouseButton);
//  switch (mouseButton) {
//    case LEFT: println("left"); break;
//    case RIGHT: println("right"); break;
//  }
//}

void mousePressed() {
  println("mousePressed");
  if (mouseButton == LEFT) {
    println("left");
    port.write('L');
  } else if (mouseButton == RIGHT) {
    println("right");
    port.write('H');
  } else {
    println("unkown");
  }
}



