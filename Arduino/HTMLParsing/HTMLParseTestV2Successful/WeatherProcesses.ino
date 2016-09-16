void gettemp(){
  Serial.println("Temp process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/gettemp.py");
  while (p.running());{
    Serial.println("Temp process executing...");
  }
  while (p.available()){
    result = p.readString();
    Serial.println(result);
    p.exitValue();
  }
  p.close();
  result = "";
  Serial.println("Temp process complete");
}

void getcond(){
  Serial.println("Cond process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/getcond.py");
  while (p.running());{
    Serial.println("Cond process executing...");
  }
  while (p.available()){
    result = p.readString();
    Serial.println(result);
    p.exitValue();
  }
  p.close();
  result = "";
  Serial.println("Cond process complete");
  
}

void getforecast(){
  Serial.println("FC process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/getforecast.py");
  while (p.running());{
    Serial.println("FC process executing...");
  }
  while (p.available()){
    result = p.readString();
    Serial.println(result);
    p.exitValue();
  }
  p.close();
  result = "";
  Serial.println("FC process complete");
}




