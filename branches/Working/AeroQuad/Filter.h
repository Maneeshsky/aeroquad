/*
  AeroQuad v2.0 - January 2010
  www.AeroQuad.com
  Copyright (c) 2010 Ted Carancho.  All rights reserved.
  An Open Source Arduino based quadrocopter.
 
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

#ifndef __FILTER_H__
#define __FILTER_H__

class Filter {
  private:
    float _smoothFactor;
    int _previousData;
    int _smoothedData;

  public:
    Filter {
      _smoothFactor = 1.0;
      _previousData = 0;
    }
    
    void initialize(float smoothFactor) {
      if (smoothFactor > 1.0) smoothFactor = 1.0;
      if (smoothFactor <= 0) smoothFactor = 0.001;
      _smoothFactor = smoothFactor;
    }
    
    int smooth(int currentData) {
      _smoothedData = _previousData * (1 - _smoothFactor) + (currentData * _smoothFactor));
      _previousData = currentData;
      return _smoothedData;
    }
};

#endif
