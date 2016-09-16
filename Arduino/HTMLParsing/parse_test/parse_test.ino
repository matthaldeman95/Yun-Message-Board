#include <Bridge.h>
#include <Process.h>

String condition;
String temp;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while(!Serial);
  
}

void loop() {
  getData();
}

void getData(){
  Process p;
  p.begin("python");
  char c = p.runShellCommand("python /mnt/sda1/arduino/test.py");
  Serial.print(c);
}

