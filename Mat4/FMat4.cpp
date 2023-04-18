#include "FMat4.hpp"
#include "../Vec3/FVec3.hpp"
#include "../Quaternion/FQuat.hpp"
#include "../Mat3/FMat3.hpp"
using namespace lm;

const FMat4 FMat4::IdentityMatrix(1.0f);

FMat4::FMat4(float p_init)
{
    m_matrix[0] = FVec4(p_init, 0, 0, 0);
    m_matrix[1] = FVec4(0, p_init, 0, 0);
    m_matrix[2] = FVec4(0, 0, p_init, 0);
    m_matrix[3] = FVec4(0, 0, 0, p_init);
}

FMat4::FMat4(float p_00, float p_01, float p_02, float p_03,
    float p_10, float p_11, float p_12, float p_13,
    float p_20, float p_21, float p_22, float p_23,
    float p_30, float p_31, float p_32, float p_33)
{
    m_matrix[0][0] = p_00;
    m_matrix[0][1] = p_01;
    m_matrix[0][2] = p_02;
    m_matrix[0][3] = p_03;

    m_matrix[1][0] = p_10;
    m_matrix[1][1] = p_11;
    m_matrix[1][2] = p_12;
    m_matrix[1][3] = p_13;

    m_matrix[2][0] = p_20;
    m_matrix[2][1] = p_21;
    m_matrix[2][2] = p_22;
    m_matrix[2][3] = p_23;

    m_matrix[3][0] = p_30;
    m_matrix[3][1] = p_31;
    m_matrix[3][2] = p_32;
    m_matrix[3][3] = p_33;
}

FMat4::FMat4(FVec4 p_row1, FVec4 p_row2, FVec4 p_row3, FVec4 p_row4)
{
    m_matrix[0] = p_row1;
    m_matrix[1] = p_row2;
    m_matrix[2] = p_row3;
    m_matrix[3] = p_row4;
}

FMat4::FMat4(const FVec3& p_position, const FQuat& p_rotation)
{
    FMat4 result = FQuat::ToRotateMat3(p_rotation);
    result = FMat4::Translate(result, p_position);
    *this = result;
}

FMat4::FMat4(const FMat4& p_toCopy)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m_matrix[i][j] = p_toCopy.m_matrix[i][j];
        }
    }
}

lm::FMat4::FMat4(const FMat3& p_toCopy)
{
    m_matrix[0] = FVec4(p_toCopy.m_matrix[0], 0);
    m_matrix[1] = FVec4(p_toCopy.m_matrix[1], 0);
    m_matrix[2] = FVec4(p_toCopy.m_matrix[2], 0);
    m_matrix[3] = FVec4(0, 0, 0, 1);
}

FMat4& lm::FMat4::operator=(const FMat3& p_other)
{
    m_matrix[0] = FVec4(p_other.m_matrix[0], 0);
    m_matrix[1] = FVec4(p_other.m_matrix[1], 0);
    m_matrix[2] = FVec4(p_other.m_matrix[2], 0);
    m_matrix[3] = FVec4(0, 0, 0, 1);
    return *this;
}

FMat4& FMat4::operator=(const FMat4& p_other)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m_matrix[i][j] = p_other.m_matrix[i][j];
        }
    }
    return *this;
}

FMat4 FMat4::operator*(const FMat4& p_other) const
{
    const FVec4 SrcA00 = m_matrix[0];
    const FVec4 SrcA10 = m_matrix[1];
    const FVec4 SrcA20 = m_matrix[2];
    const FVec4 SrcA30 = m_matrix[3];

    const FVec4 SrcB00 = p_other.m_matrix[0];
    const FVec4 SrcB10 = p_other.m_matrix[1];
    const FVec4 SrcB20 = p_other.m_matrix[2];
    const FVec4 SrcB30 = p_other.m_matrix[3];

    FMat4 result;
    result.m_matrix[0] = SrcA00 * SrcB00[0] + SrcA10 * SrcB00[1] + SrcA20 * SrcB00[2] + SrcA30 * SrcB00[3];
    result.m_matrix[1] = SrcA00 * SrcB10[0] + SrcA10 * SrcB10[1] + SrcA20 * SrcB10[2] + SrcA30 * SrcB10[3];
    result.m_matrix[2] = SrcA00 * SrcB20[0] + SrcA10 * SrcB20[1] + SrcA20 * SrcB20[2] + SrcA30 * SrcB20[3];
    result.m_matrix[3] = SrcA00 * SrcB30[0] + SrcA10 * SrcB30[1] + SrcA20 * SrcB30[2] + SrcA30 * SrcB30[3];
    return result;
}

