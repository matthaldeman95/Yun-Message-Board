/*

void getDCULast(){
  Serial.println("DCULast process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/getDCULast.py");
  while (p.running());{
    Serial.println("DCULast process executing...");
  }
  while (p.available()){
    String result = p.readString();
    Serial.println(result);
    p.exitValue();
  }
  p.close();
  Serial.println("DCULast process complete");
  
  
  
  
  
  
  
  
  
}

*/
