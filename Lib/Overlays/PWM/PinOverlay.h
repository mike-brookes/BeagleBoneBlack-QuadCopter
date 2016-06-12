//
// Created by Michael Brookes on 29/05/2016.
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

#ifndef BEAGLEBONE_PWM_PINOVERLAY_H
#define BEAGLEBONE_PWM_PINOVERLAY_H

#include "../iDeviceOverlay.h"
#include "../../Exceptions/ExceptionAid.h"

#define MAX_BUF 255

namespace abPWM {

    class PinOverlay : public abIDevice::iDeviceOverlay {

    public:

        PinOverlay( PinBlocks _BLOCK, PWMPins _PIN ) throw( PWMSetupException& );

        struct OverlaySettings {
            const char *Overlay = "bone_pwm_P";
            const char *OverlayDir = "/sys/devices/ocp.3/";
            const char *SearchFile = "pwm_test_P";
            bool OverlayLoaded;
        } Settings;

        char PinOverlayDir[MAX_BUF]; //!< Stores the PWM folder name

    private:
        void SetBlock( PinBlocks _BLOCK );
        void SetPin( PWMPins _PIN );

        void FindPinDir( );

        char PinOverlayName[24];

        PWMPins Pin;
        PinBlocks Block;

    };

}


#endif //BEAGLEBONE_PWM_PINOVERLAY_H
