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

#include "quadroCopter.h"

using namespace quadro;
using namespace quadro::pwm;
using namespace quadro::exceptions;

quadroCopter::quadroCopter()
{

    try {
        myOrientation = new orientation(); //!< myOrientation sets up a new orientation object
        myAeronautics = new aeronautics(); //!< myMovement sets up a new orientation object
    }
    catch ( setupException& e ) {
        //If a setup error occurred, we need to exit before we start flying otherwise catastrophic consequences undoubtedly will follow...
        //Re throw an exception here for the main thread to catch for a proper exit.
        throw fatalException( e.what());
    }

    setStartupTargets();

    usleep( 300000 ); //wait .3 second for sensor readings to be updated.

}

void quadroCopter::setStartupTargets()
{
    height.targetVal = 25.00;
    pitch.targetVal = 0.00;
    roll.targetVal = 0.00;
    //heading.targetVal = myOrientation->heading;
}

void quadroCopter::monitorSensorData()
{
    myOrientation->setValues();
    myAeronautics->maintainRoll( abs( myOrientation->rollPID->calculate( roll.targetVal, myOrientation->roll )) * 100,
            myOrientation->roll );

    //myAeronautics->maintainPitch( abs( myOrientation->pitchPID->calculate( pitch.targetVal, myOrientation->pitch ) ), myOrientation->pitch );
}