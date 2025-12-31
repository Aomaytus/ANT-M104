const int NTC_PIN = A7;                    // ขาที่เชื่อมต่อ NTC
const float SERIES_RESISTOR = 15000.0;     // ตัวต้านทาน Pull-up 10k โอห์ม
const float NOMINAL_RESISTANCE = 10000.0;  // ความต้านทานของ NTC ที่ 25°C
const float NOMINAL_TEMPERATURE = 28;      // อุณหภูมิที่ 25°C
const float B_COEFFICIENT = 3950.0;        // ค่าคงที่ B ของ NTC
const float ADC_MAX = 1023.0;              // ค่า ADC สูงสุด
const float VCC = 5;                     // แรงดันไฟฟ้า 5V
void GetTemp() {
  unsigned long ReadcurrentMillis = millis();
  // เรียกใช้ฟังก์ชัน GetTemp ทุกๆ intervalTemp มิลลิวินาที
  if (ReadcurrentMillis - previousMillisTemp >= intervalTemp) {
    previousMillisTemp = ReadcurrentMillis;
    // int adcValue = analogRead(NTC_PIN);          // อ่านค่า ADC
    // float voltage = (adcValue / ADC_MAX) * VCC;  // คำนวณแรงดันไฟฟ้าที่ขา NTC
    // // คำนวณความต้านทานของ NTC
    // float ntcResistance = (SERIES_RESISTOR * voltage) / (VCC - voltage);
    // // ใช้สมการ Steinhart-Hart เพื่อคำนวณอุณหภูมิ
    // float steinhart;
    // steinhart = ntcResistance / NOMINAL_RESISTANCE;     // R/R0
    // steinhart = log(steinhart);                         // ln(R/R0)
    // steinhart /= B_COEFFICIENT;                         // 1/B * ln(R/R0)
    // steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);  // + (1/T0)
    // steinhart = 1.0 / steinhart;                        // Invert
    // Temp_sensor = steinhart -= 273.15;
    Temp_sensor = analogRead(NTC_PIN);  // Convert to Celsius
    Temp_sensor = map(Temp_sensor, 473, 131, 29, 88);
  }
  // ควบคุมพัดลมตามค่าอุณหภูมิ
  if (Temp_sensor > 40.1) {
    digitalWrite(Fan, HIGH);  // เปิดพัดลม
  } else {
    digitalWrite(Fan, LOW);  // ปิดพัดลม
  }
}
