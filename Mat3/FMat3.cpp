#include "FMat3.hpp"
#include "../Quaternion/FQuat.hpp"
using namespace lm;

const FMat3 FMat3::identity = FMat3(1.0f);

FMat3::FMat3(const float p_init)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
            {
                m_matrix[i][j] = p_init;
            }
            else
            {
                m_matrix[i][j] = 0;
            }
        }
    }
}

FMat3::FMat3(const FVec3& p_vec1, const FVec3& p_vec2, const FVec3& p_vec3)
{
    m_matrix[0] = p_vec1;
    m_matrix[1] = p_vec2;
    m_matrix[2] = p_vec3;
}

FMat3::FMat3(const FVec3& p_position, const FQuat& p_rotation)
{
    FMat3 result = FQuat::ToMatrix3(p_rotation);

    result = FMat3::Translation(p_position);

    *this = result;
}

FMat3::FMat3(const FMat3& p_mat3)
{
    m_matrix[0] = p_mat3.m_matrix[0];
    m_matrix[1] = p_mat3.m_matrix[1];
    m_matrix[2] = p_mat3.m_matrix[2];
}

FMat3& FMat3::operator=(const FMat3& p_mat3)
{
    m_matrix[0] = p_mat3.m_matrix[0];
    m_matrix[1] = p_mat3.m_matrix[1];
    m_matrix[2] = p_mat3.m_matrix[2];

    return *this;
}

FVec3& FMat3::operator[](const unsigned int p_index)
{
    return m_matrix[p_index];
}

const FVec3& FMat3::operator[](const unsigned int p_index) const
{
    return m_matrix[p_index];
}

float& FMat3::operator()(const unsigned int p_row, const unsigned int p_col)
{
    return m_matrix[p_row][p_col];
}

float FMat3::operator()(const unsigned int p_row, const unsigned int p_col) const
{
    return m_matrix[p_row][p_col];
}

float& FMat3::operator()(const char* p_index)
{
    unsigned int vecIdx = p_index[1] - '1';
    switch (p_index[0])
    {
    case 'x': return m_matrix[vecIdx].x;
    case 'y': return m_matrix[vecIdx].y;
    case 'z': return m_matrix[vecIdx].z;
    default: throw std::runtime_error("FMat3::operator(): Invalid index");
    }
}

float FMat3::operator()(const char* p_index) const
{
    unsigned int vecIdx = p_index[1] - '1';
    switch (p_index[0])
    {
    case 'x': return m_matrix[vecIdx].x;
    case 'y': return m_matrix[vecIdx].y;
    case 'z': return m_matrix[vecIdx].z;
    default: throw std::runtime_error("FMat3::operator(): Invalid index");
    }
}

FMat3 FMat3::operator+(const FMat3& p_mat3) const
{
    return FMat3::Add(*this, p_mat3);
}

FMat3 FMat3::operator-(const FMat3& p_mat3) const
{
    return FMat3::Subtract(*this, p_mat3);
}

FMat3 FMat3::operator*(const FMat3& p_mat3) const
{
    return FMat3::Multiply(*this, p_mat3);
}

FMat3 FMat3::operator*(const float p_scalar) const
{
    return FMat3::Multiply(*this, p_scalar);
}

FMat3 FMat3::operator/(const float p_scalar) const
{
    return FMat3::Divide(*this, p_scalar);
}

FMat3& FMat3::operator+=(const FMat3& p_mat3)
{
    m_matrix[0] += p_mat3.m_matrix[0];
    m_matrix[1] += p_mat3.m_matrix[1];
    m_matrix[2] += p_mat3.m_matrix[2];

    return *this;
}

FMat3& FMat3::operator-=(const FMat3& p_mat3)
{
    m_matrix[0] -= p_mat3.m_matrix[0];
    m_matrix[1] -= p_mat3.m_matrix[1];
    m_matrix[2] -= p_mat3.m_matrix[2];

    return *this;
}

FMat3& FMat3::operator*=(const FMat3& p_mat3)
{
    FMat3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = m_matrix[i][0] * p_mat3.m_matrix[0][j] + m_matrix[i][1] * p_mat3.m_matrix[1][j] + m_matrix[i][2] * p_mat3.m_matrix[2][j];
        }
    }
    *this = result;
    return *this;
}

FMat3& FMat3::operator*=(const float p_scalar)
{
    m_matrix[0] *= p_scalar;
    m_matrix[1] *= p_scalar;
    m_matrix[2] *= p_scalar;

    return *this;
}

