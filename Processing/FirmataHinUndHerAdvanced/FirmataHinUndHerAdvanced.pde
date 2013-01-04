//////////////////////////////////////////////////////////////////////////////
// 
// FirmataHinUndHerAdvanced.pde
// Physical Computing – Interfacedesign, Muthesius Kunsthochschule Kiel
// 
// Created by jens on 2013-01-03.
// Copyleft 2013 Muthesius Kunsthochschule.
// 
// Beispiel zur Einführung das Arduino mit Processing mit Hilfe der
// Firmata Bibliothek zu nutzen.
// 
// Der an den digitalen Pin 2 angeschlossene Button zeichnet bei Drücken
// ein Quadrat in das Processing Fenster und das Processing Programm
// schaltet die an Pin 13 angeschlossene LED respektive an oder aus.
// 
// Button: digital Pin 2
// LED: digital Pin 13
// Firmware für das Arduino: Examples -> Firmata -> StandardFirmata
//
//////////////////////////////////////////////////////////////////////////////



// Importiere die notwendigen Module, um mit dem Arduino zu kommunizieren
import processing.serial.*;
import cc.arduino.*;

// Lege ein Arduino an
Arduino meinArduino;

// Der Pin welcher mit der LED verbunden ist
int LED = 13;

// Der Pin des Arduinos, der mit dem Button verbunden ist
int BUTTON = 2;
// Für die Edges des Buttons brauchen wir die übliche State-Variable
int buttonState = 0;


// Das Programm wird in setup() vorbereitet
void setup()
{
  // Zur Information welche Anschlüsse der Computer hat,
  // printe diese in die Console:
  println(Arduino.list());
  
  // Der Port kann von Computer zu Computer unterschiedlich sein.
  // Trage die entsprechende Nummer aus der Console am Ende dieses
  // Befehls ein
  String arduinoPort = Arduino.list()[0];
  
  // Starte das Arduino mit diesem Befehl (this, Anschluss, Geschwindigkeit)
  meinArduino = new Arduino(this, arduinoPort, 9600);
  
  // Setze den Modus der beiden Pins
  meinArduino.pinMode(BUTTON,Arduino.INPUT);
  meinArduino.pinMode(LED,Arduino.OUTPUT);
  
  // Setup Fertig
}

void draw()
{
  int button = meinArduino.digitalRead(BUTTON);
  
  // Edge Detection - hat sich der Zustand geändert?
  if(button != buttonState)
  {
    // Wir haben ein Up-Edge
    if(buttonState == Arduino.HIGH)
    {
      // Schalte die LED an:
      meinArduino.digitalWrite(LED,Arduino.HIGH);
      
      // Zeichne ein weißes Quadrat in die Mitte:
      fill(255);
      stroke(255);
      rect(10,10,width-10,height-10);
      
      println("BUTTON is HIGH");
    }
    // Wir haben ein Down-Edge
    else
    {
      // Schalte die LED aus:
      meinArduino.digitalWrite(LED,Arduino.LOW);
      
      // Zeichne ein Quadrat in die Mitte, aber ohne Füllung:
      noFill();
      stroke(255);
      rect(10,10,width-10,height-10);
      
      println("BUTTON is LOW");
    }
  }
  
  buttonState = button;
}


