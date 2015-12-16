void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int oldres = 0;

void loop() {
  // put your main code here, to run repeatedly:
  int res = analogRead(A0);
  if (oldres > res)
    Serial.println("decrece");
  else
    Serial.println("crece");
  oldres = res;
  delay(50);
}
