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
#include <string>
#include <exception>
#include "../interfaces/IDevice.h"
#include "../overlays/pinOverlay.h"
#include "./overlays/pwmOverlay.h"

namespace quadro {

    using namespace overlays;

    namespace pwm {

        class pwmDevice : public IDevice, pwmOverlay {

        public:

            pwmDevice() { };

            pwmDevice( pinBlocks _block, PWMPins _pin ) throw( pwmSetupException& );

            enum valType {
                Run, Duty, Period, Polarity, Power_Control, Power_RunTime_Active, Power_RunTime_Suspended
            };

            pinBlocks blockNum;
            PWMPins pinNum;

            string powerControlStr;

            long get( valType );

            void set( valType, long _val );

            void setPinNum( PWMPins _pin );

            void setBlockNum( pinBlocks _block );

        private:

            valType VT;

            void readDevice( valType );

            short readDevice( size_t _bufferSize );

            void initDevice() throw( pwmSetupException& );

            int connectToDevice() { return 1; }

            int writeToDevice( size_t _bufferSize ) throw( pwmSetupException& );

            void writeToDevice( valType, long _val ) throw( pwmSetupException& );

            int openDevice() throw( pwmSetupException& );

            long getCurrentReading( valType );

            char* getFilePath();

            void setValType( valType );

            void setWriteVal( long _val );

            void setFilePaths();

            long val2Write;

            ifstream PWMFile;

            string currentReading;

            overlays::pinOverlay* _pinOverlay;

            char dutyPath[50];

            char periodPath[50];

            char runPath[50];

            char polarityPath[50];

            char powerControlPath[100];

            char powerRunTime_ActivePath[100];

            char powerRunTime_SuspendedPath[100];

        };

    }

}

#endif //BEAGLEBONE_PWM_PWMDEVICE_H
