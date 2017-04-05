/*
Copyright (C) 2017 Michael Brookes

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

#include "../motors.h"

namespace quadro {

    namespace pwm {

        using namespace quadro::overlays;

        /**
         * Class for running DJI_2212 motors, extends the motors class
         */
        class dji_2212 : public motors {

            const long MAX_DUTY = 320000; //150000
            const long MIN_DUTY = 500000;
            const long SPIN_SLOWSPEED = 700000;
            const long SPIN_TAKEOFFSPEED = 250000;
            const long DEFAULT_PERIOD = 1900000;
            const long ACTIVATE_PERIOD = 1200000;
            const int DEFAULT_SPEED_STEP = 50;

        public:

            /**
             * Public entry point for running a DJI_2212 motor, set the Block and Pin number in the constructor.
             *
             * @param pinBlock _block
             * @param PWMPins _pin
             */
            dji_2212( pinBlocks _block, PWMPins _pin );

            /**
             * This method will set the basic settings to initialise the motor, this will normally result in the motor spinning slowly.
             */
            void init();

            /**
             * Set the motors duty value
             *
             * @param _duty
             */
            void setDuty( long _duty );

            /**
             * Set the motors Period value here
             *
             * @param _period
             */
            void setPeriod( long _period );

            /**
             * Set the motors Run value here
             *
             * @param _run
             */
            void setRun( int _run );

            /**
             * Set the motors Polarity here.
             *
             * @param _polarity
             */
            void setPolarity( int _polarity );

        };

    }

}

#endif //BEAGLEBONE_MOTOR_DJI_2212_H
