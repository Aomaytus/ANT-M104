void AverMode(int A, int B) {
  if (Av1 < A && Av1 < max_pwm_ir / Aver_Stop) {
    Av1 += 1;
  } else {
    Av1 = A;
  }
  if (Av2 < B && Av2 < max_pwm_ir / Aver_Stop) {
    Av2 += 1;
  } else {
    Av2 = B;
  }
  //  Serial.print(" A " + String(Av1) + " B " + String( Av2 ));
  MotorPwm(Av1, Av2);
}
