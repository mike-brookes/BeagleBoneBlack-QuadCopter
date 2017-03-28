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

#define MAX_OPERATING_HEIGHT_IN_INCES   255
#define MIN_OPERATING_HEIGHT_IN_INCES   6

#define EMERGENCY_HEIGHT_CM             23
#define EMERGENCY_HEIGHT_INCH           9

#define SONIC_INCH_MODIFYER             9.8
#define SONIC_CM_MODIFYER               2.54
#define SONIC_DATATIMER                 50000 //20HZ

namespace quadro {

    namespace analog {

        class LVMaxSonarEZ : public analogBase {
        public:

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
            void stop();

            double distance();

            __useconds_t dataTimer = SONIC_DATATIMER;

            enum deviceMode {
                Inches = 0,
                Cm = 1
            };

            enum deviceStatus {
                On = 1,
                Off = 0,
                Error = 2
            };

            deviceStatus currentStatus;
            deviceMode currentMode;

            void setMode( deviceMode _mode );

            int getStatus();

            void setStatus( deviceStatus _status );

        private:

            static void* getValueAsInt( void* static_inst );

            int getReading();

            double convertReadingToDistance( int _reading );

            int reading;

            pthread_t sonicReaderThread;

            int threadRet;
        };

    }
}
#endif //ANALOGDEVICE_LVMAXSONAREZ_H
