#include "FMat4.hpp"
#include "../Vec4/FVec4.hpp"
#include "../Vec3/FVec3.hpp"
using namespace lm;

const FMat4 FMat4::IdentityMatrix(1.0f);

FMat4::FMat4(float p_init)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				m_matrix[i][j] = p_init;
			}
			else
			{
				m_matrix[i][j] = 0.0f;
			}
		}
	}
}

FMat4::FMat4(FVec4 p_row1, FVec4 p_row2, FVec4 p_row3, FVec4 p_row4)
{
	m_matrix[0] = p_row1;
	m_matrix[1] = p_row2;
	m_matrix[2] = p_row3;
	m_matrix[3] = p_row4;
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
	FMat4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m_matrix[i][j] = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				result.m_matrix[i][j] += m_matrix[i][k] * p_other.m_matrix[k][j];
			}
		}
	}
	return result;
}

FMat4& FMat4::operator*=(const FMat4& p_other)
{
	*this = *this * p_other;
	return *this;
}

FVec4 FMat4::operator*(const FVec4& p_other) const
{
	FVec4 result;
	for (int i = 0; i < 4; i++)
	{
		result[i] = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			result[i] += m_matrix[i][j] * p_other[j];
		}
	}
	return result;
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

FMat4& FMat4::operator*=(float p_scalar)
{
	*this = *this * p_scalar;
	return *this;
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

float FMat4::operator()(int p_row, int p_col)
{
	return m_matrix[p_row][p_col];
}

const float FMat4::operator()(int p_row, int p_col) const
{
	return m_matrix[p_row][p_col];
}

float& FMat4::operator[](const char* p_index)
{
	unsigned int vecIdx = p_index[1] - '0';
	switch (p_index[0])
	{
	case 'x': return this->m_matrix[vecIdx].x;
	case 'y': return this->m_matrix[vecIdx].y;
	case 'z': return this->m_matrix[vecIdx].z;
	case 'w': return this->m_matrix[vecIdx].w;
	default: return this->m_matrix[vecIdx].x;
	}
}

const float& FMat4::operator[](const char* p_index) const
{
	unsigned int vecIdx = p_index[1] - '0';
	switch (p_index[0])
	{
	case 'x': return this->m_matrix[vecIdx].x;
	case 'y': return this->m_matrix[vecIdx].y;
	case 'z': return this->m_matrix[vecIdx].z;
	case 'w': return this->m_matrix[vecIdx].w;
	default: return this->m_matrix[vecIdx].x;
	}
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
	result["x3"] = p_translation.x;
	result["y3"] = p_translation.y;
	result["z3"] = p_translation.z;
	return result;
}

FMat4 FMat4::Rotation(const FVec3& p_rotation)
{
	FMat4 result = FMat4::Identity();
	result["x0"] = cos(p_rotation.y) * cos(p_rotation.z);
	result["x1"] = cos(p_rotation.y) * sin(p_rotation.z);
	result["x2"] = -sin(p_rotation.y);
	result["y0"] = sin(p_rotation.x) * sin(p_rotation.y) * cos(p_rotation.z) - cos(p_rotation.x) * sin(p_rotation.z);
	result["y1"] = sin(p_rotation.x) * sin(p_rotation.y) * sin(p_rotation.z) + cos(p_rotation.x) * cos(p_rotation.z);
	result["y2"] = sin(p_rotation.x) * cos(p_rotation.y);
	result["z0"] = cos(p_rotation.x) * sin(p_rotation.y) * cos(p_rotation.z) + sin(p_rotation.x) * sin(p_rotation.z);
	result["z1"] = cos(p_rotation.x) * sin(p_rotation.y) * sin(p_rotation.z) - sin(p_rotation.x) * cos(p_rotation.z);
	result["z2"] = cos(p_rotation.x) * cos(p_rotation.y);
	return result;
}

FMat4 FMat4::Scale(const FVec3& p_scale)
{
	FMat4 result = FMat4::Identity();
	result["x0"] = p_scale.x;
	result["y1"] = p_scale.y;
	result["z2"] = p_scale.z;
	return result;
}

FMat4 FMat4::LookAt(const FVec3& p_eye, const FVec3& p_target, const FVec3& p_up)
{
	const FVec3 forward(p_target - p_eye);
	FVec3::Normalize(forward);

	const FVec3 right(FVec3::Cross(forward, p_up));
	FVec3::Normalize(right);

	const FVec3 up(FVec3::Cross(right, forward));

	FMat4 result = FMat4::Identity();

	result[0][0] = right.x;
	result[1][0] = right.y;
	result[2][0] = right.z;

	result[0][1] = up.x;
	result[1][1] = up.y;
	result[2][1] = up.z;

	result[0][2] = -forward.x;
	result[1][2] = -forward.y;
	result[2][2] = -forward.z;

	result[3][0] = -FVec3::Dot(right, p_eye);
	result[3][1] = -FVec3::Dot(up, p_eye);
	result[3][2] = FVec3::Dot(forward, p_eye);

	return result;
}

FMat4 FMat4::Perspective(float p_fov, float p_aspect, float p_near, float p_far)
{
	FMat4 result = FMat4::Identity();
	float scale = tan(p_fov * PI / 360) * p_near;
	float r = p_aspect * scale;
	float l = -r;
	float t = scale;
	float b = -t;
	float x1 = 2 * p_near / (r - l);
	float y2 = 2 * p_near / (t - b);
	float x3 = (r + l) / (r - l);
	float y3 = (t + b) / (t - b);
	float z3 = -(p_far + p_near) / (p_far - p_near);
	float z4 = -(2 * p_far * p_near) / (p_far - p_near);

	result["x0"] = x1;
	result["y1"] = y2;
	result["x2"] = x3;
	result["y2"] = y3;
	result["z2"] = z3;
	result["z3"] = z4;
	result["w2"] = -1;

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

	result["x0"] = x1;
	result["y1"] = y2;
	result["z2"] = z3;
	result["x3"] = x3;
	result["y3"] = y3;
	result["z3"] = z4;

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
	result["x3"] += p_translation.x;
	result["y3"] += p_translation.y;
	result["z3"] += p_translation.z;
	return result;
}

FMat4 FMat4::Rotate(const FMat4& p_matrix, const FVec3& p_rotation)
{
	FMat4 result = p_matrix;
	result = FMat4::ZRotation(result, p_rotation.z);
	result = FMat4::XRotation(result, p_rotation.x);
	result = FMat4::YRotation(result, p_rotation.y);
	return result;
}

FMat4 FMat4::Scale(const FMat4& p_matrix, const FVec3& p_scale)
{
	FMat4 result = p_matrix;
	result["x0"] *= p_scale.x;
	result["y1"] *= p_scale.y;
	result["z2"] *= p_scale.z;
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
	result = FMat4::Translate(result, p_translation);
	result = FMat4::Rotate(result, p_rotation);
	result = FMat4::Scale(result, p_scale);
	return result;
}

FMat4 FMat4::XRotation(float p_angle)
{
	float radAngle = TO_RADIANS(p_angle);
	FMat4 result = FMat4::Identity();
	float cos = cosf(radAngle);
	float sin = sinf(radAngle);
	result["y1"] = cos;
	result["z1"] = -sin;
	result["y2"] = sin;
	result["z2"] = cos;
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
	result["x0"] = cos;
	result["z0"] = sin;
	result["x2"] = -sin;
	result["z2"] = cos;
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
	result["x0"] = cos;
	result["y0"] = -sin;
	result["x1"] = sin;
	result["y1"] = cos;
	return result;
}

FMat4 FMat4::ZRotation(const FMat4& p_matrix, float p_angle)
{
	FMat4 result = p_matrix;
	result = FMat4::Multiply(result, FMat4::ZRotation(p_angle));
	return result;
}

FMat4 FMat4::XYZRotation(const FVec3& p_rotation)
{
	FMat4 result = FMat4::Identity();
	result = FMat4::ZRotation(p_rotation.x) * FMat4::XRotation(p_rotation.y) * FMat4::YRotation(p_rotation.z);
	return result;
}

FMat4 FMat4::XYZRotation(const FMat4& p_matrix, const FVec3& p_rotation)
{
	FMat4 result = p_matrix;
	result = FMat4::Multiply(result, FMat4::XYZRotation(p_rotation));
	return result;
}

std::ostream& lm::operator<<(std::ostream& p_stream, const FMat4& p_matrix)
{
	p_stream << p_matrix["x0"] << " " << p_matrix["y0"] << " " << p_matrix["z0"] << " " << p_matrix["w0"] << std::endl;
	p_stream << p_matrix["x1"] << " " << p_matrix["y1"] << " " << p_matrix["z1"] << " " << p_matrix["w1"] << std::endl;
	p_stream << p_matrix["x2"] << " " << p_matrix["y2"] << " " << p_matrix["z2"] << " " << p_matrix["w2"] << std::endl;
	p_stream << p_matrix["x3"] << " " << p_matrix["y3"] << " " << p_matrix["z3"] << " " << p_matrix["w3"] << std::endl;
	return p_stream;
}

FMat4 lm::operator*(float p_scalar, const FMat4& p_matrix)
{
	FMat4 result = p_matrix;
	result["x0"] *= p_scalar;
	result["y0"] *= p_scalar;
	result["z0"] *= p_scalar;
	result["w0"] *= p_scalar;
	result["x1"] *= p_scalar;
	result["y1"] *= p_scalar;
	result["z1"] *= p_scalar;
	result["w1"] *= p_scalar;
	result["x2"] *= p_scalar;
	result["y2"] *= p_scalar;
	result["z2"] *= p_scalar;
	result["w2"] *= p_scalar;
	result["x3"] *= p_scalar;
	result["y3"] *= p_scalar;
	result["z3"] *= p_scalar;
	result["w3"] *= p_scalar;
	return result;
}

FMat4 lm::operator/(float p_scalar, const FMat4& p_matrix)
{
	FMat4 result = p_matrix;
	result["x0"] /= p_scalar;
	result["y0"] /= p_scalar;
	result["z0"] /= p_scalar;
	result["w0"] /= p_scalar;
	result["x1"] /= p_scalar;
	result["y1"] /= p_scalar;
	result["z1"] /= p_scalar;
	result["w1"] /= p_scalar;
	result["x2"] /= p_scalar;
	result["y2"] /= p_scalar;
	result["z2"] /= p_scalar;
	result["w2"] /= p_scalar;
	result["x3"] /= p_scalar;
	result["y3"] /= p_scalar;
	result["z3"] /= p_scalar;
	result["w3"] /= p_scalar;
	return result;
}