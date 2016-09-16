#include <Process.h>

String result = "";

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Starting bridge...\n");
  
  
}

void loop() {
  gettemp();
  getcond();
  getforecast();
  getDCULast();
  getDCUNext();
  
  delay(10000);
}
