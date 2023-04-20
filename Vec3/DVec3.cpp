#include "DVec3.hpp"

#include <utility>
#include <stdexcept>
#include <cmath>

#include "../Utilities.h"
#include "Vec4/FVec4.hpp"
#include <algorithm>
#include <limits>

using namespace lm;

const DVec3 DVec3::One(1.0, 1.0, 1.0);
const DVec3 DVec3::Zero(0.0, 0.0, 0.0);
const DVec3 DVec3::Forward(0.0, 0.0, 1.0);
const DVec3 DVec3::Right(1.0, 0.0, 0.0);
const DVec3 DVec3::Up(0.0, 1.0, 0.0);

DVec3::DVec3() : x(0.0), y(0.0), z(0.0)
{
}

DVec3::DVec3(double p_x, double p_y, double p_z)
{
    this->x = p_x;
    this->y = p_y;
    this->z = p_z;
}

DVec3::DVec3(const struct FVec4& p_toCopy) : x(p_toCopy.x), y(p_toCopy.y), z(p_toCopy.z)
{
}

DVec3::DVec3(const DVec3& p_toCopy) : x(p_toCopy.x), y(p_toCopy.y), z(p_toCopy.z)
{
}

DVec3::DVec3(double p_init)
{
    this->x = p_init;
    this->y = p_init;
    this->z = p_init;
}

DVec3 DVec3::operator-() const
{
    return operator*(-1);
}

DVec3 DVec3::operator=(const DVec3& p_other)
{
    this->x = p_other.x;
    this->y = p_other.y;
    this->z = p_other.z;

    return *this;
}

DVec3 DVec3::operator+(const DVec3& p_other) const
{
    return Add(*this, p_other);
}

DVec3& DVec3::operator+=(const DVec3& p_other)
{
    *this = Add(*this, p_other);
    return *this;
}

DVec3 DVec3::operator-(const DVec3& p_other) const
{
    return Substract(*this, p_other);
}

DVec3& DVec3::operator-=(const DVec3& p_other)
{
    *this = Substract(*this, p_other);
    return *this;
}

DVec3& lm::DVec3::operator/(const DVec3& p_other)
{
    DVec3 result = *this;
    result.x /= p_other.x;
    result.y /= p_other.y;
    result.z /= p_other.z;
    *this = result;
    return *this;
}

DVec3 lm::DVec3::operator/(const DVec3& p_other) const
{
    DVec3 result = *this;
    result.x /= p_other.x;
    result.y /= p_other.y;
    result.z /= p_other.z;

    return result;
}

DVec3 DVec3::operator*(double p_scalar) const
{
    return Multiply(*this, p_scalar);
}

DVec3& DVec3::operator*=(double p_scalar)
{
    *this = Multiply(*this, p_scalar);
    return *this;
}

DVec3 DVec3::operator/(double p_scalar) const
{
    return Divide(*this, p_scalar);
}

DVec3& DVec3::operator/=(double p_scalar)
{
    *this = Divide(*this, p_scalar);
    return *this;
}

bool DVec3::operator==(const DVec3& p_other)
{
    return
        this->x == p_other.x &&
        this->y == p_other.y &&
        this->z == p_other.z;
}

bool DVec3::operator!=(const DVec3& p_other)
{
    return !operator==(p_other);
}

const double& lm::DVec3::operator[](int p_index) const
{
    switch (p_index)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range");
    }
}

double& lm::DVec3::operator[](int p_index)
{
    switch (p_index)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range");
    }
}

const double& lm::DVec3::operator()(int p_index) const
{
    switch (p_index)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range");
    }
}

double& lm::DVec3::operator()(int p_index)
{
    switch (p_index)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range");
    }
}

DVec3 DVec3::Add(const DVec3& p_left, const DVec3& p_right)
{
    return DVec3
    (
        p_left.x + p_right.x,
        p_left.y + p_right.y,
        p_left.z + p_right.z
    );
}

DVec3 DVec3::Substract(const DVec3& p_left, const DVec3& p_right)
{
    return DVec3
    (
        p_left.x - p_right.x,
        p_left.y - p_right.y,
        p_left.z - p_right.z
    );
}

DVec3 DVec3::Multiply(const DVec3& p_target, double p_scalar)
{
    return DVec3
    (
        p_target.x * p_scalar,
        p_target.y * p_scalar,
        p_target.z * p_scalar
    );
}

DVec3 DVec3::Divide(const DVec3& p_left, double p_scalar)
{
    DVec3 result(p_left);

    if (p_scalar == 0)
        throw std::logic_error("Division by 0");

    result.x /= p_scalar;
    result.y /= p_scalar;
    result.z /= p_scalar;

    return result;
}

double DVec3::Length(const DVec3& p_target)
{
    return std::sqrt(p_target.x * p_target.x + p_target.y * p_target.y + p_target.z * p_target.z);
}

double DVec3::Dot(const DVec3& p_left, const DVec3& p_right)
{
    return p_left.x * p_right.x + p_left.y * p_right.y + p_left.z * p_right.z;
}

double DVec3::Distance(const DVec3& p_left, const DVec3& p_right)
{
    return std::sqrt
    (
        (p_left.x - p_right.x) * (p_left.x - p_right.x) +
        (p_left.y - p_right.y) * (p_left.y - p_right.y) +
        (p_left.z - p_right.z) * (p_left.z - p_right.z)
    );
}

