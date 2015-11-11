#include <stdbool.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

unsigned short r1 = 2047;
unsigned short r2 = 2047;

#define B11 0x01
#define B10 0x02
#define B9 0x04
#define B8 0x08
#define B7 0x010
#define B6 0x020
#define B5 0x040
#define B4 0x080
#define B3 0x0100
#define B2 0x0200
#define B1 0x0400

unsigned short G1() {
  r1 >>= 1;
  r1 |= (((r1&B4) >> 7) ^ (r1&B11) ? B1 : 0);
  return r1&B11;
}

unsigned short G2() {
  r2 >>= 1;
  r2 |= (((r2 & B3) >> 8)  ^ ((r2 & B4) >> 7) ^ ((r2 & B7) >> 4) ^ ((r2 & B9) >> 2) ^ ((r2 & B10) >> 1) ^ (r2 & B11) ? B1 : 0);
  return ((((r2&B4) >> 5)) ^ (r2&B9)) >> 2;
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 4);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //lcd.setCursor(0,0);
  //lcd.print(G1()^G2());
  digitalWrite(9, G1()^G2());
  //delay(500);
}