FMat4& FMat4::operator*=(const FMat4& p_other)
{
    *this = *this * p_other;
    return *this;
}

FVec4 FMat4::operator*(const FVec4& p_other) const
{
    FVec4 result = {
        m_matrix[0].x * p_other.x + m_matrix[1].x * p_other.y + m_matrix[2].x * p_other.z + m_matrix[3].x,
        m_matrix[0].y * p_other.x + m_matrix[1].y * p_other.y + m_matrix[2].y * p_other.z + m_matrix[3].y,
        m_matrix[0].z * p_other.x + m_matrix[1].z * p_other.y + m_matrix[2].z * p_other.z + m_matrix[3].z,
        m_matrix[0].w * p_other.x + m_matrix[1].w * p_other.y + m_matrix[2].w * p_other.z + m_matrix[3].w
    };
    return result;
}

FVec3 FMat4::operator*(const FVec3& p_other) const
{
    FVec4 v = { p_other.x, p_other.y, p_other.z, 1.0f };
    FVec4 result = {
        m_matrix[0].x * v.x + m_matrix[1].x * v.y + m_matrix[2].x * v.z + m_matrix[3].x,
        m_matrix[0].y * v.x + m_matrix[1].y * v.y + m_matrix[2].y * v.z + m_matrix[3].y,
        m_matrix[0].z * v.x + m_matrix[1].z * v.y + m_matrix[2].z * v.z + m_matrix[3].z,
        m_matrix[0].w * v.x + m_matrix[1].w * v.y + m_matrix[2].w * v.z + m_matrix[3].w
    };
    return FVec3{ result.x / result.w, result.y / result.w, result.z / result.w };
}

FMat4 FMat4::operator*(float p_scalar) const
{
    FMat4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m_matrix[i][j] = m_matrix[i][j] * p_scalar;
        }
    }
    return result;
}

FMat4 FMat4::operator+(const FMat4& p_other) const
{
    FMat4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m_matrix[i][j] = m_matrix[i][j] + p_other.m_matrix[i][j];
        }
    }
    return result;
}

FMat4& FMat4::operator+=(const FMat4& p_other)
{
    *this = *this + p_other;
    return *this;
}

FMat4 FMat4::operator-(const FMat4& p_other) const
{
    FMat4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m_matrix[i][j] = m_matrix[i][j] - p_other.m_matrix[i][j];
        }
    }
    return result;
}

FMat4& FMat4::operator-=(const FMat4& p_other)
{
    *this = *this - p_other;
    return *this;
}

FMat4 FMat4::operator-() const
{
    FMat4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m_matrix[i][j] = -m_matrix[i][j];
        }
    }
    return result;
}

bool lm::FMat4::IsOrthogonal() const
{
    FMat4 transpose{ 0 };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            transpose.m_matrix[i][j] = m_matrix[j][i];
            if (i > j) {
                for (int k = 0; k < j; k++) {
                    transpose.m_matrix[i][j] -= transpose.m_matrix[k][j] * transpose.m_matrix[i][k];
                }
                transpose.m_matrix[i][j] /= transpose.m_matrix[j][j];
            }
        }
    }

    FMat4 product{ 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                product.m_matrix[i][j] += m_matrix[i][k] * transpose.m_matrix[k][j];
            }
        }
    }

    const float epsilon = 0.0001f;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (std::abs(product.m_matrix[i][j] - (i == j ? 1.0f : 0.0f)) > epsilon) {
                return false;
            }
        }
    }

    return true;
}

FMat4 lm::FMat4::InverseOrtho(const FMat4& p_matrix)
{
    if (!p_matrix.IsOrthogonal())
    {
        throw std::runtime_error("Matrix is not orthogonal");
    }
    return FMat4::Transpose(p_matrix);
}

FMat4 FMat4::operator/(float p_scalar) const
{
    FMat4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m_matrix[i][j] = m_matrix[i][j] / p_scalar;
        }
    }
    return result;
}

