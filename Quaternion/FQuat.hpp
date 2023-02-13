#pragma once

#include <stdexcept>

namespace lm
{
    struct FVec3;
    struct FVec4;
    struct FMat4;
    struct FMat3;

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
        FQuat(const FMat3& other);

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
        static float Length2(FQuat const& p);

        /**
         * @brief Get the Length of the quaternion
         * @details Get the Length of the quaternion
         * @return The length of the quaternion
         * @note This is slower than length2() because it involves a square root
        */
        static float Length(FQuat const& p);

        /**
         * @brief Normalize the quaternion
         * @details Normalize the quaternion
         * @return A new quaternion with the same direction as the original but with a length of 1
         * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
        */
        static FQuat Normalize(FQuat const& p);

        /**
         * @brief Get the conjugate of the quaternion
         * @details Get the conjugate of the quaternion
         * @return A new quaternion with the same direction as the original but with a length of 1
         * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
        */
        static FQuat Conjugate(FQuat const& p);

        /**
         * @brief Get the inverse of the quaternion
         * @details Get the inverse of the quaternion
         * @return A new quaternion with the same direction as the original but with a length of 1
         * @note If the length of the quaternion is 0, the quaternion (0, 0, 0, 1) is returned
        */
        static FQuat Inverse(FQuat const& p);

        /**
         * @brief Get the dot product of two quaternions
         * @details Get the dot product of two quaternions
         * @param p The other quaternion
         * @return The dot product of the two quaternions
        */
        static float Dot(FQuat const& p, FQuat const& q);

        /**
         * @brief Get the cross product of two quaternions
         * @details Get the cross product of two quaternions
         * @param p The other quaternion
         * @return The cross product of the two quaternions
        */
        static FQuat Cross(FQuat const& p, FQuat const& q);

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
        static FQuat Rotate(FQuat const& q, FVec3 const& v);

        /**
         * @brief Rotates a quaternion around a quaternion.
         * @param q The quaternion to rotate around.
         * @returns The rotated quaternion.
         * @note The quaternion must be normalized.
        */
        static FQuat Rotate(FQuat const& p, FQuat const& q);

        /**
         * @brief Rotates a quaternion around a vector by a given angle.
         * @param v The vector to rotate around.
         * @param angle The angle to rotate.
         * @returns The rotated quaternion.
         * @note The vector must be normalized.
         * @note The angle is in degrees.
        */
        static FQuat Rotate(FQuat const& q, FVec3 const& v, float const& angle);

        /**
         * @brief Create a Matrix3 from a quaternion.
         * @return The matrix.
         * @note The matrix is a rotation matrix.
         *
        */
        static FMat3 ToMatrix3(FQuat const& q);

        /**
         * @brief Create a FQuat from a Matrix3.
         * @param m The matrix.
         * @return The quaternion.
         * @note The matrix must be a rotation matrix.
        */
        static FQuat FromMatrix3(FMat3 const& m);

        /**
         * @brief Lerps between two quaternions
         * @param q1 The first quaternion
         * @param q2 The second quaternion
         * @param t The interpolation factor
         * @return The interpolated quaternion
         * @note The interpolation factor must be between 0 and 1
        */
        static FQuat Lerp(FQuat const& q1, FQuat const& q2, float t);

        /*
        *	@brief NLerp between two quaternions
        *	@param q1 The first quaternion
        *	@param q2 The second quaternion
        *	@param t The interpolation factor
        *	@return The interpolated quaternion
        *	@note The interpolation factor must be between 0 and 1
        */
        static FQuat NLerp(FQuat const& q1, FQuat const& q2, float t);

        /*
        *	@brief SLerp between two quaternions
        *	@param q1 The first quaternion
        *	@param q2 The second quaternion
        *	@param t The interpolation factor
        *	@return The interpolated quaternion
        */
        static FQuat SLerp(FQuat const& q1, FQuat const& q2, float t);
    };

    FVec3 operator*(const FVec3& v, FQuat const& q);

    FVec4 operator*(const FVec4& v, FQuat const& q);

    FQuat operator*(float const& s, FQuat const& q);

    std::ostream& operator<<(std::ostream& os, FQuat const& q);

    std::istream& operator>>(std::istream& is, FQuat& q);
}