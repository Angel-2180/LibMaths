#pragma once

#include <iostream>

namespace lm
{
	struct FVec3
	{
		static const FVec3 One;
		static const FVec3 Zero;
		static const FVec3 Forward;
		static const FVec3 Right;
		static const FVec3 Up;

		float x;
		float y;
		float z;

		/**
		* Default constructor
		* @param p_x
		* @param p_y
		* @param p_z
		*/
		FVec3(float p_x = 0.0f, float p_y = 0.0f, float p_z = 0.0f);

		/**
		* Copy constructor
		* @param p_toCopy
		*/
		FVec3(const FVec3& p_toCopy);

		/**
		* Move constructor
		* @param p_toMove
		*/
		FVec3(FVec3&& p_toMove) noexcept = default;

		/**
		* Negation
		*/
		FVec3 operator-() const;

		/**
		* Copy assignment
		* @param p_other
		*/
		FVec3 operator=(const FVec3& p_other);

		/**
		* Calculate the sum of two vectors
		* @param p_other
		*/
		FVec3 operator+(const FVec3& p_other) const;

		/**
		* Add the right vector to the left one
		* @param p_other
		*/
		FVec3& operator+=(const FVec3& p_other);

		/**
		* Calculate the substraction of two vectors
		* @param p_other
		*/
		FVec3 operator-(const FVec3& p_other) const;

		/**
		* Remove the right vector from the left one
		* @param p_other
		*/
		FVec3& operator-=(const FVec3& p_other);

		/**
		* Calcualte the multiplication of a vector with a scalar
		* @param p_scalar
		*/
		FVec3 operator*(float p_scalar) const;

		/**
		* Multiply the vector by a scalar
		* @param p_scalar
		*/
		FVec3& operator*=(float p_scalar);

		/**
		* Return the division of scalar and actual vector
		* @param p_scalar
		*/
		FVec3 operator/(float p_scalar) const;

		/**
		* Divide scalar to the actual vector
		* @param p_scalar
		*/
		FVec3& operator/=(float p_scalar);

		/**
		* Return true if the two vectors are equals
		* @param p_other
		*/
		bool operator==(const FVec3& p_other);

		/**
		* Return true if the two vectors are different
		* @param p_other
		*/
		bool operator!=(const FVec3& p_other);

		/**
 * Return the value of the vector at the given index
 * @param p_index
 */
		const float& operator[](int p_index) const;

		/**
		 * Return the value of the vector at the given index
		 * @param p_index
		 */
		float& operator[](int p_index);

		/**
		 * Return the value of the vector at the given index
		 * @param p_index
		 */
		const float& operator()(int p_index) const;

		/**
		 * Return the value of the vector at the given index
		 * @param p_index
		 */
		float& operator()(int p_index);

		/**
		* Calculate the sum of two vectors
		* @param p_left (First vector)
		* @param p_right (Second vector)
		*/
		static FVec3 Add(const FVec3& p_left, const FVec3& p_right);

		/**
		* Calculate the substraction of two vectors
		* @param p_left (First vector)
		* @param p_right (Second vector)
		*/
		static FVec3 Substract(const FVec3& p_left, const FVec3& p_right);

		/**
		* Calculate the multiplication of a vector with a scalar
		* @param p_target
		* @param p_scalar
		*/
		static FVec3 Multiply(const FVec3& p_target, float p_scalar);

		/**
		* Divide scalar to vector left
		* @param p_left
		* @param p_scalar
		*/
		static FVec3 Divide(const FVec3& p_left, float p_scalar);

		/**
		* Return the length of a vector
		* @param p_target
		*/
		static float Length(const FVec3& p_target);

		/**
		* Return the dot product of two vectors
		* @param p_left
		* @param p_right
		*/
		static float Dot(const FVec3& p_left, const FVec3& p_right);

		/**
		* Return the distance between two vectors
		* @param p_left
		* @param p_right
		*/
		static float Distance(const FVec3& p_left, const FVec3& p_right);

		/**
		* Return the cross product of two vectors
		* @param p_left
		* @param p_right
		*/
		static FVec3 Cross(const FVec3& p_left, const FVec3& p_right);

		/**
		* Return the normalize of the given vector
		* @param p_target
		*/
		static FVec3 Normalize(const FVec3& p_target);

		/**
		* Calculate the interpolation between two vectors
		* @param p_start
		* @param p_end
		* @param p_alpha
		*/
		static FVec3 Lerp(const FVec3& p_start, const FVec3& p_end, float p_alpha);

		/**
		* Calculate the angle between two vectors
		* @param p_from
		* @param p_to
		*/
		static float AngleBetween(const FVec3& p_from, const FVec3& p_to);

		/**
		 * Return the min vector between two vectors
		 * @param p_target
		 * @param p_min
		 * @param p_max
		 */
		static FVec3 Clamp(const FVec3& p_target, const FVec3& p_min, const FVec3& p_max);

		/**
		 * return true if the vector is unit
		 */
		bool IsUnit() const;

		/**
		 * Return true if the vector is zero
		*/
		bool IsZero() const;

		/**
		 * Return the vector projected on a normal
		 * @param p_target
		 * @param p_onNormal
		 */
		static FVec3 Project(const FVec3& p_target, const FVec3& p_onNormal);

		/**
		 * Return the vector reflected on a normal
		 * @param p_target
		 * @param p_onNormal
		 */
		static FVec3 Reflect(const FVec3& p_target, const FVec3& p_onNormal);

		/**
		 * Return the vector refracted on a normal
		 * @param p_target
		 * @param p_onNormal
		 * @param p_refractiveIndex
		 */
		static FVec3 Refract(const FVec3& p_target, const FVec3& p_onNormal, float p_refractiveIndex);
	};

	/**
	 * Return the vector as a string
	 * @param p_stream
	 * @param p_vec
	*/
	std::ostream& operator<<(std::ostream& p_stream, const FVec3& p_vec);

	/**
	 * input a vector from a string
	 * @param p_stream
	 * @param p_vec
	*/
	std::istream& operator>>(std::istream& p_stream, FVec3& p_vec);

	/**
	 * Return the multiplication of a vector with a scalar
	 * @param p_scalar
	 * @param p_vec
	*/
	FVec3 operator*(float p_scalar, const FVec3& p_vec);

	FVec3 operator*(const FVec3& p_vec, const FVec3& p_vec2);

	/**
	 * Return the division of scalar and actual vector
	 * @param p_scalar
	 * @param p_vec
	*/
	FVec3 operator/(float p_scalar, const FVec3& p_vec);
}