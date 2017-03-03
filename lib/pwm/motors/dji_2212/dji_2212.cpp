//
// Created by Michael Brookes on 12/06/2016.
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

#include "dji_2212.h"

using namespace quadro::pwm;

dji_2212::dji_2212( pinBlocks _block,
        PWMPins _pin
)
        :motors( _block, _pin )
{

    this->setMaxSpeed( MAX_DUTY );
    this->setMinSpeed( MIN_DUTY );
    this->setSpeedStep( DEFAULT_SPEED_STEP );
    this->setPeriod( DEFAULT_PERIOD );
    this->setDuty( this->getMinSpeed());
    this->setPolarity( 1 );

}

void dji_2212::init()
{
    this->setPeriod( DEFAULT_PERIOD );
    this->setTargetSpeed( SPIN_SLOWSPEED );
    this->setRun( 1 );
    this->Start();
}

void dji_2212::setDuty( long _duty )
{
    this->currentDuty = _duty;
    this->set( Duty, this->currentDuty );
}

void dji_2212::setPeriod( long _period )
{
    this->currentPeriod = _period;
    this->set( Period, this->currentPeriod );
}

void dji_2212::setRun( int _run )
{
    this->currentRun = _run;
    this->set( Run, this->currentRun );
}

void dji_2212::setPolarity( int _polarity )
{
    this->currentPolarity = _polarity;
    this->set( Polarity, this->currentPolarity );
}