// Created by Michael Brookes on 06/06/2016.
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

#ifndef BEAGLEBONE_MOTOR_MOTORS_H
#define BEAGLEBONE_MOTOR_MOTORS_H

#include "../PWM/PWMDevice.h"
#include <string>

namespace abPWM {

    class Motors : public abPWM::PWMDevice {

    public:
        Motors(){};

        Motors( abIDevice::iDeviceOverlay::PinBlocks, abIDevice::iDeviceOverlay::PWMPins );

        void SetTargetSpeed( long ) throw ( long );
        void ReversePolarity( );
        void Start( );
        void Stop( );

        long CurrentDuty;
        long CurrentPeriod;
        int CurrentRun;
        int CurrentPolarity;

    protected:

        long GetMaxSpeed( );
        long GetMinSpeed( );
        int GetSpeedStep( );

        void SetMaxSpeed( long );
        void SetMinSpeed( long );
        void SetSpeedStep( int );

    private:
        enum status{ On = 1, Off = 0, Error = 3 };
        enum polarity{ Negative = 0, Positive = 1 };

        void SetStatus( status );

        void IncreaseSpeed( unsigned short _SpeedMod = 250 );
        void DecreaseSpeed( unsigned short _SpeedMod = 250 );

        static void *MaintainTargetSpeed( void * );

        pthread_t MotorSpeedThread;
        int ThreadRet;
        int SpeedStep;

        long TargetSpeed;
        long MaxSpeed;
        long MinSpeed;

        status Status;
    };

}

#endif //BEAGLEBONE_MOTOR_MOTORS_H
