//
// Created by Michael Brookes on 27/05/2016.
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

#ifndef BEAGLEBONE_PWM_PWMDEVICE_H
#define BEAGLEBONE_PWM_PWMDEVICE_H

#include <fstream>

#include "../Device/IDevice.h"
#include "../Exceptions/ExceptionAid.h"
#include "../Overlays/PWM/PWMOverlay.h"
#include "../Overlays/PWM/PinOverlay.h"

namespace abPWM {

    using namespace abIDevice;

    class PWMDevice : public abIDevice::IDevice, abPWM::PWMOverlay {

    public:

        PWMDevice(){};

        PWMDevice( PinBlocks _block, PWMPins _pin ) throw( PWMSetupException& );

        enum ValType{
            Run, Duty, Period, Polarity, Power_Control, Power_RunTime_Active, Power_RunTime_Suspended
        };

        PinBlocks BlockNum;
        PWMPins PinNum;

        string Power_ControlStr;

        long Get( ValType );

        void Set( ValType, long _val );

        void SetPinNum( PWMPins _pin );

        void SetBlockNum( PinBlocks _block );

    private:

        ValType VT;

        void ReadDevice( ValType );

        short ReadDevice( size_t _BufferSize );

        void InitDevice( ) throw( PWMSetupException& );

        int ConnectToDevice( ) { return 1; }

        int WriteToDevice( size_t _BufferSize ) throw( PWMSetupException& );

        void WriteToDevice( ValType, long int _val ) throw( PWMSetupException& );

        int OpenDevice( ) throw( PWMSetupException& );

        long GetCurrentReading( ValType );

        char* GetFilePath( );

        void SetValType( ValType );

        void SetWriteVal( long int _val );

        void SetFilePaths( );

        long Val2Write;

        ifstream PWMFile;

        string CurrentReading;

        PinOverlay* _PinOverlay;

        char DutyPath[ 50 ];

        char PeriodPath[ 50 ];

        char RunPath[ 50 ];

        char PolarityPath[ 50 ];

        char PowerControlPath[ 100 ];

        char PowerRunTime_ActivePath[ 100 ];

        char PowerRunTime_SuspendedPath[ 100 ];

    };

}

#endif //BEAGLEBONE_PWM_PWMDEVICE_H