FMat4& FMat4::operator/=(float p_scalar)
{
    *this = *this / p_scalar;
    return *this;
}

bool FMat4::operator==(const FMat4& p_other) const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_matrix[i][j] != p_other.m_matrix[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool FMat4::operator!=(const FMat4& p_other) const
{
    return !(*this == p_other);
}

FVec4& FMat4::operator[](int p_index)
{
    return m_matrix[p_index];
}

const FVec4& FMat4::operator[](int p_index) const
{
    return m_matrix[p_index];
}

FMat4 FMat4::Identity()
{
    FMat4 result;
    for (int i = 0; i < 4; i++)
    {
        result.m_matrix[i][i] = 1.0f;
    }
    return result;
}

FMat4 FMat4::Translation(const FVec3& p_translation)
{
    FMat4 result = FMat4::Identity();
    result[3][0] = p_translation.x;
    result[3][1] = p_translation.y;
    result[3][2] = p_translation.z;
    return result;
}

FMat4 FMat4::RotationEuler(const FVec3& p_rotation)
{
    const float yaw = p_rotation.x;
    const float pitch = p_rotation.y;
    const float roll = p_rotation.z;

    const float cosYaw = std::cosf(-yaw);
    const float sinYaw = std::sinf(-yaw);
    const float cosPitch = std::cosf(-pitch);
    const float sinPitch = std::sinf(-pitch);
    const float cosRoll = std::cosf(-roll);
    const float sinRoll = std::sinf(-roll);

    FMat4 Result = FMat4::Identity();
    Result[0][0] = cosPitch * cosRoll;
    Result[0][1] = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
    Result[0][2] = sinYaw * sinRoll + cosYaw * sinPitch * cosRoll;

    Result[1][0] = cosPitch * sinRoll;
    Result[1][1] = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
    Result[1][2] = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;

    Result[2][0] = -sinPitch;
    Result[2][1] = sinYaw * cosPitch;
    Result[2][2] = cosYaw * cosPitch;

    return Result;
}

FMat4 FMat4::Scale(const FVec3& p_scale)
{
    FMat4 result = FMat4::Identity();
    result[0][0] = p_scale.x;
    result[1][1] = p_scale.y;
    result[2][2] = p_scale.z;
    return result;
}

FMat4 FMat4::LookAt(const FVec3& p_eye, const FVec3& p_target, const FVec3& p_up)
{
    FVec3 const f(FVec3::Normalize(p_target - p_eye));
    FVec3 const s(FVec3::Normalize(FVec3::Cross(f, p_up)));
    FVec3 const u(FVec3::Cross(s, f));

    FMat4 Result(1);
    Result[0][0] = s.x;
    Result[1][0] = s.y;
    Result[2][0] = s.z;
    Result[0][1] = u.x;
    Result[1][1] = u.y;
    Result[2][1] = u.z;
    Result[0][2] = -f.x;
    Result[1][2] = -f.y;
    Result[2][2] = -f.z;
    Result[3][0] = -FVec3::Dot(s, p_eye);
    Result[3][1] = -FVec3::Dot(u, p_eye);
    Result[3][2] = FVec3::Dot(f, p_eye);
    return Result;
}

FMat4 FMat4::Perspective(float p_fov, float p_aspect, float p_near, float p_far)
{
    FMat4 result{};
    float scale = tan(p_fov * PI / 360) * p_near;
    float r = p_aspect * scale;
    float l = -r;
    float t = scale;
    float b = -t;
    float x1 = 2.0f * p_near / (r - l);
    float y2 = 2.0f * p_near / (t - b);
    float x3 = (r + l) / (r - l);
    float y3 = (t + b) / (t - b);
    float z3 = -(p_far + p_near) / (p_far - p_near);
    float z4 = -(2.0f * p_far * p_near) / (p_far - p_near);

    result[0][0] = x1;
    result[1][1] = y2;
    result[2][0] = x3;
    result[2][1] = y3;
    result[2][2] = z3;
    result[2][3] = -1;
    result[3][2] = z4;

    return result;
}

FMat4 FMat4::Orthographic(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far)
{
    FMat4 result = FMat4::Identity();
    float x1 = 2 / (p_right - p_left);
    float y2 = 2 / (p_top - p_bottom);
    float z3 = -2 / (p_far - p_near);
    float x3 = -(p_right + p_left) / (p_right - p_left);
    float y3 = -(p_top + p_bottom) / (p_top - p_bottom);
    float z4 = -(p_far + p_near) / (p_far - p_near);

    result[0][0] = x1;
    result[1][1] = y2;
    result[2][2] = z3;
    result[3][0] = x3;
    result[3][1] = y3;
    result[3][2] = z4;

    return result;
}

FMat4 FMat4::Transpose(const FMat4& p_matrix)
{
    FMat4 result = FMat4::Identity();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m_matrix[i][j] = p_matrix.m_matrix[j][i];
        }
    }
    return result;
}

