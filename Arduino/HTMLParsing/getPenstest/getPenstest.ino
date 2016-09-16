//Initialize I2C comm
#include <Wire.h> 
#include <Process.h>

void setup() {
  Bridge.begin();
  Serial.begin(57600);
}

void loop() {
  String data;
  data = getPens();
  Serial.println(data);

  }

String getPens(){
  String Pens = "";
  Serial.println(F("Pens process initializing..."));
  Process p;
  p.runShellCommand(F("/mnt/sda1/getPens.py"));
  while (p.available()){
    Pens = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println(F("Pens process complete"));
  Serial.println(Pens);
  return Pens;

}
