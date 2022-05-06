#include "pch.h"
#include "Vec2.h"
#include <iostream>
#include <string>

using namespace lm;

vec2 vec2::zero = vec2(0.0f);
vec2 vec2::up = vec2(0.0f, 1.0f);
vec2 vec2::down = vec2(0.0f, -1.0f);
vec2 vec2::right = vec2(1.0f, 0.0f);
vec2 vec2::left = vec2(-1.0f, 0.0f);

vec2::vec2()
{
	this->x = this->y = 0.0f;
}

vec2::vec2(float a, float b)
{
	this->x = a;
	this->y = b;
}

vec2::vec2(float a)
{
	this->x = this->y = a;
}

float vec2::X() const
{
	return this->x;
}

float vec2::Y() const
{
	return this->y;
}

float& vec2::X()
{
	return this->x;
}

float& vec2::Y()
{
	return this->y;
}

std::ostream& operator<<(std::ostream& flux, const vec2& vec)
{
	flux << vec.X() << ',' << vec.Y();
	return flux;
}

std::string operator+(std::string const& c1, const vec2& c2)
{
	return c1 + "x:" + std::to_string(c2.X()) + ", y : " + std::to_string(c2.Y());
}

std::string& operator+=(std::string& c1, const vec2& c2)
{
	c1 += "x:" + std::to_string(c2.X()) + ", y : " + std::to_string(c2.Y());
	return c1;
}

vec2 vec2::operator+(const lm::vec2& c2)
{
	float a = this->X() + c2.X();
	float b = this->Y() + c2.Y();

	vec2 v(a, b);
	return v;
}

vec2 vec2::operator-(const lm::vec2& c2)
{
	float a = this->X() - c2.X();
	float b = this->Y() - c2.Y();

	vec2 v(a, b);
	return v;
}

vec2& vec2::operator+=(const lm::vec2& c2)
{
	this->x += c2.X();
	this->y += c2.Y();
	return *this;
}
vec2& vec2::operator-=(const lm::vec2& c2)
{
	this->x -= c2.X();
	this->y -= c2.Y();
	return *this;
}


void operator>>(std::istream& flux, vec2& vec)
{
	std::cout << "enter vector: ";
	std::string s;
	flux >> s;
	int i = s.find(',');
	if (i == std::string::npos)
	{
		vec.X() = 0;
		vec.Y() = 0;
		return;
	}
	else
	{
		vec.X() = stof(s.substr(0, i));
		vec.Y() = stof(s.substr(i + 1, s.size()));
	}
}

float& vec2::operator[](int idx)
{
	if (idx == 0 || idx == 'x')
	{
		return this->x;
	}
	if (idx == 1 || idx == 'y')
	{
		return this->y;
	}
}

float& vec2::operator[](const char idx[2])
{
	if (idx == "x")
	{
		return this->x;
	}
	if (idx == "y")
	{
		return this->y;
	}
}

float vec2::length() const
{
	float i = sqrt((this->x * this->x) + (this->y * this->y));
	return i;
}

float vec2::dot_product(vec2 const& m) const
{
	return (x * m.X()) + (y * m.Y());
}

float vec2::cross_product(vec2 const& m) const
{
	return -((x * m.X()) - (y * m.Y()));
}

vec2& vec2::add(vec2 const& m)
{
	this->X() += m.X();
	this->Y() += m.Y();

	return *this;
}

vec2& vec2::scale(float a)
{
	this->x *= a;
	this->y *= a;
	return *this;
}

vec2 vec2::add(vec2 const& m) const
{
	float a = this->X() + m.X();
	float b = this->Y() + m.Y();

	vec2 v(a, b);
	return v;
}

const vec2& vec2::scale(float a) const
{
	vec2 v(this->x * a, this->y * a);
	return v;
}

vec2 vec2::normalized() const
{
	vec2 v(this->x / this->length(), this->y / this->length());
	return v;
}

void vec2::normalize()
{
	vec2 v = normalized();
	this->x = v.x;
	this->y = v.y;
}
/*
vec2& vec2::operator=(vec2 c2)
{
	this->x = c2.x;
	this->y = c2.y;
	return *this;
}
*/
int& operator==(const vec2 c1, const vec2 c2)
{
	int n = 0;
	if (c1.X() == c2.X() && c1.Y() == c2.Y())
	{
		n = 1;
	}
	return n;
}
int& operator!=(const vec2 c1, const vec2 c2)
{
	int n = 1;
	if (c1.X() == c2.X() && c1.Y() == c2.Y())
	{
		n = 0;
	}
	return n;
}
int& operator<(const vec2 c1, const vec2 c2)
{
	int n = 0;
	if (c1.X() < c2.X() && c1.Y() < c2.Y())
	{
		n = 1;
	}
	return n;
}
int& operator<=(const vec2 c1, const vec2 c2)
{
	int n = 0;
	if (c1.X() <= c2.X() && c1.Y() <= c2.Y())
	{
		n = 1;
	}
	return n;
}
int& operator>(const vec2 c1, const vec2 c2)
{
	int n = 0;
	if (c1.X() > c2.X() && c1.Y() > c2.Y())
	{
		n = 1;
	}
	return n;
}
int& operator>=(const vec2 c1, const vec2 c2)
{
	int n = 0;
	if (c1.X() >= c2.X() && c1.Y() >= c2.Y())
	{
		n = 1;
	}
	return n;
}