FMat4 FMat4::Translate(const FMat4& p_matrix, const FVec3& p_translation)
{
    FMat4 result = p_matrix;

    result[3] = p_matrix[0] * p_translation.x + p_matrix[1] * p_translation.y + p_matrix[2] * p_translation.z + p_matrix[3];
    return result;
}

FMat4 FMat4::Rotate(const FMat4& p_matrix, const FVec3& p_rotation)
{
    FMat4 result = p_matrix;

    return result * YXZRotation(p_rotation);
}

FMat4 FMat4::Rotate(const FMat4& p_matrix, float p_angle, const FVec3& p_axis)
{
    float const a = TO_RADIANS(p_angle);
    float const c = cos(a);
    float const s = sin(a);

    FVec3 axis(FVec3::Normalize(p_axis));
    FVec3 temp((float(1) - c) * axis);

    FMat4 Rotate;
    Rotate[0][0] = c + temp[0] * axis[0];
    Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
    Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

    Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
    Rotate[1][1] = c + temp[1] * axis[1];
    Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

    Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
    Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
    Rotate[2][2] = c + temp[2] * axis[2];

    FMat4 Result;
    Result[0] = p_matrix[0] * Rotate[0][0] + p_matrix[1] * Rotate[0][1] + p_matrix[2] * Rotate[0][2];
    Result[1] = p_matrix[0] * Rotate[1][0] + p_matrix[1] * Rotate[1][1] + p_matrix[2] * Rotate[1][2];
    Result[2] = p_matrix[0] * Rotate[2][0] + p_matrix[1] * Rotate[2][1] + p_matrix[2] * Rotate[2][2];
    Result[3] = p_matrix[3];
    return Result;
}

FMat4 FMat4::Scale(const FMat4& p_matrix, const FVec3& p_scale)
{
    FMat4 result = p_matrix;
    result[0][0] *= p_scale.x;
    result[1][1] *= p_scale.y;
    result[2][2] *= p_scale.z;
    return result;
}

FMat4 FMat4::Multiply(const FMat4& p_matrix1, const FMat4& p_matrix2)
{
    FMat4 result = FMat4::Identity();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.m_matrix[i][j] = p_matrix1.m_matrix[i][0] * p_matrix2.m_matrix[0][j] +
                p_matrix1.m_matrix[i][1] * p_matrix2.m_matrix[1][j] +
                p_matrix1.m_matrix[i][2] * p_matrix2.m_matrix[2][j] +
                p_matrix1.m_matrix[i][3] * p_matrix2.m_matrix[3][j];
        }
    }
    return result;
}

FMat4 FMat4::Transform(const FVec3& p_translation, const FVec3& p_rotation, const FVec3& p_scale)
{
    FMat4 result = FMat4::Identity();

    result = FMat4::Translation(p_translation) * ZRotation(p_rotation.z) * XRotation(p_rotation.x) * YRotation(p_rotation.y) * FMat4::Scale(result, p_scale);
    return result;
}

FMat4 FMat4::Transform(const FVec3& p_translation, const FQuat& p_rotation, const FVec3& p_scale)
{
    FMat4 result = FMat4::Identity();

    result = FMat4::Translation(p_translation) * FQuat::ToRotateMat3(p_rotation) * FMat4::Scale(result, p_scale);
    return result;
}

FMat4 FMat4::XRotation(float p_angle)
{
    float radAngle = TO_RADIANS(p_angle);
    FMat4 result = FMat4::Identity();
    float cos = cosf(radAngle);
    float sin = sinf(radAngle);
    result[1][1] = cos;
    result[1][2] = sin;
    result[2][1] = -sin;
    result[2][2] = cos;
    return result;
}

