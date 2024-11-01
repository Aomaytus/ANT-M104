
const int min_pwm = 1150;
const int max_pwm = 1650;
void ReadPwmModeA() {
  int A1 = 0;
  int A2 = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= pwmReadingInterval) {
    previousMillis = currentMillis;

    A2 = pulseIn(B_read, HIGH, pwmReadingDuration);

    A1 = pulseIn(A_read, HIGH, pwmReadingDuration);
    // Serial.print(" A " + String(A1) + " B " + String(A2));
    A2 = map(A2, 0, 190, 0, max_pwm_ir);
    A1 = map(A1, 0, 190, 0, max_pwm_ir);
    if (A2 < 0) { A2 = 0; }

    if (A1 >= max_pwm_ir) { A1 = max_pwm_ir; }
    if (A2 >= max_pwm_ir) { A2 = max_pwm_ir; }
 Serial.print(" A " + String(A1) + " B " + String(A2));

    AverMode(A1, A2);
  }
}
void ReadPwmModeB() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= pwmReadingInterval) {
    previousMillis = currentMillis;
    int A1 = pulseIn(B_read, HIGH, pwmReadingDuration);
    A1 = map(A1, 0, 1023, 0, max_pwm_ir);
    int pwmNC = digitalRead(A2);
  }
}
