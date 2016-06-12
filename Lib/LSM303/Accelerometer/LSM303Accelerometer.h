//
// Created by Michael Brookes on 05/05/2016.
//

#ifndef LSM303_ACCELEROMETER_LSM303ACCELEROMETER_H
#define LSM303_ACCELEROMETER_LSM303ACCELEROMETER_H


#include "../LSM303DLHC.h"
#include <bitset>
#include <math.h>

using namespace std;

#define MAX_DATASTORE 15

class LSM303Accelerometer : public LSM303DLHC {

public:

    LSM303Accelerometer( unsigned char _DeviceAddress = ACCEL_ADDRESS, int _BusId = 1 );

    void SetPitchAndRollAverages( int iterations = 50 );

    double Roll( );

    double Pitch( );

    double avgPitch;

    double avgRoll;

    double PitchDataStoredValues[MAX_DATASTORE];

    double RollDataStoredValues[MAX_DATASTORE];

private:

    void StartRecordingPitchAndRoll( );

    void AddToPitchAndRollDataStore( );

    static void* GetAccelerometerValues(  void *_ACCEL  );

    pthread_t LSM303UpdateValuesThread;
};

#endif //LSM303_ACCELEROMETER_LSM303ACCELEROMETER_H
