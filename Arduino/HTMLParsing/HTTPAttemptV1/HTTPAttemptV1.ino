#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>
#include <TextFinder.h>
HttpClient client;


String weather;
String CC;

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  weather = "";
  client.get("http://weather.yahooapis.com/forecastrss?w=2425834");
  while (client.available()){
    char c = client.read();
    weather += c;
  }
  TextFinder finder(weather);
  //Serial.println(weather);
  if(finder.find("temp=")){
    int temperature = finder.getValue();
    Serial.print("Temp C:  ");
    Serial.println(temperature);
  }
  else{Serial.println("No connection");}
  delay(10000);
}
