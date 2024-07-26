const int analogPin = A7;               // กำหนดหมายเลขขา Analog ที่เชื่อมต่อกับเซนเซอร์
const float referenceVoltage = 5.0;     // แรงดันอ้างอิง (Volt)
const float seriesResistance = 10000.0; // ค่าความต้านทานของตัวต้านทาน (Ohm)
const float NTCResistance = 2000.0;     // ค่าความต้านทานของ NTC ที่อุณหภูมิ 25°C (Ohm)
const float betaCoefficient = 3950.0;   // ค่าเบต้าของ NTC

void GetTemp() {
  int rawValue = analogRead(analogPin);                                                      // อ่านค่าแอนาล็อกจากเซนเซอร์
  float voltage = (rawValue / 1023.0) * referenceVoltage;                                    // แปลงค่าแอนาล็อกเป็นแรงดัน (Volt)
  float NTCResistanceMeasured = (seriesResistance * voltage) / (referenceVoltage - voltage); // คำนวณค่าความต้านทานของ NTC (Ohm)

  // คำนวณอุณหภูมิโดยใช้สมการแบบ Steinhart-Hart
  float steinhart;
  steinhart = NTCResistanceMeasured / NTCResistance; // (R/Ro)
  steinhart = log(steinhart);                        // ln(R/Ro)
  steinhart /= betaCoefficient;                      // 1/B * ln(R/Ro)
  steinhart += 1.0 / (25 + 273.15);                  // + (1/To)
  steinhart = 1.0 / steinhart;                       // Invert
  steinhart -= 273.15;
  Temp_sensor = (steinhart - 2.5);
  if (Temp_sensor > 45.6)
  {
    digitalWrite(Fan, HIGH);
  }
  else {
    digitalWrite(Fan, LOW);
  }
}

