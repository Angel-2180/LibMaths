#pragma once

namespace lm
{
	struct FVec2
	{
		static const FVec2 One;
		static const FVec2 Zero;

		float x;
		float y;

		/**
		* Default constructor
		* @param p_x
		* @param p_y
		*/
		FVec2(float p_x = 0.0f, float p_y = 0.0f);

		/**
		* Copy constructor
		* @param p_toCopy
		*/
		FVec2(const FVec2& p_toCopy);

		/**
		* Move constructor
		* @param p_toMove
		*/
		FVec2(FVec2&& p_toMove) noexcept = default;

		/**
		* Negation
		*/
		FVec2 operator-() const;

		/**
		* Copy assignment
		* @param p_other
		*/
		FVec2 operator=(const FVec2& p_other);

		/**
		* Calculate the sum of two vectors
		* @param p_other
		*/
		FVec2 operator+(const FVec2& p_other) const;

		/**
		* Add the right vector to the left one
		* @param p_other
		*/
		FVec2& operator+=(const FVec2& p_other);

		/**
		* Calculate the substraction of two vectors
		* @param p_other
		*/
		FVec2 operator-(const FVec2& p_other) const;

		/**
		* Remove the right vector from the left one
		* @param p_other
		*/
		FVec2& operator-=(const FVec2& p_other);

		/**
		* Calcualte the multiplication of a vector with a scalar
		* @param p_scalar
		*/
		FVec2 operator*(float p_scalar) const;

		/**
		* Multiply the vector by a scalar
		* @param p_scalar
		*/
		FVec2& operator*=(float p_scalar);

		/**
		* Return the division of scalar and actual vector
		* @param p_scalar
		*/
		FVec2 operator/(float p_scalar) const;

		/**
		* Divide scalar to the actual vector
		* @param p_scalar
		*/
		FVec2& operator/=(float p_scalar);

		/**
		* Return true if the two vectors are equals
		* @param p_other
		*/
		bool operator==(const FVec2& p_other);

		/**
		* Return true if the two vectors are different
		* @param p_other
		*/
		bool operator!=(const FVec2& p_other);

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
		static FVec2 Add(const FVec2& p_left, const FVec2& p_right);

		/**
		* Calculate the substraction of two vectors
		* @param p_left (First vector)
		* @param p_right (Second vector)
		*/
		static FVec2 Substract(const FVec2& p_left, const FVec2& p_right);

		/**
		* Calculate the multiplication of a vector with a scalar
		* @param p_target
		* @param p_scalar
		*/
		static FVec2 Multiply(const FVec2& p_target, float p_scalar);

		/**
		* Divide scalar to vector left
		* @param p_left
		* @param p_scalar
		*/
		static FVec2 Divide(const FVec2& p_left, float p_scalar);

		/**
		* Return the length of a vector
		* @param p_target
		*/
		static float Length(const FVec2& p_target);

		/**
		* Return the dot product of two vectors
		* @param p_left
		* @param p_right
		*/
		static float Dot(const FVec2& p_left, const FVec2& p_right);

		/**
		* Return the normalize of the given vector
		* @param p_target
		*/
		static FVec2 Normalize(const FVec2& p_target);

		/**
		* Calculate the interpolation between two vectors
		* @param p_start
		* @param p_end
		* @param p_alpha
		*/
		static FVec2 Lerp(const FVec2& p_start, const FVec2& p_end, float p_alpha);

		/**
		* Calculate the angle between two vectors
		* @param p_from
		* @param p_to
		*/
		static float AngleBetween(const FVec2& p_from, const FVec2& p_to);
		/**
	* Return the slerp between two vectors
	 * @param p_start
	 * @param p_end
	 * @param p_alpha
	*/
		static FVec2 Slerp(const FVec2& p_start, const FVec2& p_end, float p_alpha);

		/**
		 * Return the min vector between two vectors
		 * @param p_target
		 * @param p_min
		 * @param p_max
		 */
		static FVec2 Clamp(const FVec2& p_target, const FVec2& p_min, const FVec2& p_max);

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
		static FVec2 Project(const FVec2& p_target, const FVec2& p_onNormal);

		/**
		 * Return the vector reflected on a normal
		 * @param p_target
		 * @param p_onNormal
		 */
		static FVec2 Reflect(const FVec2& p_target, const FVec2& p_onNormal);
	};
	/**
 * Return the vector as a string
 * @param p_stream
 * @param p_vec
*/
	std::ostream& operator<<(std::ostream& p_stream, const FVec2& p_vec);

	/**
	 * input a vector from a string
	 * @param p_stream
	 * @param p_vec
	*/
	std::istream& operator>>(std::istream& p_stream, FVec2& p_vec);

	/**
	 * Return the multiplication of a vector with a scalar
	 * @param p_scalar
	 * @param p_vec
	*/
	FVec2 operator*(float p_scalar, const FVec2& p_vec);

	/**
	 * Return the division of scalar and actual vector
	 * @param p_scalar
	 * @param p_vec
	*/
	FVec2 operator/(float p_scalar, const FVec2& p_vec);
}