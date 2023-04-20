#pragma once

#include <iostream>

namespace lm
{
    struct DVec3
    {
        static const DVec3 One;
        static const DVec3 Zero;
        static const DVec3 Forward;
        static const DVec3 Right;
        static const DVec3 Up;

        double x;
        double y;
        double z;

        DVec3();

        /**
        * Default constructor
        * @param p_x
        * @param p_y
        * @param p_z
        */
        DVec3(double p_x, double p_y, double p_z);

        DVec3(double p_init);

        DVec3(const struct FVec4& p_toCopy);
        /**
        * Copy constructor
        * @param p_toCopy
        */
        DVec3(const DVec3& p_toCopy);

        /**
        * Move constructor
        * @param p_toMove
        */
        DVec3(DVec3&& p_toMove) noexcept = default;

        /**
        * Negation
        */
        DVec3 operator-() const;

        /**
        * Copy assignment
        * @param p_other
        */
        DVec3 operator=(const DVec3& p_other);

        /**
        * Calculate the sum of two vectors
        * @param p_other
        */
        DVec3 operator+(const DVec3& p_other) const;

        /**
        * Add the right vector to the left one
        * @param p_other
        */
        DVec3& operator+=(const DVec3& p_other);

        /**
        * Calculate the substraction of two vectors
        * @param p_other
        */
        DVec3 operator-(const DVec3& p_other) const;

        /**
        * Remove the right vector from the left one
        * @param p_other
        */
        DVec3& operator-=(const DVec3& p_other);

        /**
        * Calculate the division of two vectors
        * @param p_other
        */
        DVec3& operator/(const DVec3& p_other);

        DVec3 operator/(const DVec3& p_other) const;

        /**
        * Calcualte the multiplication of a vector with a scalar
        * @param p_scalar
        */
        DVec3 operator*(double p_scalar) const;

        /**
        * Multiply the vector by a scalar
        * @param p_scalar
        */
        DVec3& operator*=(double p_scalar);

        /**
        * Return the division of scalar and actual vector
        * @param p_scalar
        */
        DVec3 operator/(double p_scalar) const;

        /**
        * Divide scalar to the actual vector
        * @param p_scalar
        */
        DVec3& operator/=(double p_scalar);

        /**
        * Return true if the two vectors are equals
        * @param p_other
        */
        bool operator==(const DVec3& p_other);

        /**
        * Return true if the two vectors are different
        * @param p_other
        */
        bool operator!=(const DVec3& p_other);

        /**
 * Return the value of the vector at the given index
 * @param p_index
 */
        const double& operator[](int p_index) const;

        /**
         * Return the value of the vector at the given index
         * @param p_index
         */
        double& operator[](int p_index);

        /**
         * Return the value of the vector at the given index
         * @param p_index
         */
        const double& operator()(int p_index) const;

        /**
         * Return the value of the vector at the given index
         * @param p_index
         */
        double& operator()(int p_index);

        /**
        * Calculate the sum of two vectors
        * @param p_left (First vector)
        * @param p_right (Second vector)
        */
        static DVec3 Add(const DVec3& p_left, const DVec3& p_right);

        /**
        * Calculate the substraction of two vectors
        * @param p_left (First vector)
        * @param p_right (Second vector)
        */
        static DVec3 Substract(const DVec3& p_left, const DVec3& p_right);

        /**
        * Calculate the multiplication of a vector with a scalar
        * @param p_target
        * @param p_scalar
        */
        static DVec3 Multiply(const DVec3& p_target, double p_scalar);

        /**
        * Divide scalar to vector left
        * @param p_left
        * @param p_scalar
        */
        static DVec3 Divide(const DVec3& p_left, double p_scalar);

        /**
        * Return the length of a vector
        * @param p_target
        */
        static double Length(const DVec3& p_target);

        /**
        * Return the length of a vector squared
        * @param p_target
        */
        static double Length2(const DVec3& p_target);

        /**
        * Return the dot product of two vectors
        * @param p_left
        * @param p_right
        */
        static double Dot(const DVec3& p_left, const DVec3& p_right);

        /**
        * Return the distance between two vectors
        * @param p_left
        * @param p_right
        */
        static double Distance(const DVec3& p_left, const DVec3& p_right);

        /**
        * Return the cross product of two vectors
        * @param p_left
        * @param p_right
        */
        static DVec3 Cross(const DVec3& p_left, const DVec3& p_right);

        /**
        * Return the normalize of the given vector
        * @param p_target
        */
        static DVec3 Normalize(const DVec3& p_target);

        /**
        * Calculate the interpolation between two vectors
        * @param p_start
        * @param p_end
        * @param p_alpha
        */
        static DVec3 Lerp(const DVec3& p_start, const DVec3& p_end, double p_alpha);

        /**
        * Calculate the angle between two vectors
        * @param p_from
        * @param p_to
        */
        static double AngleBetween(const DVec3& p_from, const DVec3& p_to);

        /**
         * Return the min vector between two vectors
         * @param p_target
         * @param p_min
         * @param p_max
         */
        static DVec3 Clamp(const DVec3& p_target, const DVec3& p_min, const DVec3& p_max);

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
        static DVec3 Project(const DVec3& p_target, const DVec3& p_onNormal);

        /**
         * Return the vector reflected on a normal
         * @param p_target
         * @param p_onNormal
         */
        static DVec3 Reflect(const DVec3& p_target, const DVec3& p_onNormal);

        /**
         * Return the vector refracted on a normal
         * @param p_target
         * @param p_onNormal
         * @param p_refractiveIndex
         */
        static DVec3 Refract(const DVec3& p_target, const DVec3& p_onNormal, double p_refractiveIndex);
    };

    /**
     * Return the vector as a string
     * @param p_stream
     * @param p_vec
    */
    std::ostream& operator<<(std::ostream& p_stream, const DVec3& p_vec);

    /**
     * input a vector from a string
     * @param p_stream
     * @param p_vec
    */
    std::istream& operator>>(std::istream& p_stream, DVec3& p_vec);

    DVec3 operator*(double p_scalar, const DVec3& p_vec);

    DVec3 operator*(const DVec3& p_vec, const DVec3& p_vec2);

    DVec3 operator*= (DVec3& p_vec, const DVec3& p_vec2);

    DVec3 operator/(double p_scalar, const DVec3& p_vec);

    DVec3 operator/= (DVec3& p_vec, const DVec3& p_vec2);

    bool operator==(const DVec3& p_left, const DVec3& p_right);

    bool operator!=(const DVec3& p_left, const DVec3& p_right);
}