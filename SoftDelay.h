// ฟังก์ชันอัปเดตค่าโดยใช้ pass by reference
void updateValue(int avg, int input) {
  if (avg < input && avg < Aver_Stop) {
    avg += Stop_Low;
  } else if (input <= 0) {
    avg = 0;
  } else {
    avg = input;
  }
}

void AverMode(int A, int B) {
  updateValue(Av1, A);
  updateValue(Av2, B);
  // Serial.print(" A " + String(Av1) + " B " + String(Av2)+" Aver_Stop : "+String(Aver_Stop)+" " );
  MotorPwm(Av1, Av2);
}
