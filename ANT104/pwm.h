const int max_ppw = 1900;
const int min_ppw = 1000;
const int min_start_ppw = 1350;
const int max_start_ppw = 1550;
// ฟังก์ชัน ReadPwmModeB สำหรับ mode = 0
void PWM_power(int mode, int out_a1, int out_a2, int out_b1, int out_b2) {
  // กำหนดเงื่อนไขสำหรับ mode ที่เลือก (ในที่นี้ mode == 0)
  if (mode == 0) {
    if (out_a1 > 1 && out_a2 < 1) {
      // กรณีมีสัญญาณเฉพาะจาก out_a1 (อาจหมายถึงโหมด back)
      AverMode(out_a1 - out_b1, 0);
    } else if (out_a1 < 1 && out_a2 > 1) {
      // กรณีมีสัญญาณเฉพาะจาก out_a2 (อาจหมายถึงโหมด front)
      AverMode(0, out_a2 - out_b2);
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
      AverMode(0, out_a2 - out_b2);
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
void ReadPwmModeB(int mode) {
  int A1 = 0, A2 = 0;
  int out_a1 = 0, out_a2 = 0, out_b1 = 0, out_b2 = 0;
  unsigned long currentMillis = millis();
  // อ่านค่า PWM ตามช่วงเวลาที่กำหนด
  if (currentMillis - previousMillis >= pwmReadingInterval) {
    previousMillis = currentMillis;

    // อ่านสัญญาณ PWM จากพินที่กำหนด
    A1 = pulseIn(A_read, HIGH, pwmReadingDuration);
    if (A1 > min_ppw && A1 <= max_ppw) {
      out_a1 = map(A1, min_start_ppw, min_ppw, 0, pwm_defalue);
      out_a2 = map(A1, max_start_ppw, max_ppw, 0, pwm_defalue);
    } else if (A1 > max_ppw) {
      A1 = max_ppw;
    } else {
      out_a1 = 0;
      out_a2 = 0;
    }
    A2 = pulseIn(B_read, HIGH, pwmReadingDuration);
    if (A2 > min_ppw && A2 <= max_ppw) {
      out_b1 = map(A2, min_start_ppw, min_ppw, 0, pwm_defalue);
      out_b2 = map(A2, max_start_ppw, max_ppw, 0, pwm_defalue);
    } else if (A2 > max_ppw) {
      A2 = max_ppw;
    } else {
      out_b1 = 0;
      out_b2 = 0;
    }
    PWM_power(mode,out_a1,out_a2,out_b1, out_b2);
  }
}
