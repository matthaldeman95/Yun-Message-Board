#include <Bridge.h>

char D13value[2];

void setup() {
  memset(D13value,0,2);
  pinMode(13, OUTPUT);
  
  Bridge.begin();
  Serial.begin(9600);
}

void loop() {
  Process p;
  p.begin("python");
  p.addParameter("/mnt/sda1/arduino/test.py");
  p.run();
  while (p.available()>0){
    char c = p.read();
    Serial.print(c);
  }
  Serial.flush();
}
