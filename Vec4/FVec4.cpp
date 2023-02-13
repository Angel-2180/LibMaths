#include <utility>
#include <stdexcept>

#include "FVec4.hpp"
#include "../Vec3/FVec3.hpp"
#include "../Utilities.h"
#include "iostream"
#include <algorithm>
#include <limits>

using namespace lm;

const FVec4 FVec4::One(1.0f, 1.0f, 1.0f, 1.0f);
const FVec4 FVec4::Zero(0.0f, 0.0f, 0.0f, 0.0f);

FVec4::FVec4(float p_x, float p_y, float p_z, float p_w) : x(p_x), y(p_y), z(p_z), w(p_w)
{
}

FVec4::FVec4(const FVec4& p_toCopy) : x(p_toCopy.x), y(p_toCopy.y), z(p_toCopy.z), w(p_toCopy.w)
{
}

FVec4::FVec4(const FVec3& p_toCopy, float p_w) : x(p_toCopy.x), y(p_toCopy.y), z(p_toCopy.z), w(p_w)
{
}

FVec4 FVec4::operator-() const
{
	return operator*(-1);
}

FVec4 FVec4::operator=(const FVec4& p_other)
{
	this->x = p_other.x;
	this->y = p_other.y;
	this->z = p_other.z;
	this->w = p_other.w;

	return *this;
}

FVec4 FVec4::operator+(const FVec4& p_other) const
{
	return Add(*this, p_other);
}

FVec4& FVec4::operator+=(const FVec4& p_other)
{
	*this = Add(*this, p_other);
	return *this;
}

FVec4 FVec4::operator-(const FVec4& p_other) const
{
	return Substract(*this, p_other);
}

FVec4& FVec4::operator-=(const FVec4& p_other)
{
	*this = Substract(*this, p_other);
	return *this;
}

FVec4 FVec4::operator*(float p_scalar) const
{
	return Multiply(*this, p_scalar);
}

FVec4& FVec4::operator*=(float p_scalar)
{
	*this = Multiply(*this, p_scalar);
	return *this;
}

FVec4 FVec4::operator/(float p_scalar) const
{
	return Divide(*this, p_scalar);
}

FVec4& FVec4::operator/=(float p_scalar)
{
	*this = Divide(*this, p_scalar);
	return *this;
}

bool FVec4::operator==(const FVec4& p_other)
{
	return
		this->x == p_other.x &&
		this->y == p_other.y &&
		this->z == p_other.z &&
		this->w == p_other.w;
}

bool FVec4::operator!=(const FVec4& p_other)
{
	return !operator==(p_other);
}

const float& lm::FVec4::operator[](int p_index) const
{
	switch (p_index)
	{
	case 0:	return x;
	case 1:	return y;
	case 2:	return z;
	case 3:	return w;
	default: throw std::out_of_range("Index out of range");
	}
}

float& lm::FVec4::operator[](int p_index)
{
	switch (p_index)
	{
	case 0:	return x;
	case 1:	return y;
	case 2:	return z;
	case 3:	return w;
	default: throw std::out_of_range("Index out of range");
	}
}

const float& lm::FVec4::operator()(int p_index) const
{
	switch (p_index)
	{
	case 0:	return x;
	case 1:	return y;
	case 2:	return z;
	case 3:	return w;
	default: throw std::out_of_range("Index out of range");
	}
}

float& lm::FVec4::operator()(int p_index)
{
	switch (p_index)
	{
	case 0:	return x;
	case 1:	return y;
	case 2:	return z;
	case 3:	return w;
	default: throw std::out_of_range("Index out of range");
	}
}

FVec4 FVec4::Add(const FVec4& p_left, const FVec4& p_right)
{
	return FVec4
	(
		p_left.x + p_right.x,
		p_left.y + p_right.y,
		p_left.z + p_right.z,
		p_left.w + p_right.w
	);
}

FVec4 FVec4::Substract(const FVec4& p_left, const FVec4& p_right)
{
	return FVec4
	(
		p_left.x - p_right.x,
		p_left.y - p_right.y,
		p_left.z - p_right.z,
		p_left.w - p_right.w
	);
}

