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

#include "motors.h"

using namespace quadro::pwm;

motors::motors(
        pinBlocks _block,
        PWMPins _pin
)
        :pwmDevice( _block, _pin )
{
    targetSpeed = getMinSpeed();
};

void motors::setTargetSpeed( long _targetSpeed )
{
    if( _targetSpeed < getMaxSpeed() ) {
        targetSpeed = getMaxSpeed();
    }
    else if( _targetSpeed > getMinSpeed() ) {
        targetSpeed = getMinSpeed();
    }
    else {
        targetSpeed = _targetSpeed;
    }
}

void motors::increaseSpeed( unsigned short _speedMod )
{
    currentDuty -= _speedMod;
    set( Duty, ( currentDuty ));
}

void motors::decreaseSpeed( unsigned short _speedMod )
{
    currentDuty += _speedMod;
    set( Duty, ( currentDuty ));
}

void motors::reversePolarity()
{
    currentPolarity = ( currentPolarity == polarity::Positive ) ? polarity::Negative
                                                                : polarity::Positive;
    set( Polarity, currentPolarity );
}

void motors::setStatus( status _status )
{
    Status = _status;
    set( Run, ( Status != 3 ) ? _status : 0 );
}

void* motors::maintainTargetSpeed( void* _inst )
{
    motors* motorInst = ( motors* ) _inst;
    while ( motorInst->currentRun == status::On ) {
        if ( motorInst->currentDuty > motorInst->targetSpeed )
            motorInst->increaseSpeed();
        else
            motorInst->decreaseSpeed();
    }
    motorInst->stop();
}

void motors::start()
{
    if ( Status == status::Off ) {
        threadRet = pthread_create( &threadHandle, NULL, motors::maintainTargetSpeed, this );

        if ( threadRet == 0 )
            setStatus( status::On );
        else {
            setStatus( status::Error );
            if ( threadRet == EAGAIN )
                throw pwmSetupException( "Unable to create thread : Resource Limit Reached." );
            else
                throw pwmSetupException( "Unable to create thread : Unknown Error Occurred." );
        }
    }
}

void motors::stop()
{
    if ( Status != status::Off ) {
        setStatus( status::Off );
        pthread_exit( &threadHandle );
    }
}

long motors::getMaxSpeed()
{
    return maxSpeed;
}

long motors::getMinSpeed()
{
    return minSpeed;
}

int motors::getSpeedStep()
{
    return speedStep;
}

void motors::setMinSpeed( long _minSpeed )
{
    minSpeed = _minSpeed;
}

void motors::setMaxSpeed( long _maxSpeed )
{
    maxSpeed = _maxSpeed;
}

void motors::setSpeedStep( int _speedStep )
{
    speedStep = _speedStep;
}