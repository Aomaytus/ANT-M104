
// ฟังก์ชัน ReadPwmModeB สำหรับ mode = 0
void PWM_power(int mode, int out_a1, int out_a2, int out_b1, int out_b2) {
  // กำหนดเงื่อนไขสำหรับ mode ที่เลือก (ในที่นี้ mode == 0)
  if (mode == 0) {
    Serial.print(" mode 0 ");
    if (out_a1 > 1 && out_a2 < 1) {
      // กรณีมีสัญญาณเฉพาะจาก out_a1 (อาจหมายถึงโหมด back)
      AverMode(out_a1 - out_b2, 0);
    } else if (out_a1 < 1 && out_a2 > 1) {
      // กรณีมีสัญญาณเฉพาะจาก out_a2 (อาจหมายถึงโหมด front)
      AverMode(0, out_a2 - out_b2);
    } else if (out_b1 > 1 && out_b2 < 1) {
      // กรณีไม่มีสัญญาณจาก A แต่มีสัญญาณจาก B (โหมด lift)
      AverMode(0, out_b1);
    } else if (out_b2 > 1 && out_b1 < 1) {
      // กรณีไม่มีสัญญาณจาก A แต่มีสัญญาณจาก B (โหมด lift)
      AverMode(out_b2, 0);
    } else {
      // ไม่มีสัญญาณใด ๆ รับมา ให้หยุดมอเตอร์
      AverMode(0, 0);
    }
  } else if (mode == 1) {
    Serial.print(" mode 1 ");
    if (out_a1 > 1 && out_a2 < 1) {
      // กรณีมีสัญญาณเฉพาะจาก out_a1 (อาจหมายถึงโหมด back)
      AverMode(out_a1 - out_b1, 0);
    } else if (out_a1 < 1 && out_a2 > 1) {
      // กรณีมีสัญญาณเฉพาะจาก out_a2 (อาจหมายถึงโหมด front)
      AverMode(0, out_a2 - out_b1);
    } else if (out_b1 > 1 && out_b2 < 1) {
      // กรณีไม่มีสัญญาณจาก A แต่มีสัญญาณจาก B (โหมด lift)
      AverMode(out_b1, 0);
    } else if (out_b2 > 1 && out_b1 < 1) {
      AverMode(0, out_b2);
    } else {
      // ไม่มีสัญญาณใด ๆ รับมา ให้หยุดมอเตอร์
      AverMode(0, 0);
    }
  }
}
void check(int mode, int out_a1, int out_a2, int out_b1, int out_b2) {

  PWM_power(mode, out_a1, out_a2, out_b1, out_b2);
  // Serial.print(" ] | out_a1: ");
  // Serial.print(out_a1);
  // Serial.print(" | out_a2: ");
  // Serial.print(out_a2);
  // Serial.print(" | out_b1: ");
  // Serial.print(out_b1);
  // Serial.print(" | out_b2: ");
  // Serial.println(out_b2);
}

const int max_ppw = 1900;
const int min_ppw = 900;
const int min_start_ppw = 1350;
const int max_start_ppw = 1550;
// int lastPWM[2] = { 0, 0 };  // 0 = ช่อง A, 1 = ช่อง B

// กำหนดตัวแปร Global ไว้ด้านบนสุด
const int TOTAL_CHANNELS = 2; // แก้เลขตามจำนวนช่องของคุณ
unsigned long lastRecvTime[TOTAL_CHANNELS]; // เก็บเวลาล่าสุดที่ได้รับค่าถูกต้อง
int lastPWM[TOTAL_CHANNELS]; // เก็บค่า PWM ล่าสุด

// กำหนดค่า Deadband (ช่วงที่ยอมให้ค่าแกว่งได้โดยไม่เปลี่ยน output)
// ค่า 4-5 microseconds มักจะเพียงพอสำหรับลดอาการสั่นของเซอร์โว
const int DEADBAND = 4; 

int validatePWM(int v, int channelIndex) {
  unsigned long currentTime = millis();

  // --- ส่วนที่ 1: ระบบความปลอดภัย (Failsafe) ---
  // ถ้าเวลาผ่านไปเกิน 3000ms (3 วินาที) นับจากครั้งสุดท้ายที่ได้ค่าถูกต้อง
  if (currentTime - lastRecvTime[channelIndex] > 3000) {
    lastPWM[channelIndex] = 0; // รีเซ็ตค่าเป็น 0
    return 0; // ส่งคืน 0 ทันที
  }

  // --- ส่วนที่ 2: กรองค่าผิดปกติ (Range Check) ---
  // ถ้าค่า PWM หลุดช่วง (เช่น สายหลุด หรือสัญญาณรบกวน)
  if (v < 800 || v > 2200) {
    // คืนค่าเดิมที่เคยถูกต้องล่าสุดไปก่อน
    // (แต่ไม่อัปเดต lastRecvTime ทำให้เวลาไหลไปเรื่อยๆ จนเข้าเงื่อนไข Failsafe)
    return lastPWM[channelIndex];
  }

  // --- ส่วนที่ 3: ถ้าค่าถูกต้อง (Valid Signal) ---
  lastRecvTime[channelIndex] = currentTime; // **สำคัญ** รีเซ็ตตัวจับเวลา Failsafe

  // --- ส่วนที่ 4: ลดการสั่น (Deadband / Jitter Filter) ---
  // ถ้าค่าใหม่ต่างจากค่าเดิม น้อยกว่า Deadband ให้ใช้ค่าเดิม (ถือว่าเป็น Noise)
  if (abs(v - lastPWM[channelIndex]) < DEADBAND) {
    return lastPWM[channelIndex];
  }

  // --- ส่วนที่ 5: อัปเดตค่าใหม่ ---
  // ถ้าผ่านทุกเงื่อนไข ก็เก็บค่าใหม่และใช้งานได้เลย
  lastPWM[channelIndex] = v;
  return v;
}
void ReadPwmModeB(int mode) {
  int A1 = 0, A2 = 0;
  int out_a1 = 0, out_a2 = 0, out_b1 = 0, out_b2 = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= pwmReadingInterval) {
    previousMillis = currentMillis;

    // ===== อ่าน PWM =====
    A1 = validatePWM(pulseIn(A_read, HIGH, pwmReadingDuration), 0);
    A2 = validatePWM(pulseIn(B_read, HIGH, pwmReadingDuration), 1);

    // ===== ประมวลผล A1 =====
    if (A1 > min_ppw && A1 <= max_ppw + 200) {
      out_a1 = map(A1, min_start_ppw, min_ppw + 200, 0, pwm_defalue);
      out_a1 = constrain(out_a1, 0, pwm_defalue);

      out_a2 = map(A1, max_start_ppw, max_ppw, 0, pwm_defalue);
      out_a2 = constrain(out_a2, 0, pwm_defalue);
    } else {
      out_a1 = 0;
      out_a2 = 0;
    }

    // ===== ประมวลผล A2 =====
    if (A2 > min_ppw && A2 <= max_ppw + 200) {
      out_b1 = map(A2, min_start_ppw, min_ppw + 200, 0, pwm_defalue);
      out_b1 = constrain(out_b1, 0, pwm_defalue);

      out_b2 = map(A2, max_start_ppw, max_ppw, 0, pwm_defalue);
      out_b2 = constrain(out_b2, 0, pwm_defalue);
    } else {
      out_b1 = 0;
      out_b2 = 0;
    }

    // ===== Debug Print =====
    Serial.print(" [ A1: ");
    Serial.print(A1);
    Serial.print(" | A2: ");
    Serial.print(A2);

    check(mode, out_a1, out_a2, out_b1, out_b2);
  }
}
