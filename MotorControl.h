void Stop_ABS() {
  for (int i = 0; i < 20; i++) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    delay(i + 5);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    delay(i + 5);
  }
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
}
void Stop_FreeRun() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
}
void R(float i) {
  digitalWrite(D, HIGH); analogWrite(A, i);  // main
 
}
void RS() {
  digitalWrite(A, LOW);
  digitalWrite(D, LOW);
}
void L(float i) {
  digitalWrite(C, HIGH);analogWrite(B, i);  // main
  
}
void LS() {
  digitalWrite(B, LOW);  // main
  digitalWrite(C, LOW);

}
void CLE() {
  Av1 = 0.5;
  Av2 = 0.5;
}
void CON(int A, int B) {
  if (A >= 1 && B >= 1) {
    Stop_ABS();
    Stop_FreeRun();
    CLE();
  } else if (A >= 1 && B <= 0) {
    RS();
    L(A);
  } else if (B >= 1 && A <= 0) {
    LS();
    R(B);
  } else {
    Serial.print("Stop");
    Stop_FreeRun();
  }
}