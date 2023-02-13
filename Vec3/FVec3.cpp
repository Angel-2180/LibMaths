#include "FVec3.hpp"

#include <utility>
#include <stdexcept>
#include <cmath>

#include "../Utilities.h"
#include <algorithm>
#include <limits>

using namespace lm;

const FVec3 FVec3::One(1.0f, 1.0f, 1.0f);
const FVec3 FVec3::Zero(0.0f, 0.0f, 0.0f);
const FVec3 FVec3::Forward(0.0f, 0.0f, 1.0f);
const FVec3 FVec3::Right(1.0f, 0.0f, 0.0f);
const FVec3 FVec3::Up(0.0f, 1.0f, 0.0f);

FVec3::FVec3(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z)
{
}

FVec3::FVec3(const FVec3& p_toCopy) : x(p_toCopy.x), y(p_toCopy.y), z(p_toCopy.z)
{
}

FVec3 FVec3::operator-() const
{
    return operator*(-1);
}

FVec3 FVec3::operator=(const FVec3& p_other)
{
    this->x = p_other.x;
    this->y = p_other.y;
    this->z = p_other.z;

    return *this;
}

FVec3 FVec3::operator+(const FVec3& p_other) const
{
    return Add(*this, p_other);
}

FVec3& FVec3::operator+=(const FVec3& p_other)
{
    *this = Add(*this, p_other);
    return *this;
}

FVec3 FVec3::operator-(const FVec3& p_other) const
{
    return Substract(*this, p_other);
}

FVec3& FVec3::operator-=(const FVec3& p_other)
{
    *this = Substract(*this, p_other);
    return *this;
}

FVec3 FVec3::operator*(float p_scalar) const
{
    return Multiply(*this, p_scalar);
}

FVec3& FVec3::operator*=(float p_scalar)
{
    *this = Multiply(*this, p_scalar);
    return *this;
}

FVec3 FVec3::operator/(float p_scalar) const
{
    return Divide(*this, p_scalar);
}

FVec3& FVec3::operator/=(float p_scalar)
{
    *this = Divide(*this, p_scalar);
    return *this;
}

bool FVec3::operator==(const FVec3& p_other)
{
    return
        this->x == p_other.x &&
        this->y == p_other.y &&
        this->z == p_other.z;
}

bool FVec3::operator!=(const FVec3& p_other)
{
    return !operator==(p_other);
}

const float& lm::FVec3::operator[](int p_index) const
{
    switch (p_index)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range");
    }
}

float& lm::FVec3::operator[](int p_index)
{
    switch (p_index)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range");
    }
}

const float& lm::FVec3::operator()(int p_index) const
{
    switch (p_index)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range");
    }
}

float& lm::FVec3::operator()(int p_index)
{
    switch (p_index)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range");
    }
}

FVec3 FVec3::Add(const FVec3& p_left, const FVec3& p_right)
{
    return FVec3
    (
        p_left.x + p_right.x,
        p_left.y + p_right.y,
        p_left.z + p_right.z
    );
}

FVec3 FVec3::Substract(const FVec3& p_left, const FVec3& p_right)
{
    return FVec3
    (
        p_left.x - p_right.x,
        p_left.y - p_right.y,
        p_left.z - p_right.z
    );
}

FVec3 FVec3::Multiply(const FVec3& p_target, float p_scalar)
{
    return FVec3
    (
        p_target.x * p_scalar,
        p_target.y * p_scalar,
        p_target.z * p_scalar
    );
}

FVec3 FVec3::Divide(const FVec3& p_left, float p_scalar)
{
    FVec3 result(p_left);

    if (p_scalar == 0)
        throw std::logic_error("Division by 0");

    result.x /= p_scalar;
    result.y /= p_scalar;
    result.z /= p_scalar;

    return result;
}

float FVec3::Length(const FVec3& p_target)
{
    return std::sqrt(p_target.x * p_target.x + p_target.y * p_target.y + p_target.z * p_target.z);
}

float FVec3::Dot(const FVec3& p_left, const FVec3& p_right)
{
    return p_left.x * p_right.x + p_left.y * p_right.y + p_left.z * p_right.z;
}

