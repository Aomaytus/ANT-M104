unsigned long lastRequestTime = 0;         // เวลาที่การร้องขอครั้งล่าสุดเริ่ม
const unsigned long requestInterval = 50;  // ช่วงเวลาในการรอให้ Slave พร้อม (50 milliseconds)

String generateMACAddress() {
  String mac = "";
  for (int i = 0; i < 6; i++) {
    if (i > 0)
      mac += ":";
    mac += String(random(0, 256), HEX);
  }
  mac.toUpperCase();
  return mac;
}
String readCodeFromEEPROM() {
  int addr = 0;
  char buffer[18] = { 0 };        // ตัวแปรเก็บข้อมูลที่อ่านได้
  int j = 0;                      // ตัวชี้ตำแหน่งสำหรับตัวแปร buffer
  for (int i = 0; i < 12; i++) {  // อ่าน 12 ตัวอักษร
    if (i > 0 && i % 2 == 0) {    // แทรกเครื่องหมาย colon ทุกๆ 2 ตัวอักษร
      buffer[j++] = ':';
    }
    buffer[j++] = EEPROM.read(addr++);
  }
  buffer[j] = '\0';  // ตัวอักษรสิ้นสุดสตริง
  return String(buffer);
}
void receiveEvent(int howMany) {
  receivedCommand = " ";
  while (Wire.available()) {
    char c = Wire.read();
    receivedCommand += c;
  }
  I2Cmode = 2;
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, receivedCommand);
  // Serial.println(receivedCommand);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }
  String MACAddress_code = readCodeFromEEPROM();
  if (Read_Amp > Max_Amp || Temp_sensor < Temp_max) {
    if (doc.containsKey(MACAddress_code + "M1")) {
      int pwm = doc[MACAddress_code + "M1"];
      if (pwm > 1) {
        AverMode(pwm, 0);
      }
      // Serial.println("M1: " + String(pwm));
    }
    if (doc.containsKey(MACAddress_code + "M2")) {
      int pwm = doc[MACAddress_code + "M2"];
      if (pwm > 1) {
        AverMode(0, pwm);
      }
      // Serial.println("M2: " + String(pwm));
    }
  } else {
    
    ///
  }
}
void requestEvent() {
  StaticJsonDocument<200> doc;
  if (receivedCommand.indexOf("TEMP") != -1) {
    float temperature = Temp_sensor;
    doc["TEMP"] = temperature;
  }
  if (receivedCommand.indexOf("Aemp") != -1) {
    doc["Aemp"] = -0.07692 * Read_Amp + 50;
  }
  if (receivedCommand.indexOf("MAD") != -1) {
    String savedCode = readCodeFromEEPROM();
    // Serial.print(savedCode + " ");
    doc["MAD"] = savedCode;
  }
  if (receivedCommand.indexOf("ERROR") != -1) {
    if (Read_Amp <= Max_Amp) {
      ERROR_Ampe = 1;
    } else {
      ERROR_Ampe = 0;
    }
    doc["ERROR"] = ERROR_Ampe;
  }
  char jsonBuffer[128];
  size_t n = serializeJson(doc, jsonBuffer);
  Wire.write((const uint8_t *)jsonBuffer, n);
}

void saveCodeToEEPROM(String code) {
  int addr = 0;  // ตำแหน่งเริ่มต้นใน EEPROM
  for (int i = 0; i < code.length(); i++) {
    if (code[i] != ':') {  // ข้ามเครื่องหมาย colon
      EEPROM.update(addr++, code[i]);
    }
  }
  Serial.println("MAC Address saved to EEPROM.");
}
void I2C_Set() {
  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  bool sw1 = digitalRead(SW_tast1);
  bool sw2 = digitalRead(SW_tast2);
  if (sw1 == 1 && sw2 == 1) {
    randomSeed(analogRead(A7));
    String macAddress = generateMACAddress();
    Serial.print("Generated MAC Address: ");
    Serial.println(macAddress);
    saveCodeToEEPROM(macAddress);
  }
  String savedCode = readCodeFromEEPROM();
  Serial.println("      MAC Address: " + String(savedCode));
}
