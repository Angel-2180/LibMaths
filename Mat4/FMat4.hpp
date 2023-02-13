#pragma once

#include <iostream>

#include "../Utilities.h"
#include "../Vec4/FVec4.hpp"

namespace lm
{
    struct FVec3;
    struct FQuat;
    struct FMat3;
    /**
     * @brief A 4x4 matrix made of 4 FVec4 rows
    */
    struct FMat4
    {
        FVec4 m_matrix[4];

        static const FMat4 IdentityMatrix;

        /**
         *  @brief Creates a new matrix with all values set to 0
        */
        FMat4() = default;

        /**
         * @brief Creates a new matrix with diagonal set to p_init
         * @param p_init The value to set the diagonal to
         * @note The other values are set to 0
        */
        FMat4(float p_init);

        /**
         * @brief Creates a new matrix with the given values
         * @param p_row1 The first row
         * @param p_row2 The second row
         * @param p_row3 The third row
         * @param p_row4 The fourth row
        */
        FMat4(FVec4 p_row1, FVec4 p_row2, FVec4 p_row3, FVec4 p_row4);

        FMat4(const FVec3& p_position, const FQuat& p_rotation);

        /**
         * @brief Creates a new matrix by copying the values from another matrix
         * @param p_toCopy The matrix to copy the values from
        */
        FMat4(const FMat4& p_toCopy);
        FMat4(FMat4&& p_toMove) noexcept = default;
        FMat4& operator=(const FMat4& p_other);
        FMat4& operator=(FMat4&& p_other) noexcept = default;
        ~FMat4() = default;

        FMat4 operator*(const FMat4& p_other) const;
        FMat4& operator*=(const FMat4& p_other);
        FVec4 operator*(const FVec4& p_other) const;
        FMat4 operator*(float p_scalar) const;
        FMat4& operator*=(float p_scalar);
        FMat4 operator/(float p_scalar) const;
        FMat4& operator/=(float p_scalar);
        FMat4 operator+(const FMat4& p_other) const;
        FMat4& operator+=(const FMat4& p_other);
        FMat4 operator-(const FMat4& p_other) const;
        FMat4& operator-=(const FMat4& p_other);
        bool operator==(const FMat4& p_other) const;
        bool operator!=(const FMat4& p_other) const;
        FVec4& operator[](int p_index);
        const FVec4& operator[](int p_index) const;
        float operator()(int p_row, int p_column);
        const float operator()(int p_row, int p_column) const;
        float& operator[](const char* p_index);
        const float& operator[](const char* p_index) const;
        FMat4 operator-() const;

        /**
         * @brief Creates a new identity matrix
        */
        static FMat4 Identity();

        /**
         * @brief Creates a new translation matrix
         * @param p_translation The translation vector
        */
        static FMat4 Translation(const FVec3& p_translation);

        /**
         * @brief Creates a new rotation matrix
         * @param p_rotation The rotation vector
         * @note The rotation vector is in radians
        */
        static FMat4 Rotation(const FVec3& p_rotation);

        /**
         * @brief Creates a new scale matrix
         * @param p_scale The scale vector
        */
        static FMat4 Scale(const FVec3& p_scale);

        /**
         * @brief Create a new look at matrix
         * @param p_eye The eye position
         * @param p_target The target position
         * @param p_up The up vector
         * @return The look at matrix
         * @note The up vector must be normalized
         * @note The eye and target vectors must be different
        */
        static FMat4 LookAt(const FVec3& p_eye, const FVec3& p_target, const FVec3& p_up);

        /**
         * @brief Creates a new perspective matrix
         * @param p_fov The field of view
         * @param p_aspectRatio The aspect ratio
         * @param p_near The near plane
         * @param p_far The far plane
         * @return The perspective matrix
         * @note The near plane must be greater than 0
         * @note The far plane must be greater than the near plane
        */
        static FMat4 Perspective(float p_fov, float p_aspectRatio, float p_near, float p_far);

        /**
         * @brief Creates a new orthographic matrix
         * @param p_left The left plane
         * @param p_right The right plane
         * @param p_bottom The bottom plane
         * @param p_top The top plane
         * @param p_near The near plane
         * @param p_far The far plane
         * @return The orthographic matrix
         * @note The near plane must be greater than 0
         * @note The far plane must be greater than the near plane
        */
        static FMat4 Orthographic(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far);

        /**
         * @brief Transposes a matrix
         * @param p_matrix The matrix to transpose
         * @return The transposed matrix
        */
        static FMat4 Transpose(const FMat4& p_matrix);

