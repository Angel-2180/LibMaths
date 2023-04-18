#pragma once

#include <iostream>

namespace lm
{
    /**
     * @brief A simple 3D vector structure with basic vector operations.
     */
    struct FVec3
    {
        /**
         * @brief A vector of all zeroes.
         */
        static const FVec3 Zero;

        /**
         * @brief A vector of all ones.
         */
        static const FVec3 One;

        /**
         * @brief A forward-facing unit vector.
         */
        static const FVec3 Forward;

        /**
         * @brief A right-facing unit vector.
         */
        static const FVec3 Right;

        /**
         * @brief An upward-facing unit vector.
         */
        static const FVec3 Up;

        /**
         * @brief The X component of the vector.
         */
        float x;

        /**
         * @brief The Y component of the vector.
         */
        float y;

        /**
         * @brief The Z component of the vector.
         */
        float z;

        /**
         * @brief Default constructor. Initializes all components to zero.
         */
        FVec3();

        /**
         * @brief Constructs a new vector with the given components.
         *
         * @param p_x The X component.
         * @param p_y The Y component.
         * @param p_z The Z component.
         */
        FVec3(float p_x, float p_y, float p_z);

        /**
         * @brief Constructs a new vector with all components set to the same value.
         *
         * @param p_init The initial value for all components.
         */
        FVec3(float p_init);

        /**
         * @brief Copy constructor.
         *
         * @param p_toCopy The vector to copy.
         */
        FVec3(const FVec3& p_toCopy);

        /**
         * @brief Move constructor.
         *
         * @param p_toMove The vector to move.
         */
        FVec3(FVec3&& p_toMove) noexcept = default;

        /**
         * @brief Negation operator. Returns the negated vector.
         *
         * @return The negated vector.
         */
        FVec3 operator-() const;

        /**
         * @brief Copy assignment operator.
         *
         * @param p_other The vector to copy.
         *
         * @return A reference to the modified vector.
         */
        FVec3 operator=(const FVec3& p_other);

        /**
         * @brief Addition operator. Returns the sum of two vectors.
         *
         * @param p_other The vector to add.
         *
         * @return The sum of the two vectors.
         */
        FVec3 operator+(const FVec3& p_other) const;

        /**
         * @brief Addition assignment operator. Adds another vector to this vector.
         *
         * @param p_other The vector to add.
         *
         * @return A reference to the modified vector.
         */
        FVec3& operator+=(const FVec3& p_other);

        /**
         * @brief Subtraction operator. Returns the difference between two vectors.
         *
         * @param p_other The vector to subtract.
         *
         * @return The difference between the two vectors.
         */
        FVec3 operator-(const FVec3& p_other) const;

        /**
         * @brief Subtraction assignment operator. Subtracts another vector from this vector.
         *
         * @param p_other The vector to subtract.
         *
         * @return A reference to the modified vector.
         */
        FVec3& operator-=(const FVec3& p_other);

        /**

@brief Calculate the division of two vectors.
@param p_other The vector to divide by.
@return A new vector that is the result of the division.
*/
FVec3& operator/(const FVec3& p_other);
/**

@brief Calculate the division of two vectors.
@param p_other The vector to divide by.
@return A new vector that is the result of the division.
*/
FVec3 operator/(const FVec3& p_other) const;
/**

@brief Calculate the multiplication of a vector with a scalar.
@param p_scalar The scalar to multiply with.
@return A new vector that is the result of the multiplication.
/
FVec3 operator(float p_scalar) const;
/**

@brief Multiply the vector by a scalar.
@param p_scalar The scalar to multiply with.
@return A reference to the modified vector.
/
FVec3& operator=(float p_scalar);
/**

@brief Return the division of scalar and actual vector.
@param p_scalar The scalar to divide by.
@return A new vector that is the result of the division.
*/
FVec3 operator/(float p_scalar) const;
/**

@brief Divide scalar to the actual vector.
@param p_scalar The scalar to divide by.
@return A reference to the modified vector.
*/
FVec3& operator/=(float p_scalar);
/**

@brief Check if two vectors are equal.
@param p_other The vector to compare against.
@return True if the two vectors are equal, false otherwise.
*/
bool operator==(const FVec3& p_other);
/**

@brief Check if two vectors are different.
@param p_other The vector to compare against.
@return True if the two vectors are different, false otherwise.
*/
bool operator!=(const FVec3& p_other);
/**

@brief Return the value of the vector at the given index.
@param p_index The index to get the value for.
@return A reference to the value at the given index.
*/
const float& operator[](int p_index) const;
/**

@brief Return the value of the vector at the given index.
@param p_index The index to get the value for.
@return A reference to the value at the given index.
*/
float& operator[](int p_index);
/**

@brief Return the value of the vector at the given index.
@param p_index The index to get the value for.
@return A reference to the value at the given index.
*/
const float& operator()(int p_index) const;
/**

@brief Return the value of the vector at the given index.
@param p_index The index to get the value for.
@return A reference to the value at the given index.
*/
float& operator()(int p_index);
/**

@brief Calculate the sum of two vectors.
@param p_left The first vector to add.
@param p_right The second vector to add.
@return A new vector that is the result of the addition.
*/
static FVec3 Add(const FVec3& p_left, const FVec3& p_right);
/**

@brief Calculate the subtraction of two vectors.
@param p_left The vector to subtract from.
@param p_right The vector to subtract.
@return A new vector that is the result of the subtraction.
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
        * Return the length of a vector squared
        * @param p_target
        */
        static float Length2(const FVec3& p_target);

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

    FVec3 operator*(float p_scalar, const FVec3& p_vec);

    FVec3 operator*(const FVec3& p_vec, const FVec3& p_vec2);

    FVec3 operator*= (FVec3& p_vec, const FVec3& p_vec2);

    FVec3 operator/(float p_scalar, const FVec3& p_vec);

    FVec3 operator/= (FVec3& p_vec, const FVec3& p_vec2);

    bool operator==(const FVec3& p_left, const FVec3& p_right);

    bool operator!=(const FVec3& p_left, const FVec3& p_right);
}