float FVec3::Distance(const FVec3& p_left, const FVec3& p_right)
{
    return std::sqrt
    (
        (p_left.x - p_right.x) * (p_left.x - p_right.x) +
        (p_left.y - p_right.y) * (p_left.y - p_right.y) +
        (p_left.z - p_right.z) * (p_left.z - p_right.z)
    );
}

FVec3 FVec3::Cross(const FVec3& p_left, const FVec3& p_right)
{
    return FVec3
    (
        p_left.y * p_right.z - p_left.z * p_right.y,
        p_left.z * p_right.x - p_left.x * p_right.z,
        p_left.x * p_right.y - p_left.y * p_right.x
    );
}

FVec3 FVec3::Normalize(const FVec3& p_target)
{
    float length = Length(p_target);

    if (length > 0.0f)
    {
        float targetLength = 1.0f / length;

        return FVec3
        (
            p_target.x * targetLength,
            p_target.y * targetLength,
            p_target.z * targetLength
        );
    }
    else
    {
        return FVec3::Zero;
    }
}

FVec3 FVec3::Lerp(const FVec3& p_start, const FVec3& p_end, float p_alpha)
{
    return (p_start + (p_end - p_start) * p_alpha);
}

float FVec3::AngleBetween(const FVec3& p_from, const FVec3& p_to)
{
    float lengthProduct = Length(p_from) * Length(p_to);

    if (lengthProduct > 0.0f)
    {
        float fractionResult = Dot(p_from, p_to) / lengthProduct;

        if (fractionResult >= -1.0f && fractionResult <= 1.0f)
            return acosf(fractionResult);
    }

    return 0.0f;
}

FVec3 FVec3::Project(const FVec3& p_target, const FVec3& p_onNormal)
{
    float dot = Dot(p_target, p_onNormal);

    return FVec3
    (
        p_onNormal.x * dot,
        p_onNormal.y * dot,
        p_onNormal.z * dot
    );
}

FVec3 FVec3::Reflect(const FVec3& p_target, const FVec3& p_normal)
{
    return p_target - p_normal * 2.0f * Dot(p_target, p_normal);
}

FVec3 FVec3::Refract(const FVec3& p_target, const FVec3& p_normal, float p_eta)
{
    float dot = Dot(p_target, p_normal);
    float k = 1.0f - p_eta * p_eta * (1.0f - dot * dot);

    if (k < 0.0f)
        return FVec3::Zero;

    return p_target * p_eta - p_normal * (p_eta * dot + sqrtf(k));
}

FVec3 FVec3::Clamp(const FVec3& p_target, const FVec3& p_min, const FVec3& p_max)
{
    return FVec3
    (
        clamp(p_target.x, p_min.x, p_max.x),
        clamp(p_target.y, p_min.y, p_max.y),
        clamp(p_target.z, p_min.z, p_max.z)
    );
}

bool FVec3::IsUnit() const
{
    return std::abs(Length(*this) - 1.0f) <= std::numeric_limits<float>::epsilon() ||
        std::abs(Length(*this) - 1.0f) <= std::numeric_limits<float>::epsilon() *
        std::max(std::abs(Length(*this)), std::abs(1.0f));
}

bool FVec3::IsZero() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f;
}

std::ostream& lm::operator<<(std::ostream& p_stream, const FVec3& p_target)
{
    p_stream << "FVec3(" << p_target.x << ", " << p_target.y << ", " << p_target.z << ")";

    return p_stream;
}

std::istream& lm::operator>>(std::istream& p_stream, FVec3& p_target)
{
    p_stream >> p_target.x >> p_target.y >> p_target.z;

    return p_stream;
}

FVec3 lm::operator*(float p_scalar, const FVec3& p_target)
{
    return FVec3
    (
        p_target.x * p_scalar,
        p_target.y * p_scalar,
        p_target.z * p_scalar
    );
}

FVec3 lm::operator/(float p_scalar, const FVec3& p_target)
{
    return FVec3
    (
        p_target.x / p_scalar,
        p_target.y / p_scalar,
        p_target.z / p_scalar
    );
}

FVec3 lm::operator*(const FVec3& p_vec, const FVec3& p_vec2)
{
    return FVec3
    (
        p_vec.x * p_vec2.x,
        p_vec.y * p_vec2.y,
        p_vec.z * p_vec2.z
    );
}