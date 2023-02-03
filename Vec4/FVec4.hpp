#pragma once

namespace lm
{
	struct FVec4
	{
		static const FVec4 One;
		static const FVec4 Zero;

		float x;
		float y;
		float z;
		float w;

		/**
		* Default constructor
		* @param p_x
		* @param p_y
		* @param p_z
		* @param p_w
		*/
		FVec4(float p_x = 0.0f, float p_y = 0.0f, float p_z = 0.0f, float p_w = 0.0f);

		/**
		* Copy constructor
		* @param p_toCopy
		*/
		FVec4(const FVec4& p_toCopy);

		/**
		* Move constructor
		* @param p_toMove
		*/
		FVec4(FVec4&& p_toMove) noexcept = default;

		FVec4(const struct FVec3& p_toCopy, float p_w = 0.0f);

		/**
		* Negation
		*/
		FVec4 operator-() const;

		/**
		* Copy assignment
		* @param p_other
		*/
		FVec4 operator=(const FVec4& p_other);

		/**
		* Calculate the sum of two vectors
		* @param p_other
		*/
		FVec4 operator+(const FVec4& p_other) const;

		/**
		* Add the right vector to the left one
		* @param p_other
		*/
		FVec4& operator+=(const FVec4& p_other);

		/**
		* Calculate the substraction of two vectors
		* @param p_other
		*/
		FVec4 operator-(const FVec4& p_other) const;

		/**
		* Remove the right vector from the left one
		* @param p_other
		*/
		FVec4& operator-=(const FVec4& p_other);

		/**
		* Calcualte the multiplication of a vector with a scalar
		* @param p_scalar
		*/
		FVec4 operator*(float p_scalar) const;

		/**
		* Multiply the vector by a scalar
		* @param p_scalar
		*/
		FVec4& operator*=(float p_scalar);

		/**
		* Return the division of scalar and actual vector
		* @param p_scalar
		*/
		FVec4 operator/(float p_scalar) const;

		/**
		* Divide scalar to the actual vector
		* @param p_scalar
		*/
		FVec4& operator/=(float p_scalar);

		/**
		* Return true if the two vectors are equals
		* @param p_other
		*/
		bool operator==(const FVec4& p_other);

		/**
		* Return true if the two vectors are different
		* @param p_other
		*/
		bool operator!=(const FVec4& p_other);

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
		static FVec4 Add(const FVec4& p_left, const FVec4& p_right);

		/**
		* Calculate the substraction of two vectors
		* @param p_left (First vector)
		* @param p_right (Second vector)
		*/
		static FVec4 Substract(const FVec4& p_left, const FVec4& p_right);

		/**
		* Calculate the multiplication of a vector with a scalar
		* @param p_target
		* @param p_scalar
		*/
		static FVec4 Multiply(const FVec4& p_target, float p_scalar);

		/**
		* Divide scalar to vector left
		* @param p_left
		* @param p_scalar
		*/
		static FVec4 Divide(const FVec4& p_left, float p_scalar);

		/**
		* Return the length of a vector
		* @param p_target
		*/
		static float Length(const FVec4& p_target);

		/**
		* Return the dot product of two vectors
		* @param p_left
		* @param p_right
		*/
		static float Dot(const FVec4& p_left, const FVec4& p_right);

		/**
		* Return the normalize of the given vector
		* @param p_target
		*/
		static FVec4 Normalize(const FVec4& p_target);

		/**
		* Calculate the interpolation between two vectors
		* @param p_start
		* @param p_end
		* @param p_alpha
		*/
		static FVec4 Lerp(const FVec4& p_start, const FVec4& p_end, float p_alpha);

		/**
		 * Calculate the interpolation between two vectors
		 * @param p_start
		 * @param p_end
		 * @param p_alpha
		 */

		static FVec4 Slerp(const FVec4& p_start, const FVec4& p_end, float p_alpha);

		/**
		 * Return the min vector between two vectors
		 * @param p_target
		 * @param p_min
		 * @param p_max
		 */
		static FVec4 Clamp(const FVec4& p_target, const FVec4& p_min, const FVec4& p_max);

		/**
		 * Homogenize the vector
		*/
		void Homogenize();

		/**
		 * Return true if the vector is homogenized
		*/
		bool IsHomogenized() const;

		/**
		 * Return true if the vector is zero
		*/
		bool IsZero() const;

		/**
		 * Return true if the vector is unit
		*/
		bool IsUnit() const;
	};

	/**
	 * Return the vector as a string
	 * @param p_stream
	 * @param p_vec
	*/
	std::ostream& operator<<(std::ostream& p_stream, const FVec4& p_vec);

	/**
	 * input a vector from a string
	 * @param p_stream
	 * @param p_vec
	*/
	std::istream& operator>>(std::istream& p_stream, FVec4& p_vec);

	/**
	 * Return the multiplication of a vector with a scalar
	 * @param p_scalar
	 * @param p_vec
	*/
	FVec4 operator*(float p_scalar, const FVec4& p_vec);

	/**
	 * Return the division of scalar and actual vector
	 * @param p_scalar
	 * @param p_vec
	*/
	FVec4 operator/(float p_scalar, const FVec4& p_vec);
}