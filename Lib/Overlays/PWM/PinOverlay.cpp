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

#include "PinOverlay.h"
#include "../../PWM/PWMDevice.h"

namespace abPWM {

    PinOverlay::PinOverlay( PinBlocks _BLOCK, PWMPins _PIN ) throw( PWMSetupException& ) {

        this->SetBlock( _BLOCK );
        this->SetPin( _PIN );
        this->FindPinDir( );

        if( ! this->Settings.OverlayLoaded ) {
            snprintf( this->PinOverlayName,
                      sizeof( this->PinOverlayName ),
                      "%s%d_%d",
                      this->Settings.Overlay,
                      this->Block,
                      this->Pin );
            this->Settings.OverlayLoaded = this->Load( this->PinOverlayName );
        }

        if( !this->Settings.OverlayLoaded ) {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ),
                      "Fatal Analog Error - Unable to load overlay : %s",
                      this->Settings.Overlay );
            throw PWMSetupException( this->ErrMessage );
        }

    }

    void PinOverlay::SetBlock( PinBlocks _BLOCK ) { this->Block = _BLOCK; }

    void PinOverlay::SetPin( PWMPins _PIN ) { this->Pin = _PIN; }

    void PinOverlay::FindPinDir( ) {
        for( int i = 1; i <= RETRIES; i++ ) {
            snprintf( this->PinOverlayDir,
                      sizeof( this->PinOverlayDir ),
                      "%s%s%d_%d.%d",
                      this->Settings.OverlayDir,
                      this->Settings.SearchFile,
                      this->Block,
                      this->Pin,
                      i );

            if( this->IsLoaded( this->PinOverlayDir ) ) {
                this->Settings.OverlayLoaded = true;
                break;
            }

            else if ( i == RETRIES ) {
                this->Settings.OverlayLoaded = false;
            }
        }
    }

}