//
// Created by Michael Brookes on 22/05/2016.
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

#ifndef ANALOGDEVICE_ANALOGOVERLAY_H
#define ANALOGDEVICE_ANALOGOVERLAY_H

#define ANALOG_MAX_BUF 1024

#include "../iDeviceOverlay.h"
#include "../../Exceptions/ExceptionAid.h"

namespace abAnalog {

    class AnalogOverlay : public abIDevice::iDeviceOverlay {

    public:
        AnalogOverlay( ) throw( AnalogSetupException& );

        struct OverlaySettings {
            const char *Overlay = "cape-bone-iio";
            const char *SearchFile = "AIN0";
            const char *FileType = "AIN";
            const char *HelperParentDir = "/sys/devices/ocp.3/";
            char HelperPath[ ANALOG_MAX_BUF ];
            bool OverlayLoaded;
        } Settings;

        char AnalogFilePath[ ANALOG_MAX_BUF ];

    private:

        void FindHelperDir( );

    };

}
#endif //ANALOGDEVICE_ANALOGOVERLAY_H
