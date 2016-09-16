const int LED = 20;


void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

}

void loop() {
  String data = "";
  if(Serial.available()){
    data = Serial.readStringUntil('\n');
    if(data == "OFF"){
      digitalWrite(LED, LOW);
      Serial.println(data);
    }
    else if(data == "ON"){
      digitalWrite(LED, HIGH);
      Serial.println(data);
    }
    
  }
  
}
