#include <Process.h>

String string;

void setup() {
  Bridge.begin();
  Serial.begin(9600);

}

void loop() {
  string = getSteelers();
  Serial.println(string);

}

String getSteelers(){
  String Steelers = "";
  Serial.println("Steelers process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/getSteelers.py");
  while (p.available()){
    Steelers = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println("DSteelers process complete");
  Serial.println(Steelers);
  Serial.println("End process");
  return Steelers;

}
