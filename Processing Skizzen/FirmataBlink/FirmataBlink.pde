//////////////////////////////////////////////////////////////////////////////
// 
// FirmataBlink.pde
// Physical Computing – Interfacedesign, Muthesius Kunsthochschule Kiel
// 
// Created by jens on 2013-01-03.
// Copyleft 2013 Muthesius Kunsthochschule.
// 
// Basis Beispiel zur Einführung Kommunikation Arduino <-> Processing
// Ein absolutes Minimumbeispiel zur Demonstration der Datenübertragung.
// 
// LED: digital Pin 13
// Firmware für das Arduino: Examples -> Firmata -> StandardFirmata
// 
//////////////////////////////////////////////////////////////////////////////

import processing.serial.*;
import cc.arduino.*;

Arduino meinArduino;
int LED = 13;

void setup()
{
  // Liste die Anschlüsse
  println(Arduino.list());
  
  // Verbinde zum Arduino an Anschluss 0 (bei Bedarf ändern!)
  meinArduino = new meinArduino(this,Arduino.list()[0],9600);

  // Der LED-Pin soll im OUTPUT Modus sein
  meinArduino.pinMode(LED, Arduino.OUTPUT);
}

void draw()
{
  // Blinke
  meinArduino.digitalWrite(LED, Arduino.HIGH);
  delay(1000);
  meinArduino.digitalWrite(LED, Arduino.LOW);
  delay(1000);
}

