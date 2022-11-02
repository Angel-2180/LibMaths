#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Quaternion/Quaternion.h"
#include "Vec3/Vec3.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace lm;

#define COMPILE_QUAT_TESTS 1
#if COMPILE_QUAT_TESTS

#define COMPILE_TEST_1 1
TEST_CASE("QuaternionTest test1", "[QuaternionTest]")
{
#if COMPILE_TEST_1
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

		//test with glm conjugate of Quaternion
		glm::quat glmQ1(4, 1, 2, 3);
		Quaternion<float> q8(1, 2, 3, 4);
		glm::quat glmQ2 = conjugate(glmQ1);
		Quaternion<float> q9 = q8.Conjugate();
		REQUIRE(q9.X() == glmQ2.x);
		REQUIRE(q9.Y() == glmQ2.y);
		REQUIRE(q9.Z() == glmQ2.z);
		REQUIRE(q9.W() == glmQ2.w);
	}
#else
	REQUIRE(false);
#endif
}
#define COMPILE_TEST_2 0
TEST_CASE("QuaternionTest test2", "[QuaternionTest]")
{
#if COMPILE_TEST_2
	SECTION("QuaternionTest")
	{
		//test converssion quaternion to matrix
		Quaternion<float> q1(1, 2, 3, 4);
		mat4 m1 = q1.toMatrix4();
		glm::quat glmQ1(4, 1, 2, 3);
		glm::mat4 glmM1 = glm::toMat4(glmQ1);
		REQUIRE(m1[0][0] == glmM1[0][0]);
		REQUIRE(m1[0][1] == glmM1[0][1]);
		REQUIRE(m1[0][2] == glmM1[0][2]);
		REQUIRE(m1[0][3] == glmM1[0][3]);
		REQUIRE(m1[1][0] == glmM1[1][0]);
		REQUIRE(m1[1][1] == glmM1[1][1]);
		REQUIRE(m1[1][2] == glmM1[1][2]);
		REQUIRE(m1[1][3] == glmM1[1][3]);
		REQUIRE(m1[2][0] == glmM1[2][0]);
		REQUIRE(m1[2][1] == glmM1[2][1]);
		REQUIRE(m1[2][2] == glmM1[2][2]);
		REQUIRE(m1[2][3] == glmM1[2][3]);
		REQUIRE(m1[3][0] == glmM1[3][0]);
		REQUIRE(m1[3][1] == glmM1[3][1]);
		REQUIRE(m1[3][2] == glmM1[3][2]);
		REQUIRE(m1[3][3] == glmM1[3][3]);

		//test converssion matrix to quaternion
		Quaternion<float> q2(m1.transpose());
		glm::quat glmQ2 = glm::toQuat(glmM1);
		REQUIRE(q2.X() == glmQ2.x);
		REQUIRE(q2.Y() == glmQ2.y);
		REQUIRE(q2.Z() == glmQ2.z);
		REQUIRE(q2.W() == glmQ2.w);
	}
#else
	REQUIRE(false);
#endif
}

#endif

// 	}