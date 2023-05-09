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

#ifndef HALF_CIRCLE
#define HALF_CIRCLE 180.0f
#endif

#undef PI

#define PI (4.f * atan(1.f))
#define TO_RADIANS(value) value * PI / 180.f
#define TO_DEGREES(value) value * 180.f / PI

namespace lm
{
	inline double radiansToDegrees(const double rad)
	{
		return rad * (HALF_CIRCLE / PI);
	}

	inline double degreesToRadians(const double deg)
	{
		return deg * (PI / HALF_CIRCLE);
	}

	template<typename T>
	inline T clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	inline float randomFloat(const float min, const float max)
	{
		return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	}

	inline int randomInt(const int min, const int max)
	{
		return min + rand() % (max - min + 1);
	}
}