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

#include "orientation.h"

using namespace quadro;

orientation::orientation()
{
    try {
        //Create a new LVMaxSonarEZ object
        sonicSensor = new LVMaxSonarEZ();

        //Set the height calculation mode to Centimetres.
        sonicSensor->setMode( LVMaxSonarEZ::deviceMode::Cm );

        //Start the sensors main thread, runs while the sensor is on.
        sonicSensor->start();

        //Create a new LSM303Accelerometer, this sensors thread is initiated in the constructor
        accelerometer = new LSM303Accelerometer();

        //Start the sensors main thread, runs while the sensor is on.
        accelerometer->start();

        //Create a new LSM303Magnetometer, this sensors thread is initiated in the constructor
        magnetometer = new LSM303Magnetometer();

        //Start the sensors main thread, runs while the sensor is on.
        magnetometer->start();

        //Create a new L3GD20H, this sensors thread is initiated in the constructor
        gyroscope = new L3GD20H();

        //Start the sensors main thread, runs while the sensor is on.
        gyroscope->start();
    }
    catch ( analog::analogSetupException& e ) {
        throw setupException( analog::STARTUP_FAILURE + " Details : " + e.what());
    }
    catch ( i2c::i2cSetupException& e ) {
        throw setupException( i2c::STARTUP_FAILURE + " Details : " + e.what());
    }

    //Set up a new PID object for Pitch
    pitchPID = new PID( 0.1, 40, -40, 1.3, 0.05, 15 );

    //Set up a new PID object for Roll
    rollPID = new PID( 0.1, 250, -250, 1.3, 0, 15 );

    //select the Kalman filter method by default, this can be altered using the public setDataFilterSelection method.
    setDataFilterSelection( KALMAN );

}

orientation::~orientation() noexcept
{
    sonicSensor->stop();
    accelerometer->stop( accelerometer->threadHandle );
    magnetometer->stop( magnetometer->threadHandle );
    gyroscope->stop( gyroscope->threadHandle );
}

void orientation::setValues()
{

    //Complimentary filter method
    if ( dataFilterSelection == COMPLIMENTARY ) {
        runComplimentaryCalculations();
    }

    //Kalman Filter Method.
    if ( dataFilterSelection == KALMAN ) {
        runKalmanCalculations();
    }

#ifdef STORE_DATA
    dataStorageFile.open( position->dataStorageFileName );
    if ( dataStorageFile.is_open()) {
        dataStorageFile << position->pitch << "," << position->roll;
        dataStorageFile.close();
    }
#endif

}

void orientation::runKalmanCalculations()
{
    pitch = float( kalmanPitch.getAngle( accelerometer->pitch, gyroscope->angle.x, DATA_RATE ));
    roll = float( kalmanRoll.getAngle( accelerometer->roll, gyroscope->angle.y, DATA_RATE ));

    yaw = 0;
    height = 0;
    baroHeight = 0;
    sonicHeight = 0;
    heading = 0;
}

void orientation::runComplimentaryCalculations()
{
    float CFANGLEX = 0;
    float CFANGLEY = 0;
    pitch = COMPLIMENTARY_FILTER_TUNING * ( CFANGLEX + gyroscope->angle.x * DATA_RATE )
            + ( 1 - COMPLIMENTARY_FILTER_TUNING ) * accelerometer->pitch;
    roll = COMPLIMENTARY_FILTER_TUNING * ( CFANGLEY + gyroscope->angle.y * DATA_RATE )
            + ( 1 - COMPLIMENTARY_FILTER_TUNING ) * accelerometer->roll;

    yaw = 0;
    height = 0;
    baroHeight = 0;
    sonicHeight = 0;
    heading = 0;
}

void orientation::setDataFilterSelection( int _dataFilter )
{
    dataFilterSelection = _dataFilter;
}