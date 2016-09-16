//Initialize I2C comm
#include <Wire.h> 
#include <Process.h>

int condnum;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  

}

void loop() {
  condnum = getNumber();
  Serial.print("Number received: ");  
  Serial.println(condnum);

}

int getNumber(){
  String num = "";
  Serial.println("Number process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/getnumber.py");
  while (p.available()){
    num = p.readString();
    p.exitValue();
  }
  p.close();
  Serial.println("Number process complete");
  Serial.println(num);
  condnum = num.toInt();
  return condnum;
  }
