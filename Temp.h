const int analogPin = A7;               // กำหนดหมายเลขขา Analog ที่เชื่อมต่อกับเซนเซอร์
const float referenceVoltage = 4.9;     // แรงดันอ้างอิง (Volt)
const float seriesResistance = 570.0;  // ค่าความต้านทานของตัวต้านทาน (Ohm)
const float NTCResistance = 47000.0;     // ค่าความต้านทานของ NTC ที่อุณหภูมิ 25°C (Ohm)
const float betaCoefficient = 5000.0;   // ค่าเบต้าของ NTC

int tenp_count = 0;
int rawValueSum = 0;  // เก็บผลรวมค่า rawValue

void GetTemp() {
  unsigned long ReadcurrentMillis = millis();
  // เรียกใช้ฟังก์ชัน GetTemp ทุกๆ intervalTemp มิลลิวินาที
  if (ReadcurrentMillis - previousMillisTemp >= intervalTemp) {
    previousMillisTemp = ReadcurrentMillis;
    if (tenp_count < 10) {
      rawValueSum += analogRead(analogPin);  // สะสมค่า rawValue
      tenp_count++;
    } else {
      float rawValueAvg = rawValueSum / 10.0;  // เฉลี่ยค่า rawValue
      float voltage = (rawValueAvg / 1023.0) * referenceVoltage;  // แปลงเป็นแรงดัน (Volt)
      float NTCResistanceMeasured = (seriesResistance * voltage) / (referenceVoltage - voltage);  // คำนวณค่าความต้านทาน NTC

      // คำนวณอุณหภูมิโดยใช้สมการแบบ Steinhart-Hart
      float steinhart;
      steinhart = NTCResistanceMeasured / NTCResistance;  // (R/Ro)
      steinhart = log(steinhart);  // ln(R/Ro)
      steinhart /= betaCoefficient;  // 1/B * ln(R/Ro)
      steinhart += 1.0 / (25 + 273.15);  // + (1/To)
      steinhart = 1.0 / steinhart;  // Invert
      steinhart -= 273.15;  // แปลงเป็นองศาเซลเซียส
      Temp_sensor = steinhart;

      // รีเซ็ตตัวนับและค่า rawValue
      tenp_count = 0;
      rawValueSum = 0;
    }

    // ควบคุมพัดลมตามค่าอุณหภูมิ
    if (Temp_sensor > 40.1) {
      digitalWrite(Fan, HIGH);  // เปิดพัดลม
    } else {
      digitalWrite(Fan, LOW);  // ปิดพัดลม
    }
  }
}
