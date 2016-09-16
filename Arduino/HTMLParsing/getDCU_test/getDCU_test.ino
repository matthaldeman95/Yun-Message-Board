//Initialize I2C comm
#include <Wire.h> 
#include <Process.h>

void setup() {
  Bridge.begin();

}

void loop() {
  String data;
  data = getDCU();
  Serial.println(data);

}

String getDCU(){
  String DCU = "";
  Serial.println(F("DCU process initializing..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getDCU.py"));
  while (p.available()){
    DCU = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("DCU process complete"));
  Serial.println(DCU);
  return DCU;

}
