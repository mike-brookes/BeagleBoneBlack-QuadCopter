//
// Created by Michael Brookes on 12/06/2016.
/*
Copyright (C) 2016 Michael Brookes

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BEAGLEBONE_MOTOR_DJI_2212_H
#define BEAGLEBONE_MOTOR_DJI_2212_H
#define MAX_DUTY            150000
#define MIN_DUTY            780000
#define SPIN_SLOWSPEED      700000
#define SPIN_TAKEOFFSPEED   250000
#define DEFAULT_PERIOD      1900000
#define ACTIVATE_PERIOD     1200000
#define DEFAULT_SPEED_STEP  250

#include "../Motors.h"

using namespace abPWM;

class DJI_2212 : public Motors {

public:
    DJI_2212( abIDevice::iDeviceOverlay::PinBlocks, abIDevice::iDeviceOverlay::PWMPins );
    void Init( );
    void SetDuty( long );
    void SetPeriod( long );
    void SetRun( int );
    void SetPolarity( int );

};


#endif //BEAGLEBONE_MOTOR_DJI_2212_H