FVec4 FVec4::Multiply(const FVec4& p_target, float p_scalar)
{
	return FVec4
	(
		p_target.x * p_scalar,
		p_target.y * p_scalar,
		p_target.z * p_scalar,
		p_target.w * p_scalar
	);
}

FVec4 FVec4::Divide(const FVec4& p_left, float p_scalar)
{
	FVec4 result(p_left);

	if (p_scalar == 0)
		throw std::logic_error("Division by 0");

	result.x /= p_scalar;
	result.y /= p_scalar;
	result.z /= p_scalar;
	result.w /= p_scalar;

	return result;
}

float FVec4::Length(const FVec4& p_target)
{
	return sqrtf(p_target.x * p_target.x + p_target.y * p_target.y + p_target.z * p_target.z + p_target.w * p_target.w);
}

float FVec4::Dot(const FVec4& p_left, const FVec4& p_right)
{
	return p_left.x * p_right.x + p_left.y * p_right.y + p_left.z * p_right.z + p_left.w * p_right.w;
}

FVec4 FVec4::Normalize(const FVec4& p_target)
{
	float length = Length(p_target);

	if (length > 0.0f)
	{
		float targetLength = 1.0f / length;

		return FVec4
		(
			p_target.x * targetLength,
			p_target.y * targetLength,
			p_target.z * targetLength,
			p_target.w * targetLength
		);
	}
	else
	{
		return FVec4::Zero;
	}
}

FVec4 FVec4::Lerp(const FVec4& p_start, const FVec4& p_end, float p_alpha)
{
	return (p_start + (p_end - p_start) * p_alpha);
}

FVec4 FVec4::Slerp(const FVec4& p_start, const FVec4& p_end, float p_alpha)
{
	float dot = Dot(p_start, p_end);

	if (dot > 0.9995f)
	{
		return Lerp(p_start, p_end, p_alpha);
	}

	dot = clamp(dot, -1.0f, 1.0f);

	float theta = acosf(dot) * p_alpha;
	FVec4 relativeVec = Normalize(p_end - p_start * dot);
	return ((p_start * cosf(theta)) + (relativeVec * sinf(theta)));
}

FVec4 FVec4::Clamp(const FVec4& p_target, const FVec4& p_min, const FVec4& p_max)
{
	return FVec4
	(
		clamp(p_target.x, p_min.x, p_max.x),
		clamp(p_target.y, p_min.y, p_max.y),
		clamp(p_target.z, p_min.z, p_max.z),
		clamp(p_target.w, p_min.w, p_max.w)
	);
}

void FVec4::Homogenize()
{
	if (w != 0.0f)
	{
		x /= w;
		y /= w;
		z /= w;
		w = 1.0f;
	}
}

bool FVec4::IsHomogenized() const
{
	return (w == 1.0f);
}

bool FVec4::IsZero() const
{
	return (x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f);
}

bool FVec4::IsUnit() const
{
	return std::abs(Length(*this) - 1.0f) <= std::numeric_limits<float>::epsilon() ||
		std::abs(Length(*this) - 1.0f) <= std::numeric_limits<float>::epsilon() *
		std::max(std::abs(Length(*this)), std::abs(1.0f));
}

std::ostream& lm::operator<<(std::ostream& p_stream, const FVec4& p_target)
{
	p_stream << "FVec4(" << p_target.x << ", " << p_target.y << ", " << p_target.z << ", " << p_target.w << ")";
	return p_stream;
}

std::istream& lm::operator>>(std::istream& p_stream, FVec4& p_target)
{
	p_stream >> p_target.x >> p_target.y >> p_target.z >> p_target.w;
	return p_stream;
}

FVec4 lm::operator*(float p_scalar, const FVec4& p_vec)
{
	return FVec4::Multiply(p_vec, p_scalar);
}

FVec4 lm::operator/(float p_scalar, const FVec4& p_vec)
{
	return FVec4::Divide(p_vec, p_scalar);
}