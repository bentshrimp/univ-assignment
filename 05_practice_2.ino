void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7,0);
  delay(1000);
  
  for (int i = 0; i < 5; i++){
    Serial.println("blink");
    digitalWrite(7,1);
    delay(100);
    digitalWrite(7,0);
    delay(100);
  }
}

void loop() {
  digitalWrite(7,1);
  while(1){};
}
