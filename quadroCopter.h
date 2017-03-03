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

#ifndef QUADRO_QUADRO_H
#define QUADRO_QUADRO_H
#define MOTOR_COUNT 4

#include "lib/PWM/motors/dji_2212/dji_2212.h"
#include "Lib/Orientation/orientation.h"
#include "Lib/External/PID.h"

namespace quadro {

    class quadroCopter {

    public:

        quadroCopter();

        void maintainTargets();

        void setStartupTargets();

        struct target {
            double targetVal;
        } height, roll, pitch, heading;

        enum STATE {
            NORMAL = 1,
            MOVING = 2,
            URGENT = 5,
            PANIC = 10
        } state;

        pwm::dji_2212* motor[4];
        orientation* myOrientation;
        PID* pitchPID;
        PID* rollPID;

    private:

        void maintainHeight();

        void maintainRoll();

        void maintainPitch();

        void maintainHeading();

    };

}
#endif //QUADRO_QUADRO_H
