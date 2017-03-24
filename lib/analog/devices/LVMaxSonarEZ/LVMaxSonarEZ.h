//
// Created by Michael Brookes on 26/05/2016.
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

#define MAX_OPERATING_HEIGHT 255
#define MIN_OPERATING_HEIGHT 6

#define EMERGENCY_HEIGHT_CM 23
#define EMERGENCY_HEIGHT_INCH 9

#define MAX_DATASTORE        15
#define SONIC_INCH_MODIFYER  9.8
#define SONIC_CM_MODIFYER    2.54
#define SONIC_DATATIMER      50000 //20HZ

namespace quadro {

    namespace analog {

        class LVMaxSonarEZ : public analogBase {
        public:

            LVMaxSonarEZ();

            void start();

            void stop();

            double distance();

            double avgDistance();

            double dataStoredValues[MAX_DATASTORE];

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
            string currentError;

            void setMode( deviceMode _mode );

            void setStatus( deviceStatus _status );

        private:

            static void* getValueAsInt( void* static_inst );

            int getReading();

            void setAverage( int iterations );

            void addToDataStore();

            double convertReadingToDistance( int _reading );

            int reading;
            double avgReading;

            pthread_t sonicReaderThread;
            int threadRet;
        };

    }
}
#endif //ANALOGDEVICE_LVMAXSONAREZ_H
