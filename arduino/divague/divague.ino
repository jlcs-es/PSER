#define pinLed 10
#define tempResN A2
#define tempResP A0
#define luzRes A1 
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Led:
  pinMode(pinLed,OUTPUT);

  // Debug
  Serial.begin(9600);

  // LCD
  lcd.begin(16, 2);
}

void loop() {
  delay(20);

  // Temperaturas:
  Serial.println("Resistencia positiva:");
  int res = analogRead(tempResP);
  double temp = (4.88*res-400)/19.5-10.0;
  Serial.println(temp);

  Serial.println("Resistencia negativa:");
  res = analogRead(tempResN);
  Serial.println((1.-res/1024.)*100.-25.);

  // Luz:
  Serial.println("Resistencia de luz:");
  res = analogRead(luzRes);
  Serial.println(128-(unsigned char)(res/4));

  // Led:
  res = res/4 > 127 ? 127 : res/4;
  analogWrite(pinLed,(128-res)*2-1);

  // LCD:
  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.print(temp);
  
}
