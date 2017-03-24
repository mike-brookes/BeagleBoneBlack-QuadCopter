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

#include "quadroCopter.h"

int main()
{
    using namespace quadro;

    /**
    * @param startTime for timing iterations in the main thread loop.
    */
    int startTime;
    
    /**
    * Initialise a pointer for main quadroCopter object.
    */
    quadroCopter* AeroBot;
    
    /**
    * @param AeroBot new quadroCopter object.
    * The constructor in the quadroCopter :
    *  - Loads the device tree overlays
    *  - Exports the pins required by Motors and Sensors
    *  - Sets up the Analog pin
    *  - Initialises the Accelerometer, Magnetometer, Gyroscope, Motors and Sonic Sensor
    *  - Starts the threads that update values constantly.
    */
    AeroBot = new quadroCopter;

    /*
    * Program initialisation.
    * From here, I loop for the lifetime of the program - the idea is to have this as stream lined as possible to allow for ease of adding new features later.
    * This main thread simply reads current values and makes required changes to maintain set targets. i.e 0 degree pitch and roll to hover.
    */
    while ( 1 ) {
        /**
        * Record the start time for this iteration.
        */
        startTime = Timer::milliTimer();
        
        /**
        * Make motor adjustments to ensure the quadCopter is maintaining it's target values.
        */
        AeroBot->maintainTargets();
        
        /**
        * Waste of resources to loop too fast, wait here until data is refreshed based on the data rate.
        */
        while ( Timer::milliTimer() - startTime < ( DATA_RATE * 1000 )) {
            usleep( 100 );
        }
    }
}
