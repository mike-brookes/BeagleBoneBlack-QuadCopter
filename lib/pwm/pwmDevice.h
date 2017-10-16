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

#ifndef BEAGLEBONE_PWM_PWMDEVICE_H
#define BEAGLEBONE_PWM_PWMDEVICE_H

#include <fstream>
#include <string>
#include <exception>
#include "../interfaces/IDevice.h"
#include "../overlays/pinOverlay.h"
#include "./overlays/pwmOverlay.h"

namespace quadro {

    using namespace overlays;

    namespace pwm {

        /**
         * Base class for PWM devices
         * @uses IDevice, pwmOverlay
         */
        class pwmDevice : public IDevice, pwmOverlay {

        public:

            /**
             * Base class for PWM devices
             * @uses IDevice, pwmOverlay
             */
            pwmDevice() = default;;

            /**
             * Alternative constructor, setting the pins on setup.
             *
             * @throws pwmSetupException
             * @param pinBlocks _block
             * @param PWNPins _pin
             */
            pwmDevice( pinBlocks _block, PWMPins _pin ) throw( pwmSetupException& );

            /**
             * This is a list of types allowed when accessing PWM Values.
             */
            enum valType {
                Run, //!< Run Value Type
                Duty, //!< Duty Value Type
                Period, //!< Period Value Type
                Polarity, //!< Polarity Value Type
                Power_Control, //!< Power_Control Value Type
                Power_RunTime_Active, //!< Power_RunTime_Active Value Type
                Power_RunTime_Suspended, //!< Power_RunTime_Suspended Value Type
                None
            };

            pinBlocks blockNum{}; //!< stores the PWM device block num
            PWMPins pinNum{}; //!< stores the PWM device pin num

            string powerControlStr; //!< stores the current power setting string

            /**
             * Use this method to get a pwm value as specified from valType
             *
             * @param _vt
             * @return
             */
            long get( valType _vt );

            /**
             * Use this method to set a pwm value as specified by valType
             *
             * @param _vt
             * @param _val
             */
            void set( valType _vt, long _val );

            /**
             * Set PWM Pin num from available PWMPins
             *
             * @param _pin
             */
            void setPinNum( PWMPins _pin );

            /**
             * Sets the pwm block number - on the beaglebone black this will be 8 or 9 only
             *
             * @param pinBlocks _block
             */
            void setBlockNum( pinBlocks _block );

        private:

            valType VT = valType::None; //!< Container for the val type

            /**
             * Reads the file of valType (enum) e.g duty
             *
             * @param valType
             */
            void readDevice( valType _vt );

            /**
             * Read _bufferSize amount of bytes from the device file
             *
             * @param _bufferSize
             * @return short
             */
            short readDevice( size_t _bufferSize ) override;

            /**
             * Runs an init check to make sure the applicable pwm overlay has been loaded.
             *
             * @throws pwmSetupException
             */
            void initDevice() throw( pwmSetupException& ) override;

            /**
             * TODO: Implement a connection test functionality here.
             * @return
             */
            int connectToDevice() override { return 1; }

            /**
             * Write a value to the PWM file
             *
             * @throws pwmSetupException
             * @param _bufferSize
             * @return int
             */
            int writeToDevice( size_t _bufferSize ) throw( pwmSetupException& ) override;

            /**
             * This function is called when setting a pwm value, the valType is the file you need to write to : e.g duty
             * Only values from the valType Enum will be allowed.
             *
             * @param _vt a member of valType
             * @param _val
             */
            void writeToDevice( valType _vt, long _val ) throw( pwmSetupException& );

            /**
             * Open the device's duty file unless otherwise specified
             *
             * @thows pwmSetupException
             * @return int
             */
            int openDevice() throw( pwmSetupException& ) override;

            /**
             *
             * @return long
             */
            long getCurrentReading( valType _vt );

            /**
             * Returns the current file name full path
             *
             * @return char full path to the specified file
             */
            char* getFilePath();

            /**
             * Return the filepath of the type specified with valType
             *
             * @param _vt
             */
            void setValType( valType _vt );

            /**
             * Set the value to be written
             *
             * @param _val
             */
            void setWriteVal( long _val );

            /**
             * Set all file paths now for ease of use.
             */
            void setFilePaths();

            long val2Write{}; //!< stores the value to be written

            ifstream PWMFile; //!< File stream handle

            string currentReading; //!< latest reading from a file

            overlays::pinOverlay* _pinOverlay{}; //!< setup a pointer to the pinOverlay class

            char dutyPath[50]{}; //!< storage for the duty file path

            char periodPath[50]{}; //!< storage for the period file path

            char runPath[50]{}; //!< storage for the run file path

            char polarityPath[50]{}; //!< storage for the polarity file path

            char powerControlPath[100]{}; //!< storage for the power control file path

            char powerRunTime_ActivePath[100]{}; //!< storage for the power run time active file path

            char powerRunTime_SuspendedPath[100]{}; //!< storage for the power run time suspended file path

        };

    }

}

#endif //BEAGLEBONE_PWM_PWMDEVICE_H
