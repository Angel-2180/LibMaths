#include <iostream>
#include <sstream>

#include "catch.hpp"

#include "Vec3/Vec3.h"

#define COMPILE_VEC3_TESTS 0
#if COMPILE_VEC3_TESTS

// Lorsque vous pensez avoir fini de coder le test 1,
// passez ce define a 1 pour compiler le test
#define COMPILE_TEST_1 1

TEST_CASE("Vec3 Test 1", "[vec3]")
{
#if COMPILE_TEST_1
	lm::vec3 v1;
	REQUIRE(v1.X() == 0.f);
	REQUIRE(v1.Y() == 0.f);
	REQUIRE(v1.Z() == 0.f);

	const lm::vec3 v2(1.0f, 2.5f, 3.0f);
	REQUIRE(v2.X() == 1.f);
	REQUIRE(v2.Y() == 2.5f);
	REQUIRE(v2.Z() == 3.0f);

	lm::vec3 v3 = v2;
	REQUIRE(v2.X() == v3.X());
	REQUIRE(v2.Y() == v3.Y());
	REQUIRE(v2.Z() == v3.Z());

	v3.X() = v3.Y() = v3.Z() = 1.2f;
	REQUIRE(v3.X() == v3.Y());
	REQUIRE(v3.X() == v3.Z());
	REQUIRE(v3.X() == 1.2f);

	lm::vec3 v4(0.2f, 10.0f, 20.0f);
	REQUIRE(v4.X() == 0.2f);
	REQUIRE(v4.Y() == 10.0f);
	REQUIRE(v4.Z() == 20.0f);

	v4 = v3;
	REQUIRE(v4.X() == v3.X());
	REQUIRE(v4.Y() == v3.Y());
	REQUIRE(v4.Z() == v3.Z());

#else
	{
		REQUIRE(false); // Missing test
	}
#endif
}

#define COMPILE_TEST_2 1

TEST_CASE("Vec3 Test 2", "[vec3]")
{
#if COMPILE_TEST_2
	lm::vec3 v1 = lm::vec3::zero;
	REQUIRE(v1.X() == 0.f);
	REQUIRE(v1.Y() == 0.f);
	REQUIRE(v1.Z() == 0.f);

	v1 = lm::vec3::up;
	REQUIRE(v1.X() == 0.f);
	REQUIRE(v1.Y() == 1.f);
	REQUIRE(v1.Z() == 0.f);

	v1 = lm::vec3::down;
	REQUIRE(v1.X() == 0.f);
	REQUIRE(v1.Y() == -1.f);
	REQUIRE(v1.Z() == 0.f);

	v1 = lm::vec3::left;
	REQUIRE(v1.X() == -1.f);
	REQUIRE(v1.Y() == 0.f);
	REQUIRE(v1.Z() == 0.f);

	v1 = lm::vec3::right;
	REQUIRE(v1.X() == 1.f);
	REQUIRE(v1.Y() == 0.f);
	REQUIRE(v1.Z() == 0.f);

	float f = v1[1] = 20.0f;
	f = v1[0] = 2.0f * f;
	REQUIRE(v1.X() == 40.f);
	REQUIRE(v1.Y() == 20.0f);

	float x = v1['x'] = 78.0f;
	float y = v1['y'] = 67.0f;
	float z = v1['z'] = 56.0f;
	REQUIRE(v1.X() == 78.0f);
	REQUIRE(v1.Y() == 67.0f);
	REQUIRE(v1.Z() == 56.0f);
	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;

	// Save cout's buffer here
	std::streambuf* sbuf = std::cout.rdbuf();

	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());

	std::cout << "v1 : " << v1 << std::endl;

	x = v1["x"] = 12.0f;
	y = v1["y"] = 23.0f;
	z = v1["z"] = 34.0f;
	REQUIRE(v1.X() == 12.0f);
	REQUIRE(v1.Y() == 23.0f);
	REQUIRE(v1.Z() == 34.0f);
	REQUIRE(x == 12.0f);
	REQUIRE(y == 23.0f);
	REQUIRE(z == 34.0f);

	// Restore cout's buffer
	std::cout.rdbuf(sbuf);
#else
	{
		REQUIRE(false); // Missing test
	}
#endif
}

#define COMPILE_TEST_3 0

TEST_CASE("Vec3 Test 3", "[vec3]")

{
#if COMPILE_TEST_3
	// Premiere version :
	lm::vec3 v;
	std::cin >> v;
	std::cout << "v : " << v << std::endl;

	// Deuxieme version :
	std::stringstream buffer;
	buffer << "3.5,2.7,4.0\n";
	buffer >> v;
	REQUIRE(v.X() == 3.5f);
	REQUIRE(v.Y() == 2.7f);
	REQUIRE(v.Z() == 4.0f);

#else
	{
		REQUIRE(false); // Missing test
	}
#endif
}

#define COMPILE_TEST_4 1

TEST_CASE("Vec3 Test 4", "[vec3]")
{
#if COMPILE_TEST_4
	lm::vec3 v1(1.0f, 2.5f, 3.0f);

	std::string v1string = "v1: ";
	v1string = v1string + v1;
	v1string += ", v1 again : ";
	v1string += v1;
	REQUIRE(v1string == "v1: (1.000000, 2.500000, 3.000000), v1 again : (1.000000, 2.500000, 3.000000)");

	float dot = v1.dotProduct(lm::vec3(1.0f, -1.0f, 0.0f));
	REQUIRE(dot == -1.5f);

	float length = v1.length();
	REQUIRE(length == Approx(4.031128874f));

	lm::vec3 v2 = v1.normalized();
	REQUIRE(v2.X() == 1.0f / 3.741657f);
	REQUIRE(v2.Y() == 2.5f / 3.741657f);
	REQUIRE(v2.Z() == 3.0f / 3.741657f);

	lm::vec3 v3 = v1.crossProduct(lm::vec3(1.0f, -1.0f, 0.0f));
	REQUIRE(v3.X() == 0.0f);
	REQUIRE(v3.Y() == 0.0f);
	REQUIRE(v3.Z() == 1.0f);

#else
	{
		REQUIRE(false); // Missing test
	}
#endif
}

#define COMPILE_TEST_5 1

TEST_CASE("Vec3 Test 5", "[vec3]")
{
#if COMPILE_TEST_5

	lm::vec3 v1(1.0f, 2.5f, 3.0f);
	REQUIRE(v1.X() == 1.0f);
	REQUIRE(v1.Y() == 2.5f);
	REQUIRE(v1.Z() == 3.0f);

	lm::vec3 v2(1.0f, 2.5f, 3.0f);
	REQUIRE(v2.X() == 1.0f);
	REQUIRE(v2.Y() == 2.5f);
	REQUIRE(v2.Z() == 3.0f);

	lm::vec3 v3 = v1.add(v2);
	std::cout << "x: " << v3.X() << " y: " << v3.Y() << " z: " << v3.Z() << '\n';
	REQUIRE(v3.X() == 2.0f);
	REQUIRE(v3.Y() == 5.0f);
	REQUIRE(v3.Z() == 6.0f);

	v2.add(v1).add(v3);
	std::cout << "x: " << v2.X() << " y: " << v2.Y() << " z: " << v2.Z() << '\n';
	REQUIRE(v2.X() == 3.0f);
	REQUIRE(v2.Y() == 7.5f);
	REQUIRE(v2.Z() == 9.0f);
#endif
}
#endif