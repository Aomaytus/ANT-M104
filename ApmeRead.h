void clear_Avr() {
    Av1 = 0;
    Av2 = 0;
}
void aemp_cooldown() {
  if (Read_Amp > Max_Amp) {
    if (Aver_Stop < 160) {
      Aver_Stop += 1;
    }
  }
}
void ApmeCheck(int Read_Amp) {
  if (Read_Amp <= Max_Amp || Temp_sensor > Temp_max) {
    // Serial.print("stop  Read_Amp = " + String(Read_Amp));
    Stop_FreeRun();
    clear_Avr();
    digitalWrite(ERROR_LED, HIGH);
    delay(Auto_Delay);
    if (Aver_Stop > 1) {
      Aver_Stop = Aver_Stop - 2.2;
    }
  } else {
    digitalWrite(ERROR_LED, LOW);
    SwMote();
  }
  aemp_cooldown();
}
//auto funtion
void get_Amp() {
  unsigned long ReadcurrentMillis = millis();
  if (ReadcurrentMillis - AempMillis >= AempReadingInterval) {
    AempMillis = ReadcurrentMillis;
    for (int i = 0; i < 5; i++) {
      Read_Amp = +analogRead(A2);
    }
    Read_Amp / 5;
    ApmeCheck(Read_Amp);
  }
}
