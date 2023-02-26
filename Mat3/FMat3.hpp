#pragma once

#include <iostream>

#include "../Utilities.h"
#include "../Vec3/FVec3.hpp"

namespace lm
{
	struct FQuat;
	struct FMat4;
	struct FMat3
	{
		FVec3 m_matrix[3];

		static const FMat3 identity;

		FMat3() = default;
		FMat3(const float init);
		FMat3(float p_00, float p_01, float p_02, float p_10, float p_11,
			float p_12, float p_20, float p_21, float p_22);
		FMat3(const FVec3& v1, const FVec3& v2, const FVec3& v3);
		FMat3(const FMat3& mat3);
		FMat3(FMat3&& mat3) noexcept = default;
		FMat3(const FMat4& mat4);
		FMat3(FMat4&& mat4) noexcept;

		~FMat3() = default;

		FMat3& operator=(const FMat3& mat3);
		FMat3& operator=(FMat3&& mat3) noexcept = default;
		FVec3& operator[](const unsigned int index);
		const FVec3& operator[](const unsigned int index) const;


		FMat3 operator+(const FMat3& mat3) const;
		FMat3 operator-(const FMat3& mat3) const;
		FMat3 operator*(const FMat3& mat3) const;
		FMat3 operator*(const float scalar) const;
		FMat3 operator/(const float scalar) const;
		FMat3& operator+=(const FMat3& mat3);
		FMat3& operator-=(const FMat3& mat3);
		FMat3& operator*=(const FMat3& mat3);
		FMat3& operator*=(const float scalar);
		FMat3& operator/=(const float scalar);
		FMat3 operator-() const;
		bool operator==(const FMat3& mat3) const;
		bool operator!=(const FMat3& mat3) const;

		/**
		 * @brief Returns the identity matrix
		 * @return FMat3
		 * @note The identity matrix is a square matrix with ones on the main diagonal and zeros elsewhere.
		*/
		static FMat3 Identity();

		/**
		 * @brief Returns the transpose of the given matrix
		 * @param mat3 Matrix to transpose
		 * @return FMat3 Transpose of the given matrix
		 * @note The transpose of a matrix is another matrix obtained by changing rows to columns and columns to rows.
		*/
		static FMat3 Transpose(const FMat3& mat3);

		/**
		 * @brief Returns the determinant of the given matrix
		 * @param mat3 Matrix to get the determinant of
		 * @return float Determinant of the given matrix
		 * @note The determinant of a matrix is a scalar value that can be computed from the elements of a square matrix and encodes certain properties of the linear transformation described by the matrix.
		*/
		static float Determinant(const FMat3& mat3);

		/**
		 * @brief Returns the adjugate of the given matrix
		 * @param mat3 Matrix to get the adjugate of
		 * @return FMat3 Adjugate of the given matrix
		 * @note The adjugate of a matrix is the transpose of the cofactor matrix of the given matrix.
		*/
		static FMat3 Inverse(const FMat3& mat3);

		/**
		 * @brief Returns the rotation matrix of the given angle and axis
		 * @param angle Angle to rotate by
		 * @param axis Axis to rotate around
		 * @return FMat3 Rotation matrix of the given angle and axis
		 * @note The rotation matrix is a matrix that describes a rotation in 3D space.
		 * @note The Angle must be in Degrees.
		*/
		static FMat3 Rotation(const float angle, const FVec3& axis);


		static FMat3 Rotate(const FMat3& p_mat3, const float p_angle, const FVec3& p_axis);

		/**
		 * @brief Returns the scale matrix of the given scale
		 * @param x Scale on the x-axis
		 * @param y Scale on the y-axis
		 * @param z Scale on the z-axis
		 * @return FMat3 Scale matrix of the given scale
		*/
		static FMat3 Scale(const float x, const float y, const float z);

		/**
		 * @brief Returns the scale matrix of the given scale
		 * @param scale FVec3 to scale by
		 * @return FMat3 Scale matrix of the given scale
		*/
		static FMat3 Scale(const FVec3& scale);

