//
// Created by Michael Brookes on 20/05/2016.
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

#ifndef ANALOGDEVICE_ANALOGDEVICE_H
#define ANALOGDEVICE_ANALOGDEVICE_H

#include "../Device/IDevice.h"
#include "../Exceptions/ExceptionAid.h"
#include "../Overlays/Analog/AnalogOverlay.h"

#include <unistd.h>
#include <fstream>
#include <string>

namespace abAnalog {

    using namespace std;

    class AnalogDevice : public abIDevice::IDevice {

    public:
        /**
         \fn Public Destructor
         */
        ~AnalogDevice( );

        /**
         \fn Public Constructor
         */
        AnalogDevice( );

        enum AnalogPort {
            PORT0 = 0, //!< Analog Port 0 (P9, Pin 39)
            PORT1 = 1, //!< Analog Port 1 (P9, Pin 40)
            PORT2 = 2, //!< Analog Port 2 (P9, Pin 37)
            PORT3 = 3, //!< Analog Port 3 (P9, Pin 38)
            PORT4 = 4, //!< Analog Port 4 (P9, Pin 33)
            PORT5 = 5, //!< Analog Port 5 (P9, Pin 36)
            PORT6 = 6  //!< Analog Port 6 (P9, Pin 35)
        };

        short ReadDevice( size_t _BufferSize );

        int GetCurrentReading( );

        void SetDevicePort( AnalogPort _AP );

    private:

        AnalogOverlay _AnalogOverlay;

        AnalogPort DevicePort;

        ifstream DeviceFile;

        string DeviceFilePath;

        string CurrentReading;

        string EmptyString;

        void InitDevice( ) throw( AnalogSetupException& );

        void SetDeviceFilePath( );

        int ConnectToDevice( ) throw( AnalogSetupException& ) { return 1; }

        int WriteToDevice( size_t _BufferSize ) throw( AnalogSetupException& ) { return 1; }

        int OpenDevice( ) throw( AnalogSetupException& );

        int FileHandle;

    };

}
#endif //ANALOGDEVICE_ANALOGDEVICE_H
