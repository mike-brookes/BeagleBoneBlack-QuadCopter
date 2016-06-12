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

#include "AnalogOverlay.h"

namespace abAnalog {

    AnalogOverlay::AnalogOverlay( ) throw( AnalogSetupException& ) {
        this->FindHelperDir( );
        if( !this->Settings.OverlayLoaded )
            this->Settings.OverlayLoaded = this->Load( this->Settings.Overlay );
        if( !this->Settings.OverlayLoaded ) {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ),
                      "Fatal Analog Error - Unable to load overlay : %s",
                      this->Settings.Overlay );
            throw AnalogSetupException( this->ErrMessage );
        }
    }

    void AnalogOverlay::FindHelperDir( ) {
        for( int i = 1; i <= RETRIES; i++ ) {
            snprintf( this->AnalogFilePath,
                      sizeof( this->AnalogFilePath ),
                      "%shelper.%d/%s",
                      this->Settings.HelperParentDir,
                      i,
                      this->Settings.SearchFile );

            if( this->IsLoaded( this->AnalogFilePath )) {
                this->Settings.OverlayLoaded = true;

                snprintf( this->Settings.HelperPath,
                          sizeof( this->Settings.HelperPath ),
                          "%shelper.%d/",
                          this->Settings.HelperParentDir,
                          i );
                break;
            }
            else if( i == RETRIES )
                this->Settings.OverlayLoaded = false;
        }
    }

}