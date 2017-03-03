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

#include "pwmOverlay.h"

using namespace quadro::pwm;

pwmOverlay::pwmOverlay() throw( pwmSetupException& )
{

    this->settings.overlayLoaded = this->isLoaded( this->settings.searchFile );

    if ( !this->settings.overlayLoaded )
        this->settings.overlayLoaded = this->load( this->settings.overlay );

    if ( !this->settings.overlayLoaded ) {
        snprintf( this->errMessage, sizeof( this->errMessage ),
                "Fatal analogBase Error - Unable to load overlays : %s",
                this->settings.overlay );
        throw pwmSetupException( this->errMessage );
    }

}