FMat3& FMat3::operator/=(const float p_scalar)
{
    m_matrix[0] /= p_scalar;
    m_matrix[1] /= p_scalar;
    m_matrix[2] /= p_scalar;

    return *this;
}

FMat3 FMat3::operator-() const
{
    return FMat3(-m_matrix[0], -m_matrix[1], -m_matrix[2]);
}

bool FMat3::operator==(const FMat3& p_mat3) const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_matrix[i][j] != p_mat3.m_matrix[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool FMat3::operator!=(const FMat3& p_mat3) const
{
    return !(*this == p_mat3);
}

FMat3 FMat3::Identity()
{
    return FMat3(FVec3(1.0f, 0.0f, 0.0f), FVec3(0.0f, 1.0f, 0.0f), FVec3(0.0f, 0.0f, 1.0f));
}

FMat3 FMat3::Transpose(const FMat3& mat3)
{
    FMat3 result = FMat3::Identity();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = mat3.m_matrix[j][i];
        }
    }
    return result;
}

float FMat3::Determinant(const FMat3& mat3)
{
    return mat3.m_matrix[0][0] * (mat3.m_matrix[1][1] * mat3.m_matrix[2][2] - mat3.m_matrix[1][2] * mat3.m_matrix[2][1]) -
        mat3.m_matrix[0][1] * (mat3.m_matrix[1][0] * mat3.m_matrix[2][2] - mat3.m_matrix[1][2] * mat3.m_matrix[2][0]) +
        mat3.m_matrix[0][2] * (mat3.m_matrix[1][0] * mat3.m_matrix[2][1] - mat3.m_matrix[1][1] * mat3.m_matrix[2][0]);
}

FMat3 FMat3::Inverse(const FMat3& mat3)
{
    FMat3 result = FMat3::Identity();
    float det = FMat3::Determinant(mat3);
    if (det == 0.0f)
    {
        throw std::runtime_error("FMat3::Inverse(): Determinant is 0");
    }
    result.m_matrix[0][0] = (mat3.m_matrix[1][1] * mat3.m_matrix[2][2] - mat3.m_matrix[1][2] * mat3.m_matrix[2][1]) / det;
    result.m_matrix[0][1] = (mat3.m_matrix[0][2] * mat3.m_matrix[2][1] - mat3.m_matrix[0][1] * mat3.m_matrix[2][2]) / det;
    result.m_matrix[0][2] = (mat3.m_matrix[0][1] * mat3.m_matrix[1][2] - mat3.m_matrix[0][2] * mat3.m_matrix[1][1]) / det;
    result.m_matrix[1][0] = (mat3.m_matrix[1][2] * mat3.m_matrix[2][0] - mat3.m_matrix[1][0] * mat3.m_matrix[2][2]) / det;
    result.m_matrix[1][1] = (mat3.m_matrix[0][0] * mat3.m_matrix[2][2] - mat3.m_matrix[0][2] * mat3.m_matrix[2][0]) / det;
    result.m_matrix[1][2] = (mat3.m_matrix[0][2] * mat3.m_matrix[1][0] - mat3.m_matrix[0][0] * mat3.m_matrix[1][2]) / det;
    result.m_matrix[2][0] = (mat3.m_matrix[1][0] * mat3.m_matrix[2][1] - mat3.m_matrix[1][1] * mat3.m_matrix[2][0]) / det;
    result.m_matrix[2][1] = (mat3.m_matrix[0][1] * mat3.m_matrix[2][0] - mat3.m_matrix[0][0] * mat3.m_matrix[2][1]) / det;
    result.m_matrix[2][2] = (mat3.m_matrix[0][0] * mat3.m_matrix[1][1] - mat3.m_matrix[0][1] * mat3.m_matrix[1][0]) / det;
    return result;
}

FMat3 FMat3::RotationX(float p_angle)
{
    float radAngle = TO_RADIANS(p_angle);
    FMat3 result = FMat3::Identity();
    result.m_matrix[1][1] = cos(radAngle);
    result.m_matrix[1][2] = -sin(radAngle);
    result.m_matrix[2][1] = sin(radAngle);
    result.m_matrix[2][2] = cos(radAngle);
    return result;
}

FMat3 FMat3::RotationY(float p_angle)
{
    float radAngle = TO_RADIANS(p_angle);
    FMat3 result = FMat3::Identity();
    result.m_matrix[0][0] = cos(radAngle);
    result.m_matrix[0][2] = sin(radAngle);
    result.m_matrix[2][0] = -sin(radAngle);
    result.m_matrix[2][2] = cos(radAngle);
    return result;
}

