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
#define MOTOR_COUNT 4

#include "lib/PWM/motors/dji_2212/dji_2212.h"
#include "lib/exceptions/fatalException.h"
#include "lib/Orientation/orientation.h"
#include "lib/External/PID.h"
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
         * maintainTargets()
         * Allows me to determine what targets should be met in each run.
         * @param none
         * @returns none
         */
        void maintainTargets();

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
         * Four pointers for new DJI_2212 objects
         */
        pwm::dji_2212* motor[4];

        /**
         * Pointer for a new orientation object
         */
        orientation* myOrientation;

        /**
         * Pointer for a new PID (Proportional–Integral–Derivative) object for pitch values
         */
        PID* pitchPID;

        /**
         * Pointer for a new PID (Proportional–Integral–Derivative) object for roll values
         */
        PID* rollPID;

    private:

        /**
         * maintainAltitude()
         * Allow the quadcopter to analyse current altitude related sensor readings against target settings and adjust motors accordingly
         * @param none
         * @return none
         * TODO: implement this method
         */
        void maintainAltitude();

        /**
         * maintainHeading()
         * Allow the quadcopter to analyse current heading readings against target settings and adjust motors accordingly
         * @param none
         * @return none
         * TODO: implement this method
         */
        void maintainHeading();

        /**
         * maintainRoll()
         * Allow the quadcopter to analyse current readings against target settings and adjust motors accordingly
         * @param none
         * @return none
         * TODO: handle potential errors.
         */
        void maintainRoll();

        /**
         * maintainPitch()
         * Allow the quadcopter to analyse current readings against target settings and adjust motors accordingly
         * @param none
         * @return none
         * TODO: handle potential errors.
         */
        void maintainPitch();


    };

}
#endif //QUADRO_QUADRO_H
