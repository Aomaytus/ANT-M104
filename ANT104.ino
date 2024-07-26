byte A_read = 8;   //PWM
byte B_read = 7;   //PWM
int A = 3,         //PWM
  B = 5,           //pwm
  C = 4,           //Digital
  D = 2,           //Digital
  Fan = 13,        //Digital
  Back_read = 12;  //digital
unsigned long previousMillisTemp = 0;
const long intervalTemp = 10000;  // กำหนดเวลาในมิลลิวินาที (ตัวอย่าง: 1000ms)
float Temp_sensor = 50.0;
int sw = 0;
int Read_Amp = 0;
const float Temp_max = 80.0;
const float pwm_defalue = 254;
float dutyCycleA = 0.0;
float dutyCycleB = 0.0;
unsigned long previousMillis = 0;
unsigned long pwmReadingInterval = 50;
unsigned long pwmReadingDuration = 2500;  // ระยะเวลาการอ่าน 1000 มิลลิวินาที 740
float Av1 = 0.5, Av2 = 0.5;
unsigned int max_pwm_ir = 254;
float Aver_Stop = 160;
int Auto_Delay = 5;
unsigned long AempMillis = 0;
unsigned long AempReadingInterval = 10;
const int Max_Amp = 130;
#include "pwm.h";
#include "Temp.h";
void setup() {
  Serial.begin(115200);
  pinMode(A_read, INPUT);
  pinMode(B_read, INPUT);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(Fan, OUTPUT);

  digitalWrite(A, LOW);
  digitalWrite(D, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(Fan, LOW);
  Serial.println("******************************* restart ");
}
void get_Amp() {
  unsigned long ReadcurrentMillis = millis();
  if (ReadcurrentMillis - AempMillis >= AempReadingInterval) {
    AempMillis = ReadcurrentMillis;
    for (int i = 0; i < 5; i++) {
      Read_Amp =+ analogRead(A2);
    }
    Read_Amp / 5;
    Read_Amp = (Read_Amp);
    motor(Read_Amp);
  }
}
void motor(int Read_Amp) {
  if (Read_Amp <= Max_Amp || Temp_sensor > Temp_max) {
    Serial.print("****************** stop ****************** Read_Amp = " + String(Read_Amp));
    Stop_FreeRun();
    CLE();
    delay(Auto_Delay);
    Auto_Delay = 50;
    if (Aver_Stop > 1) {
      Aver_Stop = Aver_Stop - 2.2;
    }
  } else {
    Read_pwm();
  }

}
void loop() {
  get_Amp();
  unsigned long ReadcurrentMillis = millis();
  // เรียกใช้ฟังก์ชัน GetTemp ทุกๆ intervalTemp มิลลิวินาที
  if (ReadcurrentMillis - previousMillisTemp >= intervalTemp) {
    previousMillisTemp = ReadcurrentMillis;
    GetTemp();
    if (Read_Amp > Max_Amp) {
      Auto_Delay = 5;
      if (Aver_Stop < 160) {
        Aver_Stop += 1;
      }
    }
  }
  // Serial.println(" Amp = :" + String(Read_Amp) + " Tem = " + String(Temp_sensor));
}
