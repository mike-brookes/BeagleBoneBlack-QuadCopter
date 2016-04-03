//
//  main.cpp
//  QuadCopter
//
//  Created by Michael Brookes on 03/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#include "BBBConfiguration.h"
#include "Quadro.h"
#include <iostream>
#include <fstream>
using namespace std;

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
sleep(5);
    Quadro.SetAllMotorsPower( BBBPWMDevice::PWM_RunValues::ON );
    Quadro.SetAllMotorsSpeed( 450000 );

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
        ofstream my_file;
        my_file.open ("accel_data.dat");
        my_file << "\t\tPitch\t\t=\t" << Quadro.Accelerometer.Pitch << "\t\t|\tRoll\t\t=\t" << Quadro.Accelerometer.Roll << endl;
        my_file << "\t\tTarget Pitch\t=\t" << Quadro.Config.General.TargetValues.Pitch << "\t\t|\tTarget Roll\t=\t" << Quadro.Config.General.TargetValues.Roll << endl;
        my_file.close();
        //if( Quadro.Accelerometer.Pitch > 45 || Quadro.Accelerometer.Pitch < -45 || Quadro.Accelerometer.Roll > 45 || Quadro.Accelerometer.Roll < -45 ) {
        //    cout << "Pitch or Roll went higher than 45 degrees - program exited." << endl;
        //    cout << "Pitch = " << Quadro.Accelerometer.Pitch << endl;
        //    cout << "Roll = " << Quadro.Accelerometer.Roll << endl;
        //    Quadro.SetAllMotorsSpeed( MOTOR_SLOWSPEED );
        //    usleep(10000);
        //    exit( 1 );
        //}
        usleep( 5000 );
    }

}