#include <stdbool.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

bool r1[10] = {1,1,1,1,1,1,1,1,1,1};
bool r2[10] = {1,1,1,1,1,1,1,1,1,1};

void shift(bool * r) {
  for (int i = 9; i >= 1; i--)
    r[i] = r[i-1];
}

bool G1() {
  bool r = r1[9];
  bool l = (r1[9] ^ r1[2])&1;
  shift(r1);
  r1[0] = l;
  return r;
}

bool G2() {
  bool r = (r2[2] ^ r2[7])&1;
  bool l = (r2[9] ^ r2[8] ^ r2[7] ^ r2[5] ^ r2[2] ^ r2[1])&1;
  shift(r2);
  r2[0] = l;
  return r;
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
}
