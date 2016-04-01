/*
 * BBBQuadro.h
 *
 *  Created on: 6 Dec 2015
 *      Author: Michael Brookes
 */

#ifndef SRC_H_BBBQUADRO_H_
#define SRC_H_BBBQUADRO_H_

#include "BBBAnalogDevice.h"
#include "BBBLSM303DLHC.h"
#include "BBBPWMDevice.h"
#include "BBBL3GD20H.h"
#include "BBBConfiguration.h"
#include <cstdlib>
#include <cmath>
#include <pthread.h>
#include <iomanip>

class Quadro {

public:
    Quadro( );
    ~Quadro( );

    int AddAnalogDevices( );

    int AddI2CDevices( );

    int AddMotors( );

    void SetAllMotorsSpeed( int motor_speed );

    void SetAllMotorsPower( BBBPWMDevice::PWM_RunValues val );

    void SetMotorSpeed( int motor_index, int motor_speed );

    void SetMotorPower( int motor_index, BBBPWMDevice::PWM_RunValues val );

    int SpeedUpMotor( int motor_index );

    int SlowDownMotor( int motor_index );

    void ControlPitch( double DataDiff );

    void ControlRoll( double DataDiff );

    void ControlYaw( double DataDiff );

    void CheckSensorsForSense( );

    void SetDefaultTargetValuesBasedOnStaticAverages( );

    void Pitch( );

    void Roll( );

    void Yaw( );

    BBBPWMDevice propellerMotor[PROPELLER_COUNT];
    BBBAnalogDevice AnalogSensor[ANALOG_SENSOR_COUNT];
    BBBLSM303DLHC Accelerometer;
    BBBLSM303DLHC Magnetometer;
    BBBL3GD20H Gyroscope;
    BBBConfiguration Config;

protected:
    void *status;
};

template <class T>
T AnalyseData( T DataArray[MAX_DATASTORE], T TargetValue, T AllowedErrorValue ) {
    if( abs( DataArray[ ( MAX_DATASTORE - 1 ) ] - TargetValue ) > abs( AllowedErrorValue )) {
        for( int i = 0; i < MAX_DATASTORE; i++ ) {
            if( abs( DataArray[ i ] - TargetValue ) <= abs( AllowedErrorValue ))
                return 0;
            else if( i == ( MAX_DATASTORE - 1 )) {
                return abs( DataArray[ MAX_DATASTORE - 1 ] - TargetValue );
            }
        }
        return 0;
    }
    else
        return 0;
}

#endif /* SRC_H_BBBQUADRO_H_ */
