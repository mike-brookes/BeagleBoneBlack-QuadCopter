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

            //The reason these values are set in this class : Every motor type will have it's own values.
            //For each motor type, the motors class should be extended and the below values set accordingly.
            const long MAX_DUTY = 140000; //!< Maximum Duty Value, any lower than this doesn't impact the motors
            const long MIN_DUTY = 200000; //!< Minimum Duty Value, any higher than this doesn't impact the motors
            const long SPIN_SLOWSPEED = 700000; //!< Used to show the motors are set up correctly.
            const long SPIN_TAKEOFFSPEED = 250000; //!< Speed of motors required to achieve lift off.
            const long DEFAULT_PERIOD = 1900000; //!< This value is used when you want to fly.
            const long ACTIVATE_PERIOD = 1200000; //!< This value should only be used in setup to initialise the motors.

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

        };

    }

}

#endif //BEAGLEBONE_MOTOR_DJI_2212_H
