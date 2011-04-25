/*
  AeroQuad v3.0 - May 2011
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

#include "Gyroscope_ITG3200.h"

#include <Wire.h>
#include <AQMath.h>
#include <Device_I2C.h>

Gyroscope_ITG3200::Gyroscope_ITG3200(boolean useSeccondAddress) {
  scaleFactor = radians(1.0 / 14.375);  //  ITG3200 14.375 LSBs per �/sec
  gyroAddress = ITG3200_ADDRESS;
  if (useSeccondAddress)
	gyroAddress = ITG3200_ADDRESS-1;
}
  

void Gyroscope_ITG3200::initialize(void) {
  smoothFactor = 1.0;
  updateRegisterI2C(gyroAddress, ITG3200_RESET_ADDRESS, ITG3200_RESET_VALUE); // send a reset to the device
  updateRegisterI2C(gyroAddress, ITG3200_LOW_PASS_FILTER_ADDR, ITG3200_MEMORY_ADDRESS); // 10Hz low pass filter
  updateRegisterI2C(gyroAddress, ITG3200_RESET_ADDRESS, ITG3200_OSCILLATOR_VALUE); // use internal oscillator 
}
    
void Gyroscope_ITG3200::measure(void) {
  sendByteI2C(gyroAddress, ITG3200_MEMORY_ADDRESS);
  Wire.requestFrom(gyroAddress, ITG3200_BUFFER_SIZE);
    
  // The following 3 lines read the gyro and assign it's data to gyroADC
  // in the correct order and phase to suit the standard shield installation
  // orientation.  See TBD for details.  If your shield is not installed in this
  // orientation, this is where you make the changes.
  int gyroADC[3];
  gyroADC[ROLL]  = ((Wire.receive() << 8) | Wire.receive())  - zero[ROLL];
  gyroADC[PITCH] = zero[PITCH] - ((Wire.receive() << 8) | Wire.receive());
  gyroADC[YAW]   = zero[YAW] - ((Wire.receive() << 8) | Wire.receive());

  for (byte axis = 0; axis <= YAW; axis++) {
    rate[axis] = filterSmooth(gyroADC[axis] * scaleFactor, rate[axis], smoothFactor);
  }
 
  // Measure gyro heading
  long int currentTime = micros();
  if (rate[YAW] > radians(1.0) || rate[YAW] < radians(-1.0)) {
    heading += rate[YAW] * ((currentTime - lastMesuredTime) / 1000000.0);
  }
  lastMesuredTime = currentTime;
}

void Gyroscope_ITG3200::calibrate() {
  int findZero[FINDZERO];
    
  for (byte axis = 0; axis < 3; axis++) {
    for (int i=0; i<FINDZERO; i++) {
	  sendByteI2C(gyroAddress, (axis * 2) + ITG3200_LOW_PASS_FILTER_VALUE);
      findZero[i] = readWordI2C(gyroAddress);
      delay(10);
    }
    zero[axis] = findMedianInt(findZero, FINDZERO);
  }
}