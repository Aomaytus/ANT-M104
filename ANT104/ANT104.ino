// #include <stdint.h>
byte A_read = A0;  //PWM input
byte B_read = A1;  //PWM input
// byte analogPin = A7;  // กำหนดหมายเลขขา Analog ที่เชื่อมต่อกับเซนเซอร์
const int A = 3,  //PWM
  B = 5,          //pwm
  C = 4,          //Digital
  D = 2,          //Digital
  SW_modeIO = 9,
          SW_modeRead = 11,
          SW_tast1 = 6,
          SW_tast2 = 10,
          Fan = 13,
          ERROR_LED = 12;
int I2Cmode = 0;

unsigned long AempMillis = 0;
unsigned long AempReadingInterval = 45;

unsigned long previousMillisTemp = 0;
const long intervalTemp = 1500;  // กำหนดเวลาในมิลลิวินาที (ตัวอย่าง: 1000ms)

unsigned long previousMillis = 0;
unsigned long pwmReadingInterval = 45;
unsigned long pwmReadingDuration = 35000;  // ระยะเวลาการอ่าน 1000 มิลลิวินาที 2500

const float Temp_max = 100.0;  //set max
const float pwm_defalue = 254;
const int Auto_Delay = 10;
float Temp_sensor = 50.0;
int Max_Amp = 300;  //600  150
int16_t Aver_Stop = 2;
float Stop_Low = 1;
float Av1 = 0.5, Av2 = 0.5;
const int Max_Amp_value = 620;  //640
const int Min_Amp_value = 510;  //510 ปรับค่า Over lode แบบอัตโนมัติ ตัดกระแสตามระบบสัญญาณ input
int16_t max_pwm_ir = 254;

// int sw = 0;
int Read_Amp = 0;
int16_t ERROR_Ampe = 0;
#include "Temp.h";
#include "Sw.h";
#include <Wire.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "ApmeRead.h";
#define I2C_SLAVE_ADDR 8
String receivedCommand = "";
String lastReceivedData = " ";
bool newDataReceived = false;
#include "I2C.h";
void setup() {
  Serial.begin(9600);
  pinMode(A_read, INPUT);
  pinMode(B_read, INPUT);
  // pinMode(analogPin,INPUT_PULLUP);
  pinMode(SW_modeIO, INPUT_PULLUP);
  pinMode(SW_modeRead, INPUT_PULLUP);
  // pinMode(SW_tast1, INPUT);
  // pinMode(SW_tast2, INPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  digitalWrite(A, LOW);
  digitalWrite(D, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(Fan, LOW);

  digitalWrite(ERROR_LED, LOW);
  Serial.println(" START ");
  I2C_Set();
}
void loop() {
  get_Amp();
  GetTemp();
  Serial.println("Amp: " + String(Read_Amp) + " Max Amp: " + String(Max_Amp) + " Tem: " + String(Temp_sensor) + " Aver_Stop: " + String(Aver_Stop));
  // Serial.println("");
}
