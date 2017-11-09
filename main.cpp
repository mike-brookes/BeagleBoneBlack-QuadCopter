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

//#include <chrono>
#include "quadroCopter.h"

int main()
{
    using namespace quadro;

    /**
    * @param startTime for timing iterations in the main thread loop.
    */
    //int startTime;

    /**
    * Initialise a pointer for main quadroCopter object.
    */
    quadroCopter* AeroBot;

    /**
    * @var AeroBot as new quadroCopter object.
    * The constructor in the quadroCopter :
    *  - Loads the device tree overlays
    *  - Exports the pins required by Motors and Sensors
    *  - Sets up the Analog pin
    *  - Initialises the Accelerometer, Magnetometer, Gyroscope, Motors and Sonic Sensor
    *  - Starts the threads that update values constantly.
    */
    try {
        AeroBot = new quadroCopter;
    }
    catch ( exceptions::fatalException& e ) {
        //print the error and exit immediately, running exit here should cause everything to destruct properly.
        cout << "Fatal Exception With Message : " << e.what() << endl;
        exit( 1 );
    }

    /**
    * Program initialisation...
    * From here, the program loops indefinitely - the idea is to have this as stream lined as possible to allow for ease of adding new features later.
    * This main thread simply reads current values and makes required changes to maintain set targets. i.e 0 degree pitch and roll to hover.
    */
    while ( true ) {

        //struct timespec start, finish;
        //double elapsed;

        //clock_gettime(CLOCK_MONOTONIC, &start);

        /**
        * Record the start time for this iteration.
        */
        //startTime = Timer::milliTimer();

        /**
        * Make motor adjustments to ensure the quadCopter is maintaining it's target values.
        */
        AeroBot->monitorSensorData();

        /**
        * Waste of resources to loop too fast, wait here until data is refreshed based on the data rate.
        */
//        while ( Timer::milliTimer() - startTime < ( AeroBot->myOrientation->DATA_RATE * 1000 )) {
//            usleep( 100 );
//        }

        //clock_gettime(CLOCK_MONOTONIC, &finish);

        //elapsed = (finish.tv_sec - start.tv_sec);
        //elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        //cout << "Elapsed Time = " << elapsed << endl;

    }
}
