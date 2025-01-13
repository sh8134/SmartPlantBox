#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //0x27 or 0x3F

//clear
  
  int AA = 6;
  int AB = 7;
  int AC = 3;

  //clear
  //int previousButtonState = HIGH;
  int moistureThreshold = 20;
  unsigned long buttonPressTime;
  unsigned long buttonReleasedTime;
  int displayOn = 0;
  int previousDisplay = 0;
  //bool pumpOn = false;
  //clear

void setup() {
  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);

  //clear
  pinMode(AC, INPUT_PULLUP);
  pinMode(A0, INPUT);
  //clear
  lcd.init();
  lcd.backlight();
  //pinMode(buttonPin, INPUT);
}

//clear

void loop() {
  // LCD initial print-out
  int data = analogRead(A0);
  //int percent = map(data, 1023, 210, 0, 100); 
   int percent = map(data, 0, 800, 0, 100);

   //clear


  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(percent);
  lcd.print("%");

  //clear

  //lcd.setCursor(0, 1);
  //lcd.print("Threshold: ");
  //lcd.print(moistureThreshold);
  //lcd.print("%");
  //delay(500);

//clear


  //Switch
 int buttonState = digitalRead(AC);
  if (buttonState == LOW && buttonPressTime == 0) {
    buttonPressTime = millis();
  }

  if (buttonState == HIGH && buttonPressTime != 0) {
    buttonReleasedTime = millis() - buttonPressTime;
    buttonPressTime = 0;
    if(buttonReleasedTime > 1000 && buttonReleasedTime < 3000){
      displayOn = 2;
      moistureThreshold = 20;
    } else if (buttonReleasedTime > 3000 && buttonReleasedTime < 5000){
      displayOn = 3;
       moistureThreshold = 40;
    } else if (buttonReleasedTime > 5000 && buttonReleasedTime < 7000){
      displayOn = 4;
       moistureThreshold = 80;  
    } else if(buttonReleasedTime > 10000 && buttonReleasedTime < 20000){
      displayOn = 5;
    }
  }


//clear 

  if (displayOn != previousDisplay) {
    
    if (displayOn == 2) {
      lcd.setCursor(0, 1);
      lcd.print("plant type: A"); //A
    } else if (displayOn == 3) {
      lcd.setCursor(0, 1);
      lcd.print("plant type: B");
    } else if (displayOn == 4) {
      lcd.setCursor(0, 1);
      lcd.print("plant type: C");
    } else if(displayOn == 5){
      displayOn = 0;
    } 

    //여기 출력값 넣어햘 수
    previousDisplay = displayOn;
  
  }


//clear


  //기존코드임 ㅇㅇ
 // int buttonState = digitalRead(AC);

  //if (buttonState == LOW && previousButtonState == HIGH) {
    //if (moistureThreshold == 20) {
      //moistureThreshold = 50;
    //} else {
     // moistureThreshold = 20;
    //}
  //}

  //previousButtonState = buttonState; 



//Water pump
  if (percent < moistureThreshold){
  digitalWrite(AA, HIGH);
  digitalWrite(AB, LOW);
  delay(300);
  digitalWrite(AA, LOW);
  digitalWrite(AB, LOW);
  delay(300);
  }
  else {
  digitalWrite(AA, LOW);
  digitalWrite(AB, LOW);
} 

}