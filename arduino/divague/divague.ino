#define pinLed 10
#define tempResN A2
#define tempResP A0
#define luzRes A1 

void setup() {
  // Led:
  pinMode(pinLed,OUTPUT);

  // Debug
  Serial.begin(9600);
}

void loop() {
  delay(20);

  // Temperaturas:
  Serial.println("Resistencia positiva:");
  int res = analogRead(tempResP);
  Serial.println((4.88*res-400)/19.5-10.0);

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
}
