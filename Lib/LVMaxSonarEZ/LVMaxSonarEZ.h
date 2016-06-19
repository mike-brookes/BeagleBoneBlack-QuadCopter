//
// Created by Michael Brookes on 26/05/2016.
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

#ifndef ANALOGDEVICE_LVMAXSONAREZ_H
#define ANALOGDEVICE_LVMAXSONAREZ_H

#include "../Analog/AnalogDevice.h"
#include <sstream>

#define MAX_OPERATING_HEIGHT 255
#define MIN_OPERATING_HEIGHT 6

#define EMERGENCY_HEIGHT_CM 23
#define EMERGENCY_HEIGHT_INCH 9

#define MAX_DATASTORE        15
#define SONIC_INCH_MODIFYER  9.8
#define SONIC_CM_MODIFYER    2.54
#define SONIC_DATATIMER      50000 //20HZ

using namespace std;

class LVMaxSonarEZ : public abAnalog::AnalogDevice {
public:

    LVMaxSonarEZ( );

    void Start( );
    void Stop( );

    double Distance( );
    double AvgDistance( );

    double DataStoredValues[ MAX_DATASTORE ];

    __useconds_t DataTimer = SONIC_DATATIMER;

    enum DeviceMode {
        Inches = 0,
        Cm = 1
    };

    enum DeviceStatus {
        On = 1,
        Off = 0,
        Error = 2
    };

    DeviceStatus CurrentStatus;
    DeviceMode CurrentMode;
    string CurrentError;

    void SetMode( DeviceMode _mode );
    void SetStatus( DeviceStatus _status );

private:

    static void *GetValueAsInt( void *static_inst );
    int GetReading( );
    void SetAverage( int iterations );
    void AddToDataStore( );
    double ConvertReadingToDistance( int _reading );

    int Reading;
    double AvgReading;

    pthread_t SonicReaderThread;
    int ThreadRet;
};


#endif //ANALOGDEVICE_LVMAXSONAREZ_H
