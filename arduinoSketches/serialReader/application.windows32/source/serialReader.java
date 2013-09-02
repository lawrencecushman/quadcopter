import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class serialReader extends PApplet {



Serial serialPort;
String myString = null;
PFont font;

public void setup() {
 size(500,500);
 println(Serial.list());
 
 font = createFont("Helvetica", 16, true); // Helvetica, 16pt font, AA on
 
 serialPort  = new Serial(this, Serial.list()[0], 9600);
 serialPort.clear();
 
 myString = serialPort.readStringUntil(';');
 myString = null;
}

public void draw() {
  background(0,0,0);
  textFont(font);
  fill(128);
  
  while (serialPort.available() > 0) {
    myString = serialPort.readStringUntil(';');
    if (myString != null){
       myString = myString.substring(0,myString.length()-2);
       println(myString);
       int[] vals = PApplet.parseInt(myString.split(","));
       
    }
  } 
}

  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--full-screen", "--bgcolor=#666666", "--stop-color=#cccccc", "serialReader" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
