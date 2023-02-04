#include "FQuat.hpp"

#include "../Utilities.h"

using namespace lm;

lm::FQuat::FQuat(): x(0), y(0), z(0), w(0) {}

lm::FQuat::FQuat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

lm::FQuat::FQuat(FQuat const &q): x(q.x), y(q.y), z(q.z), w(q.w) {}

lm::FQuat::FQuat(FVec3 axis, float angle)
{
	float radAngle = TO_RADIANS(angle);
	axis = FVec3::Normalize(axis);
	float s = sin(radAngle / 2);
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
	w = cos(radAngle / 2);
}

lm::FQuat::FQuat(const Mat3 &other) { fromMatrix3(other); }

const FQuat FQuat::identity = FQuat(0, 0, 0, 1);

float& FQuat::operator[](const int index)
{
	switch (index)
	{
	case 0:		return x;
	case 1:		return y;
	case 2:		return z;
	case 3:		return w;

	case 'x':	return x;
	case 'y':	return y;
	case 'z':	return z;
	case 'w':	return w;

	default:
		throw std::runtime_error("Quaternion::operator[]: Invalide index or out of range");
	}
}

const float FQuat::operator[](const int index) const
{
	switch (index)
	{
	case 0:		return x;
	case 1:		return y;
	case 2:		return z;
	case 3:		return w;

	case 'x':	return x;
	case 'y':	return y;
	case 'z':	return z;
	case 'w':	return w;

	default:
		throw std::runtime_error("Quaternion::operator[]: Invalide index or out of range");
	}
}

const FVec3& lm::FQuat::getVec3Part() const
{
	return FVec3(x, y, z);
}

const FVec4& lm::FQuat::getVec4Part() const
{
	return FVec4(x, y, z, w);
}

float lm::FQuat::length2() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

float lm::FQuat::length() const
{
	return sqrt(length2());
}

FQuat lm::FQuat::normalize() const
{
	float len = length();
	if (len <= 0)
	{

		return FQuat(0, 0, 0, 1);
	}
	float oneOverLen = 1 / len;
	return FQuat(x * oneOverLen, y * oneOverLen, z * oneOverLen, w * oneOverLen);
}

FQuat lm::FQuat::conjugate() const
{
	return FQuat(-x, -y, -z, w);
}

FQuat lm::FQuat::inverse() const
{
	return conjugate() / length2();
}

float lm::FQuat::dot(FQuat const& p) const
{
	return (x * p.x) + (y * p.y) + (z * p.z) + (w * p.w);
}

const FQuat lm::FQuat::cross(FQuat const& q) const
{
	return FQuat(
		this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
		this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z,
		this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x,
		this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z);
}

FQuat lm::FQuat::operator=(FQuat const& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;

	return *this;
}

FQuat lm::FQuat::operator+=(FQuat const& q)
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;

	return *this;
}

FQuat lm::FQuat::operator-=(FQuat const& q)
{
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;

	return *this;
}

FQuat lm::FQuat::operator*=(FQuat const& r)
{
	FQuat const p(*this);
	FQuat const q(r);

	this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
	this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
	this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
	this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;

	return *this;
}

FQuat lm::FQuat::operator*=(const float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;

	return *this;
}

FQuat lm::FQuat::operator/=(const float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;

	return *this;
}

FQuat lm::FQuat::operator-() const
{
	return FQuat(-x, -y, -z, -w);
}

const FQuat lm::FQuat::operator+(FQuat const& q) const
{
	return FQuat(*this) += q;
}

const FQuat lm::FQuat::operator-(FQuat const& q) const
{
	return FQuat(*this) -= q;
}

const FQuat lm::FQuat::operator*(FQuat const& p) const
{
	return FQuat(*this) *= p;
}

const FQuat lm::FQuat::operator*(float const& s) const
{
	return FQuat(*this) *= s;
}

const FVec3 lm::FQuat::operator*(FVec3 const& v) const
{
	const FVec3 quatVector(x, y, z);
	const FVec3 uv(FVec3::Cross(quatVector, v));
	const FVec3 uuv(FVec3::Cross(quatVector, uv));

	return v + ((uv * w) + uuv) * 2;
}

const FVec4 lm::FQuat::operator*(FVec4 const& v) const
{
	return FVec4(*this * FVec3(v.x, v.y, v.z), v.w);
}

