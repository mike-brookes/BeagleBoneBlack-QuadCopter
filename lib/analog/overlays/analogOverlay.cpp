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

#include "analogOverlay.h"

using namespace quadro::analog;

analogOverlay::analogOverlay() throw( analogSetupException& )
{
    this->findHelperDir();
    if ( !this->settings.overlayLoaded )
        this->settings.overlayLoaded = this->load( this->settings.overlay );
    if ( !this->settings.overlayLoaded ) {
        snprintf( this->errMessage, sizeof( this->errMessage ),
                "Fatal analogBase Error - Unable to load overlays : %s",
                this->settings.overlay );
        throw analogSetupException( this->errMessage );
    }
}

void analogOverlay::findHelperDir()
{
    for ( int i = 1; i <= RETRIES; i++ ) {
        snprintf( this->analogFilePath,
                sizeof( this->analogFilePath ),
                "%shelper.%d/%s",
                this->settings.helperParentDir,
                i,
                this->settings.searchFile );

        if ( this->isLoaded( this->analogFilePath )) {
            this->settings.overlayLoaded = true;

            snprintf( this->settings.helperPath,
                    sizeof( this->settings.helperPath ),
                    "%shelper.%d/",
                    this->settings.helperParentDir,
                    i );
            break;
        }
        else if ( i == RETRIES )
            this->settings.overlayLoaded = false;
    }
}