DVec3 DVec3::Cross(const DVec3& p_left, const DVec3& p_right)
{
    return DVec3
    (
        p_left.y * p_right.z - p_left.z * p_right.y,
        p_left.z * p_right.x - p_left.x * p_right.z,
        p_left.x * p_right.y - p_left.y * p_right.x
    );
}

DVec3 DVec3::Normalize(const DVec3& p_target)
{
    double length = Length(p_target);

    if (length > 0.0)
    {
        double targetLength = 1.0 / length;

        return DVec3
        (
            p_target.x * targetLength,
            p_target.y * targetLength,
            p_target.z * targetLength
        );
    }
    else
    {
        return DVec3::Zero;
    }
}

double DVec3::Length2(const DVec3& p_target)
{
    return p_target.x * p_target.x + p_target.y * p_target.y + p_target.z * p_target.z;
}

DVec3 DVec3::Lerp(const DVec3& p_start, const DVec3& p_end, double p_alpha)
{
    return (p_start + (p_end - p_start) * p_alpha);
}

double DVec3::AngleBetween(const DVec3& p_from, const DVec3& p_to)
{
    auto vec1 = Normalize(p_from);
    auto vec2 = Normalize(p_to);
    double dot = Dot(vec1, vec2);
    double lenSq1 = Length2(vec1);
    double lenSq2 = Length2(vec2);
    return std::acos(dot / std::sqrt(lenSq1 * lenSq2));
}

DVec3 DVec3::Project(const DVec3& p_target, const DVec3& p_onNormal)
{
    double aDotb = Dot(p_target, p_onNormal);

    double bDotB = Dot(p_onNormal, p_onNormal);

    if (bDotB == 0.0)
    {
        return DVec3::Zero;
    }

    return (aDotb / bDotB) * p_onNormal;
}

DVec3 DVec3::Reflect(const DVec3& p_target, const DVec3& p_normal)
{
    return p_target - p_normal * 2.0 * Dot(p_target, p_normal);
}

DVec3 DVec3::Refract(const DVec3& p_target, const DVec3& p_normal, double p_eta)
{
    double dot = Dot(p_target, p_normal);
    double k = 1.0 - p_eta * p_eta * (1.0 - dot * dot);

    if (k < 0.0)
        return DVec3::Zero;

    return p_target * p_eta - p_normal * (p_eta * dot + sqrtf(k));
}

DVec3 DVec3::Clamp(const DVec3& p_target, const DVec3& p_min, const DVec3& p_max)
{
    return DVec3
    (
        clamp(p_target.x, p_min.x, p_max.x),
        clamp(p_target.y, p_min.y, p_max.y),
        clamp(p_target.z, p_min.z, p_max.z)
    );
}

bool DVec3::IsUnit() const
{
    return std::abs(Length(*this) - 1.0) <= std::numeric_limits<double>::epsilon() ||
        std::abs(Length(*this) - 1.0) <= std::numeric_limits<double>::epsilon() *
        std::max(std::abs(Length(*this)), std::abs(1.0));
}

bool DVec3::IsZero() const
{
    return x == 0.0 && y == 0.0 && z == 0.0;
}

std::ostream& lm::operator<<(std::ostream& p_stream, const DVec3& p_target)
{
    p_stream << "DVec3(" << p_target.x << ", " << p_target.y << ", " << p_target.z << ")";

    return p_stream;
}

std::istream& lm::operator>>(std::istream& p_stream, DVec3& p_target)
{
    char c;
    p_stream >> c;
    p_stream >> p_target.x;
    p_stream >> c;
    p_stream >> p_target.y;
    p_stream >> c;
    p_stream >> p_target.z;
    p_stream >> c;

    return p_stream;
}

DVec3 lm::operator*(double p_scalar, const DVec3& p_target)
{
    return DVec3
    (
        p_target.x * p_scalar,
        p_target.y * p_scalar,
        p_target.z * p_scalar
    );
}

DVec3 lm::operator/(double p_scalar, const DVec3& p_target)
{
    return DVec3
    (
        p_target.x / p_scalar,
        p_target.y / p_scalar,
        p_target.z / p_scalar
    );
}

DVec3 lm::operator*(const DVec3& p_vec, const DVec3& p_vec2)
{
    return DVec3
    (
        p_vec.x * p_vec2.x,
        p_vec.y * p_vec2.y,
        p_vec.z * p_vec2.z
    );
}

DVec3 lm::operator/= (DVec3& p_left, const DVec3& p_right)
{
    p_left.x /= p_right.x;
    p_left.y /= p_right.y;
    p_left.z /= p_right.z;

    return p_left;
}

DVec3 lm::operator*= (DVec3& p_left, const DVec3& p_right)
{
    p_left.x *= p_right.x;
    p_left.y *= p_right.y;
    p_left.z *= p_right.z;

    return p_left;
}

bool lm::operator==(const DVec3& p_left, const  DVec3& p_right)
{
    return p_left.x == p_right.x && p_left.y == p_right.y && p_left.z == p_right.z;
}

bool lm::operator!=(const DVec3& p_left, const  DVec3& p_right)
{
    return p_left.x != p_right.x || p_left.y != p_right.y || p_left.z != p_right.z;
}