FMat4 FMat4::XRotation(const FMat4& p_matrix, float p_angle)
{
    FMat4 result = p_matrix;
    result = FMat4::Multiply(result, FMat4::XRotation(p_angle));
    return result;
}

FMat4 FMat4::YRotation(float p_angle)
{
    float radAngle = TO_RADIANS(p_angle);
    FMat4 result = FMat4::Identity();
    float cos = cosf(radAngle);
    float sin = sinf(radAngle);
    result[0][0] = cos;
    result[0][2] = -sin;
    result[2][0] = sin;
    result[2][2] = cos;
    return result;
}

FMat4 FMat4::YRotation(const FMat4& p_matrix, float p_angle)
{
    FMat4 result = p_matrix;
    result = FMat4::Multiply(result, FMat4::YRotation(p_angle));
    return result;
}

FMat4 FMat4::ZRotation(float p_angle)
{
    float radAngle = TO_RADIANS(p_angle);
    FMat4 result = FMat4::Identity();
    float cos = cosf(radAngle);
    float sin = sinf(radAngle);
    result[0][0] = cos;
    result[0][1] = sin;
    result[1][0] = -sin;
    result[1][1] = cos;
    return result;
}

FMat4 FMat4::ZRotation(const FMat4& p_matrix, float p_angle)
{
    FMat4 result = p_matrix;
    result = FMat4::Multiply(result, FMat4::ZRotation(p_angle));
    return result;
}

FMat4 FMat4::YXZRotation(const FVec3& p_rotation)
{
    float yaw = p_rotation.x;
    float pitch = p_rotation.y;
    float roll = p_rotation.z;

    FMat4 Result = FMat4::Identity();
    float cosYaw = cosf(yaw);
    float sinYaw = sinf(yaw);
    float cosPitch = cosf(pitch);
    float sinPitch = sinf(pitch);
    float cosRoll = cosf(roll);
    float sinRoll = sinf(roll);

    Result[0][0] = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
    Result[0][1] = sinRoll * cosPitch;
    Result[0][2] = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
    Result[0][3] = float(0);
    Result[1][0] = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
    Result[1][1] = cosRoll * cosPitch;
    Result[1][2] = sinRoll * sinYaw + cosYaw * sinPitch * cosRoll;
    Result[1][3] = float(0);
    Result[2][0] = sinYaw * cosPitch;
    Result[2][1] = -sinPitch;
    Result[2][2] = cosYaw * cosPitch;
    Result[2][3] = float(0);
    Result[3] = FVec4(0, 0, 0, 1);
    return Result;
}

float* FMat4::ToArray(const FMat4& p_matrix)
{
    float* result = new float[16];
    result[0] = p_matrix[0][0];
    result[1] = p_matrix[0][1];
    result[2] = p_matrix[0][2];
    result[3] = p_matrix[0][3];
    result[4] = p_matrix[1][0];
    result[5] = p_matrix[1][1];
    result[6] = p_matrix[1][2];
    result[7] = p_matrix[1][3];
    result[8] = p_matrix[2][0];
    result[9] = p_matrix[2][1];
    result[10] = p_matrix[2][2];
    result[11] = p_matrix[2][3];
    result[12] = p_matrix[3][0];
    result[13] = p_matrix[3][1];
    result[14] = p_matrix[3][2];
    result[15] = p_matrix[3][3];
    return result;
}

FMat4 lm::FMat4::ToMat4(const FMat3& p_matrix)
{
    FMat4 result = FMat4::Identity();
    result[0][0] = p_matrix[0][0];
    result[0][1] = p_matrix[0][1];
    result[0][2] = p_matrix[0][2];
    result[1][0] = p_matrix[1][0];
    result[1][1] = p_matrix[1][1];
    result[1][2] = p_matrix[1][2];
    result[2][0] = p_matrix[2][0];
    result[2][1] = p_matrix[2][1];
    result[2][2] = p_matrix[2][2];

    return result;
}

