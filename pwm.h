
// ฟังก์ชัน ReadPwmModeB สำหรับ mode = 0
void ReadPwmModeB(int mode) {
  int A1 = 0, A2 = 0;
  int out_a1 = 0, out_a2 = 0, out_b1 = 0, out_b2 = 0;
  unsigned long currentMillis = millis();

  // อ่านค่า PWM ตามช่วงเวลาที่กำหนด
  if (currentMillis - previousMillis >= pwmReadingInterval) {
    previousMillis = currentMillis;

    // อ่านสัญญาณ PWM จากพินที่กำหนด
    A1 = pulseIn(A_read, HIGH, pwmReadingDuration);
    A2 = pulseIn(B_read, HIGH, pwmReadingDuration);

    // แปลงค่า PWM ให้อยู่ในช่วงที่ต้องการโดยใช้ map()
    // (ค่าใน map() อาจต้องปรับตามลักษณะของสัญญาณจริง)
    out_a1 = map(A1, 1390, 999, 0, pwm_defalue);
    out_a2 = map(A1, 1550, 1950, 0, pwm_defalue);
    out_b1 = map(A2, 1390, 999, 0, pwm_defalue);
    out_b2 = map(A2, 1550, 1950, 0, pwm_defalue);

    // จำกัดค่าที่ได้ให้อยู่ในช่วงที่ต้องการ
    if (out_a1 < 0) out_a1 = 0;
    if (out_a1 >= max_pwm_ir) out_a1 = max_pwm_ir;
    if (out_a2 < 0) out_a2 = 0;
    if (out_a2 >= max_pwm_ir) out_a2 = max_pwm_ir;
    if (out_b1 < 0) out_b1 = 0;
    if (out_b1 >= max_pwm_ir) out_b1 = max_pwm_ir;
    if (out_b2 < 0) out_b2 = 0;
    if (out_b2 >= max_pwm_ir) out_b2 = max_pwm_ir;

    // กำหนดเงื่อนไขสำหรับ mode ที่เลือก (ในที่นี้ mode == 0)
    if (mode == 0) {
      if (out_a1 > 1 && out_a2 < 1) {
        // กรณีมีสัญญาณเฉพาะจาก out_a1 (อาจหมายถึงโหมด back)
        AverMode(out_a1 - out_b1, 0);
      } else if (out_a1 < 1 && out_a2 > 1) {
        // กรณีมีสัญญาณเฉพาะจาก out_a2 (อาจหมายถึงโหมด front)
        AverMode(0, out_a2 - out_b1);
      } else if (out_a1 < 1 && out_a2 < 1 && out_b1 > 1 && out_b2 < 1) {
        // กรณีไม่มีสัญญาณจาก A แต่มีสัญญาณจาก B (โหมด lift)
        AverMode(out_b1, 0);
      } else if (out_a1 < 1 && out_a2 < 1 && out_b1 < 1 && out_b2 > 1) {
        AverMode(0, out_b2);
      } else {
        // ไม่มีสัญญาณใด ๆ รับมา ให้หยุดมอเตอร์
        AverMode(0, 0);
      }
    } else if (mode == 1) {
      if (out_a1 > 1 && out_a2 < 1) {
        // กรณีมีสัญญาณเฉพาะจาก out_a1 (อาจหมายถึงโหมด back)
        AverMode(out_a1 - out_b1, 0);
      } else if (out_a1 < 1 && out_a2 > 1) {
        // กรณีมีสัญญาณเฉพาะจาก out_a2 (อาจหมายถึงโหมด front)
        AverMode(0, out_a2 - out_b1);
      } else if (out_a1 < 1 && out_a2 < 1 && out_b1 > 1 && out_b2 < 1) {
        // กรณีไม่มีสัญญาณจาก A แต่มีสัญญาณจาก B (โหมด lift)
        AverMode(0, out_b1);
      } else if (out_a1 < 1 && out_a2 < 1 && out_b1 < 1 && out_b2 > 1) {
        AverMode(out_b2, 0);
      } else {
        // ไม่มีสัญญาณใด ๆ รับมา ให้หยุดมอเตอร์
        AverMode(0, 0);
      }
    }
    // ปริ้นทุกค่าในบรรทัดเดียวกัน
    Serial.print("A1: ");
    Serial.print(A1);
    Serial.print(" | A2: ");
    Serial.print(A2);
    Serial.print(" | out_a1: ");
    Serial.print(out_a1);
    Serial.print(" | out_a2: ");
    Serial.print(out_a2);
    Serial.print(" | out_b1: ");
    Serial.print(out_b1);
    Serial.print(" | out_b2: ");
    Serial.println(out_b2);
  }
}