FMat3 FMat3::RotationZ(float p_angle)
{
    float radAngle = TO_RADIANS(p_angle);
    FMat3 result = FMat3::Identity();
    result.m_matrix[0][0] = cos(radAngle);
    result.m_matrix[0][1] = -sin(radAngle);
    result.m_matrix[1][0] = sin(radAngle);
    result.m_matrix[1][1] = cos(radAngle);
    return result;
}

FMat3 FMat3::Rotation(float p_angle, const FVec3& p_axis)
{
    float radAngle = TO_RADIANS(p_angle);
    FMat3 result = FMat3::Identity();
    float c = cos(radAngle);
    float s = sin(radAngle);
    float t = 1.0f - c;
    result.m_matrix[0][0] = t * p_axis.x * p_axis.x + c;
    result.m_matrix[0][1] = t * p_axis.x * p_axis.y - s * p_axis.z;
    result.m_matrix[0][2] = t * p_axis.x * p_axis.z + s * p_axis.y;
    result.m_matrix[1][0] = t * p_axis.x * p_axis.y + s * p_axis.z;
    result.m_matrix[1][1] = t * p_axis.y * p_axis.y + c;
    result.m_matrix[1][2] = t * p_axis.y * p_axis.z - s * p_axis.x;
    result.m_matrix[2][0] = t * p_axis.x * p_axis.z - s * p_axis.y;
    result.m_matrix[2][1] = t * p_axis.y * p_axis.z + s * p_axis.x;
    result.m_matrix[2][2] = t * p_axis.z * p_axis.z + c;
    return result;
}

FMat3 FMat3::Rotation(const FVec3& p_rotation)
{
    FMat3 result = FMat3::Identity();
    result = FMat3::RotationX(p_rotation.x) * FMat3::RotationY(p_rotation.y) * FMat3::RotationZ(p_rotation.z);
    return result;
}

FMat3 FMat3::Rotation(const float p_angle)
{
    FMat3 result = FMat3::Identity();
    result = FMat3::RotationX(p_angle) * FMat3::RotationY(p_angle) * FMat3::RotationZ(p_angle);
    return result;
}

FMat3 FMat3::Rotation(const float p_angleX, const float p_angleY, const float p_angleZ)
{
    FMat3 result = FMat3::Identity();
    result = FMat3::RotationX(p_angleX) * FMat3::RotationY(p_angleY) * FMat3::RotationZ(p_angleZ);
    return result;
}

FMat3 FMat3::Scale(const FVec3& p_scale)
{
    FMat3 result = FMat3::Identity();
    result.m_matrix[0][0] = p_scale.x;
    result.m_matrix[1][1] = p_scale.y;
    result.m_matrix[2][2] = p_scale.z;
    return result;
}

FMat3 FMat3::Scale(const float p_scale)
{
    FMat3 result = FMat3::Identity();
    result.m_matrix[0][0] = p_scale;
    result.m_matrix[1][1] = p_scale;
    result.m_matrix[2][2] = p_scale;
    return result;
}

FMat3 FMat3::Scale(const float p_scaleX, const float p_scaleY, const float p_scaleZ)
{
    FMat3 result = FMat3::Identity();
    result.m_matrix[0][0] = p_scaleX;
    result.m_matrix[1][1] = p_scaleY;
    result.m_matrix[2][2] = p_scaleZ;
    return result;
}

FMat3 FMat3::Translation(const FVec3& p_translation)
{
    FMat3 result = FMat3::Identity();
    result.m_matrix[2][0] = p_translation.x;
    result.m_matrix[2][1] = p_translation.y;
    result.m_matrix[2][2] = p_translation.z;
    return result;
}

FMat3 FMat3::Translation(const float p_x, const float p_y, const float p_z)
{
    FMat3 result = FMat3::Identity();
    result.m_matrix[2][0] = p_x;
    result.m_matrix[2][1] = p_y;
    result.m_matrix[2][2] = p_z;
    return result;
}

FMat3 FMat3::Multiply(const FMat3& p_mat1, const FMat3& p_mat2)
{
    FMat3 result = FMat3::Identity();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = p_mat1.m_matrix[i][0] * p_mat2.m_matrix[0][j] + p_mat1.m_matrix[i][1] * p_mat2.m_matrix[1][j] + p_mat1.m_matrix[i][2] * p_mat2.m_matrix[2][j];
        }
    }
    return result;
}

