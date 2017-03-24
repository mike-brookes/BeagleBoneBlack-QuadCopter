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

/**
 * quadroCopter constructor
 * Initialises motors
 * Sets up a new orientation object which contains all sensor data related to orientation.
 * Also sets up the PID controllers.
 * @params none
 */
quadroCopter::quadroCopter()
{

    /**
     * Create a new orientation object
     */
    myOrientation = new orientation();

    setStartupTargets();

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

/**
 * setStartupTargets()
 * This method is only called once - it determines what the quadcopter will do on startup.
 * @param none
 * @return none
 */
void quadroCopter::setStartupTargets()
{
    height.targetVal = 25.00;
    pitch.targetVal = 0.00;
    roll.targetVal = 0.00;
    //heading.targetVal = myOrientation->heading;
}

/**
 * maintainTargets()
 * Allows me to determine what targets should be met in each run.
 * @param none
 * @returns none
 */
void quadroCopter::maintainTargets()
{
    //maintainHeight( );
    maintainRoll( );
    maintainPitch();
    //maintainHeading();
}

/**
 * maintainHeight()
 * Allow the quadcopter to analyse current readings against target settings and adjust motors accordingly
 * @param none
 * @return none
 * TODO: implement this method
 */
void quadroCopter::maintainHeight()
{
//Plan here is to use Barometer, GPS and Sonic Sensor to maintain height
}

/**
 * maintainHeading()
 * Allow the quadcopter to analyse current readings against target settings and adjust motors accordingly
 * @param none
 * @return none
 * TODO: implement this method
 */
void quadroCopter::maintainHeading()
{
//Plan here is to use Magnetometer and GPS readings to maintain heading
}

/**
 * maintainRoll()
 * Allow the quadcopter to analyse current readings against target settings and adjust motors accordingly
 * @param none
 * @return none
 * TODO: handle potential errors.
 */
void quadroCopter::maintainRoll()
{

    double dutyIncreaseValue = rollPID->calculate( roll.targetVal, myOrientation->roll );

    if( myOrientation->roll < 0 ) {
        motor[ 0 ]->setTargetSpeed( long( motor[ 0 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        motor[ 1 ]->setTargetSpeed( long( motor[ 3 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        motor[ 2 ]->setTargetSpeed( long( motor[ 1 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        motor[ 3 ]->setTargetSpeed( long( motor[ 2 ]->currentDuty - dutyIncreaseValue ) ); //speed up
    }
    else {
        motor[ 0 ]->setTargetSpeed( long( motor[ 0 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        motor[ 1 ]->setTargetSpeed( long( motor[ 3 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        motor[ 2 ]->setTargetSpeed( long( motor[ 1 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        motor[ 3 ]->setTargetSpeed( long( motor[ 2 ]->currentDuty + dutyIncreaseValue ) ); //slow down
    }

//    printf( "   Current Roll : \033[22;36m%7.2f \033[0m \t Increase Value :  \033[22;36m%7.2f \033[0m\n",
//            myOrientation->roll, dutyIncreaseValue );

}

/**
 * maintainPitch()
 * Allow the quadcopter to analyse current readings against target settings and adjust motors accordingly
 * @param none
 * @return none
 * TODO: handle potential errors.
 */
void quadroCopter::maintainPitch()
{

    double dutyIncreaseValue = pitchPID->calculate( pitch.targetVal, myOrientation->pitch );

    if( myOrientation->pitch < 0 ) {
        motor[ 0 ]->setTargetSpeed( long( motor[ 0 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        motor[ 1 ]->setTargetSpeed( long( motor[ 1 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        motor[ 2 ]->setTargetSpeed( long( motor[ 2 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        motor[ 3 ]->setTargetSpeed( long( motor[ 3 ]->currentDuty - dutyIncreaseValue ) ); //speed up
    }
    else {
        motor[ 0 ]->setTargetSpeed( long( motor[ 0 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        motor[ 1 ]->setTargetSpeed( long( motor[ 1 ]->currentDuty - dutyIncreaseValue ) ); //speed up
        motor[ 2 ]->setTargetSpeed( long( motor[ 2 ]->currentDuty + dutyIncreaseValue ) ); //slow down
        motor[ 3 ]->setTargetSpeed( long( motor[ 3 ]->currentDuty + dutyIncreaseValue ) ); //slow down
    }

//    printf( "   Current Pitch : \033[22;36m%7.2f \033[0m \t Increase Value :  \033[22;36m%7.2f \033[0m\n",
//            myOrientation->pitch, dutyIncreaseValue );


}