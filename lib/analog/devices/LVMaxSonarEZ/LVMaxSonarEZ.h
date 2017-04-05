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

#ifndef ANALOGDEVICE_LVMAXSONAREZ_H
#define ANALOGDEVICE_LVMAXSONAREZ_H

#include "../../analogBase.h"
#include <sstream>

namespace quadro {

    namespace analog {

        class LVMaxSonarEZ : public analogBase {

        public:

            const float SONIC_INCH_MODIFIER = 9.8f; //!< @var Used in calculating the current height in Inches
            const float SONIC_CM_MODIFIER = 2.54f; //!< @var Used in calculating the current height in Centimetres

            static const unsigned int SONIC_DATATIMER = 50000; //!< @var Used to time each iteration of the thread gathering sensor data (20hz)

            const int MAX_OPERATING_HEIGHT_IN_INCES = 255; //!< @var The furthest distance that can be read.
            const int MIN_OPERATING_HEIGHT_IN_INCES = 6; //!< @var The closest distance that can be read.

            /**
             * Class constructor - by default this constructor sets the height mode to CM and the devices status to off.
             * @see start() for initialising the sensors main thread.
             */
            LVMaxSonarEZ();

            /**
             * start() - Allows the independent control to start the thread that updates the Sonic Sensor readings.
             * @param none
             * @throws analogSetupException
             * @returns int deviceStatus : 1 = on, 0 = off or 2 = error
             */
            int start();

            /**
             * stop() - Allows the independent control to stop the current thread.
             * @param none
             * @throws analogRuntimeException
             * @returns enum deviceStatus : 1 = on, 0 = off or 2 = error
             */
            int stop();

            /**
             * This method provides access to the private calculate distance result.
             *
             * @return double
             */
            double getDistance();

            //!< Storage of the timer for the sensors main thread, based on the data rate of the sensor
            __useconds_t dataTimer = SONIC_DATATIMER;

            /*!
             * Select a deviceMode, changes the returned distance value to the selected type.
             */
            enum deviceMode {
                Inches = 0,
                Cm = 1
            };

            /*!
             * Stores the current deviceStatus for easy reference fro other objects
             */
            enum deviceStatus {
                On = 1, //!< Status On (thread is active)
                Off = 0, //!< Status Off (thread is disabled)
                Error = 2 //!< Status Error (thread is disabled)
            };

            //!< @var currentStatus holds a deviceStatus value
            deviceStatus currentStatus;

            //!< @var currentMode holds a deviceMode value
            deviceMode currentMode;

            /*!
             * setMode allows the mode of the sensor to be changed to one of the values set in deviceModes
             *
             * @param _mode
             */
            void setMode( deviceMode _mode );

            /*!
             * getStatus returns the current status of the sensor
             *
             * @return int
             */
            int getStatus();

            /*!
             * setStatus allows the status of the sensor to be changed to one of the values set in deviceStatus
             *
             * @param _status
             */
            void setStatus( deviceStatus _status );

            pthread_t threadHandle; //!< @var pthread_t handle

        private:

            /*!
             * Used in the pthread_create call, starts the thread loop for updating sensor values.
             *
             * @param static_inst
             */
            static void* runMainSensorUpdateThread( void* static_inst );

            /*!
             * This method does the math to convert the sensor reading to a distance stored as a double
             *
             * @param _reading
             * @return double
             */
            double convertReadingToDistance( int _reading );

            int reading; //!< @var contains the current sensor raw value, updated in the thread loop

            int threadRet; //!< @var thread return value
        };

    }
}
#endif //ANALOGDEVICE_LVMAXSONAREZ_H
