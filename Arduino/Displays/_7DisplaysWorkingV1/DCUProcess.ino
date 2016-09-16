void getDCULast(){
  String result;
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
  Serial.println("DCULast process complete");
  
  
  int strl = result.length();
  int adjlength = (strl*8 + 16);
  //Serial.println(adjlength); 
  
  matrix2.clear();  matrix3.clear();  matrix4.clear();  matrix5.clear();
  matrix2.setTextSize(1);  matrix3.setTextSize(1);  matrix4.setTextSize(1);  matrix5.setTextSize(1);  
  matrix2.setRotation(3);  matrix3.setRotation(3);  matrix4.setRotation(3);  matrix5.setRotation(3); 
  matrix2.setTextWrap(false); matrix3.setTextWrap(false);  matrix4.setTextWrap(false);  matrix5.setTextWrap(false);
  for(int i = 0; i>=-adjlength; i--){
          matrix2.clear(); matrix3.clear();   matrix4.clear();  matrix5.clear();
          matrix2.setCursor(i+24,0);  matrix3.setCursor(i+16,0);  matrix4.setCursor(i+8,0);  matrix5.setCursor(i,0);
          matrix5.print(result);  matrix4.print(result);  matrix3.print(result);  matrix2.print(result);
          matrix2.writeDisplay();  matrix3.writeDisplay();  matrix4.writeDisplay();  matrix5.writeDisplay();
          delay(100);
      }
  
  
  
  
  
  
}
