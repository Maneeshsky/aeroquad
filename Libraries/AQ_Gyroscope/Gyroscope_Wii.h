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

#ifndef _AEROQUAD_GYROSCOPE_WII_H_
#define _AEROQUAD_GYROSCOPE_WII_H_

#include <Gyroscope.h>
#include "../AQ_Platform_Wii/Platform_Wii.h"

class Gyroscope_Wii : public Gyroscope {
private:
  Platform_Wii *platformWii;

public:
  Gyroscope_Wii();
  
  void setPlatformWii(Platform_Wii *platformWii);
  void measure(void);
  void calibrate(void);
};
#endif