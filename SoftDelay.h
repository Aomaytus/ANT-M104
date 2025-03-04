int updateValue(int input) {
  int avg = input;  // ใช้ค่า input เป็นค่าเริ่มต้น
  if (avg < input && avg < Aver_Stop) {
    avg += Stop_Low;
  } else if (input <= 0) {
    avg = 0;
  } else {
    avg = input;
  }
  return avg;  // คืนค่าผลลัพธ์
}

void AverMode(int A, int B) {
  Av1 = updateValue(A);
  Av2 = updateValue(B);  // แก้ไขให้ถูกต้อง
  MotorPwm(Av1, Av2);
}
