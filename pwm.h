#include "MotorControl.h";
void Aver(float A, float B) {
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
  Serial.println("A1 = " + String(Av1) + " A2 = " + String(Av2) + " Aver_Stop = " + String(Aver_Stop) + " Auto_Delay = " + String(Auto_Delay));
  CON(Av1, Av2);  // เรียกใช้ฟังก์ชัน CON ด้วยค่าของ Av1 และ Av2
}
void Read_pwm() {
  int A1 = 0, A2 = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= pwmReadingInterval) {
    previousMillis = currentMillis;
  A2 = pulseIn(B_read, HIGH,pwmReadingDuration);
  A2 = map(A2, 0, 1023, 0, max_pwm_ir);
  A1 = pulseIn(A_read, HIGH,pwmReadingDuration);
  A1 = map(A1, 0, 1023, 0, max_pwm_ir);
  if (A1 >= max_pwm_ir) { A1 = max_pwm_ir; }
  if (A2 >= max_pwm_ir) { A2 = max_pwm_ir; }
  Aver(A1, A2);
  }
}