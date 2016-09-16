void getDCULast(){
  Serial.println("DCULast process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/getDCULast.py");
  while (p.running());{
    Serial.println("DCULast process executing...");
  }
  while (p.available()){
    result = p.readString();
    Serial.println(result);
    p.exitValue();
  }
  p.close();
  result = "";
  Serial.println("DCULast process complete");
}

void getDCUNext(){
  Serial.println("DCUNext process initializing...");
  Process p;
  p.runShellCommand("/mnt/sda1/getDCUNext.py");
  while (p.running());{
    Serial.println("DCUNext process executing...");
  }
  while (p.available()){
    result = p.readString();
    Serial.println(result);
    p.exitValue();
  }
  p.close();
  result = "";
  Serial.println("DCUNext process complete");
}



