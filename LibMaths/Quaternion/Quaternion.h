#pragma once
#include "Mat3/Mat3.h"
#include "Mat4/Mat4.h"
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
		Quaternion(const Mat4<T>& mat)
		{
			this->fromMatrix4(mat);
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

		//Create Matrix from Quaternion
		Mat4<T> toMatrix4() const
		{
			Mat4<T> m;
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
			m[0][0] = 1 - 2 *yy - 2 * zz;
			m[0][1] = 2 * xy - 2 * wz;
			m[0][2] = 2 * xz + 2 * wy;
			m[0][3] = 0;

			m[1][0] = 2 * xy + 2 * wz;
			m[1][1] = 1 - 2 * xx - 2 * zz;
			m[1][2] = 2 * yz - 2 * wx;
			m[1][3] = 0;

			m[2][0] = 2 * xz - 2 * wy;
			m[2][1] = 2 * yz + 2 * wx;
			m[2][2] = 1 - 2 * xx - 2 * yy;
			m[2][3] = 0;

			m[3][0] = 0;
			m[3][1] = 0;
			m[3][2] = 0;
			m[3][3] = 1;

			return m;
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
			m[0][0] = 1 - 2 *yy - 2 * zz;
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

		//Create Quaternion from Matrix
		Quaternion<T> fromMatrix4(const Mat4<T>& m)
		{
			T trace = m[0][0] + m[1][1] + m[2][2];
			T s = 0.0f;

			if (trace > 0)
			{
				s = sqrt(trace + 1.0f) * 2;
				x = (m[2][1] - m[1][2]) / s;
				y = (m[0][2] - m[2][0]) / s;
				z = (m[1][0] - m[0][1]) / s;
				w = 0.25f * s;
			}
			else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
			{
				s = sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]) * 2;
				x = 0.25f * s;
				y = (m[0][1] + m[1][0]) / s;
				z = (m[0][2] + m[2][0]) / s;
				w = (m[2][1] - m[1][2]) / s;
			}
			else if (m[1][1] > m[2][2])
			{
				s = sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]) * 2;
				x = (m[0][1] + m[1][0]) / s;
				y = 0.25f * s;
				z = (m[1][2] + m[2][1]) / s;
				w = (m[0][2] - m[2][0]) / s;
			}
			else
			{
				s = sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]) * 2;
				x = (m[0][2] + m[2][0]) / s;
				y = (m[1][2] + m[2][1]) / s;
				z = 0.25f * s;
				w = (m[1][0] - m[0][1]) / s;
			}

			return *this;
		}
		//Create Quaternion from Matrix3
		Quaternion<T> fromMatrix3(const Mat3<T>& m)
		{
			T trace = m[0][0] + m[1][1] + m[2][2];
			T s = 0.0f;

			if (trace > 0)
			{
				s = sqrt(trace + 1.0f) * 2;
				x = (m[2][1] - m[1][2]) / s;
				y = (m[0][2] - m[2][0]) / s;
				z = (m[1][0] - m[0][1]) / s;
				w = 0.25f * s;
			}
			else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
			{
				s = sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]) * 2;
				x = 0.25f * s;
				y = (m[0][1] + m[1][0]) / s;
				z = (m[0][2] + m[2][0]) / s;
				w = (m[2][1] - m[1][2]) / s;
			}
			else if (m[1][1] > m[2][2])
			{
				s = sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]) * 2;
				x = (m[0][1] + m[1][0]) / s;
				y = 0.25f * s;
				z = (m[1][2] + m[2][1]) / s;
				w = (m[0][2] - m[2][0]) / s;
			}
			else
			{
				s = sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]) * 2;
				x = (m[0][2] + m[2][0]) / s;
				y = (m[1][2] + m[2][1]) / s;
				z = 0.25f * s;
				w = (m[1][0] - m[0][1]) / s;
			}

			return *this;
		}
	};
	template <typename T> const Quaternion<T> Quaternion<T>::identity = Quaternion<T>(0, 0, 0, 1);

	typedef Quaternion<float> Quatf;
}