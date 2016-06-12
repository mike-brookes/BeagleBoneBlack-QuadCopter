//
// Created by Michael Brookes on 21/05/2016.
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

#include "iDeviceOverlay.h"

namespace abIDevice {

    iDeviceOverlay::iDeviceOverlay( ) {
    }

    bool iDeviceOverlay::IsLoaded( const char *SearchFile ) {
#ifdef DEBUG
        cout << "Searching for : " << SearchFile << endl;
#endif
        if( stat( SearchFile, &sb ) == 0 ) {
#ifdef DEBUG
            cout << "-- Found it..." << endl;
#endif
            return true;
        }
#ifdef DEBUG
        cout << "-- File not found..." << endl;
#endif
        return false;
    }

    bool iDeviceOverlay::Load( const char *Overlay ) {
        try {
#ifdef DEBUG
            cout << "-- Overlay not loaded yet, attempting to load : " << Overlay << endl;
#endif
            this->FileHandle = open( SLOTS_DIR, O_WRONLY );
            if( write( this->FileHandle, Overlay, 1024 ) > 0 ) {
                close( this->FileHandle );
#ifdef DEBUG
                cout << "--- Overlay loaded successfully." << endl;
#endif
                return true;
            }
            else {
#ifdef DEBUG
                cout << "--- Failed to load overlay." << endl;
#endif
                return false;
            }
        } catch( exception &e ) {
            cerr << "Exception : " << e.what( ) << endl;
        }
    }

}