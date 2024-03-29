#include "FMat3.hpp"
#include "../Quaternion/FQuat.hpp"
#include "../Mat4/FMat4.hpp"
using namespace lm;

const FMat3 FMat3::identity = FMat3(1.0f);

FMat3::FMat3(const float p_init)
{
	m_matrix[0][0] = p_init;
	m_matrix[1][1] = p_init;
	m_matrix[2][2] = p_init;
}

FMat3::FMat3(float p_00, float p_01, float p_02,
	float p_10, float p_11, float p_12,
	float p_20, float p_21, float p_22)
{
	m_matrix[0][0] = p_00;
	m_matrix[0][1] = p_01;
	m_matrix[0][2] = p_02;

	m_matrix[1][0] = p_10;
	m_matrix[1][1] = p_11;
	m_matrix[1][2] = p_12;

	m_matrix[2][0] = p_20;
	m_matrix[2][1] = p_21;
	m_matrix[2][2] = p_22;
}

FMat3::FMat3(const FVec3& p_vec1, const FVec3& p_vec2, const FVec3& p_vec3)
{
	m_matrix[0] = p_vec1;
	m_matrix[1] = p_vec2;
	m_matrix[2] = p_vec3;
}

FMat3::FMat3(const FMat4& p_mat4)
{
	m_matrix[0] = p_mat4[0];
	m_matrix[1] = p_mat4[1];
	m_matrix[2] = p_mat4[2];
}

FMat3::FMat3(FMat4&& mat4) noexcept 

{
	m_matrix[0] = mat4[0];
	m_matrix[1] = mat4[1];
	m_matrix[2] = mat4[2];
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
	return m_matrix[0] == p_mat3.m_matrix[0] && m_matrix[1] == p_mat3.m_matrix[1] && m_matrix[2] == p_mat3.m_matrix[2];
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
	return FMat3(FVec3(mat3[0][0], mat3[1][0], mat3[2][0]), FVec3(mat3[0][1], mat3[1][1], mat3[2][1]), FVec3(mat3[0][2], mat3[1][2], mat3[2][2]));
}

float FMat3::Determinant(const FMat3& mat3)
{
	return  (
		+mat3[0][0] * (mat3[1][1] * mat3[2][2] - mat3[2][1] * mat3[1][2])
		- mat3[1][0] * (mat3[0][1] * mat3[2][2] - mat3[2][1] * mat3[0][2])
		+ mat3[2][0] * (mat3[0][1] * mat3[1][2] - mat3[1][1] * mat3[0][2]));
}

FMat3 FMat3::Inverse(const FMat3& mat3)
{
	float OneOverDeterminant = static_cast<float>(1) / (
		+mat3[0][0] * (mat3[1][1] * mat3[2][2] - mat3[2][1] * mat3[1][2])
		- mat3[1][0] * (mat3[0][1] * mat3[2][2] - mat3[2][1] * mat3[0][2])
		+ mat3[2][0] * (mat3[0][1] * mat3[1][2] - mat3[1][1] * mat3[0][2]));

	FMat3 Inverse;
	Inverse[0][0] = +(mat3[1][1] * mat3[2][2] - mat3[2][1] * mat3[1][2]) * OneOverDeterminant;
	Inverse[1][0] = -(mat3[1][0] * mat3[2][2] - mat3[2][0] * mat3[1][2]) * OneOverDeterminant;
	Inverse[2][0] = +(mat3[1][0] * mat3[2][1] - mat3[2][0] * mat3[1][1]) * OneOverDeterminant;
	Inverse[0][1] = -(mat3[0][1] * mat3[2][2] - mat3[2][1] * mat3[0][2]) * OneOverDeterminant;
	Inverse[1][1] = +(mat3[0][0] * mat3[2][2] - mat3[2][0] * mat3[0][2]) * OneOverDeterminant;
	Inverse[2][1] = -(mat3[0][0] * mat3[2][1] - mat3[2][0] * mat3[0][1]) * OneOverDeterminant;
	Inverse[0][2] = +(mat3[0][1] * mat3[1][2] - mat3[1][1] * mat3[0][2]) * OneOverDeterminant;
	Inverse[1][2] = -(mat3[0][0] * mat3[1][2] - mat3[1][0] * mat3[0][2]) * OneOverDeterminant;
	Inverse[2][2] = +(mat3[0][0] * mat3[1][1] - mat3[1][0] * mat3[0][1]) * OneOverDeterminant;

	return Inverse;
}



FMat3 FMat3::Rotation(float p_angle, const FVec3& p_axis)
{
	FMat3 result = FMat3::Identity();
	const FVec3 axis = FVec3::Normalize(p_axis);
	const float RadAngle = TO_RADIANS(p_angle);
	const float Rx = axis.x;
	const float Ry = axis.y;
	const float Rz = axis.z;
	const float Rx2 = Rx * Rx;
	const float Ry2 = Ry * Ry;
	const float Rz2 = Rz * Rz;
	const float cosTheta = std::cosf(RadAngle);
	const float sinTheta = std::sinf(RadAngle);

	result[0] = FVec3(cosTheta + Rx2 * (1 - cosTheta), Rx * Ry * (1 - cosTheta) - Rz * sinTheta, Rx * Rz * (1 - cosTheta) + Ry * sinTheta);
	result[1] = FVec3(Ry * Rx * (1 - cosTheta) + Rz * sinTheta, cosTheta + Ry2 * (1 - cosTheta), Ry * Rz * (1 - cosTheta) - Rx * sinTheta);
	result[2] = FVec3(Rz * Rx * (1 - cosTheta) - Ry * sinTheta, Rz * Ry * (1 - cosTheta) + Rx * sinTheta, cosTheta + Rz2 * (1 - cosTheta));

	
	return  Transpose(result);

}

FMat3 FMat3::Rotate(const FMat3& p_mat, const float p_angle, const FVec3& p_axis)
{

	float radAngle = TO_RADIANS(p_angle);
	float const a = radAngle;

	float const c = cos(a);
	float const s = sin(a);

	FVec3 axis(FVec3::Normalize(p_axis));
	FVec3 temp((float(1) - c) * axis);

	FMat3 Rotate;
	Rotate[0][0] = c + temp[0] * axis[0];
	Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
	Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

	Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
	Rotate[1][1] = c + temp[1] * axis[1];
	Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

	Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
	Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
	Rotate[2][2] = c + temp[2] * axis[2];

	FMat3 Result;
	Result[0] = p_mat[0] * Rotate[0][0] + p_mat[1] * Rotate[0][1] + p_mat[2] * Rotate[0][2];
	Result[1] = p_mat[0] * Rotate[1][0] + p_mat[1] * Rotate[1][1] + p_mat[2] * Rotate[1][2];
	Result[2] = p_mat[0] * Rotate[2][0] + p_mat[1] * Rotate[2][1] + p_mat[2] * Rotate[2][2];

	return Result;
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