#include "Arduino.h"
#include "MotorControl.h";
#include "SoftDelay.h";
#include "AnalongInput.h";
#include "pwm.h";
const long checkInterval = 20;          // เช็คเงื่อนไขทุก 20ms
const long switchReadInterval = 2000;  // อ่านค่าทุก 5 วินาที

unsigned long previousCheckTime = 0;
unsigned long previousSwitchReadTime = 0;
bool test_sw1, test_sw2;
bool switch_state[2] = { 0, 0 };  // เก็บค่าบิตของสวิตช์
void ReadSwitchState() {
  unsigned long currentTime = millis();
  if (currentTime - previousSwitchReadTime >= switchReadInterval) {
    previousSwitchReadTime = currentTime;

    switch_state[0] = digitalRead(SW_modeIO);
    switch_state[1] = digitalRead(SW_modeRead);

    int mode = (switch_state[1] << 1) | switch_state[0];  // รวมค่าเป็นเลขฐานสอง

    // Serial.println("Switch Updated: " + String(switch_state[0]) + " " + String(switch_state[1]));
  }
}
void SwMote() {
  unsigned long currentTime = millis();
  if (currentTime - previousCheckTime >= checkInterval) {
    previousCheckTime = currentTime;
    // อ่านค่าจากสวิตช์ทุก 5 วินาที
    ReadSwitchState();
    pinMode(SW_tast1, OUTPUT);
    pinMode(SW_tast2, OUTPUT);
    digitalWrite(SW_tast1, LOW);
    digitalWrite(SW_tast2, LOW);
    pinMode(SW_tast1, INPUT);
    pinMode(SW_tast2, INPUT);
    bool test_sw1 = digitalRead(SW_tast1);
    bool test_sw2 = digitalRead(SW_tast2);
    // Serial.println("  Array : " + String(switch_state[0]) + String(switch_state[1]) + "  : " + String(test_sw1) + "" + String(test_sw2));
    if (test_sw1 == 0 && test_sw2 == 0) {
      if (switch_state[0] == 0 && switch_state[1] == 0) {
        ReadPwmModeB(0);
      } else if (switch_state[0] == 0 && switch_state[1] == 1) {
        ReadPwmModeB(1);
      } else if (switch_state[0] == 1 && switch_state[1] == 0) {
        ReadAnalongModeC();
      } else {
        MotorPwm(0, 0);
      }
    }
    /////////////////////////////
    else if (test_sw1 == 1 || test_sw2 == 1) {
      if (test_sw1 == 1) {
        MotorPwm(pwm_defalue, 0);
      } else if (test_sw2 == 1) {
        MotorPwm(0, pwm_defalue);
      } else {
        MotorPwm(0, 0);
      }
    }
  }
}
