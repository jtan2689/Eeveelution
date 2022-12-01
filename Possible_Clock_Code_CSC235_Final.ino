//credit to https://create.arduino.cc/projecthub/plouc68000/simplest-uno-digital-clock-ever-4613aa

#include "LiquidCrystal.h"

//digital pins 2-7
int rwPin = 2;
int ePin = 3;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;
LiquidCrystal lcd(rwPin, ePin, d4, d5, d6, d7);

//contrast
int contPin = 9;
const int contrast = 30;

//initial display
int hour = 12;
int minute = 59;
int second = 45;

//buttons will equal digitalRead of hours and minutes
int but1;
int but2;

//pins for buttons
int hourBut = 0;
int minBut = 1;

// Backlight Time Out 
const int light = 150;
int blTo = light;
int bl = 10;
const int backlight = 120;

static uint32_t lastTime;
static uint32_t currentTime;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  
  pinMode(hourBut,INPUT_PULLUP); 
  pinMode(minBut,INPUT_PULLUP);
  
  analogWrite(contPin,contrast);
  analogWrite(bl,backlight);
  
  currentTime = millis();

  lcd.print("0");
    lcd.print(hour);
    lcd.print(":");

    lcd.print("0");
    lcd.print(minute);
    lcd.print(":");

    lcd.print("0");
    lcd.print(second);
    
}

void loop() {
  
  // put your main code here, to run repeatedly:
  lcd.begin(16,2);

  lcd.setCursor(0,0);
  lcd.print("Time ");
  if (hour < 10)lcd.print("0");
    lcd.print(hour);
    lcd.print(":");
 

  if (minute < 10) lcd.print("0");
    lcd.print(minute);
    lcd.print(":");
  
  
  if (second < 10) lcd.print("0");
    lcd.print(second); 
  

  lcd.setCursor(0,1);

  for (int i = 0; i < 5; i++) {
    while ((currentTime - lastTime) < 200){
      currentTime = millis();
    }
    lastTime = currentTime;

    but1 = digitalRead(hourBut);
    but2 = digitalRead(minBut);

    blTo--;
    if (blTo == 0) {
      analogWrite(bl, 50);
      blTo++;
    }

    if ( (but1 == 0|but2 == 0) & blTo == 1) {
      blTo = light;
      analogWrite(bl, backlight);

      while (but1 == 0|but2 == 0) {
        but1 = digitalRead(hourBut);
        but2 = digitalRead(minBut);
      }
    }
    else {
      if (but1 == 0) {
        hour++;
        blTo = light;
        analogWrite(bl, backlight);
      }

      if (but2 == 0) {
        second = 0;
        minute++;
        blTo = light;
        analogWrite(bl, backlight); 
      }

      if (second == 60) {
        second = 0;
        minute++;
      }

      if (minute == 60) {
        minute = 0;
        hour++;
      }

      if (hour == 13) {
        hour = 1;
      }

      if (but1 == 0|but2 == 0) {
        lcd.setCursor(0,0);
        lcd.print("Time ");
        if (hour < 10) {
          lcd.print("0");
          lcd.print(hour);
          lcd.print(":");
        }
        
        if (minute < 10) {
          lcd.print("0");
          lcd.print(minute);
          lcd.print(":");
        }
        
        if (second < 10) {
          lcd.print("0");
          lcd.print(second);
        }

        lcd.setCursor(0,1);
        
      }
    }
  }
  
  second++;
  if (second == 60) {
    second == 0;
    minute++;
  }

  if (minute == 60) {
    minute = 0;
    hour++;
  }

  if (hour == 13) {
    hour = 1;
  }
}
