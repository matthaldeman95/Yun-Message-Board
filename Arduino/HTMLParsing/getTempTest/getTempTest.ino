#include <Process.h>

String temperature;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Starting bridge...\n");
  
  
}

void loop() {
  temperature = "";
  getTemp();
  Serial.print("String recovered: ");
  Serial.println(temperature);
}


  


