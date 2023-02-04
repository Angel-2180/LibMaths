#pragma once

#include <stdexcept>

#include "Mat3/Mat3.h"
#include "Mat4/Mat4.h"
#include "Vec3/Vec3.h"

#include "Utilities.h"

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
		
		/**
		 * @brief Default constructor
		 * @details Set all components to 0
		*/
		Quaternion() : x(0), y(0), z(0), w(0) {}

		/**
		 * @brief Constructor
		 * @details Set all components to the same value
		 * @param value Value to set all components to
		 * @return A new quaternion with all components set to value
		*/
		Quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		/**
		 * @brief Constructor copy
		 * @details Copy all components from another quaternion
		 * @param q Quaternion to copy from
		 * @return A new quaternion with the same components as q
		*/
		Quaternion(Quaternion<T> const& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

		/**
		 * @brief Constructor from axis and angle
		 * @details Create a quaternion from an axis and an angle
		 * @param axis Axis to rotate around
		 * @param angle Angle to rotate
		 * @return A new quaternion with the same components as q
		 * @note The angle is in degrees
		*/
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

		/**
		 * @brief Constructor from matrix
		 * @details Create a quaternion from a matrix
		 * @param other Matrix to convert
		 * @return A new quaternion with the same components as q
		*/
		Quaternion(const Mat3<T>& other) { fromMatrix3(other); }

		~Quaternion() {} = default;

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

		/**
		 * @brief Get the vector part of the quaternion
		 * @details Get the vector part of the quaternion
		 * @return A new vector with the same components as the vector part of the quaternion
		*/
		const Vec3<T>& getVec3Part() const { return Vec3<T>(x, y, z); }

		/**
		 * @brief Get the vector part of the quaternion
		 * @details Get the vector part of the quaternion
		 * @return A new vector with the same components as the vector part of the quaternion
		*/
		const Vec4<T>& getVec4Part() const { return Vec4<T>(x, y, z, w); }

		/************************************\
		*                                    *
		*             Geometric              *
		*                                    *
		\************************************/


		/**
		 * @brief Get the Length of the quaternion squared\
		 * @details Get the Length of the quaternion squared
		 * @return The length of the quaternion squared
		 * @note This is faster than length() because it avoids a square root
		 * @note This is useful for comparing the length of two quaternions
		*/
		T length2() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}


		/**
		 * @brief Get the Length of the quaternion
		 * @details Get the Length of the quaternion
		 * @return The length of the quaternion
		 * @note This is slower than length2() because it involves a square root
		*/
		T length() const
		{
			return sqrt(length2());
		}

		/**
		 * @brief Normalize the quaternion
		 * @details Normalize the quaternion
		 * @return A new quaternion with the same direction as the original but with a length of 1
		 * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
		*/
		Quaternion<T> normalize() const
		{
			T len = length();
			if (len <= static_cast<T>(0))
				return Quaternion<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
			T oneOverLen = static_cast<T>(1) / len;
			return Quaternion<T>(x * oneOverLen, y * oneOverLen, z * oneOverLen, w * oneOverLen);
		}


		/**
		 * @brief Get the conjugate of the quaternion
		 * @details Get the conjugate of the quaternion
		 * @return A new quaternion with the same direction as the original but with a length of 1
		 * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
		*/
		Quaternion<T> conjugate() const
		{
			return Quaternion<T>(-x, -y, -z, w);
		}

		/**
		 * @brief Get the inverse of the quaternion
		 * @details Get the inverse of the quaternion
		 * @return A new quaternion with the same direction as the original but with a length of 1
		 * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
		*/
		Quaternion<T> inverse() const
		{
			return conjugate() / length2();
		}

		/**
		 * @brief Get the dot product of two quaternions
		 * @details Get the dot product of two quaternions
		 * @param p The other quaternion
		 * @return The dot product of the two quaternions
		*/
		T dot(Quaternion<T> const& p) const
		{
			return (x * p.x) + (y * p.y) + (z * p.z) + (w * p.w);
		}

		/**
		 * @brief Get the cross product of two quaternions
		 * @details Get the cross product of two quaternions
		 * @param p The other quaternion
		 * @return The cross product of the two quaternions
		*/
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
			const Vec3<T> uv(quatVector.cross(v));
			const Vec3<T> uuv(quatVector.cross(uv));

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

		/**
		 * @brief Returns true if the quaternion is a unit quaternion.
		 * @return True if the quaternion is a unit quaternion.
		 * @note A unit quaternion is a quaternion with a length of 1.
		 * @note This function is not very accurate.
		*/
		bool isUnit() const
		{
			return dot(*this) == static_cast<T>(1);
		}

		/************************************\
		*                                    *
		*               Angle                *
		*                                    *
		\************************************/

		/**
		 * @brief Returns the angle of the quaternion.
		 * @return The angle of the quaternion.
		 * @note The angle is in radians.
		*/
		float getAngle() const
		{
			return float(2 * acos(w));
		}

		/**
		 * @brief Returns the angle from this quaternion to another quaternion.
		 * @param q The quaternion.
		 * @return The angle of the quaternion.
		 * @note The angle is in radians.
		*/
		float getAngle(Quaternion<T> const& q) const
		{
			return float(2 * acos(dot(q)));
		}

		/************************************\
		*                                    *
		*           Transformation           *
		*                                    *
		\************************************/

		/**
		 * @brief Rotates a quaternion around a vector.
		 * @param v The vector to rotate around.
		 *	@note The vector must be normalized.
		 *	@returns The rotated quaternion.
		*/
		Quaternion<T> rotate(const Vec3<T>& v) const
		{
			Quaternion<T> q(v.x, v.y, v.z, 0);
			q = *this * q * inverse();
			return q;
		}

		/**
		 * @brief Rotates a quaternion around a quaternion.
		 * @param q The quaternion to rotate around.
		 * @returns The rotated quaternion.
		 * @note The quaternion must be normalized.
		*/
		Quaternion<T> rotate(Quaternion<T> const& q) const
		{
			return *this * q * inverse();
		}

		/**
		 * @brief Rotates a quaternion around a vector by a given angle.
		 * @param v The vector to rotate around.
		 * @param angle The angle to rotate.
		 * @returns The rotated quaternion.
		 * @note The vector must be normalized.
		 * @note The angle is in degrees.
		*/
		Quaternion<T> rotate(const Vec3<T>& axis, float angle)
		{
			float radAngle = TO_RADIANS(angle);
			float halfAngle = radAngle / 2;
			T sinHalfAngle = sin(halfAngle);
			T cosHalfAngle = cos(halfAngle);
			return Quaternion<T>(axis.X() * sinHalfAngle, axis.Y() * sinHalfAngle, axis.Z() * sinHalfAngle, cosHalfAngle);
		}

		/**
		 * @brief Create a Matrix3 from a quaternion.
		 * @return The matrix.
		 * @note The matrix is a rotation matrix.
		 * 
		*/
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

		/**
		 * @brief Create a Quaternion from a Matrix3.
		 * @param m The matrix.
		 * @return The quaternion.
		 * @note The matrix must be a rotation matrix.
		*/
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
	inline constexpr static Vec3<T> operator*(const Vec3<T>& v, Quaternion<T> const& q)
	{
		return q.inverse() * v;
	}

	template <typename T>
	inline constexpr static Vec4<T> operator*(const Vec4<T>& v, Quaternion<T> const& q)
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