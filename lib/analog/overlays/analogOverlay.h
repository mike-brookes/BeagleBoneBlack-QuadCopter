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

/**
 * Overlay files are used by the beaglebone to expose a certain functionality, this class exposes the Analog Pins.
 *
 * @author Michael Brookes
 * @version 0.1.1
 */
#ifndef ANALOGDEVICE_ANALOGOVERLAY_H
#define ANALOGDEVICE_ANALOGOVERLAY_H

#define ANALOG_MAX_BUF 1024

#include "../../overlays/overlayBase.h"
#include "../Exceptions/analogSetupException.h"

namespace quadro {

    namespace analog {

        /**
         * This class loads the device tree overlay required to use Analog devices on the Beagle Bone
         * @implements iDeviceOverlay
         */
        class analogOverlay : public overlays::overlayBase {

        public:
            /**
             * Public access point for analogOverlay()
             * @throws analogSetupException
             */
            analogOverlay() throw( analogSetupException& );

            /**
             * This struct contains settings required to load the overlay
             */
            struct overlaySettings {
                const char* overlay = "cape-bone-iio"; //<! overlays Name
                const char* searchFile = "AIN0"; //<! Successful setup file name
                const char* fileType = "AIN"; //<! Successful setup folder name
                const char* helperParentDir = "/sys/devices/ocp.3/"; //<! Location for ananlog file structure
                char helperPath[ANALOG_MAX_BUF]; //<! Full path to analogBase helper file.
                bool overlayLoaded; //<! Boolean that holds the loaded value
            } settings;

            char analogFilePath[ANALOG_MAX_BUF]; //<! Full path to analogBase file

        private:

            /**
             * Function to locate the helper dir - this function is required because everytime the beaglebone reboots the
             * the helper dir has a new index appended to it's name i.e "helper.6"
             */
            void findHelperDir();

        };

    } //end namespace analog

} //end namespace quadro

#endif //ANALOGDEVICE_ANALOGOVERLAY_H
