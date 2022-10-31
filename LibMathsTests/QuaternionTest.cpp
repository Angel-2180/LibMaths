#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Quaternion/Quaternion.h"
#include "Vec3/Vec3.h"
using namespace lm;

#define COMPILE_QUAT_TESTS 1
#if COMPILE_QUAT_TESTS

TEST_CASE("QuaternionTest", "[QuaternionTest]")
{
	SECTION("QuaternionTest")
	{
		Quaternion<float> q1(1, 2, 3, 4);
		Quaternion<float> q2(5, 6, 7, 8);
		Quaternion<float> q3 = q1 + q2;
		REQUIRE(q3.X() == 6);
		REQUIRE(q3.Y() == 8);
		REQUIRE(q3.Z() == 10);
		REQUIRE(q3.W() == 12);

		Quaternion<float> q4 = q1 - q2;
		REQUIRE(q4.X() == -4);
		REQUIRE(q4.Y() == -4);
		REQUIRE(q4.Z() == -4);
		REQUIRE(q4.W() == -4);

		//Quaternion<float> q5 = q1 * q2;
		//REQUIRE(q5.X() == -60);
		//REQUIRE(q5.Y() == 12);
		//REQUIRE(q5.Z() == 30);
		//REQUIRE(q5.W() == -24);

		vec3 p(2, 0, 0);
		vec3 v(0, 0, 1);
		float theta = 180;
		Quaternion<float> q6;
		vec3 result = q6.Rotate(v, theta, p);
		REQUIRE(result.X() == -2);
		//REQUIRE(result.Y() == Approx(0.f));
		//REQUIRE(result.Z() == Approx(0.f));

		p = vec3(0, 10, 0);
		v = vec3(1, 1, 0);
		theta = 270;
		Quaternion<float> q7;
		result = q7.Rotate(v, theta, p);
		REQUIRE(result.X() == Approx(5.0f));
		REQUIRE(result.Y() == Approx(5.0f));
		//REQUIRE(result.Z() == Approx(-7.07f));
	}
}

#endif

// 	}