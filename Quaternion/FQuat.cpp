#include "FQuat.hpp"
#include "../Mat3/FMat3.hpp"
#include "../Mat4/FMat4.hpp"
#include "../Vec3/FVec3.hpp"
#include "../Vec4/FVec4.hpp"
#include "../Utilities.h"

using namespace lm;

lm::FQuat::FQuat() : x(0), y(0), z(0), w(1) {}

lm::FQuat::FQuat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

lm::FQuat::FQuat(FQuat const& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

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

lm::FQuat::FQuat(const FMat3& other) { FromMatrix3(other); }

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

float FQuat::Length2(const FQuat& q)
{
	return (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);
}

float FQuat::Length(const FQuat& q)
{
	return sqrt(Length2(q));
}

FQuat lm::FQuat::Normalize(const FQuat& q)
{
	float length = Length(q);
	return FQuat(q.x / length, q.y / length, q.z / length, q.w / length);
}

FQuat FQuat::Conjugate(const FQuat& q)
{
	return FQuat(-q.x, -q.y, -q.z, q.w);
}

FQuat FQuat::Inverse(const FQuat& q)
{
	return Conjugate(q) / Length2(q);
}

float FQuat::Dot(const FQuat& q1, const FQuat& q2)
{
	return (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
}

FQuat FQuat::Cross(const FQuat& q1, const FQuat& q2)
{
	return FQuat(
		(q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y),
		(q1.w * q2.y) + (q1.y * q2.w) + (q1.z * q2.x) - (q1.x * q2.z),
		(q1.w * q2.z) + (q1.z * q2.w) + (q1.x * q2.y) - (q1.y * q2.x),
		(q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z)
	);
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

	x = (p.w * q.x) + (p.x * q.w) + (p.y * q.z) - (p.z * q.y);
	y = (p.w * q.y) + (p.y * q.w) + (p.z * q.x) - (p.x * q.z);
	z = (p.w * q.z) + (p.z * q.w) + (p.x * q.y) - (p.y * q.x);
	w = (p.w * q.w) - (p.x * q.x) - (p.y * q.y) - (p.z * q.z);

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
	FQuat const q(*this);
	return FQuat(
		(q.w * p.x) + (q.x * p.w) + (q.y * p.z) - (q.z * p.y),
		(q.w * p.y) + (q.y * p.w) + (q.z * p.x) - (q.x * p.z),
		(q.w * p.z) + (q.z * p.w) + (q.x * p.y) - (q.y * p.x),
		(q.w * p.w) - (q.x * p.x) - (q.y * p.y) - (q.z * p.z)
	);
}

const FQuat lm::FQuat::operator*(float const& s) const
{
	return FQuat(*this) *= s;
}

const FVec3 lm::FQuat::operator*(FVec3 const& v) const
{
	FQuat const q(*this);
	FQuat const p(v.x, v.y, v.z, 0.0f);
	FQuat const r = q * p * Conjugate(q);

	return FVec3(r.x, r.y, r.z);
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
	return Dot(*this, *this) == 1;
}

float lm::FQuat::getAngle() const
{
	return float(2 * acos(w));
}

float lm::FQuat::getAngle(FQuat const& q) const
{
	return float(2 * acos(Dot(*this, q)));
}

FQuat FQuat::Rotate(FQuat const& q, FVec3 const& v)
{
	FQuat qv = FQuat(v.x, v.y, v.z, 0);
	return q * qv * Inverse(q);
}

FQuat FQuat::Rotate(FQuat const& p, FQuat const& q)
{
	return p * q * Inverse(p);
}

FQuat FQuat::Rotate(FQuat const& q, FVec3 const& v, float const& angle)
{
	return Rotate(q, FQuat(v, angle));
}

FMat3 lm::FQuat::ToMatrix3(FQuat const& q)
{
	FMat3 m;
	float xx = q.x * q.x;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float xw = q.x * q.w;
	float yy = q.y * q.y;
	float yz = q.y * q.z;
	float yw = q.y * q.w;
	float zz = q.z * q.z;
	float zw = q.z * q.w;
	float ww = q.w * q.w;
	float wx = q.w * q.x;
	float wy = q.w * q.y;
	float wz = q.w * q.z;
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

FQuat lm::FQuat::FromMatrix3(FMat3 const& m)
{
	FQuat result;
	float trace = m[0][0] + m[1][1] + m[2][2];
	float s = 0.0f;

	if (trace > 0)
	{
		s = sqrtf(trace + 1.0f) * 2;
		result.x = (m[2][1] - m[1][2]) / s;
		result.y = (m[0][2] - m[2][0]) / s;
		result.z = (m[1][0] - m[0][1]) / s;
		result.w = 0.25f * s;
	}
	else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
	{
		s = sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]) * 2;
		result.x = 0.25f * s;
		result.y = (m[0][1] + m[1][0]) / s;
		result.z = (m[0][2] + m[2][0]) / s;
		result.w = (m[2][1] - m[1][2]) / s;
	}
	else if (m[1][1] > m[2][2])
	{
		s = sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]) * 2;
		result.x = (m[0][1] + m[1][0]) / s;
		result.y = 0.25f * s;
		result.z = (m[1][2] + m[2][1]) / s;
		result.w = (m[0][2] - m[2][0]) / s;
	}
	else
	{
		s = sqrtf(1.0f + m[2][2] - m[0][0] - m[1][1]) * 2;
		result.x = (m[0][2] + m[2][0]) / s;
		result.y = (m[1][2] + m[2][1]) / s;
		result.z = 0.25f * s;
		result.w = (m[1][0] - m[0][1]) / s;
	}

	return result;
}

