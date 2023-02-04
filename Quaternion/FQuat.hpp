#pragma once

#include <stdexcept>

#include "../Mat3/FMat3.hpp"
#include "../Mat4/FMat4.hpp"
#include "../Vec3/FVec3.hpp"
#include "../Vec4/FVec4.hpp"



namespace lm
{
	struct FQuat
	{
	public:
		float x, y, z, w;

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
		FQuat();

		/**
		 * @brief Constructor
		 * @details Set all components to the same value
		 * @param value Value to set all components to
		 * @return A new quaternion with all components set to value
		*/
		FQuat(float x, float y, float z, float w);

		/**
		 * @brief Constructor copy
		 * @details Copy all components from another quaternion
		 * @param q FQuat to copy from
		 * @return A new quaternion with the same components as q
		*/
		FQuat(FQuat const& q);

		FQuat(FQuat&& p_toMove) noexcept = default;

		/**
		 * @brief Constructor from axis and angle
		 * @details Create a quaternion from an axis and an angle
		 * @param axis Axis to rotate around
		 * @param angle Angle to rotate
		 * @return A new quaternion with the same components as q
		 * @note The angle is in degrees
		*/
		FQuat(FVec3 axis, float angle);

		/**
		 * @brief Constructor from matrix
		 * @details Create a quaternion from a matrix
		 * @param other Matrix to convert
		 * @return A new quaternion with the same components as q
		*/
		FQuat(const Mat3& other);

		~FQuat() = default;

		static const FQuat identity;

		/************************************\
		*                                    *
		*             Accessor               *
		*                                    *
		\************************************/

		float& operator[](const int index);

		const float operator[](const int index) const;

		/**
		 * @brief Get the vector part of the quaternion
		 * @details Get the vector part of the quaternion
		 * @return A new vector with the same components as the vector part of the quaternion
		*/
		const FVec3& getVec3Part() const;

		/**
		 * @brief Get the vector part of the quaternion
		 * @details Get the vector part of the quaternion
		 * @return A new vector with the same components as the vector part of the quaternion
		*/
		const FVec4& getVec4Part() const;

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
		float length2() const;

		/**
		 * @brief Get the Length of the quaternion
		 * @details Get the Length of the quaternion
		 * @return The length of the quaternion
		 * @note This is slower than length2() because it involves a square root
		*/
		float length() const;

		/**
		 * @brief Normalize the quaternion
		 * @details Normalize the quaternion
		 * @return A new quaternion with the same direction as the original but with a length of 1
		 * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
		*/
		FQuat normalize() const;


		/**
		 * @brief Get the conjugate of the quaternion
		 * @details Get the conjugate of the quaternion
		 * @return A new quaternion with the same direction as the original but with a length of 1
		 * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
		*/
		FQuat conjugate() const;

		/**
		 * @brief Get the inverse of the quaternion
		 * @details Get the inverse of the quaternion
		 * @return A new quaternion with the same direction as the original but with a length of 1
		 * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
		*/
		FQuat inverse() const;

		/**
		 * @brief Get the dot product of two quaternions
		 * @details Get the dot product of two quaternions
		 * @param p The other quaternion
		 * @return The dot product of the two quaternions
		*/
		float dot(FQuat const& p) const;

		/**
		 * @brief Get the cross product of two quaternions
		 * @details Get the cross product of two quaternions
		 * @param p The other quaternion
		 * @return The cross product of the two quaternions
		*/
		const FQuat cross(FQuat const& q) const;

		/************************************\
		*                                    *
		*             Arithmetic             *
		*                                    *
		\************************************/

		// -- Unary arithmetic operators --

		FQuat operator=(FQuat const& q);

		FQuat operator+=(FQuat const& q);

		FQuat operator-=(FQuat const& q);

		FQuat operator*=(FQuat const& r);

		FQuat operator*=(const float s);

		FQuat operator/=(const float s);

		// -- Unary bit operators --

		FQuat operator-() const;

		// -- Binary operators --

		const FQuat operator+(FQuat const& q) const;

		const FQuat operator-(FQuat const& q) const;

		const FQuat operator*(FQuat const& p) const;

		const FQuat operator*(float const& s) const;

		const FVec3 operator*(FVec3 const& v) const;

		const FVec4 operator*(FVec4 const& v) const;

		const FQuat operator/(const float s) const;

		// -- Boolean operators --

		bool operator==(FQuat const& q) const;

		bool operator!=(FQuat const& q) const;
		/**
		 * @brief Returns true if the quaternion is a unit quaternion.
		 * @return True if the quaternion is a unit quaternion.
		 * @note A unit quaternion is a quaternion with a length of 1.
		 * @note This function is not very accurate.
		*/
		bool isUnit() const;

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
		float getAngle() const;

		/**
		 * @brief Returns the angle from this quaternion to another quaternion.
		 * @param q The quaternion.
		 * @return The angle of the quaternion.
		 * @note The angle is in radians.
		*/
		float getAngle(FQuat const& q) const;

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
		FQuat rotate(const FVec3& v) const;

		/**
		 * @brief Rotates a quaternion around a quaternion.
		 * @param q The quaternion to rotate around.
		 * @returns The rotated quaternion.
		 * @note The quaternion must be normalized.
		*/
		FQuat rotate(FQuat const& q) const;

		/**
		 * @brief Rotates a quaternion around a vector by a given angle.
		 * @param v The vector to rotate around.
		 * @param angle The angle to rotate.
		 * @returns The rotated quaternion.
		 * @note The vector must be normalized.
		 * @note The angle is in degrees.
		*/
		FQuat rotate(const FVec3& axis, float angle);

		/**
		 * @brief Create a Matrix3 from a quaternion.
		 * @return The matrix.
		 * @note The matrix is a rotation matrix.
		 *
		*/
		Mat3 toMatrix3() const;

		/**
		 * @brief Create a FQuat from a Matrix3.
		 * @param m The matrix.
		 * @return The quaternion.
		 * @note The matrix must be a rotation matrix.
		*/
		FQuat fromMatrix3(const Mat3& m);
	};

	static FVec3 operator*(const FVec3& v, FQuat const& q);

	static FVec4 operator*(const FVec4& v, FQuat const& q);

	static FQuat operator*(float const& s, FQuat const& q);

	std::ostream& operator<<(std::ostream& os, FQuat const& q);

	std::istream& operator>>(std::istream& is, FQuat& q);
}