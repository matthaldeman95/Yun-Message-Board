/*
  YahooWeather
  
  This example code is in the public domain.
*/

#include <Bridge.h>
#include <Temboo.h>
#define TEMBOO_ACCOUNT "haldeman3"  // Your Temboo account name 
#define TEMBOO_APP_KEY_NAME "myFirstApp"  // Your Temboo app key name
#define TEMBOO_APP_KEY "977a1e79821646f3beec98c36f0e41e1"  // Your Temboo app key

// the address for which a weather forecast will be retrieved
String ADDRESS_FOR_FORECAST = "104 Franklin St., New York NY 10013";

int numRuns = 1;   // execution count, so that this doesn't run forever
int maxRuns = 10;  // max number of times the Yahoo WeatherByAddress Choreo should be run


void setup() {
  Serial.begin(9600);
    
  // for debugging, wait until a serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();

}

void loop()
{
  // while we haven't reached the max number of runs...
  if (numRuns <= maxRuns) {
      
    // print status
    Serial.println("Running GetWeatherByAddress - Run #" + String(numRuns++) + "...");

    // create a TembooChoreo object to send a Choreo request to Temboo
    TembooChoreo GetWeatherByAddressChoreo;
    
    // invoke the Temboo client
    GetWeatherByAddressChoreo.begin();

    // add your temboo account info
    GetWeatherByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetWeatherByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetWeatherByAddressChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // set the name of the choreo we want to run
    GetWeatherByAddressChoreo.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");
    
    // set choreo inputs; in this case, the address for which to retrieve weather data
    // the Temboo client provides standardized calls to 100+ cloud APIs
    GetWeatherByAddressChoreo.addInput("Address", ADDRESS_FOR_FORECAST);

    
    // add an output filter to extract the current temperature
    GetWeatherByAddressChoreo.addOutputFilter("temperature", "/rss/channel/item/yweather:condition/@temp", "Response");

    
    // run the choreo 
    GetWeatherByAddressChoreo.run();
        
    // when the choreo results are available, print them to the serial monitor
    while(GetWeatherByAddressChoreo.available()) {
          
      char c = GetWeatherByAddressChoreo.read();    
      Serial.print(c);
    }
    GetWeatherByAddressChoreo.close();
  }

  Serial.println("Waiting...");
  Serial.println("");
  delay(30000); // wait 30 seconds between GetWeatherByAddress calls
}
