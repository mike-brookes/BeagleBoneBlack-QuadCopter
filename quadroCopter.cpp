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

#include "quadroCopter.h"

using namespace quadro;
using namespace quadro::pwm;

quadroCopter::quadroCopter()
{

    myOrientation = new orientation();

    this->setStartupTargets();

    motor[ 0 ] = new dji_2212( pinBlocks::BLOCK_P9,
            PWMPins::PIN_42 );

    motor[ 1 ] = new dji_2212( pinBlocks::BLOCK_P8,
            PWMPins::PIN_19 );

    motor[ 2 ] = new dji_2212( pinBlocks::BLOCK_P9,
            PWMPins::PIN_14 );

    motor[ 3 ] = new dji_2212( pinBlocks::BLOCK_P9,
            PWMPins::PIN_22 );
    //add additional motors here, specifying block and pin accordingly.

    motor[ 0 ]->init();
    motor[ 1 ]->init();
    motor[ 2 ]->init();
    motor[ 3 ]->init();

    sleep( 1 ); //wait 1 second for readings to be updated.
    pitchPID = new PID( 0.2, 100, -100, 0.1, 0.01, 0.5 );
    rollPID = new PID( 0.2, 100, -100, 0.1, 0.01, 0.5 );

}

void quadroCopter::setStartupTargets()
{
    this->height.targetVal = 25.00;
    this->pitch.targetVal = 0.00;
    this->roll.targetVal = 0.00;
    //this->heading.targetVal = myOrientation->heading;
}

void quadroCopter::maintainTargets()
{
    //this->maintainHeight( );
    this->maintainRoll( );
    this->maintainPitch();
    //this->maintainHeading();
}

void quadroCopter::maintainHeight()
{

}

void quadroCopter::maintainRoll()
{

    double dutyIncreaseValue = pitchPID->calculate( this->roll.targetVal, this->myOrientation->roll );

    if( this->myOrientation->roll < 0 ) {
        this->motor[ 0 ]->setTargetSpeed( long( this->motor[ 0 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        this->motor[ 1 ]->setTargetSpeed( long( this->motor[ 3 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        this->motor[ 2 ]->setTargetSpeed( long( this->motor[ 1 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        this->motor[ 3 ]->setTargetSpeed( long( this->motor[ 2 ]->currentDuty - dutyIncreaseValue ) ); //speed up
    }
    else {
        this->motor[ 0 ]->setTargetSpeed( long( this->motor[ 0 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        this->motor[ 1 ]->setTargetSpeed( long( this->motor[ 3 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        this->motor[ 2 ]->setTargetSpeed( long( this->motor[ 1 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        this->motor[ 3 ]->setTargetSpeed( long( this->motor[ 2 ]->currentDuty + dutyIncreaseValue ) ); //slow down
    }

    printf( "   Current Roll : \033[22;36m%7.2f \033[0m \t Increase Value :  \033[22;36m%7.2f \033[0m\n",
            this->myOrientation->roll, dutyIncreaseValue );


}

void quadroCopter::maintainPitch()
{

    double dutyIncreaseValue = pitchPID->calculate( this->pitch.targetVal, this->myOrientation->pitch );

    if( this->myOrientation->pitch < 0 ) {
        this->motor[ 0 ]->setTargetSpeed( long( this->motor[ 0 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        this->motor[ 1 ]->setTargetSpeed( long( this->motor[ 1 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        this->motor[ 2 ]->setTargetSpeed( long( this->motor[ 2 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        this->motor[ 3 ]->setTargetSpeed( long( this->motor[ 3 ]->currentDuty - dutyIncreaseValue ) ); //speed up
    }
    else {
        this->motor[ 0 ]->setTargetSpeed( long( this->motor[ 0 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        this->motor[ 1 ]->setTargetSpeed( long( this->motor[ 1 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        this->motor[ 2 ]->setTargetSpeed( long( this->motor[ 2 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        this->motor[ 3 ]->setTargetSpeed( long( this->motor[ 3 ]->currentDuty + dutyIncreaseValue ) ); //slow down
    }

    printf( "   Current Pitch : \033[22;36m%7.2f \033[0m \t Increase Value :  \033[22;36m%7.2f \033[0m\n",
            this->myOrientation->pitch, dutyIncreaseValue );


}

void quadroCopter::maintainHeading()
{

}