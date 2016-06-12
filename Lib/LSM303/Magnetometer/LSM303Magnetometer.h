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

#ifndef LSM303_ACCELEROMETER_LSM303Magnetometer_H
#define LSM303_ACCELEROMETER_LSM303Magnetometer_H


#include "../LSM303DLHC.h"
#include <bitset>
#include <math.h>

using namespace std;

#define MAX_DATASTORE 15

class LSM303Magnetometer : public LSM303DLHC {

public:

    LSM303Magnetometer( unsigned char _DeviceAddress = MAG_ADDRESS, int _BusId = 1 );

    void SetHeadingAverages( int iterations = 50 );

    double Heading( );

    double avgHeading;

    double HeadingDataStoredValues[MAX_DATASTORE];

private:

    void StartRecordingHeading( );

    void AddToHeadingDataStore( );

    static void* GetMagnetometerValues(  void *_ACCEL  );

    pthread_t LSM303UpdateValuesThread;

};

#endif //LSM303_ACCELEROMETER_LSM303Magnetometer_H