void lm::FMat4::Decompose(const FMat4 &p_mat,  FVec3 &p_position,  FVec3 &p_rotation,  FVec3 &p_scale)
{
    p_position = FVec3(p_mat[3][0], p_mat[3][1], p_mat[3][2]);

    p_scale.x = FVec3::Length(FVec3(p_mat[0][0], p_mat[0][1], p_mat[0][2]));
    p_scale.y = FVec3::Length(FVec3(p_mat[1][0], p_mat[1][1], p_mat[1][2]));
    p_scale.z = FVec3::Length(FVec3(p_mat[2][0], p_mat[2][1], p_mat[2][2]));

    FMat4 rot = p_mat;
    rot[0][0] /= p_scale.x;
    rot[0][1] /= p_scale.x;
    rot[0][2] /= p_scale.x;
    rot[1][0] /= p_scale.y;
    rot[1][1] /= p_scale.y;
    rot[1][2] /= p_scale.y;
    rot[2][0] /= p_scale.z;
    rot[2][1] /= p_scale.z;
    rot[2][2] /= p_scale.z;


    p_rotation.x = atan2f(rot[2][1], rot[2][2]);
    p_rotation.y = atan2f(-rot[2][0], sqrtf(rot[2][1] * rot[2][1] + rot[2][2] * rot[2][2]));
    p_rotation.z = atan2f(rot[1][0], rot[0][0]);

    p_rotation = -p_rotation;

    float x = radiansToDegrees(p_rotation.x);
    float y = radiansToDegrees(p_rotation.y);
    float z = radiansToDegrees(p_rotation.z);

    p_rotation = FVec3 { x, y, z };

}



FMat4 lm::FMat4::Inverse(const FMat4& p_matrix)
{
    float Coef00 = p_matrix[2][2] * p_matrix[3][3] - p_matrix[3][2] * p_matrix[2][3];
    float Coef02 = p_matrix[1][2] * p_matrix[3][3] - p_matrix[3][2] * p_matrix[1][3];
    float Coef03 = p_matrix[1][2] * p_matrix[2][3] - p_matrix[2][2] * p_matrix[1][3];

    float Coef04 = p_matrix[2][1] * p_matrix[3][3] - p_matrix[3][1] * p_matrix[2][3];
    float Coef06 = p_matrix[1][1] * p_matrix[3][3] - p_matrix[3][1] * p_matrix[1][3];
    float Coef07 = p_matrix[1][1] * p_matrix[2][3] - p_matrix[2][1] * p_matrix[1][3];

    float Coef08 = p_matrix[2][1] * p_matrix[3][2] - p_matrix[3][1] * p_matrix[2][2];
    float Coef10 = p_matrix[1][1] * p_matrix[3][2] - p_matrix[3][1] * p_matrix[1][2];
    float Coef11 = p_matrix[1][1] * p_matrix[2][2] - p_matrix[2][1] * p_matrix[1][2];

    float Coef12 = p_matrix[2][0] * p_matrix[3][3] - p_matrix[3][0] * p_matrix[2][3];
    float Coef14 = p_matrix[1][0] * p_matrix[3][3] - p_matrix[3][0] * p_matrix[1][3];
    float Coef15 = p_matrix[1][0] * p_matrix[2][3] - p_matrix[2][0] * p_matrix[1][3];

    float Coef16 = p_matrix[2][0] * p_matrix[3][2] - p_matrix[3][0] * p_matrix[2][2];
    float Coef18 = p_matrix[1][0] * p_matrix[3][2] - p_matrix[3][0] * p_matrix[1][2];
    float Coef19 = p_matrix[1][0] * p_matrix[2][2] - p_matrix[2][0] * p_matrix[1][2];

    float Coef20 = p_matrix[2][0] * p_matrix[3][1] - p_matrix[3][0] * p_matrix[2][1];
    float Coef22 = p_matrix[1][0] * p_matrix[3][1] - p_matrix[3][0] * p_matrix[1][1];
    float Coef23 = p_matrix[1][0] * p_matrix[2][1] - p_matrix[2][0] * p_matrix[1][1];

    FVec4 Fac0(Coef00, Coef00, Coef02, Coef03);
    FVec4 Fac1(Coef04, Coef04, Coef06, Coef07);
    FVec4 FacosPitch(Coef08, Coef08, Coef10, Coef11);
    FVec4 Fac3(Coef12, Coef12, Coef14, Coef15);
    FVec4 Fac4(Coef16, Coef16, Coef18, Coef19);
    FVec4 Fac5(Coef20, Coef20, Coef22, Coef23);

    FVec4 Vec0(p_matrix[1][0], p_matrix[0][0], p_matrix[0][0], p_matrix[0][0]);
    FVec4 Vec1(p_matrix[1][1], p_matrix[0][1], p_matrix[0][1], p_matrix[0][1]);
    FVec4 VecosPitch(p_matrix[1][2], p_matrix[0][2], p_matrix[0][2], p_matrix[0][2]);
    FVec4 Vec3(p_matrix[1][3], p_matrix[0][3], p_matrix[0][3], p_matrix[0][3]);

    FVec4 Inv0(Vec1 * Fac0 - VecosPitch * Fac1 + Vec3 * FacosPitch);
    FVec4 Inv1(Vec0 * Fac0 - VecosPitch * Fac3 + Vec3 * Fac4);
    FVec4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
    FVec4 Inv3(Vec0 * FacosPitch - Vec1 * Fac4 + VecosPitch * Fac5);

    FVec4 SignA(+1, -1, +1, -1);
    FVec4 SignB(-1, +1, -1, +1);

    FMat4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

    FVec4 Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

    FVec4 Dot0(p_matrix[0] * Row0);
    float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

    float OneOverDeterminant = 1.0f / Dot1;

    return Inverse * OneOverDeterminant;
}

