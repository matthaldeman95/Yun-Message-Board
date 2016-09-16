#include <Wire.h> 

#include <Process.h>

void setup() {
  Bridge.begin();
  Serial.begin(9600);

}

void loop() {
  String data = DCULast();
  Serial.println(data);
}

String DCULast(){
  String DCULast = "";
  Serial.println("DCULast process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/getDCULast.py");
  while (p.available()){
    DCULast = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println("DCULast process complete");
  return DCULast;
}

