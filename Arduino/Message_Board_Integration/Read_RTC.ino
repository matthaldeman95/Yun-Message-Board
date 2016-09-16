void writeTime(){
  matrix0.clear();
  matrix0.drawColon(true);
  int hour=Clock.getHour(h12, PM);
  float htens = (hour)/10;
  if(htens < 1){
     matrix0.writeDigitNum(0x01, hour);
     matrix0.writeDisplay();
  }
  else{
    matrix0.writeDigitNum(0x00, 1);
    int newhour = (hour - 10);
    matrix0.writeDigitNum(0x01, newhour);
    matrix0.writeDisplay();
  }
  
  int minute=Clock.getMinute();
  float mtens = minute/10;
  if(mtens < 1){
    matrix0.writeDigitNum(0x03, 0);
    matrix0.writeDigitNum(0x04, minute);
    matrix0.writeDisplay();
  }
  else{
    float mins = minute - (mtens*10);
    matrix0.writeDigitNum(0x03, mtens);
    matrix0.writeDigitNum(0x04, mins);
    matrix0.writeDisplay();
  }
}

  
void writeDate(){
  matrix1.clear();
  float month = Clock.getMonth(Century);
  float montens = month/10;
  if(montens < 1){
    matrix1.writeDigitNum(0x00, month);
    matrix1.writeDisplay();
  }
  else{
    float months = month - (montens*10);
    matrix1.writeDigitNum(0x00, montens);
    matrix1.writeDigitNum(0x01, months);
    matrix1.writeDisplay();
  }
  
  int date = Clock.getDate();
  float dtens = date/10;
  if(dtens < 1){
    matrix1.writeDigitNum(0x03, date);
    matrix1.writeDisplay();
  }
  else{
    float dates = date - (dtens*10);
    matrix1.writeDigitNum(0x03, dtens);
    matrix1.writeDigitNum(0x04, dates);
    matrix1.writeDisplay();
  }
}


