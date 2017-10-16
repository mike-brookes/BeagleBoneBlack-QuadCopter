//
// Created by Michael Brookes on 29/05/2016.
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

#ifndef BEAGLEBONE_PWM_PINOVERLAY_H
#define BEAGLEBONE_PWM_PINOVERLAY_H

#include "overlayBase.h"
#include "exceptions/overlaySetupException.h"

#define MAX_BUF 255

namespace quadro {

    namespace overlays {

        class pinOverlay : public overlayBase {

        public:

            pinOverlay( pinBlocks _BLOCK, PWMPins _PIN ) throw( overlaySetupException& );

            struct overlaySettings {
                const char* overlay = "bone_pwm_P";
                const char* overlayDir = "/sys/devices/ocp.3/";
                const char* searchFile = "pwm_test_P";
                bool overlayLoaded{};
            } settings;

            char pinOverlayDir[MAX_BUF]; //!< Stores the PWM folder name

        private:
            void setBlock( pinBlocks _BLOCK );

            void setPin( PWMPins _PIN );

            void findPinDir();

            char pinOverlayName[24];

            PWMPins pin;
            pinBlocks block;

        };

    }

}

#endif //BEAGLEBONE_PWM_PINOVERLAY_H