FQuat lm::FQuat::Lerp(FQuat const& q1, FQuat const& q2, float t)
{
	float alpha = clamp(t, 0.0f, 1.0f);
	FQuat q = q1 + alpha * (q2 - q1);
	return q;
}

FQuat FQuat::NLerp(FQuat const& q1, FQuat const& q2, float t)
{
	float alpha = clamp(t, 0.0f, 1.0f);
	FQuat q;

	float dot = FQuat::Dot(q1, q2);
	if (dot < 0)
	{
		q = q1 + alpha * (-q2 - q1);
	}
	else
	{
		q = q1 + alpha * (q2 - q1);
	}
	return FQuat::Normalize(q);
}

FQuat FQuat::SLerp(FQuat const& q1, FQuat const& q2, float t)
{
	FQuat from = q1;
	FQuat to = q2;

	t = clamp(t, 0.f, 1.f);
	float cosAngle = FQuat::Dot(from, to);

	if (cosAngle < 0.f)
	{
		cosAngle = -cosAngle;
		to = FQuat(-to.x, -to.y, -to.z, -to.w);
	}

	if (cosAngle < 0.95f)
	{
		float angle = std::acos(cosAngle);
		float sinAngle = std::sin(angle);
		float invSinAngle = 1.f / sinAngle;
		float t1 = std::sin((1 - t) * angle) * invSinAngle;
		float t2 = std::sin(t * angle) * invSinAngle;
		return FQuat(from.x * t1 + to.x * t2, from.y * t1 + to.y * t2, from.z * t1 + to.z * t2, from.w * t1 + to.w * t2);
	}
	else
	{
		return FQuat::Lerp(from, to, t);
	}
	// Normalize(q1);
	// Normalize(q2);
	// float alpha = clamp(t, 0.0f, 1.0f);
	// float dot = Dot(q1, q2);

	// if (dot == 1)
	// {
	// 	return q1;
	// }

	// float theta = std::acos(dot);
	// float sinTheta = std::sin(theta);
	// float w1 = std::sin((1 - alpha) * theta) / sinTheta;
	// float w2 = std::sin(alpha * theta) / sinTheta;

	// FQuat q;

	// q = w1 * q1 + w2 * q2;

	// return Normalize(q);
}

FVec3 lm::operator*(const FVec3& v, FQuat const& q)
{
	return FQuat::Inverse(q) * v;
}

FVec4 lm::operator*(const FVec4& v, FQuat const& q)
{
	return FQuat::Inverse(q) * v;
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