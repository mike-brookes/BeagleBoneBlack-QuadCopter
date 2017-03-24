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

/**
    This class handles some of the low level operations required for controlling PWM motors.
    It has been designed to be extended by a class that sets your specific motor type requirements.

    @namespace abPWM
    @author Michael Brookes

*/

#include "motors.h"

using namespace quadro::pwm;

motors::motors(
        pinBlocks _block,
        PWMPins _pin
)
        :pwmDevice( _block, _pin )
{
    this->targetSpeed = this->getMinSpeed();
};

void motors::setTargetSpeed( long _targetSpeed ) throw( long )
{
    this->targetSpeed = _targetSpeed;
    try {
        if ( this->targetSpeed < this->getMaxSpeed())
            throw ( this->getMaxSpeed());
        else if ( this->targetSpeed > this->getMinSpeed())
            throw ( this->getMinSpeed());
    }
    catch ( long& e ) {
        this->setTargetSpeed( e );
    }
}

void motors::increaseSpeed( unsigned short _speedMod )
{
    this->currentDuty -= _speedMod;
    this->set( Duty, ( this->currentDuty ));
}

void motors::decreaseSpeed( unsigned short _speedMod )
{
    this->currentDuty += _speedMod;
    this->set( Duty, ( this->currentDuty ));
}

void motors::reversePolarity()
{
    this->currentPolarity = ( this->currentPolarity == polarity::Positive ) ? polarity::Negative
                                                                            : polarity::Positive;
    this->set( Polarity, this->currentPolarity );
}

void motors::setStatus( status _status )
{
    this->Status = _status;
    this->set( Run, ( this->Status != 3 ) ? _status : 0 );
}

void* motors::maintainTargetSpeed( void* _inst )
{
    motors* MotorInst = ( motors* ) _inst;
    while ( MotorInst->currentRun == status::On ) {
        if ( MotorInst->currentDuty > MotorInst->targetSpeed )
            MotorInst->increaseSpeed();
        else
            MotorInst->decreaseSpeed();
    }
    MotorInst->Stop();
}

void motors::Start()
{
    if ( this->Status == status::Off ) {
        this->threadRet = pthread_create( &this->motorSpeedThread, NULL, motors::maintainTargetSpeed, this );

        if ( this->threadRet == 0 )
            this->setStatus( status::On );
        else {
            this->setStatus( status::Error );
            if ( this->threadRet == EAGAIN )
                throw ( "Unable to create thread : Resource Limit Reached." );
            else
                throw ( "Unable to create thread : Unknown Error Occurred." );
        }
    }
}

void motors::Stop()
{
    cout << "Stopping motor" << endl;
    if ( this->Status != status::Off ) {
        this->setStatus( status::Off );
        pthread_exit( &this->motorSpeedThread );
    }
}

long motors::getMaxSpeed()
{
    return this->maxSpeed;
}

long motors::getMinSpeed()
{
    return this->minSpeed;
}

int motors::getSpeedStep()
{
    return this->speedStep;
}

void motors::setMinSpeed( long _minSpeed )
{
    this->minSpeed = _minSpeed;
}

void motors::setMaxSpeed( long _maxSpeed )
{
    this->maxSpeed = _maxSpeed;
}

void motors::setSpeedStep( int _speedStep )
{
    this->speedStep = _speedStep;
}