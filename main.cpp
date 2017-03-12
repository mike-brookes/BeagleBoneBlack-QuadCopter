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

#include "quadroCopter.h"

int main()
{
    using namespace quadro;

    quadroCopter* AeroBot;
    AeroBot = new quadroCopter;

    int startTime;

    while ( 1 ) {
        startTime = Timer::milliTimer();
        AeroBot->maintainTargets();
        while ( Timer::milliTimer() - startTime < ( DATA_RATE * 1000 )) {
            usleep( 100 );
        }
    }
}