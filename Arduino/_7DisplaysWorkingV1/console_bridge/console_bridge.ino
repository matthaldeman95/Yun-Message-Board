

#include <Console.h>
#include <Wire.h>

String name;
String data;

//Initialize Adafruit LED Backpacks
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix3 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix4 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix6 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix7 = Adafruit_8x8matrix();

void setup() {
  // Initialize Console and wait for port to open:
  Bridge.begin();
  Console.begin();

  // Wait for Console port to connect
  while (!Console);

  Console.println("Type message here: ");
  
  matrix0.begin(0x70);  Serial.print(F("0..."));
  matrix1.begin(0x71);  Serial.print(F("1..."));
  matrix2.begin(0x72);  Serial.print(F("2..."));
  matrix3.begin(0x73);  Serial.print(F("3..."));
  matrix4.begin(0x74);  Serial.print(F("4..."));
  matrix6.begin(0x76);  Serial.print(F("6..."));
  matrix7.begin(0x77);  Serial.print(F("7... Done"));
  
}


void loop() {
  if (Console.available() > 0) {
    char c = Console.read(); // read the next char received
    if (c == '\n') {
      
      //print text with the name received
      Console.println();
      Console.println("Type new message here:  ");
        
        int strl = name.length();
      int adjlength = (strl * 8 + 16);
      
      matrix2.clear();  matrix3.clear();  matrix4.clear();  matrix6.clear();
      matrix2.setTextSize(1);  matrix3.setTextSize(1);  matrix4.setTextSize(1);  matrix6.setTextSize(1);
      matrix2.setRotation(3);  matrix3.setRotation(3);  matrix4.setRotation(3);  matrix6.setRotation(3);
      matrix2.setTextWrap(false); matrix3.setTextWrap(false);  matrix4.setTextWrap(false);  matrix6.setTextWrap(false);
      for (int n = 0; n >= -adjlength; n--) {
        matrix2.clear(); matrix3.clear();   matrix4.clear();  matrix6.clear();
        matrix2.setCursor(n + 24, 0);  matrix3.setCursor(n + 16, 0);  matrix4.setCursor(n + 8, 0);  matrix6.setCursor(n, 0);
        matrix6.print(name);  matrix4.print(name);  matrix3.print(name);  matrix2.print(name);
        matrix2.writeDisplay();  matrix3.writeDisplay();  matrix4.writeDisplay();  matrix6.writeDisplay();
        delay(30);
        
        
      }
      name = "";
      
      
      
  
    }
    else {  	 // if the buffer is empty Cosole.read() returns -1
      name += c; // append the read char from Console to the name string
    }
  } 
  
  
  
}