std::ostream& lm::operator<<(std::ostream& p_stream, const FMat4& p_matrix)
{
    p_stream << p_matrix[0][0] << " " << p_matrix[0][1] << " " << p_matrix[0][2] << " " << p_matrix[0][3] << std::endl;
    p_stream << p_matrix[1][0] << " " << p_matrix[1][1] << " " << p_matrix[1][2] << " " << p_matrix[1][3] << std::endl;
    p_stream << p_matrix[2][0] << " " << p_matrix[2][1] << " " << p_matrix[2][2] << " " << p_matrix[2][3] << std::endl;
    p_stream << p_matrix[3][0] << " " << p_matrix[3][1] << " " << p_matrix[3][2] << " " << p_matrix[3][3] << std::endl;
    return p_stream;
}

std::istream& lm::operator>>(std::istream& p_stream, FMat4& p_matrix)
{
    p_stream >> p_matrix[0][0];
    p_stream >> p_matrix[0][1];
    p_stream >> p_matrix[0][2];
    p_stream >> p_matrix[0][3];
    p_stream >> p_matrix[1][0];
    p_stream >> p_matrix[1][1];
    p_stream >> p_matrix[1][2];
    p_stream >> p_matrix[1][3];
    p_stream >> p_matrix[2][0];
    p_stream >> p_matrix[2][1];
    p_stream >> p_matrix[2][2];
    p_stream >> p_matrix[2][3];
    p_stream >> p_matrix[3][0];
    p_stream >> p_matrix[3][1];
    p_stream >> p_matrix[3][2];
    p_stream >> p_matrix[3][3];
    return p_stream;
}

FMat4 lm::operator*(float p_scalar, const FMat4& p_matrix)
{
    FMat4 result = p_matrix;
    result[0][0] *= p_scalar;
    result[0][1] *= p_scalar;
    result[0][2] *= p_scalar;
    result[0][3] *= p_scalar;
    result[1][0] *= p_scalar;
    result[1][1] *= p_scalar;
    result[1][2] *= p_scalar;
    result[1][3] *= p_scalar;
    result[2][0] *= p_scalar;
    result[2][1] *= p_scalar;
    result[2][2] *= p_scalar;
    result[2][3] *= p_scalar;
    result[3][0] *= p_scalar;
    result[3][1] *= p_scalar;
    result[3][2] *= p_scalar;
    result[3][3] *= p_scalar;
    return result;
}

FMat4 lm::operator/(float p_scalar, const FMat4& p_matrix)
{
    FMat4 result = p_matrix;
    result[0][0] /= p_scalar;
    result[0][1] /= p_scalar;
    result[0][2] /= p_scalar;
    result[0][3] /= p_scalar;
    result[1][0] /= p_scalar;
    result[1][1] /= p_scalar;
    result[1][2] /= p_scalar;
    result[1][3] /= p_scalar;
    result[2][0] /= p_scalar;
    result[2][1] /= p_scalar;
    result[2][2] /= p_scalar;
    result[2][3] /= p_scalar;
    result[3][0] /= p_scalar;
    result[3][1] /= p_scalar;
    result[3][2] /= p_scalar;
    result[3][3] /= p_scalar;
    return result;
}