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

#include "pinOverlay.h"
#include "../pwm/pwmDevice.h"

using namespace quadro::overlays;

pinOverlay::pinOverlay( pinBlocks _BLOCK, PWMPins _PIN ) throw( overlaySetupException& )
{

    this->setBlock( _BLOCK );
    this->setPin( _PIN );
    this->findPinDir();

    if ( !this->settings.overlayLoaded ) {
        snprintf( this->pinOverlayName,
                sizeof( this->pinOverlayName ),
                "%s%d_%d",
                this->settings.overlay,
                this->block,
                this->pin );
        this->settings.overlayLoaded = this->load( this->pinOverlayName );
    }

    if ( !this->settings.overlayLoaded ) {
        snprintf( this->errMessage, sizeof( this->errMessage ),
                "Fatal analogBase Error - Unable to load overlays : %s",
                this->settings.overlay );
        throw overlaySetupException( this->errMessage );
    }

}

void pinOverlay::setBlock( pinBlocks _BLOCK ) { this->block = _BLOCK; }

void pinOverlay::setPin( PWMPins _PIN ) { this->pin = _PIN; }

void pinOverlay::findPinDir()
{
    for ( int i = 1; i <= RETRIES; i++ ) {
        snprintf( this->pinOverlayDir,
                sizeof( this->pinOverlayDir ),
                "%s%s%d_%d.%d",
                this->settings.overlayDir,
                this->settings.searchFile,
                this->block,
                this->pin,
                i );

        if ( this->isLoaded( this->pinOverlayDir )) {
            this->settings.overlayLoaded = true;
            break;
        }

        else if ( i == RETRIES ) {
            this->settings.overlayLoaded = false;
        }
    }
}