const FQuat lm::FQuat::operator/(const float s) const
{
	return FQuat(
		x / s, y / s, z / s, w / s);
}

bool lm::FQuat::operator==(FQuat const& q) const
{
	return x == q.x && y == q.y && z == q.z && w == q.w;
}

bool lm::FQuat::operator!=(FQuat const& q) const
{
	return x != q.x || y != q.y || z != q.z || w != q.w;
}

bool lm::FQuat::isUnit() const
{
	return dot(*this) == 1;
}

float lm::FQuat::getAngle() const
{
	return float(2 * acos(w));
}

float lm::FQuat::getAngle(FQuat const& q) const
{
	return float(2 * acos(dot(q)));
}

FQuat lm::FQuat::rotate(const FVec3& v) const
{
	FQuat q(v.x, v.y, v.z, 0);
	q = *this * q * inverse();
	return q;
}

FQuat lm::FQuat::rotate(FQuat const& q) const
{
	return *this * q * inverse();
}

FQuat lm::FQuat::rotate(const FVec3& axis, float angle)
{
	float radAngle = TO_RADIANS(angle);
	float halfAngle = radAngle / 2;
	float sinHalfAngle = sin(halfAngle);
	float cosHalfAngle = cos(halfAngle);
	return FQuat(axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle, cosHalfAngle);
}

Mat3 lm::FQuat::toMatrix3() const
{
	Mat3 m;
	float xx = x * x;
	float xy = x * y;
	float xz = x * z;
	float xw = x * w;
	float yy = y * y;
	float yz = y * z;
	float yw = y * w;
	float zz = z * z;
	float zw = z * w;
	float ww = w * w;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;
	m[0][0] = 1 - 2 * yy - 2 * zz;
	m[0][1] = 2 * xy - 2 * wz;
	m[0][2] = 2 * xz + 2 * wy;

	m[1][0] = 2 * xy + 2 * wz;
	m[1][1] = 1 - 2 * xx - 2 * zz;
	m[1][2] = 2 * yz - 2 * wx;

	m[2][0] = 2 * xz - 2 * wy;
	m[2][1] = 2 * yz + 2 * wx;
	m[2][2] = 1 - 2 * xx - 2 * yy;

	return m;
}

FQuat lm::FQuat::fromMatrix3(const Mat3& m)
{
	float trace = m[0][0] + m[1][1] + m[2][2];
	float s = 0.0f;

	if (trace > 0)
	{
		s = sqrtf(trace + 1.0f) * 2;
		x = (m[2][1] - m[1][2]) / s;
		y = (m[0][2] - m[2][0]) / s;
		z = (m[1][0] - m[0][1]) / s;
		w = 0.25f * s;
	}
	else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
	{
		s = sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]) * 2;
		x = 0.25f * s;
		y = (m[0][1] + m[1][0]) / s;
		z = (m[0][2] + m[2][0]) / s;
		w = (m[2][1] - m[1][2]) / s;
	}
	else if (m[1][1] > m[2][2])
	{
		s = sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]) * 2;
		x = (m[0][1] + m[1][0]) / s;
		y = 0.25f * s;
		z = (m[1][2] + m[2][1]) / s;
		w = (m[0][2] - m[2][0]) / s;
	}
	else
	{
		s = sqrtf(1.0f + m[2][2] - m[0][0] - m[1][1]) * 2;
		x = (m[0][2] + m[2][0]) / s;
		y = (m[1][2] + m[2][1]) / s;
		z = 0.25f * s;
		w = (m[1][0] - m[0][1]) / s;
	}

	return *this;
}

FVec3 lm::operator*(const FVec3& v, FQuat const& q)
{
	return q.inverse() * v;
}

FVec4 lm::operator*(const FVec4& v, FQuat const& q)
{
	return q.inverse() * v;
}

FQuat lm::operator*(float const& s, FQuat const& q)
{
	return q * s;
}

std::ostream& lm::operator<<(std::ostream& os, FQuat const& q)
{
	os << "FQuat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
	return os;
}

std::istream& lm::operator>>(std::istream& is, FQuat& q)
{
	char c;

	// Remove "FQuat("
	for (int i = 0; i < 11; ++i)
	{
		is >> c;
	}

	is >> q.x;

	is >> c;

	is >> q.y;

	is >> c;

	is >> q.z;

	is >> c;

	is >> q.w;

	is >> c;

	return is;
}
