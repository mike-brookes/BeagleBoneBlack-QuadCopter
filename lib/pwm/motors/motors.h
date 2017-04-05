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

#ifndef BEAGLEBONE_MOTOR_MOTORS_H
#define BEAGLEBONE_MOTOR_MOTORS_H

#include "../pwmDevice.h"
#include <string>

namespace quadro {

    namespace pwm {

        /**
         * Base class for adding functionality to the program for pwm motors
         */
        class motors : public pwmDevice {

        public:
            /**
             * default constructor
             */
            motors() { };

            /**
             * Constructor for initialising the motor with it's associated pinBlock and PWMPin
             *
             * @param pinBlocks _block
             * @param PWMPins _pin
             */
            motors( pinBlocks _block, PWMPins _pin );

            /**
             * Set the speed that you want the motor to achieve.
             *
             * @param _targetSpeed
             */
            void setTargetSpeed( long _targetSpeed );

            /**
             * Reverse the motors polarity using this method
             */
            void reversePolarity();

            /**
             * If the motor thread isn't running, this method will start the thread running which continuously attempts to maintain the
             * current motor speed as closely as possible to the target speed that has been set.
             *
             * @throws pwmSetupException
             */
            void start();

            /**
             * Run this method if you want to stop your motor from maintaining it's targets.
             * Please note, this will make the motor stop completely - if in mid air...well...catastrophe!
             */
            void stop();

            long currentDuty; //!< Storage for the current Duty value
            long currentPeriod; //!< Storage for the current Period value
            int currentRun; //!< Storage for the current Run value
            int currentPolarity; //!< Storage for the current Polarity value

        protected:

            /**
             * Every motor has it's own max PWM value, you can retrieve it here after it has been set using setMaxSpeed()
             *
             * @see setMaxSpeed()
             * @return long maxSpeed
             */
            long getMaxSpeed();

            /**
             * Every motor has it's own min PWM value, you can retrieve it here after it has been set using setMinSpeed()
             *
             * @see setMinSpeed()
             * @return long minSpeed
             */
            long getMinSpeed();

            /**
             * After testing you may find you need to change how fast the motors speed up and slow down, one way of accomplishing
             * this is to set the speed step to a larger number, you can get the current speed step here.
             *
             * @return int
             */
            int getSpeedStep();

            /**
             * Set your motors max speed here, it will probably be the lowest of the numbers as lower means faster.
             *
             * @param _maxSpeed
             */
            void setMaxSpeed( long _maxSpeed );

            /**
             * Set your motors min speed here, it will probably be the highest of the numbers as higher means slower.
             *
             * @param _minSpeed
             */
            void setMinSpeed( long _minSpeed );

            /**
             * Set the speed step increment here, this is how fast your motor will speed up - some testing may be required
             * to find the ideal setting.
             *
             * @param _speedStep
             */
            void setSpeedStep( int _speedStep );

        private:

            /**
             * The available motor status settings
             */
            enum status {
                On = 1, //!< Status On
                Off = 0, //!< Status Off
                Error = 3 //!< Status Error
            };

            /**
             * Polarity settings
             */
            enum polarity {
                Negative = 0, //!< Polarity is set to negative
                Positive = 1 //!< Polarity is set to positive
            };

            /**
             * Set the motor status as per the available status settings
             *
             * @param _status
             */
            void setStatus( status _status );

            /**
             * Increase the motor speed, if no speed step is specified this method will use the default value.
             *
             * @param _SpeedMod (defaults to 250)
             */
            void increaseSpeed( unsigned short _SpeedMod = 250 );

            /**
             * Decrease the motor speed, if no speed step is specified this method will use the default value.
             *
             * @param _SpeedMod (defaults to 250)
             */
            void decreaseSpeed( unsigned short _SpeedMod = 250 );

            /**
             * Main thread for each motor, its goal is to maintain the motors current speed in line with the set target speed.
             *
             * @return 0
             */
            static void* maintainTargetSpeed( void* );

            pthread_t threadHandle; //!< Thread Handle
            int threadRet; //!< Thread return value
            int speedStep; //!< Storage for the size of step taken when speeding up or slowing down motors

            long targetSpeed; //!< Storage for this motors target speed.
            long maxSpeed; //!< Storage for this motors max speed value.
            long minSpeed; //!< Storage for this motors min speed value.

            status Status; //!< Storage for this motors status.
        };

    }

}

#endif //BEAGLEBONE_MOTOR_MOTORS_H
