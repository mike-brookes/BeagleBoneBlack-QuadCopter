//
// Created by Michael Brookes on 21/05/2016.
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

#include <iostream>
#include <exception>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>

#ifndef ANALOGDEVICE_OVERLAYS_H
#define ANALOGDEVICE_OVERLAYS_H

#define RETRIES 99
//#define DEBUG

#define SLOTS_DIR "/sys/devices/bone_capemgr.9/slots" //!< Full system path to SLOTS, used to export device tree overlays.

using namespace std;

namespace abIDevice {
    class iDeviceOverlay {
    public:
        iDeviceOverlay( );

        bool IsLoaded( const char *SearchFile );

        bool Load( const char *Overlay );

        int FileHandle;

        char ErrMessage[1024];

        struct stat sb;

        enum PinBlocks {
            BLOCK_P9 = 9, //!< P9 on your BBB | USB facing you, P9 is the pin block on the left hand side.
            BLOCK_P8 = 8, //!< P8 on your BBB | USB facing you, P8 is the pin block on the right hand side.
        };

        /**
         \brief PinNum refers to a exposed PWM Pin on your BBB, this enum can be expanded to include more if required.
         */
        enum PWMPins {
            PIN_42 = 42, //!< GPIO PWM Pin Number 42
            PIN_22 = 22, //!< GPIO PWM Pin Number 22
            PIN_19 = 19, //!< GPIO PWM Pin Number 19
            PIN_14 = 14, //!< GPIO PWM Pin Number 14
        };

    };
}

#endif //ANALOGDEVICE_OVERLAYS_H
