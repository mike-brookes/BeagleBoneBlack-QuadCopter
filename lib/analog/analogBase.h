//
// Created by Michael Brookes on 20/05/2016.
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

#ifndef ANALOGDEVICE_ANALOGDEVICE_H
#define ANALOGDEVICE_ANALOGDEVICE_H

#include "Exceptions/analogSetupException.h"
#include "Exceptions/analogRuntimeException.h"

#include "../Interfaces/IDevice.h"
#include "overlays/analogOverlay.h"

#include <unistd.h>
#include <fstream>
#include <string>

namespace quadro { //<! Main Quadro Namespace

    namespace analog {

        /*!
         * This class provides functionality for controlling analog devices on the beaglebone.
         * @implements IDevice
         */
        class analogBase : public IDevice {

        public:
            /*!
             * Public Destructor
             */
            ~analogBase();

            /*!
             * Public Constructor - sets the default port to 0 and attempts to initialise that device.
             * @throws analogSetupException
             */
            analogBase();

            /*!
             * enum for the available ports that can be used for Analog communication
             */
            enum analogPort {
                PORT0 = 0, //!< Analog Port 0 (P9, Pin 39)
                PORT1 = 1, //!< Analog Port 1 (P9, Pin 40)
                PORT2 = 2, //!< Analog Port 2 (P9, Pin 37)
                PORT3 = 3, //!< Analog Port 3 (P9, Pin 38)
                PORT4 = 4, //!< Analog Port 4 (P9, Pin 33)
                PORT5 = 5, //!< Analog Port 5 (P9, Pin 36)
                PORT6 = 6  //!< Analog Port 6 (P9, Pin 35)
            };

            /*!
             * getCurrentReading is the public method that returns the result from the private readDevice()
             * @return
             */
            int getCurrentReading();

            /*!
             * setDevicePort allows selection of an analog port (analogPort)
             * @param analogPort _AP
             */
            void setDevicePort( analogPort _AP );

        private:

            analogOverlay _analogOverlay; //!< Loads the overlays for Analog devices.

            analogPort devicePort; //!< Enum type analogPort

            ifstream deviceFile; //!< Streaming object

            string deviceFilePath; //!< File path

            string currentReading; //!< Last reading from the device

            /*!
             * readDevice allows us to read the value on a specified Analog Port.
             * @param _bufferSize
             * @return short
             */
            short readDevice( size_t _bufferSize );

            /*!
             * initDevice attempts to load the overlay
             * @throws analogSetupException
             */
            void initDevice() throw( analogSetupException& );

            /*!
             * setDeviceFilePath appends the helper file path with the analog file name and port.
             */
            void setDeviceFilePath();

            /*!
             * unused but a part of the interface
             * @todo use this function to check everything is setup correctly
             * @return int
             */
            int connectToDevice() throw( analogSetupException& ) { return 1; }

            /*!
             * unused but a part of the interface
             * @param _bufferSize
             * @return int
             */
            int writeToDevice( size_t _bufferSize ) throw( analogSetupException& ) { return 1; }

            /*!
             * This method checks the analog file can be opened in binary mode for reading.
             * @throws analogSetupException
             * @return int
             */
            int openDevice() throw( analogSetupException& );

        };

    }

}
#endif //ANALOGDEVICE_ANALOGDEVICE_H
