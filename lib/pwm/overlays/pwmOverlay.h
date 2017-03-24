//
// Created by Michael Brookes on 27/05/2016.
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

#ifndef BEAGLEBONE_PWM_PWMOVERLAY_H
#define BEAGLEBONE_PWM_PWMOVERLAY_H

#include "../../overlays/overlayBase.h"
#include "../exceptions/pwmSetupException.h"

namespace quadro {

    namespace pwm {

        class pwmOverlay : public overlays::overlayBase {
        public:

            pwmOverlay() throw( pwmSetupException& );

            struct overlaySettings {
                const char* overlay = "am33xx_pwm";
                const char* searchFile = "/sys/devices/ocp.3/48300000.epwmss/modalias";
                bool overlayLoaded;
            } settings;

        };

    }

}

#endif //BEAGLEBONE_PWM_PWMOVERLAY_H