        /**
         * @brief Translates a matrix
         * @param p_matrix The matrix to translate
         * @param p_translation The translation vector
         * @return The translated matrix
        */
        static FMat4 Translate(const FMat4& p_matrix, const FVec3& p_translation);

        /**
         * @brief Rotates a matrix
         * @param p_matrix The matrix to rotate
         * @param p_rotation The rotation vector
         * @return The rotated matrix
         * @note The rotation vector is in degrees
        */
        static FMat4 Rotate(const FMat4& p_matrix, const FVec3& p_rotation);

        /**
         * @brief Scales a matrix
         * @param p_matrix The matrix to scale
         * @param p_scale The scale vector
         * @return The scaled matrix
        */
        static FMat4 Scale(const FMat4& p_matrix, const FVec3& p_scale);

        /**
         * @brief Multiplies two matrices
         * @param p_matrix1 The first matrix
         * @param p_matrix2 The second matrix
         * @return The multiplied matrix
        */
        static FMat4 Multiply(const FMat4& p_matrix1, const FMat4& p_matrix2);

        /**
         * @brief Creates a new transformation matrix
         * @param p_translation The translation vector
         * @param p_rotation The rotation vector
         * @param p_scale The scale vector
         * @return The transformation matrix
         * @note The rotation vector is in degrees
        */
        static FMat4 Transform(const FVec3& p_translation, const FVec3& p_rotation, const FVec3& p_scale);

        /**
         * @brief Creates a new Rotation matrix around the X axis
         * @param p_angle The angle of rotation
         * @return The rotation matrix
         * @note The angle is in degrees
         * @note The matrix is not multiplied by the current matrix
        */
        static FMat4 XRotation(float p_angle);

        /**
         * @brief Creates a new Rotation matrix around the X axis from the passed matrix
         * @param p_matrix The matrix to rotate
         * @param p_angle The angle of rotation
         * @return The rotation matrix
         * @note The angle is in degrees
        */
        static FMat4 XRotation(const FMat4& p_matrix, float p_angle);

        /**
         * @brief Creates a new Rotation matrix around the Y axis
         * @param p_angle The angle of rotation
         * @return The rotation matrix
         * @note The angle is in degrees
         * @note The matrix is not multiplied by the current matrix
        */
        static FMat4 YRotation(float p_angle);

        /**
         * @brief Creates a new Rotation matrix around the Y axis from the passed matrix
         * @param p_matrix The matrix to rotate
         * @param p_angle The angle of rotation
         * @return The rotation matrix
         * @note The angle is in degrees
        */
        static FMat4 YRotation(const FMat4& p_matrix, float p_angle);

        /**
         * @brief Creates a new Rotation matrix around the Z axis
         * @param p_angle The angle of rotation
         * @return The rotation matrix
         * @note The angle is in degrees
         * @note The matrix is not multiplied by the current matrix
        */
        static FMat4 ZRotation(float p_angle);

        /**
         * @brief Creates a new Rotation matrix around the Z axis from the passed matrix
         * @param p_matrix The matrix to rotate
         * @param p_angle The angle of rotation
         * @return The rotation matrix
         * @note The angle is in degrees
        */
        static FMat4 ZRotation(const FMat4& p_matrix, float p_angle);

        /**
         * @brief Creates a new Rotation matrix using the ZXY rotation order
         * @param p_angle The angle of rotation
         * @return The rotation matrix
         * @note The angle is in degrees
         * @note The matrix is not multiplied by the current matrix
        */
        static FMat4 XYZRotation(const FVec3& p_rotation);

        /**
         * @brief Creates a new Rotation matrix using the ZXY rotation order from the passed matrix
         * @param p_matrix The matrix to rotate
         * @param p_angle The angle of rotation
         * @return The rotation matrix
         * @note The angle is in degrees
        */
        static FMat4 XYZRotation(const FMat4& p_matrix, const FVec3& p_rotation);

        /**
         * @brief Converts the matrix to an array
         * @return The array
        */
        static float* ToArray(const FMat4& p_matrix);

        /*
        * @brief Converts a 3x3 matrix to a 4x4 matrix
        * @param p_matrix The 3x3 matrix
        * @return The 4x4 matrix
        */
        static FMat4 ToMat4(const FMat3& p_matrix);

        /**
         * @brief inverts a matrix
         * @param p_matrix The matrix to invert
         * @return The inverted matrix
        */
        static FMat4 Inverse(const FMat4& p_matrix);
    };

    std::ostream& operator<<(std::ostream& p_stream, const FMat4& p_matrix);

    std::istream& operator>>(std::istream& p_stream, FMat4& p_matrix);

    FMat4 operator*(float p_scalar, const FMat4& p_matrix);

    FMat4 operator/(float p_scalar, const FMat4& p_matrix);
}