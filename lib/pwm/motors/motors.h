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

#include "../pwmDevice.h"
#include <string>

namespace quadro {

    namespace pwm {

        class motors : public pwmDevice {

        public:
            motors() { };

            motors( pinBlocks, PWMPins );

            void setTargetSpeed( long ) throw( long );

            void reversePolarity();

            void Start();

            void Stop();

            long currentDuty;
            long currentPeriod;
            int currentRun;
            int currentPolarity;

        protected:

            long getMaxSpeed();

            long getMinSpeed();

            int getSpeedStep();

            void setMaxSpeed( long );

            void setMinSpeed( long );

            void setSpeedStep( int );

        private:
            enum status {
                On = 1, Off = 0, Error = 3
            };
            enum polarity {
                Negative = 0, Positive = 1
            };

            void setStatus( status );

            void increaseSpeed( unsigned short _SpeedMod = 250 );

            void decreaseSpeed( unsigned short _SpeedMod = 250 );

            static void* maintainTargetSpeed( void* );

            pthread_t motorSpeedThread;
            int threadRet;
            int speedStep;

            long targetSpeed;
            long maxSpeed;
            long minSpeed;

            status Status;
        };

    }

}

#endif //BEAGLEBONE_MOTOR_MOTORS_H
