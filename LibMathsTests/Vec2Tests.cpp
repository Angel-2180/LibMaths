#include <iostream>
#include <sstream>

#include "catch.hpp"

#include "Vec2/Vec2.h"

#define COMPILE_VEC2_TESTS 0
#if COMPILE_VEC2_TESTS

// Lorsque vous pensez avoir fini de coder le test 1,
// passez ce define a 1 pour compiler le test
#define COMPILE_TEST_1 1

TEST_CASE("Vec2 Test 1", "[vec2]")
{
#if COMPILE_TEST_1
	lm::vec2 v1;
	REQUIRE(v1.X() == 0.f);
	REQUIRE(v1.Y() == 0.f);

	const lm::vec2 v2(1.0f, 2.5f);
	REQUIRE(v2.X() == 1.f);
	REQUIRE(v2.Y() == 2.5f);

	lm::vec2 v3 = v2;
	REQUIRE(v2.X() == v3.X());
	REQUIRE(v2.Y() == v3.Y());

	v3.X() = v3.Y() = 1.2f;
	REQUIRE(v3.X() == v3.Y());
	REQUIRE(v3.X() == 1.2f);

	lm::vec2 v4(0.2f, 10.0f);
	REQUIRE(v4.X() == 0.2f);
	REQUIRE(v4.Y() == 10.0f);

	v4 = v3;
	REQUIRE(v4.X() == v3.X());
	REQUIRE(v4.Y() == v3.Y());

	lm::vec2 v5 = 3.0f;
	REQUIRE((v5.X() == 3.0f));
	REQUIRE(v5.Y() == 3.0f);
#else
	REQUIRE(false); // Missing test
#endif
}

// Lorsque vous pensez avoir fini de coder le test 2,
// passez ce define a 1 pour compiler le test
#define COMPILE_TEST_2 1

TEST_CASE("Vec2 Test 2", "[vec2]")
{
#if COMPILE_TEST_2
	lm::vec2 v1 = lm::vec2::zero;
	REQUIRE(v1.X() == 0.f);
	REQUIRE(v1.Y() == 0.f);

	v1 = lm::vec2::up;
	REQUIRE(v1.X() == 0.f);
	REQUIRE(v1.Y() == 1.f);

	v1 = lm::vec2::down;
	REQUIRE(v1.X() == 0.f);
	REQUIRE(v1.Y() == -1.f);

	v1 = lm::vec2::left;
	REQUIRE(v1.X() == -1.f);
	REQUIRE(v1.Y() == 0.f);

	v1 = lm::vec2::right;
	REQUIRE(v1.X() == 1.f);
	REQUIRE(v1.Y() == 0.f);

	float f = v1[1] = 20.0f;
	f = v1[0] = 2.0f * f;

	REQUIRE(v1.X() == 40.f);
	REQUIRE(v1.Y() == 20.f);

	float x = v1['x'] = 78.0f;
	float y = v1['y'] = 67.0f;
	REQUIRE(v1.X() == 78.0f);
	REQUIRE(v1.Y() == 67.0f);

	// This can be an ofstream as well or any other ostream
	std::stringstream buffer;

	// Save cout's buffer here
	std::streambuf* sbuf = std::cout.rdbuf();

	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());

	std::cout << "v1 : " << v1 << std::endl;

	//std::cout << buffer.str();
	x = v1["x"] = 12.0f;
	y = v1["y"] = 34.0f;
	REQUIRE(v1.X() == 12.0f);
	REQUIRE(v1.Y() == 34.0f);
	REQUIRE(x == 12.0f);
	REQUIRE(y == 34.0f);

	std::cout << "v1 : " << v1 << std::endl;

	std::string output = buffer.str();
	REQUIRE(output == "v1 : 78,67\nv1 : 12,34\n");
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

#else
	REQUIRE(false);
#endif
}

// Lorsque vous pensez avoir fini de coder le test 3,
// passez ce define a 1 pour compiler le test
#define COMPILE_TEST_3 1

TEST_CASE("Vec2 Test 3", "[vec2]")
{
#if COMPILE_TEST_3

	// Premiere version :
	lm::vec2 v;
	std::cin >> v;
	std::cout << "v : " << v << std::endl;

	// Deuxieme version :
	std::stringstream buffer;
	buffer << "3.5,2.7\n";
	buffer >> v;
	REQUIRE(v.X() == 3.5f);
	REQUIRE(v.Y() == 2.7f);

#else
	REQUIRE(false);
#endif
}

// Lorsque vous pensez avoir fini de coder le test 4,
// passez ce define a 1 pour compiler le test
#define COMPILE_TEST_4 1

TEST_CASE("Vec2 Test 4", "[vec2]")
{
#if COMPILE_TEST_4

	const lm::vec2 v1(12.0f, 97.0f);

	std::string v1string = "v1: ";
	v1string = v1string + v1;
	v1string += ", v1 again : ";
	v1string += v1;
	REQUIRE(v1string == "v1: x:12.000000, y : 97.000000, v1 again : x:12.000000, y : 97.000000");

	float dot = v1.dotProduct(lm::vec2(1.0f, -1.0f));
	REQUIRE(dot == -85);

	float len = v1.length();
	REQUIRE(len == Approx(97.7394));

	float xprod = v1.crossProduct(lm::vec2(1.0f, -1.0f));
	REQUIRE(xprod == -109);

#else
	REQUIRE(false);
#endif
}

