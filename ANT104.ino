byte A_read = A0;  //PWM input
byte B_read = A1;  //PWM input

const int A = 3,  //PWM
          B = 5,          //pwm
          C = 4,          //Digital
          D = 2,          //Digital
          Fan = 13,       //Digital
          ERROR_LED = 12;     //digital

int SW_tast1 = 6;
int SW_tast2 = 10;
int I2Cmode = 0;

unsigned long AempMillis = 0;
unsigned long AempReadingInterval = 10;

unsigned long previousMillisTemp = 0;
const long intervalTemp = 1200;  // กำหนดเวลาในมิลลิวินาที (ตัวอย่าง: 1000ms)

unsigned long previousMillis = 0;
unsigned long pwmReadingInterval = 20;

unsigned long pwmReadingDuration = 10000;  // ระยะเวลาการอ่าน 1000 มิลลิวินาที 2500

const float Temp_max = 80.0;  //set max
const float pwm_defalue = 254;
const int Auto_Delay = 500;
float Temp_sensor = 50.0;

//float dutyCycleA = 0.0;
//float dutyCycleB = 0.0;

float Aver_Stop = 160;
float Av1 = 0.5, Av2 = 0.5;

unsigned int max_pwm_ir = 254;
const int Max_Amp = 130;
int sw = 0;
int Read_Amp = 0;
int ERROR_Ampe = 0;
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
  pinMode(9, INPUT_PULLUP);
  pinMode(SW_tast1, INPUT);
  pinMode(SW_tast2, INPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  I2C_Set();
  digitalWrite(A, LOW);
  digitalWrite(D, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(Fan, LOW);
  digitalWrite(ERROR_LED, LOW);
  Serial.println("restart");
}
void loop() {
  get_Amp();
  GetTemp();
    Serial.print(" Amp = :" + String(Read_Amp) + " Tem = " + String(Temp_sensor) + " Aver_Stop " + String(Aver_Stop)  );
  Serial.println("");
}
