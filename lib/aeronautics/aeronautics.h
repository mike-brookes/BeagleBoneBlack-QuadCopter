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

#ifndef QUADRO_AERONAUTICS_H
#define QUADRO_AERONAUTICS_H

#include "../pwm/motors/dji_2212/dji_2212.h"

namespace quadro {

using namespace pwm;

    class aeronautics {

    public:
        aeronautics();

        /**
         * Four pointers for new DJI_2212 motors
         */
        dji_2212* motor[4];

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
         * maintainRoll() - Analyse target settings and adjust motors accordingly
         *
         * @param _duty_increment
         * @param _roll
         * @return none
         * TODO: handle potential errors.
         */
        void maintainRoll( double _duty_increment, float _roll );

        /**
         * maintainPitch() - Analyse target settings and adjust motors accordingly
         *
         * @param none
         * @param _pitch
         * @return none
         * TODO: handle potential errors.
         */
        void maintainPitch( double _duty_increment, float _pitch );

    };

}
#endif //QUADRO_AERONAUTICS_H
