#include "FVec2.hpp"
#include <utility>

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <limits>
#include "Utilities.h"
using namespace lm;

const FVec2 FVec2::One(1.0f, 1.0f);
const FVec2 FVec2::Zero(0.0f, 0.0f);

FVec2::FVec2(float p_x, float p_y) :
	x(p_x), y(p_y)
{
}

FVec2::FVec2(const FVec2& p_toCopy) :
	x(p_toCopy.x), y(p_toCopy.y)
{
}

FVec2 FVec2::operator-() const
{
	return operator*(-1);
}

FVec2 FVec2::operator=(const FVec2& p_other)
{
	this->x = p_other.x;
	this->y = p_other.y;

	return *this;
}

FVec2 FVec2::operator+(const FVec2& p_other) const
{
	return Add(*this, p_other);
}

FVec2& FVec2::operator+=(const FVec2& p_other)
{
	*this = Add(*this, p_other);
	return *this;
}

FVec2 FVec2::operator-(const FVec2& p_other) const
{
	return Substract(*this, p_other);
}

FVec2& FVec2::operator-=(const FVec2& p_other)
{
	*this = Substract(*this, p_other);
	return *this;
}

FVec2 FVec2::operator*(float p_scalar) const
{
	return Multiply(*this, p_scalar);
}

FVec2& FVec2::operator*=(float p_scalar)
{
	*this = Multiply(*this, p_scalar);
	return *this;
}

FVec2 FVec2::operator/(float p_scalar) const
{
	return Divide(*this, p_scalar);
}

FVec2& FVec2::operator/=(float p_scalar)
{
	*this = Divide(*this, p_scalar);
	return *this;
}

bool FVec2::operator==(const FVec2& p_other)
{
	return
		this->x == p_other.x &&
		this->y == p_other.y;
}

bool FVec2::operator!=(const FVec2& p_other)
{
	return !operator==(p_other);
}

const float& lm::FVec2::operator[](int p_index) const
{
	switch (p_index)
	{
	case 0:	return x;
	case 1:	return y;

	default:
		throw std::out_of_range("Index out of range");
	}
}

float& lm::FVec2::operator[](int p_index)
{
	switch (p_index)
	{
	case 0:	return x;
	case 1:	return y;

	default:
		throw std::out_of_range("Index out of range");
	}
}

const float& lm::FVec2::operator()(int p_index) const
{
	switch (p_index)
	{
	case 0:	return x;
	case 1:	return y;

	default:
		throw std::out_of_range("Index out of range");
	}
}

float& lm::FVec2::operator()(int p_index)
{
	switch (p_index)
	{
	case 0:	return x;
	case 1:	return y;

	default:
		throw std::out_of_range("Index out of range");
	}
}

FVec2 FVec2::Add(const FVec2& p_left, const FVec2& p_right)
{
	return FVec2
	(
		p_left.x + p_right.x,
		p_left.y + p_right.y
	);
}

FVec2 FVec2::Substract(const FVec2& p_left, const FVec2& p_right)
{
	return FVec2
	(
		p_left.x - p_right.x,
		p_left.y - p_right.y
	);
}

FVec2 FVec2::Multiply(const FVec2& p_target, float p_scalar)
{
	return FVec2
	(
		p_target.x * p_scalar,
		p_target.y * p_scalar
	);
}

FVec2 FVec2::Divide(const FVec2& p_left, float p_scalar)
{
	FVec2 result(p_left);

	if (p_scalar == 0)
		throw std::logic_error("Division by 0");

	result.x /= p_scalar;
	result.y /= p_scalar;

	return result;
}

float FVec2::Length(const FVec2& p_target)
{
	return sqrtf(p_target.x * p_target.x + p_target.y * p_target.y);
}

float FVec2::Dot(const FVec2& p_left, const FVec2& p_right)
{
	return p_left.x * p_right.x + p_left.y * p_right.y;
}

FVec2 FVec2::Normalize(const FVec2& p_target)
{
	float length = Length(p_target);

	if (length > 0.0f)
	{
		float targetLength = 1.0f / length;

		return FVec2
		(
			p_target.x * targetLength,
			p_target.y * targetLength
		);
	}
	else
	{
		return FVec2::Zero;
	}
}

FVec2 FVec2::Lerp(const FVec2& p_start, const FVec2& p_end, float p_alpha)
{
	return (p_start + (p_end - p_start) * p_alpha);
}

float FVec2::AngleBetween(const FVec2& p_from, const FVec2& p_to)
{
	float lengthProduct = Length(p_from) * Length(p_to);

	if (lengthProduct > 0.0f)
	{
		float fractionResult = Dot(p_from, p_to) / lengthProduct;

		if (fractionResult >= -1.0f && fractionResult <= 1.0f)
			return acosf(fractionResult);
	}

	return 0.0f;
}

std::ostream& lm::operator<<(std::ostream& p_stream, const FVec2& p_vec)
{
	p_stream << "Vec2(" << p_vec.x << ", " << p_vec.y << ")";
}

std::istream& lm::operator>>(std::istream& p_stream, FVec2& p_vec)
{
	p_stream >> p_vec.x >> p_vec.y;
	return p_stream;
}

FVec2 lm::operator*(float p_scalar, const FVec2& p_vec)
{
	return FVec2::Multiply(p_vec, p_scalar);
}

FVec2 lm::operator/(float p_scalar, const FVec2& p_vec)
{
	return FVec2::Divide(p_vec, p_scalar);
}

FVec2 FVec2::Slerp(const FVec2& p_start, const FVec2& p_end, float p_alpha)
{
	float dot = Dot(p_start, p_end);

	if (dot < 0.0f)
	{
		dot = -dot;
	}

	if (dot > 0.9995f)
	{
		return Lerp(p_start, p_end, p_alpha);
	}

	float theta = acosf(dot);
	float sinTheta = sinf(theta);

	float startWeight = sinf((1.0f - p_alpha) * theta) / sinTheta;
	float endWeight = sinf(p_alpha * theta) / sinTheta;

	return (p_start * startWeight) + (p_end * endWeight);
}

FVec2 FVec2::Clamp(const FVec2& p_target, const FVec2& p_min, const FVec2& p_max)
{
	return FVec2
	(
		clamp(p_target.x, p_min.x, p_max.x),
		clamp(p_target.y, p_min.y, p_max.y)
	);
}

bool FVec2::IsZero() const
{
	return x == 0.0f && y == 0.0f;
}

FVec2 FVec2::Reflect(const FVec2& p_target, const FVec2& p_normal)
{
	return p_target - 2.0f * Dot(p_target, p_normal) * p_normal;
}

FVec2 FVec2::Project(const FVec2& p_target, const FVec2& p_normal)
{
	return Dot(p_target, p_normal) * p_normal;
}

bool FVec2::IsUnit() const
{
	return std::abs(Length(*this) - 1.0f) <= std::numeric_limits<float>::epsilon() ||
		std::abs(Length(*this) - 1.0f) <= std::numeric_limits<float>::epsilon() *
		std::max(std::abs(Length(*this)), std::abs(1.0f));
}