FMat3 lm::FMat3::Multiply(const FMat3& mat3, const FVec3& vec3)
{
    FMat3 result = FMat3::Identity();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = mat3.m_matrix[i][0] * vec3.x + mat3.m_matrix[i][1] * vec3.y + mat3.m_matrix[i][2] * vec3.z;
        }
    }
    return result;
}

FMat3 FMat3::Multiply(const FMat3& p_mat, const float p_scalar)
{
    FMat3 result = FMat3::Identity();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = p_mat.m_matrix[i][j] * p_scalar;
        }
    }
    return result;
}

FMat3 FMat3::Add(const FMat3& p_mat1, const FMat3& p_mat2)
{
    FMat3 result = FMat3::Identity();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = p_mat1.m_matrix[i][j] + p_mat2.m_matrix[i][j];
        }
    }
    return result;
}

FMat3 FMat3::Subtract(const FMat3& p_mat1, const FMat3& p_mat2)
{
    FMat3 result = FMat3::Identity();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = p_mat1.m_matrix[i][j] - p_mat2.m_matrix[i][j];
        }
    }
    return result;
}

FMat3 lm::FMat3::Divide(const FMat3& mat3, const float scalar)
{
    FMat3 result = FMat3::Identity();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = mat3.m_matrix[i][j] / scalar;
        }
    }
    return result;
}

FMat3 FMat3::Divide(const FMat3& p_mat1, const FMat3& p_mat2)
{
    FMat3 result = FMat3::Identity();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.m_matrix[i][j] = p_mat1.m_matrix[i][j] / p_mat2.m_matrix[i][j];
        }
    }
    return result;
}

FMat3 FMat3::Transform(const FVec3& p_position, const FVec3& p_rotation, const FVec3& p_scale)
{
    FMat3 result = FMat3::Identity();
    result = FMat3::Translation(p_position) * FMat3::Rotation(p_rotation) * FMat3::Scale(p_scale);
    return result;
}

float* lm::FMat3::ToArray(const FMat3& mat3)
{
    float* result = new float[9];
    result[0] = mat3.m_matrix[0][0];
    result[1] = mat3.m_matrix[0][1];
    result[2] = mat3.m_matrix[0][2];
    result[3] = mat3.m_matrix[1][0];
    result[4] = mat3.m_matrix[1][1];
    result[5] = mat3.m_matrix[1][2];
    result[6] = mat3.m_matrix[2][0];
    result[7] = mat3.m_matrix[2][1];
    result[8] = mat3.m_matrix[2][2];
    return result;
}

std::ostream& lm::operator<<(std::ostream& p_stream, const FMat3& p_mat)
{
    p_stream << p_mat.m_matrix[0][0] << " " << p_mat.m_matrix[0][1] << " " << p_mat.m_matrix[0][2] << std::endl;
    p_stream << p_mat.m_matrix[1][0] << " " << p_mat.m_matrix[1][1] << " " << p_mat.m_matrix[1][2] << std::endl;
    p_stream << p_mat.m_matrix[2][0] << " " << p_mat.m_matrix[2][1] << " " << p_mat.m_matrix[2][2] << std::endl;
    return p_stream;
}

std::istream& lm::operator>>(std::istream& p_stream, FMat3& p_mat)
{
    p_stream >> p_mat.m_matrix[0][0] >> p_mat.m_matrix[0][1] >> p_mat.m_matrix[0][2];
    p_stream >> p_mat.m_matrix[1][0] >> p_mat.m_matrix[1][1] >> p_mat.m_matrix[1][2];
    p_stream >> p_mat.m_matrix[2][0] >> p_mat.m_matrix[2][1] >> p_mat.m_matrix[2][2];
    return p_stream;
}

FMat3 lm::operator*(const float p_scalar, const FMat3& p_mat)
{
    return FMat3::Multiply(p_mat, p_scalar);
}

FMat3 lm::operator/(const float p_scalar, const FMat3& p_mat)
{
    return FMat3::Divide(p_mat, p_scalar);
}

FMat3 lm::operator*(const FMat3& p_mat, const FVec3& p_vec)
{
    return FMat3::Multiply(p_mat, p_vec);
}

FMat3 lm::operator*(const FVec3& p_vec, const FMat3& p_mat)
{
    return FMat3::Multiply(p_mat, p_vec);
}