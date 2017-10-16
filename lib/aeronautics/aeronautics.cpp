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

#include "aeronautics.h"

using namespace quadro;
using namespace std;

aeronautics::aeronautics()
{

    motor[ 0 ] = new dji_2212( pinBlocks::BLOCK_P9,
            PWMPins::PIN_42 );

    motor[ 1 ] = new dji_2212( pinBlocks::BLOCK_P8,
            PWMPins::PIN_19 );

    motor[ 2 ] = new dji_2212( pinBlocks::BLOCK_P9,
            PWMPins::PIN_14 );

    motor[ 3 ] = new dji_2212( pinBlocks::BLOCK_P9,
            PWMPins::PIN_22 );
//    //add additional motors here, specifying block and pin accordingly.

    motor[ 0 ]->init();
    motor[ 1 ]->init();
    motor[ 2 ]->init();
    motor[ 3 ]->init();

}

void aeronautics::maintainAltitude()
{
//TODO: Plan here is to use Barometer, GPS and Sonic Sensor to maintain altitude
}

void aeronautics::maintainHeading()
{
//TODO: Plan here is to use Magnetometer and GPS readings to maintain heading
}

void aeronautics::maintainRoll( double _duty_increment, float _roll )
{
    if( _roll > 0 ) {
        motor[ 2 ]->setTargetSpeed( long( motor[ 2 ]->currentDuty + _duty_increment ) );
        motor[ 0 ]->setTargetSpeed( long( motor[ 0 ]->currentDuty - _duty_increment ) );
    }
    else {
        motor[ 0 ]->setTargetSpeed( long( motor[ 0 ]->currentDuty + _duty_increment ) );
        motor[ 2 ]->setTargetSpeed( long( motor[ 2 ]->currentDuty - _duty_increment ) );
    }
}

void aeronautics::maintainPitch( double _duty_increment, float _pitch )
{
    if( _pitch > 0 ) {
        motor[ 1 ]->setTargetSpeed( long( motor[ 1 ]->currentDuty - _duty_increment ) );
        motor[ 3 ]->setTargetSpeed( long( motor[ 3 ]->currentDuty + _duty_increment ) );
    }
    else {
        motor[ 3 ]->setTargetSpeed( long( motor[ 3 ]->currentDuty - _duty_increment ) );
        motor[ 1 ]->setTargetSpeed( long( motor[ 1 ]->currentDuty + _duty_increment ) );
    }
}