int switchPin1 = D3;
int switchPin2 = D4;
int LedPin1 = D0; //d0
int LedPin2 = D2;
int switchValue;
int switchValue1;

void setup() {
  pinMode(LedPin1, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);

}

void loop() {
  switchValue = digitalRead(switchPin1);
  switchValue1 = digitalRead(switchPin2);
  digitalWrite(LedPin1, switchValue);
  digitalWrite(LedPin2, !switchValue1);

}
