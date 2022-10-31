#pragma once
#include "Vec3/Vec3.h"
namespace lm
{
	template <typename T> class Quaternion
	{
	private:
		T x, y, z, w;

	public:
		const double static radiansToDegrees(const double rad)
		{
			return rad * (HALF_CIRCLE / M_PI);
		}

		const double static degreesToRadians(const double deg)
		{
			return deg * (M_PI / HALF_CIRCLE);
		}
		static const Quaternion<T> identity;

		T& operator[](const int index)
		{
			switch (index)
			{
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			case 3:
				return this->w;
			default:
				return this->x;
			}
		}

		const T operator[](const int index) const
		{
			switch (index)
			{
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			case 3:
				return this->w;
			default:
				return this->x;
			}
		}

		T& X()
		{
			return this->x;
		}

		const T X() const
		{
			return this->x;
		}

		T& Y()
		{
			return this->y;
		}

		const T Y() const
		{
			return this->y;
		}

		T& Z()
		{
			return this->z;
		}

		const T Z() const
		{
			return this->z;
		}

		T& W()
		{
			return this->w;
		}

		const T W() const
		{
			return this->w;
		}

		Quaternion()
		{
			x = y = z = 0;
			w = 1;
		}
		Quaternion(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		Quaternion(const Quaternion<T>& q)
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
		}
		~Quaternion()
		{
		}
		const Vec3<T>& getVectorPart() const
		{
			return Vec3<T>(x, y, z);
		}
		Quaternion<T> operator+(const Quaternion<T>& q) const
		{
			return Quaternion<T>(x + q.x, y + q.y, z + q.z, w + q.w);
		}
		Quaternion<T> operator-(const Quaternion<T>& q) const
		{
			return Quaternion<T>(x - q.x, y - q.y, z - q.z, w - q.w);
		}
		Quaternion<T> operator*(const Quaternion<T>& q) const
		{
			return Quaternion<T>(w * q.x + x * q.w + y * q.z - z * q.y,
				w * q.y + y * q.w + z * q.x - x * q.z,
				w * q.z + z * q.w + x * q.y - y * q.x,
				w * q.w - x * q.x - y * q.y - z * q.z);
		}
		Quaternion<T> operator*(const T& s) const
		{
			return Quaternion<T>(x * s, y * s, z * s, w * s);
		}
		Quaternion<T> operator/(const T& s) const
		{
			return Quaternion<T>(x / s, y / s, z / s, w / s);
		}
		Quaternion<T> operator-() const
		{
			return Quaternion<T>(-x, -y, -z, -w);
		}

		Quaternion<T>& operator=(const Quaternion<T>& q)
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
			return *this;
		}
		Quaternion<T>& operator+=(const Quaternion<T>& q)
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			return *this;
		}

		Quaternion<T>& operator-=(const Quaternion<T>& q)
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			return *this;
		}
		Quaternion<T>& operator*=(const Quaternion<T>& q)
		{
			*this = *this * q;
			return *this;
		}
		Quaternion<T>& operator*=(const T& s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}
		Quaternion<T>& operator/=(const T& s)
		{
			x /= s;
			y /= s;
			z /= s;
			w /= s;
			return *this;
		}

		bool operator==(const Quaternion<T>& q) const
		{
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}
		bool operator!=(const Quaternion<T>& q) const
		{
			return x != q.x || y != q.y || z != q.z || w != q.w;
		}

		T Length() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}
		T LengthSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}
		Quaternion<T> Conjugate() const
		{
			return Quaternion<T>(-x, -y, -z, w);
		}
		Quaternion<T> Inverse() const
		{
			return Conjugate() / LengthSquared();
		}
		Quaternion<T> Normalize() const
		{
			return *this / Length();
		}
		Quaternion<T> Rotate(const Vec3<T>& v) const
		{
			Quaternion<T> q(v.x, v.y, v.z, 0);
			q = *this * q * Inverse();
			return q;
		}

		Quaternion<T> Rotate(const Quaternion<T>& q) const
		{
			return *this * q * Inverse();
		}

		Quaternion<T> Rotate(const Vec3<T>& axis, const T& angle)
		{
			T halfAngle = angle / 2;
			T sinHalfAngle = sin(degreesToRadians(halfAngle));
			T cosHalfAngle = cos(degreesToRadians(halfAngle));
			return Quaternion<T>(axis.X() * sinHalfAngle, axis.Y() * sinHalfAngle, axis.Z() * sinHalfAngle, cosHalfAngle);
		}

		// Rotate point p by a vector and an angle
		Vec3<T> Rotate(Vec3<T>& v, const T& angle, const Vec3<T>& p)
		{
			v.normalize();
			Quaternion<T> g = Rotate(v, angle);

			Quaternion<T> q(p.X(), p.Y(), p.Z(), 0);

			Quaternion<T> pPrime(g * q * g.Conjugate());

			return  pPrime.getVectorPart();
		}
	};
	template <typename T> const Quaternion<T> Quaternion<T>::identity = Quaternion<T>(0, 0, 0, 1);

	typedef Quaternion<float> Quatf;
}