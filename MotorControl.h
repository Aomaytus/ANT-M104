
void Stop_ABS(bool is) {
  static bool hasRun = false;
  if (is && !hasRun) {
    for (int step = 0; step < 10; step++) {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      delay(step + 2);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      delay(step + 2);
      if (Read_Amp <= Max_Amp) {
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        Serial.print("Stop_ABS");
        break;
      }
    }
    hasRun = true;  // ทำครบ
  } else if (!is) {
    hasRun = false;  // รีเซ็ตค่าเมื่อ is == false
  }
  // Serial.print("hasRun " + String(hasRun));
}

void Stop_FreeRun() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
}
void R(int i) {
  digitalWrite(D, HIGH);
  analogWrite(A, i);  // main
}
void RS() {
  digitalWrite(A, LOW);
  digitalWrite(D, LOW);
}
void L(int i) {
  digitalWrite(C, HIGH);
  analogWrite(B, i);  // main
}
void LS() {
  digitalWrite(B, LOW);  // main
  digitalWrite(C, LOW);
}
void MotorPwm(int A, int B) {
  if (A >= 1 && B <= 0) {
    LS();
    R(A);
    Stop_ABS(false);  // รีเซ็ตสถานะ
  } else if (B >= 1 && A <= 0) {
    RS();
    L(B);
    Stop_ABS(false);  // รีเซ็ตสถานะ
  } else {
    // Serial.print("Stop");
    Stop_ABS(true);  // จะทำงานเพียงครั้งเดียว
    Stop_FreeRun();
  }
  Serial.print(" A : " + String(A) + " B : " + String(B) + " ");
}
