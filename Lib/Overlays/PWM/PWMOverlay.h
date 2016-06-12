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

#ifndef BEAGLEBONE_PWM_PWMOVERLAY_H
#define BEAGLEBONE_PWM_PWMOVERLAY_H

#include "../iDeviceOverlay.h"
#include "../../Exceptions/ExceptionAid.h"

namespace abPWM {

    class PWMOverlay : public abIDevice::iDeviceOverlay {
    public:

        PWMOverlay( ) throw( PWMSetupException& );

        struct OverlaySettings {
            const char *Overlay = "am33xx_pwm";
            const char *SearchFile = "/sys/devices/ocp.3/48300000.epwmss/modalias";
            bool OverlayLoaded;
        } Settings;

    };

}

#endif //BEAGLEBONE_PWM_PWMOVERLAY_H
