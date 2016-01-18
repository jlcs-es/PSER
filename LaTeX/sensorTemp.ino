int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println((5000.*sensorValue/1024.-400.)/19.5);
  //Serial.println((4.9*sensorValue-400)/19.5);
  Serial.println();
  delay(1000);
}
