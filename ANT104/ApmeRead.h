unsigned long AempMillis_clear = 0;
unsigned long AempReadingInterval_clear = 4000;

void clear_Avr()
{
  Av1 = 0;
  Av2 = 0;
}
void aemp_cooldown()
{
  unsigned long ReadcurrentMillis_clear = millis();
  if (ReadcurrentMillis_clear - AempMillis_clear >= AempReadingInterval_clear)
  {
    AempMillis_clear = ReadcurrentMillis_clear;
    if (Aver_Stop > 1)
    {
      Aver_Stop -= 1;
    }
    // Serial.print("                                                         Auto_Delay = " + String(Auto_Delay));
  }
}
void ApmeCheck(float Read_Amp)
{
  // 
  if (Read_Amp <= Max_Amp || Temp_sensor > Temp_max)
  {
    Serial.print("                                                  stop " + String(Read_Amp));
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    clear_Avr();
    digitalWrite(ERROR_LED, HIGH);
    delay(Auto_Delay);

    if (Aver_Stop < 10)
    {
      Aver_Stop += 1;
    }
  }
  else
  {
    digitalWrite(ERROR_LED, LOW);
    SwMote();
    aemp_cooldown();
  }
}
// auto funtion
void get_Amp()
{
  unsigned long ReadcurrentMillis = millis();
  if (ReadcurrentMillis - AempMillis >= AempReadingInterval)
  {
    AempMillis = ReadcurrentMillis;

    // อ่านค่า Analog 5 ครั้งและหาเฉลี่ย
    Read_Amp = 0;
    for (int i = 0; i < 5; i++)
    {
      Read_Amp += analogRead(A2);
    }
    Read_Amp = Read_Amp / 5; // คำนวณค่าเฉลี่ยจริงๆ

    // // ตรวจสอบค่าของ Av1 และ Av2
    // if (Av1 > 1 || Av2 > 1) {
    //   int Av = (Av1 > 1) ? Av1 : Av2;  // ใช้ค่าที่มากกว่า 1
    //   Max_Amp = map(Av, 0, 254, Max_Amp_value, Min_Amp_value);
    //   Serial.print("  Av " + String(Av));
    //   // จำกัดค่า Max_Amp ให้อยู่ในช่วงที่กำหนด
    //   if (Max_Amp > Max_Amp_value) {
    //     Max_Amp = Max_Amp_value;
    //   } else if (Max_Amp < Min_Amp_value) {
    //     Max_Amp = Min_Amp_value;
    //   }
    // }

    // ตรวจสอบค่ากระแส
    ApmeCheck(Read_Amp);
  }
}
