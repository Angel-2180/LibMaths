#pragma once
#include <iostream>

namespace lm
{
	class vec2
	{
	public:
		vec2();
		vec2(float a, float b);
		vec2(float a);


		// vector function
		float X() const;
		float Y() const;
		float& X();
		float& Y();
		float dot_product(vec2 const& m) const;
		float length() const;
		float cross_product(vec2 const& m) const;
		vec2& add(vec2 const& m);
		vec2 add(vec2 const& m) const;
		vec2& scale(float a);
		const vec2& scale(float a) const;
		vec2 normalized() const;
		void normalize();

		//surcharge operator
		float& operator[](int idx);
		float& operator[](const char idx[2]);
		vec2 operator+(const lm::vec2& c2);
		vec2& operator+=(const lm::vec2& c2);
		vec2 operator-(const lm::vec2& c2);
		vec2& operator-=(const lm::vec2& c2);
		//vec2& operator=(vec2 c2);

		//value fonction
		static vec2 zero;
		static vec2 up;
		static vec2 down;
		static vec2 left;
		static vec2 right;

	private:
		float x, y;
	};
}
std::ostream& operator<<(std::ostream& flux, const lm::vec2& vec);
std::string operator+(std::string const& c1, const lm::vec2& c2);
std::string& operator+=(std::string& c1, const lm::vec2& c2);


void operator>>(std::istream& flux, lm::vec2& vec);
int& operator==(const lm::vec2 c1, const lm::vec2 c2);
int& operator!=(const lm::vec2 c1, const lm::vec2 c2);
int& operator<(const lm::vec2 c1, const lm::vec2 c2);
int& operator<=(const lm::vec2 c1, const lm::vec2 c2);
int& operator>(const lm::vec2 c1, const lm::vec2 c2);
int& operator>=(const lm::vec2 c1, const lm::vec2 c2);
