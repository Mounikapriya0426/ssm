int LEDpin = D6;

void setup() {
  Serial.begin(9600);
  analogWrite(LEDpin, 1024);
  
 }

void loop() {
  int dutycycle = analogRead(A0);
  if(dutycycle > 1023) dutycycle = 1023;
  Serial.print("Duty Cycle: ");
  Serial.println(dutycycle);
  analogWrite(LEDpin, dutycycle);
  delay(100);

}
