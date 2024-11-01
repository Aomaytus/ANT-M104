#include "MotorControl.h";
#include "Aver.h";
#include "AnalongInput.h";
#include "pwm.h";
void SwMote() {
  int switch_mode = digitalRead(9);
  int switch_i2c = digitalRead(10);
  int test_sw1 = digitalRead(SW_tast1);
  int test_sw2 = digitalRead(SW_tast2);
  if (test_sw1 == 1 || test_sw2 == 1) {
    if (test_sw1 == 1) {
      MotorPwm(254, 0);
    }
    else if (test_sw2 == 1) {
      MotorPwm(0, 254);
    }
  }
  else if (test_sw1 == 0 || test_sw2 == 0) {
    if ( switch_mode == 1 && switch_i2c == 0) {
      ReadPwmModeA();
    }
    else if (switch_mode == 0 && switch_i2c == 0) {
      ReadAnalongModeC();

    }

    else if  (switch_i2c == 1) {
      // I2C mode
    }
    else if (switch_i2c == 1 && switch_mode == 1 ) {

    }
    //PPW mode
  } else {
    MotorPwm(0, 0);
  }
}
