#pragma once

#include <stdexcept>

#include "../Mat3/Mat3.h"
#include "../Mat4/Mat4.h"
#include "../Vec3/Vec3.h"

#include "../Utilities.h"

namespace lm
{
	template <typename T> class Quaternion
	{
	public:
		T x, y, z, w;

	public:

		/************************************\
		*                                    *
		*           Instantiation            *
		*                                    *
		\************************************/

		Quaternion() : x(0), y(0), z(0), w(0) {}

		Quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		Quaternion(Quaternion<T> const& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

		Quaternion(Vec3<T> axis, float angle)
		{
			float radAngle = TO_RADIANS(angle);
			axis = axis.normalize();
			T s = sin(radAngle / 2);
			x = axis.X() * s;
			y = axis.Y() * s;
			z = axis.Z() * s;
			w = cos(radAngle / 2);
		}
		Quaternion(const Mat3<T>& other) { fromMatrix3(other); }

		~Quaternion() {}

		static const Quaternion<T> identity;

		/************************************\
		*                                    *
		*             Accessor               *
		*                                    *
		\************************************/

		T& operator[](const int index)
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

		const T operator[](const int index) const
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

		const Vec3<T>& getVec3Part() const { return Vec3<T>(x, y, z); }

		const Vec4<T>& getVec4Part() const { return Vec4<T>(x, y, z, w); }

		/************************************\
		*                                    *
		*             Geometric              *
		*                                    *
		\************************************/

		T length2() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}

		T length() const
		{
			return sqrt(length2());
		}

		Quaternion<T> normalize() const
		{
			T len = length();
			if (len <= static_cast<T>(0))
				return Quaternion<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
			T oneOverLen = static_cast<T>(1) / len;
			return Quaternion<T>(x * oneOverLen, y * oneOverLen, z * oneOverLen, w * oneOverLen);
		}

		Quaternion<T> conjugate() const
		{
			return Quaternion<T>(-x, -y, -z, w);
		}

		Quaternion<T> inverse() const
		{
			return conjugate() / length2();
		}

		T dot(Quaternion<T> const& p) const
		{
			return (x * p.x) + (y * p.y) + (z * p.z) + (w * p.w);
		}

		const Quaternion<T> cross(Quaternion<T> const& q) const
		{
			return Quaternion<T>(
				this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
				this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z,
				this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x,
				this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z);
		}

		/************************************\
		*                                    *
		*             Arithmetic             *
		*                                    *
		\************************************/

		// -- Unary arithmetic operators --

		Quaternion<T> operator=(Quaternion<T> const& q)
		{
			x = static_cast<T>(q.x);
			y = static_cast<T>(q.y);
			z = static_cast<T>(q.z);
			w = static_cast<T>(q.w);

			return *this;
		}

		Quaternion<T> operator+=(Quaternion<T> const& q)
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;

			return *this;
		}

		Quaternion<T> operator-=(Quaternion<T> const& q)
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;