		/**
		 * @brief Returns the scale matrix of the given scale
		 * @param scale Scale to scale by
		 * @return FMat3 Scale matrix of the given scale
		*/
		static FMat3 Scale(const float scale);


		/**
		 * @brief Returns the Multiplied matrix of the given matrix and scalar
		 * @param mat3 Matrix to multiply
		 * @param scalar Scalar to multiply by
		 * @return FMat3 Multiplied matrix of the given matrix and scalar
		 * @note The multiplication of a matrix by a scalar is a matrix obtained by multiplying each element of the matrix by the scalar.
		*/
		static FMat3 Multiply(const FMat3& mat3, const float scalar);

		/**
		 * @brief Returns the Multiplied matrix of the given matrix and matrix
		 * @param mat3 Matrix to multiply
		 * @param mat3_2 Matrix to multiply by
		 * @return FMat3 Multiplied matrix of the given matrix and matrix
		 * @note The multiplication of two matrices is a matrix obtained by multiplying each element of the matrix by the scalar.
		*/
		static FMat3 Multiply(const FMat3& mat3, const FMat3& mat3_2);

		/**
		 * @brief Returns the Multiplied matrix of the given matrix and vector
		 * @param mat3 Matrix to multiply
		 * @param vec3 Vector to multiply by
		 * @return FMat3 Multiplied matrix of the given matrix and vector
		 * @note The multiplication of a matrix by a vector is a vector obtained by multiplying each element of the matrix by the vector.
		*/
		static FMat3 Multiply(const FMat3& mat3, const FVec3& vec3);

		/**
		 * @brief Returns the Added matrix of the given matrix and matrix
		 * @param mat3 Matrix to add
		 *  @param mat3_2 Matrix to add by
		 * @return FMat3 Added matrix of the given matrix and matrix
		 * @note The addition of two matrices is a matrix obtained by adding each element of the matrix by the scalar.
		*/
		static FMat3 Add(const FMat3& mat3, const FMat3& mat3_2);

		/**
		 * @brief Returns the Subtracted matrix of the given matrix and matrix
		 * @param mat3 Matrix to subtract
		 * @param mat3_2 Matrix to subtract by
		 * @return FMat3 Subtracted matrix of the given matrix and matrix
		 * @note The subtraction of two matrices is a matrix obtained by subtracting each element of the matrix by the scalar.
		*/
		static FMat3 Subtract(const FMat3& mat3, const FMat3& mat3_2);

		/**
		 * @brief Returns the Divided matrix of the given matrix and scalar
		 * @param mat3 Matrix to divide
		 * @param scalar Scalar to divide by
		 * @return FMat3 Divided matrix of the given matrix and scalar
		 * @note The division of a matrix by a scalar is a matrix obtained by dividing each element of the matrix by the scalar.
		*/
		static FMat3 Divide(const FMat3& mat3, const float scalar);

		/**
		 * @brief Returns the Divided matrix of the given matrix and matrix
		 * @param mat3 Matrix to divide
		 * @param mat3_2 Matrix to divide by
		 * @return FMat3 Divided matrix of the given matrix and matrix
		 * @note The division of two matrices is a matrix obtained by dividing each element of the matrix by the scalar.
		*/
		static FMat3 Divide(const FMat3& mat3, const FMat3& mat3_2);

		/**
		 * @brief Returns the array of the given matrix
		 * @param mat3 Matrix to convert to array
		 * @return float* Array of the given matrix
		*/
		static float* ToArray(const FMat3& mat3);


	};

	std::ostream& operator<<(std::ostream& os, const FMat3& mat3);
	std::istream& operator>>(std::istream& is, FMat3& mat3);

	FMat3 operator*(const float scalar, const FMat3& mat3);
	FMat3 operator/(const float scalar, const FMat3& mat3);

	FMat3 operator*(const FMat3& p_mat, const FVec3& p_vec);
	FMat3 operator*(const FVec3& vec3, const FMat3& mat3);
}