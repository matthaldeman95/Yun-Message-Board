/*

void getTemp(){
  temperature = "";
  Serial.println("Temp process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/gettemp.py");
  while (p.running());{
    Serial.println("Temp process executing...");
  }
  while (p.available()){
    temperature = p.readString();
    Serial.println(temperature);
    p.exitValue();
  }
  p.close();
  Serial.println("Temp process complete");
}


  */