			return *this;
		}

		Quaternion<T> operator*=(Quaternion<T> const& r)
		{
			Quaternion<T> const p(*this);
			Quaternion<T> const q(r);

			this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
			this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
			this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
			this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;

			return *this;
		}

		Quaternion<T> operator*=(const T s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;

			return *this;
		}

		Quaternion<T> operator/=(const T s)
		{
			x /= s;
			y /= s;
			z /= s;
			w /= s;

			return *this;
		}

		// -- Unary bit operators --

		Quaternion<T> operator-() const
		{
			return Quaternion<T>(-x, -y, -z, -w);
		}

		// -- Binary operators --

		const Quaternion<T> operator+(Quaternion<T> const& q) const
		{
			return Quaternion<T>(*this) += q;
		}

		const Quaternion<T> operator-(Quaternion<T> const& q) const
		{
			return Quaternion<T>(*this) -= q;
		}

		const Quaternion<T> operator*(Quaternion<T> const& p) const
		{
			return Quaternion<T>(*this) *= p;
		}

		const Quaternion<T> operator*(T const& s) const
		{
			return Quaternion<T>(*this) *= s;
		}

		const Vec3<T> operator*(Vec3<T> const& v) const
		{
			const Vec3<T> quatVector(x, y, z);
			const Vec3<T> uv(quatVector.crossProduct(v));
			const Vec3<T> uuv(quatVector.crossProduct(uv));

			return v + ((uv * w) + uuv) * static_cast<T>(2);
		}

		const Vec4<T> operator*(Vec4<T> const& v) const
		{
			return Vec4<T>(*this * Vec3<T>(v.x, v.y, v.z), v.w);
		}

		const Quaternion<T> operator/(const T s) const
		{
			return Quaternion<T>(
				x / s, y / s, z / s, w / s);
		}

		// -- Boolean operators --

		bool operator==(Quaternion<T> const& q) const
		{
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}

		bool operator!=(Quaternion<T> const& q) const
		{
			return x != q.x || y != q.y || z != q.z || w != q.w;
		}

		bool isUnit() const
		{
			return dot(*this) == static_cast<T>(1);
		}

		/************************************\
		*                                    *
		*               Angle                *
		*                                    *
		\************************************/

		float getAngle() const
		{
			return float(2 * acos(w));
		}

		float getAngle(Quaternion<T> const& q) const
		{
			return float(2 * acos(dot(q)));
		}

		/************************************\
		*                                    *
		*           Transformation           *
		*                                    *
		\************************************/

		Quaternion<T> rotate(const Vec3<T>& v) const
		{
			Quaternion<T> q(v.x, v.y, v.z, 0);
			q = *this * q * inverse();
			return q;
		}

		Quaternion<T> rotate(Quaternion<T> const& q) const
		{
			return *this * q * inverse();
		}

		Quaternion<T> rotate(const Vec3<T>& axis, float angle)
		{
			radAngle = TO_RADIANS(angle);
			float halfAngle = radAngle / 2;
			T sinHalfAngle = sin(halfAngle);
			T cosHalfAngle = cos(halfAngle);
			return Quaternion<T>(axis.X() * sinHalfAngle, axis.Y() * sinHalfAngle, axis.Z() * sinHalfAngle, cosHalfAngle);
		}

		//Create Matrix3 from Quaternion
		Mat3<T> toMatrix3() const
		{
			Mat3<T> m;
			T xx = x * x;
			T xy = x * y;
			T xz = x * z;
			T xw = x * w;
			T yy = y * y;
			T yz = y * z;
			T yw = y * w;
			T zz = z * z;
			T zw = z * w;
			T ww = w * w;
			T wx = w * x;
			T wy = w * y;
			T wz = w * z;
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

		//Create Quaternion from Matrix3
		Quaternion<T> fromMatrix3(const Mat3<T>& m)
		{
			T trace = m[0][0] + m[1][1] + m[2][2];
			T s = 0.0f;

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
	};
	template <typename T> const Quaternion<T> Quaternion<T>::identity = Quaternion<T>(0, 0, 0, 1);

	typedef Quaternion<int>		Quati;
	typedef Quaternion<float>	Quatf;
	typedef Quaternion<double>	Quatd;

	template <typename T>
	inline constexpr static lm::Vec3<T> operator*(const lm::Vec3<T>& v, Quaternion<T> const& q)
	{
		return q.inverse() * v;
	}

	template <typename T>
	inline constexpr static lm::Vec4<T> operator*(const lm::Vec4<T>& v, Quaternion<T> const& q)
	{
		return q.inverse() * v;
	}

	template <typename T>
	inline constexpr static Quaternion<T> operator*(T const& s, Quaternion<T> const& q)
	{
		return q *= s;
	}

	template <typename T>
	inline constexpr std::ostream& operator<<(std::ostream& os, Quaternion<T> const& q)
	{
		os << "Quaternion(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
		return os;
	}

	template <typename T>
	inline constexpr std::istream& operator>>(std::istream& is, Quaternion<T>& q)
	{
		char c;

		// Remove "Quaternion("
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
}