//
// Created by Michael Brookes on 06/02/2017.
//

#include "Timer.h"

int Timer::milliTimer()
{
    timeval tv{};
    gettimeofday( &tv, nullptr );
    return ( tv.tv_sec ) * 1000 + ( tv.tv_usec ) / 1000;
}