// Lorsque vous pensez avoir fini de coder le test 5,
// passez ce define a 1 pour compiler le test
#define COMPILE_TEST_5 1

TEST_CASE("Vec2 Test 5", "[vec2]")
{
#if COMPILE_TEST_5

	const lm::vec2 v1(2.0f, 3.0f);
	REQUIRE(v1.X() == 2.0f);
	REQUIRE(v1.Y() == 3.0f);

	lm::vec2 v2(1.2f, 4.5f);
	REQUIRE(v2.X() == 1.2f);
	REQUIRE(v2.Y() == 4.5f);

	lm::vec2 v3 = v1.add(v2);
	std::cout << "x: " << v3.X() << " y: " << v3.Y() << '\n';
	REQUIRE(v3.X() == 3.2f);
	REQUIRE(v3.Y() == 7.5f);

	v2.add(v1).add(v3);
	REQUIRE(v1.X() == 2.0f);
	REQUIRE(v1.Y() == 3.0f);
	REQUIRE(v2.X() == 6.4f);
	REQUIRE(v2.Y() == 15.f);
	REQUIRE(v3.X() == 3.2f);
	REQUIRE(v3.Y() == 7.5f);

	lm::vec2 v4(0.5f, 6.3f);
	v4.scale(2.0f);
	REQUIRE(v4.X() == 1.f);
	REQUIRE(v4.Y() == 12.6f);

	lm::vec2 v5 = v1.scale(3.0f);
	REQUIRE(v5.X() == 6.f);
	REQUIRE(v5.Y() == 9.f);

	lm::vec2 norm = v1.normalized();
	REQUIRE(norm.X() == Approx(0.5547f));
	REQUIRE(norm.Y() == Approx(0.83205f));

	v5.normalize();
	REQUIRE(v5.X() == Approx(0.5547f));
	REQUIRE(v5.Y() == Approx(0.83205f));

	REQUIRE(v1 == v1);
	REQUIRE_FALSE(v1 == v5);
	REQUIRE_FALSE(v1 != v1);
	REQUIRE(v1 != v5);
	REQUIRE_FALSE(v1 < v5);
	REQUIRE_FALSE(v1 <= v5);
	REQUIRE(v1 > v5);
	REQUIRE(v1 >= v5);

#else
	REQUIRE(false);
#endif
}

// Lorsque vous pensez avoir fini de coder le test 6,
// passez ce define a 1 pour compiler le test
#define COMPILE_TEST_6 1

TEST_CASE("Vec2 Test 6", "[vec2]")
{
#if COMPILE_TEST_6

	const lm::vec2 v1(2.0f, 1.5f);
	REQUIRE(v1.X() == 2.0f);
	REQUIRE(v1.Y() == 1.5f);

	lm::vec2 v2(0.5f, 3.0f);
	REQUIRE(v2.X() == 0.5f);
	REQUIRE(v2.Y() == 3.0f);

	lm::vec2 v3 = v1 + v2;
	REQUIRE(v3.X() == 2.5f);
	REQUIRE(v3.Y() == 4.5f);

	v2 += v1;
	REQUIRE(v2.X() == 2.5f);
	REQUIRE(v2.Y() == 4.5f);

	lm::vec2 v4 = (v1 - v2);
	REQUIRE(v4.X() == -0.5f);
	REQUIRE(v4.Y() == -3.f);

	v2 -= v1;
	REQUIRE(v2.X() == 0.5f);
	REQUIRE(v2.Y() == 3.f);

	lm::vec2 v5 = -v1;
	REQUIRE(v5.X() == -2.f);
	REQUIRE(v5.Y() == -1.5f);

	lm::vec2 v6 = v1 * 5.f;
	REQUIRE(v6.X() == 10.f);
	REQUIRE(v6.Y() == 7.5f);

	v6 = 5.f * v1;
	REQUIRE(v6.X() == 10.f);
	REQUIRE(v6.Y() == 7.5f);

	lm::vec2 v7 = v1 / 2.f;
	REQUIRE(v7.X() == 1.f);
	REQUIRE(v7.Y() == 0.75f);

	v7 = 2.f / v1;
	REQUIRE(v7.X() == Approx(1.f));
	REQUIRE(v7.Y() == Approx(1.33333f));

	v2 *= 2.0f;
	REQUIRE(v2.X() == 1.f);
	REQUIRE(v2.Y() == 6.f);

	v2 /= 2.0f;
	REQUIRE(v2.X() == 0.5f);
	REQUIRE(v2.Y() == 3.f);

	v2++;    // v2.x *= (length + 1) / length; v2.y *= (length + 1) / length;
	REQUIRE(v2.X() == Approx(0.664399f));
	REQUIRE(v2.Y() == Approx(3.98639f));

	v2--;    // v2.x *= (length - 1) / length; v2.y *= (length - 1) / length;
	REQUIRE(v2.X() == 0.5f);
	REQUIRE(v2.Y() == 3.f);

	float dp = (v1, v2);
	REQUIRE(dp == 5.5f);

#else
	REQUIRE(false);
#endif
}

#endif