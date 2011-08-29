/*
  AeroQuad v3.0 - April 2011
  www.AeroQuad.com 
  Copyright (c) 2011 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.
 
  This program is free software: you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or 
  (at your option) any later version. 

  This program is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  GNU General Public License for more details. 

  You should have received a copy of the GNU General Public License 
  along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

//#define MOTOR_PWM
//#define MOTOR_PWM_Timer
#define MOTOR_APM
//#define MOTOR_I2C

//#define NB_MOTOR_4
//#define NB_MOTOR_6
#define NB_MOTOR_8


#if defined MOTOR_PWM
  #include <Motors.h>
  #include <Motors_PWM.h>
  Motors_PWM motorsSpecific;
  Motors *motors = &motorsSpecific;
  
  void initMotors(NB_Motors motorConfig) {
    motors->initialize(motorConfig); 
  }
#elif defined MOTOR_PWM_Timer
  #include <Motors.h>
  #include <Motors_PWM_Timer.h>
  Motors_PWM_Timer motorsSpecific;
  Motors *motors = &motorsSpecific;
  
  void initMotors(NB_Motors motorConfig) {
    motors->initialize(motorConfig); 
  }

#elif defined MOTOR_APM
  #include <APM_RC.h>
  #include <Motors.h>
  #include <Motors_APM.h>
  Motors_APM motorsSpecific;
  Motors *motors = &motorsSpecific;
  
  void initMotors(NB_Motors motorConfig) {
    initRC();
    motors->initialize(motorConfig); 
  }
  
#elif defined MOTOR_I2C
  #include <Wire.h>
  #include <Device_I2C.h>
  #include <Motors.h>
  #include <Motors_I2C.h>
  Motors_I2C motorsSpecific;
  Motors *motors = &motorsSpecific;

  void initMotors(NB_Motors motorConfig) {
    Wire.begin();
    motors->initialize(motorConfig); 
  }

  
#endif

#if defined (NB_MOTOR_4)
  #define NB_MOTOR 4
  #define NB_MOTOR_CONFIG FOUR_Motors
#elif defined (NB_MOTOR_6)
  #define NB_MOTOR 6
  #define NB_MOTOR_CONFIG SIX_Motors
#else
  #define NB_MOTOR 8
  #define NB_MOTOR_CONFIG HEIGHT_Motors
#endif


void setup() {
  Serial.begin(115200);
  initMotors(NB_MOTOR_CONFIG);
}

void testMotor(int motor) {
  Serial.println();
  Serial.print("TEST MOTOR ");
  Serial.println(motor);
  for (int motorTrust = 1000; motorTrust < 1200; motorTrust+=10) {
    motors->setMotorCommand(motor, motorTrust);
    motors->write();
    delay(200);
  }
  for (int motorTrust = 1200; motorTrust > 1000; motorTrust-=10) {
    motors->setMotorCommand(motor, motorTrust);
    motors->write();
    delay(200);
  }
  motors->setMotorCommand(motor, 1000);
  motors->write();
}
 
void loop() {
  
  Serial.println("===================== START MOTOR TEST =========================");
  for (int motor = 0; motor < NB_MOTOR; motor++) {
    testMotor(motor);
    delay(1000);
  }
}








