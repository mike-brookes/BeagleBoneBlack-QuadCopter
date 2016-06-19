//
// Created by Michael Brookes on 27/05/2016.
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

#ifndef QUADRO_QUADRO_H
#define QUADRO_QUADRO_H
#define MOTOR_COUNT 4

#include "Lib/Motors/DJI_2212/DJI_2212.h"
#include "Lib/LVMaxSonarEZ/LVMaxSonarEZ.h"
#include "Lib/LSM303/Accelerometer/LSM303Accelerometer.h"
#include "Lib/LSM303/Magnetometer/LSM303Magnetometer.h"

class Quadro {

public:

    Quadro( );

    void MaintainTargets( );

    void SetStartupTargets( );

    struct Target {
        double TargetVal;
        double AllowableError;
    } Height, Roll, Pitch, Heading;

    enum STATE {
        NORMAL = 1,
        MOVING = 2,
        URGENT = 5,
        PANIC = 10
    } State;

    DJI_2212 *Motor[4];

    //using namespace abI2C;
    LSM303Accelerometer *Accelerometer;
    LSM303Magnetometer *Magnetometer;

    LVMaxSonarEZ *SonicSensor;
private:

    void MaintainHeight( );

    void MaintainRoll( );

    void MaintainPitch( );

    void MaintainHeading( );

    void SpeedUpMotors( );

    void SlowDownMotors( );

    void SpeedUpMotors( int[ 2 ] );

    void SlowDownMotors( int[ 2 ] );

    double ActionRequired( double[ 15 ], Target );

    double ConvertDoubleToPositive( double );

};

#endif //QUADRO_QUADRO_H
