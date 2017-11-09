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
        :pwmDevice( _block, _pin ) { };

void motors::setTargetSpeed( long targetSpeed_ )
{
    if ( targetSpeed_ > minSpeed ) {
        targetSpeed = minSpeed;
    }
    else if ( targetSpeed_ < maxSpeed ) {
        targetSpeed = maxSpeed;
    }
    else {
        targetSpeed = targetSpeed_;
    }
    
    setDuty( targetSpeed );
}

void motors::reversePolarity()
{
    currentPolarity = ( currentPolarity == polarity::Positive ) ? polarity::Negative
                                                                : polarity::Positive;
    set( Polarity, currentPolarity );
}

void motors::setStatus( status status_ )
{
    Status = status_;
    set( Run, ( Status != 3 ) ? status_ : 0 );
}

//void* motors::maintainTargetSpeed( void* inst_ )
//{
//    auto* motorInst = ( motors* ) inst_;
//    while ( motorInst->currentRun == status::On ) {
//        motorInst->setDuty( motorInst->targetSpeed );
//    }
//    motorInst->stop();
//    return nullptr;
//}

void motors::start()
{
    if ( Status == status::Off ) {
        //threadRet = pthread_create( &threadHandle, nullptr, motors::maintainTargetSpeed, this );

//        if ( threadRet == 0 )
        setStatus( status::On );
//        else {
//            setStatus( status::Error );
//            if ( threadRet == EAGAIN )
//                throw pwmSetupException( "Unable to create thread : Resource Limit Reached." );
//            else
//                throw pwmSetupException( "Unable to create thread : Unknown Error Occurred." );
//        }
    }
}

void motors::stop()
{
    if ( Status != status::Off ) {
        setStatus( status::Off );
        pthread_exit( &threadHandle );
    }
}

void motors::setDuty( long duty_ )
{
    currentDuty = duty_;
    set( Duty, currentDuty );
}

void motors::setPeriod( long period_ )
{
    currentPeriod = period_;
    set( Period, currentPeriod );
}

void motors::setPeriodByHz( int hz_ )
{
    currentPeriod = ( unsigned long ) ( 1e9 / hz_ );
    set( Period, currentPeriod );
}

void motors::setRun( int run_ )
{
    currentRun = run_;
    set( Run, currentRun );
}

void motors::setPolarity( int polarity_ )
{
    currentPolarity = polarity_;
    set( Polarity, currentPolarity );
}

void motors::setMinSpeed( long minSpeed_ )
{
    minSpeed = minSpeed_;
}

void motors::setMaxSpeed( long maxSpeed_ )
{
    maxSpeed = maxSpeed_;
}