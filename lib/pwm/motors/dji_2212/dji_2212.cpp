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

#include "dji_2212.h"

using namespace quadro::pwm;

dji_2212::dji_2212( pinBlocks _block,
        PWMPins _pin
)
        :motors( _block, _pin )
{

    setMaxSpeed( MAX_DUTY );
    setMinSpeed( MIN_DUTY );
    setSpeedStep( DEFAULT_SPEED_STEP );
    setPeriod( DEFAULT_PERIOD );
    setDuty( getMinSpeed());
    setPolarity( 1 );

}

void dji_2212::init()
{
    setPeriod( DEFAULT_PERIOD );
    setTargetSpeed( SPIN_SLOWSPEED );
    setRun( 1 );
    start();
}

void dji_2212::setDuty( long _duty )
{
    currentDuty = _duty;
    set( Duty, currentDuty );
}

void dji_2212::setPeriod( long _period )
{
    currentPeriod = _period;
    set( Period, currentPeriod );
}

void dji_2212::setRun( int _run )
{
    currentRun = _run;
    set( Run, currentRun );
}

void dji_2212::setPolarity( int _polarity )
{
    currentPolarity = _polarity;
    set( Polarity, currentPolarity );
}