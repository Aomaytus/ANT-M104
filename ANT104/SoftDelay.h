int RISE_SPEED_defalue = 4;
#define SMOOTHNESS 10
int RISE_SPEED = 3;
float count_av = 1.0;
#define MAX_STEP 65     // จำกัดเฉพาะตอนขึ้น

int updateValueA(int input) {
  static float avg = 0.0;

  int diff = input - avg;

  // ⚠ จำกัด MAX_STEP เฉพาะตอน "เพิ่มขึ้น"
  if (diff > MAX_STEP) {
    input = avg + MAX_STEP;
    diff = input - avg;
  }

  // ถ้าเป็น 0 รีเซตทันที
  if (input == 0) {
    avg = 0;
  }
  else {
    // ช่วงเริ่มค่อย ๆ ขึ้น
    int rise = (avg < 5) ? (RISE_SPEED * 3) : RISE_SPEED;

    if (diff > 0) {
      // ขึ้นแบบช้า
      avg += max(count_av, diff / rise);
    } 
    else if (diff < 0) {
      // ⚡ ลดทันที ไม่ผ่าน MAX_STEP
      avg = input;
    }
  }

  return avg;
}

int updateValueB(int input) {
  static float avg = 0.0;

  int diff = input - avg;

  // ⚠ จำกัดเฉพาะตอนขึ้น
  if (diff > MAX_STEP) {
    input = avg + MAX_STEP;
    diff = input - avg;
  }

  if (input == 0) {
    avg = 0;
  }
  else {
    int rise = (avg < 5) ? (RISE_SPEED * 3) : RISE_SPEED;

    if (diff > 0) {
      avg += max(count_av, diff / rise);
    } 
    else if (diff < 0) {
      // ⚡ ลดทันที ไม่ต้องจำกัด
      avg = input;
    }
  }

  return avg;
}

void AverMode(int A, int B) {
  if (A >= 0 && B >= 0) {
    Av1 = updateValueA(A);
    Av2 = updateValueB(B);
    MotorPwm(Av1, Av2);
  } else {
    MotorPwm(0, 0);
  }
}
