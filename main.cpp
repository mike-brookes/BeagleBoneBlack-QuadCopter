//
//  main.cpp
//  QuadCopter
//
//  Created by Michael Brookes on 03/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#include "BBBConfiguration.h"
#include "Quadro.h"

int main( void ) {

    Quadro Quadro;

    if( Quadro.AddAnalogDevices( ) == 0 ) {
        cerr << "Error adding Analog Devices." << endl;
        exit( 1 );
    }

    if( Quadro.AddI2CDevices( ) == 0 ) {
        cerr << "Error adding I2C Devices." << endl;
        exit( 1 );
    }

    if( Quadro.AddMotors( ) == 0 ) {
        cerr << "Error adding Motors." << endl;
        exit( 1 );
    }

    Quadro.SetAllMotorsPower( BBBPWMDevice::PWM_RunValues::ON );
    Quadro.SetAllMotorsSpeed( MOTOR_SLOWSPEED );

    Quadro.Accelerometer.StartRecordingPitchAndRoll( );
    Quadro.Magnetometer.StartRecordingHeading( );
    Quadro.Gyroscope.Start( );
    Quadro.AnalogSensor[ 0 ].Start( );
    Quadro.Accelerometer.SetPitchAndRollAverages( 50 );
    Quadro.Magnetometer.SetHeadingAverages( 50 );
    Quadro.Gyroscope.SetAverages( 50 );
    Quadro.AnalogSensor[ 0 ].SetAverages( 50 );
    Quadro.SetDefaultTargetValuesBasedOnStaticAverages( );

    usleep( 20000 );

    while( 1 ) {
        Quadro.CheckSensorsForSense( );
        usleep( 5000 );
    }

}