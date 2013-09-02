import processing.serial.*;

Serial serialPort;
String myString = null;
PFont font;

void setup() {
 size(500,500);
 println(Serial.list());
 
 font = createFont("Helvetica", 16, true); // Helvetica, 16pt font, AA on
 
 serialPort  = new Serial(this, Serial.list()[0], 9600);
 serialPort.clear();
 
 myString = serialPort.readStringUntil(';');
 myString = null;
}

void draw() {
  background(0,0,0);
  textFont(font);
  fill(128);
  
  while (serialPort.available() > 0) {
    myString = serialPort.readStringUntil(';');
    if (myString != null){
       myString = myString.substring(0,myString.length()-2);
       println(myString);
       int[] vals = int(myString.split(","));
       
    }
  } 
}

