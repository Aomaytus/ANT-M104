// int16_t sw_stop = 0;
void ReadAnalongModeC() {
  int A = analogRead(A_read);
  A = map(A, 30, 1000, 1, pwm_defalue);
  if (A >= pwm_defalue) { A = pwm_defalue; }
  if (A < 0) { A = 0; }
  bool B = digitalRead(B_read);
  if (B == 0) {
    AverMode(A, 0);
  } else if (B == 1) {
    AverMode(0, A);
  }
  // Serial.println(" A " + String(A) + " B " + String(B));
}
void ReadAnalongModeD() {
  int A = analogRead(A_read);
  bool B = digitalRead(B_read);
  // Serial.println(" A " + String(A) + " B " + String(B));
  // AverMode(AnalogA, AnalogNC);
}