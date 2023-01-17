#pragma once

#define _USE_MATH_DEFINES_
#include <cmath>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#ifdef far
#undef far
#endif

#ifdef near
#undef near
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef HALF_CIRCLE
#define HALF_CIRCLE 180.0f
#endif

namespace lm
{
    inline double radiansToDegrees(const double rad)
    {
        return rad * (HALF_CIRCLE / M_PI);
    }

    inline double degreesToRadians(const double deg)
    {
        return deg * (M_PI / HALF_CIRCLE);
    }
}