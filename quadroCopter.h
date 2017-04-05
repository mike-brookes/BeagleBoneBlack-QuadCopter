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

#ifndef QUADRO_QUADRO_H
#define QUADRO_QUADRO_H

#include "lib/exceptions/fatalException.h"
#include "lib/orientation/orientation.h"
#include "lib/aeronautics/aeronautics.h"

#include <sstream>

namespace quadro {

    class quadroCopter {

    public:

        /**
         * quadroCopter constructor
         * Initialises motors
         * Sets up a new orientation object which contains all sensor data related to orientation.
         * Also sets up the PID controllers.
         * @params none
         */
        quadroCopter();

        /**
         * setStartupTargets()
         * This method is only called once - it determines what the quadcopter will do on startup.
         * @param none
         * @return none
         */
        void setStartupTargets();

        /**
         * A storage struct that contains all the quadcopters targets.
         */
        struct target {
            double targetVal;
        } height, roll, pitch, heading;

        /**
         * What is the quadcopters current state
         */
        enum STATE {
            NORMAL = 1,
            MOVING = 2,
            URGENT = 5,
            PANIC = 10
        } state;

        /**
         * Pointer for a new orientation object
         */
        orientation* myOrientation;

        /**
         * Pointer for a new aeronautics object
         */
        aeronautics* myAeronautics;

        /**
         * Compare sensor data against targets and send data to Aeronautic library.
         */
        void monitorSensorData();
    };

}
#endif //QUADRO_QUADRO_H
