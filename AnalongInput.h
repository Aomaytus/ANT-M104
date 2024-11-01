
void ReadAnalongModeC() {
  int A = analogRead(A1);
  //  if (AnalogA > 900) { AnalogA = 900; }
  int B = analogRead(A0);
  //   if (AnalogNC > 900) { AnalogNC = 900; }
  //  int A = map(AnalogA, 10, 900, 0, max_pwm_ir);
  //  int B = map(AnalogNC, 10, 900, 0, max_pwm_ir);

//  Serial.println(" A " + String(A) + " B " + String(B));
//    AverMode(A, B);
}
void ReadAnalongModeD() {
  int AnalogA = analogRead(A1);
  int AnalogNC = digitalRead(A0);
  AnalogA = map(AnalogA, 0, 1023, 0, 255);
  AverMode(AnalogA, AnalogNC);
}
