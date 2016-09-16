#include <Bridge.h>
#include <Temboo.h>
#define TEMBOO_ACCOUNT "haldeman3"  // Your Temboo account name 
#define TEMBOO_APP_KEY_NAME "myFirstApp"  // Your Temboo app key name
#define TEMBOO_APP_KEY "977a1e79821646f3beec98c36f0e41e1"  // Your Temboo app key

String ADDRESS_FOR_FORECAST = "624 17th Street, Huntginton WV";

void setup() {
  Serial.begin(9600);
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop() {
  Serial.println("Running GetWeatherByAddress...");
  
  TembooChoreo Temp;
  
  Temp.begin();
  Temp.setAccountName(TEMBOO_ACCOUNT);
  Temp.setAppKeyName(TEMBOO_APP_KEY_NAME);
  Temp.setAppKey(TEMBOO_APP_KEY);
  
  Temp.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");
  
  //Input address
  Temp.addInput("Address", ADDRESS_FOR_FORECAST);
  
  //Output filter
  //Temp.addOutputFilter("temperature", "/rss/channel/item/yweather:condition/@temp","Response");
  //Temp.addOutputFilter("currentcondition", "rss/channel/item/yweather:condition/@text", "Response");
  //Temp.addOutputFilter("forecasttext", "rss.channel/item/description", "Response");
  
  //Run choreo
  Temp.run();
  while(Temp.available()){
    char c = Temp.read();
    Serial.print(c);
    /*
    String label = Temp.readStringUntil('\x1F');
    label.trim();
    String data = Temp.readStringUntil('\x1E');
    data.trim();
    
    if(label == "currentcondition"){
      String CC = data;
      Serial.print("Current condition:");
      Serial.println(CC);
    }
    else if(label == "temperature"){
      String temperature = data;
      Serial.print("Temperature: ");
      Serial.println(data);
    }
    else if(label = "HTTP_CODE"){
      if(data != "200"){
        Serial.print("Error");
      }
    }*/
    
  }
  Temp.close();
  delay(5000);
}
