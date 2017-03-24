//
// Created by Michael Brookes on 21/05/2016.
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

#include "overlayBase.h"

using namespace quadro::overlays;

overlayBase::overlayBase()
{
}

bool overlayBase::isLoaded( const char* searchFile )
{
#ifdef DEBUG
    cout << "Searching for : " << searchFile << endl;
#endif
    if ( stat( searchFile, &sb ) == 0 ) {
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

bool overlayBase::load( const char* Overlay )
{
    try {
#ifdef DEBUG
        cout << "-- overlay not loaded yet, attempting to load : " << overlay << endl;
#endif
        this->fileHandle = open( SLOTS_DIR, O_WRONLY );
        if ( write( this->fileHandle, Overlay, 1024 ) > 0 ) {
            close( this->fileHandle );
#ifdef DEBUG
            cout << "--- overlay loaded successfully." << endl;
#endif
            return true;
        }
        else {
#ifdef DEBUG
            cout << "--- Failed to load overlay." << endl;
#endif
            return false;
        }
    }
    catch ( exception& e ) {
        cerr << "Exception : " << e.what() << endl;
    }
}