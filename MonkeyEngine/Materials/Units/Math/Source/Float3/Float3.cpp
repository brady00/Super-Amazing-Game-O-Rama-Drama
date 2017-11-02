#include "Float3.h"

namespace MonkeyEngine
{
	namespace MEMath
	{
		const Float3 Float3::Back = Float3(0.0f, 0.0f, -1.0f);
		const Float3 Float3::Down = Float3(0.0f, -1.0f, 0.0f);
		const Float3 Float3::Forward = Float3(0.0f, 0.0f, 1.0f);
		const Float3 Float3::Left = Float3(-1.0f, 0.0f, 0.0f);
		const Float3 Float3::NegativeInfinity = Float3(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
		const Float3 Float3::One = Float3(1.0f, 1.0f, 1.0f);
		const Float3 Float3::PositiveInfinity = Float3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
		const Float3 Float3::Right = Float3(1.0f, 0.0f, 0.0f);
		const Float3 Float3::Up = Float3(0.0f, 1.0f, 0.0f);
		const Float3 Float3::Zero = Float3(0.0f, 0.0f, 0.0f);

		Float3::Float3()
		{
			x = y = z = 0; 
		}

		Float3::Float3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Float3::Float3(float* xyz)
		{
			x = xyz[0];
			y = xyz[1];
			z = xyz[2];
		}

		Float3::~Float3()
		{

		}

		float Float3::Magnitude()
		{
			return XMVector3Length(XMLoadFloat3(&XMFLOAT3(x, y, z))).m128_f32[0];
		}

		Float3 Float3::Normalized()
		{
			XMVECTOR temp = XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(x, y, z)));
			XMFLOAT3 temp2;
			XMStoreFloat3(&temp2, temp);
			return Float3(temp2.x, temp2.y, temp2.z);
		}

		float Float3::SqrMagnitude()
		{
			return XMVector3LengthSq(XMLoadFloat3(&XMFLOAT3(x, y, z))).m128_f32[0];
		}

		float Float3::Angle(Float3 from, Float3 to)
		{
			return XMConvertToDegrees(XMVector3AngleBetweenVectors(XMLoadFloat3(&XMFLOAT3(from.x, from.y, from.z)), XMLoadFloat3(&XMFLOAT3(to.x, to.y, to.z))).m128_f32[0]);
		}

		Float3 Float3::ClampMagnitude(Float3 from, float maxLength)
		{
			if (from.Magnitude() >= maxLength)
				return from;
			return from.Normalized() * maxLength;
		}

		Float3 Float3::Cross(Float3 left, Float3 right)
		{
			XMVECTOR temp = XMVector3Cross(XMLoadFloat3(&XMFLOAT3(left.x, left.y, left.z)), XMLoadFloat3(&XMFLOAT3(right.x, right.y, right.z)));
			XMFLOAT3 temp2;
			XMStoreFloat3(&temp2, temp);
			return Float3(temp2.x, temp2.y, temp2.z);
		}

		float Float3::Distance(Float3 pointA, Float3 pointB)
		{
			return (pointA - pointB).Magnitude();
		}

		float Float3::Dot(Float3 left, Float3 right)
		{
			return XMVector3Dot(XMLoadFloat3(&XMFLOAT3(left.x, left.y, left.z)), XMLoadFloat3(&XMFLOAT3(right.x, right.y, right.z))).m128_f32[0];
		}

		Float3 Float3::Lerp(Float3 left, Float3 right, float ratio)
		{
			XMVECTOR temp = XMVectorLerp(XMLoadFloat3(&XMFLOAT3(left.x, left.y, left.z)), XMLoadFloat3(&XMFLOAT3(right.x, right.y, right.z)), ratio);
			XMFLOAT3 temp2;
			XMStoreFloat3(&temp2, temp);
			temp2.x < 0.0f ? temp2.x = 0.0f : (temp2.x > 1.0f ? temp2.x = 1.0f : temp2.x);
			temp2.y < 0.0f ? temp2.y = 0.0f : (temp2.y > 1.0f ? temp2.y = 1.0f : temp2.y);
			temp2.z < 0.0f ? temp2.z = 0.0f : (temp2.z > 1.0f ? temp2.z = 1.0f : temp2.z);
			return Float3(temp2.x, temp2.y, temp2.z);
		}

		Float3 Float3::LerpUnclamped(Float3 left, Float3 right, float ratio)
		{
			XMVECTOR temp = XMVectorLerp(XMLoadFloat3(&XMFLOAT3(left.x, left.y, left.z)), XMLoadFloat3(&XMFLOAT3(right.x, right.y, right.z)), ratio);
			XMFLOAT3 temp2;
			XMStoreFloat3(&temp2, temp);
			return Float3(temp2.x, temp2.y, temp2.z);
		}

		Float3 Float3::Max(Float3 left, Float3 right)
		{
			return Float3(std::max(left.x, right.x), std::max(left.y, right.y), std::max(left.z, right.z));
		}

		Float3 Float3::Min(Float3 left, Float3 right)
		{
			return Float3(std::min(left.x, right.x), std::min(left.y, right.y), std::min(left.z, right.z));
		}

		Float3 Float3::MoveTowards(Float3 current, Float3 Target, float MaxDistanceDelta)
		{
			Float3 temp = Target - current;
			temp = Float3::ClampMagnitude(temp, MaxDistanceDelta);
			return current + temp;
		}

		Float3 Float3::Normalize(Float3& vec)
		{
			return (vec = vec.Normalized());
		}

		void Float3::OrthoNormalize(Float3& normal, Float3& tangent)
		{
			normal = normal.Normalized();
			Float3 proj;
			proj = normal * Dot(tangent, normal);
			tangent -= proj;
			tangent = tangent.Normalized();
		}

		void Float3::OrthoNormalize(Float3& normal, Float3& tangent, Float3& binormal)
		{
			OrthoNormalize(normal, tangent);
			binormal = Cross(normal, tangent);
			binormal = binormal.Normalized();
		}

		Float3 Float3::Project(Float3 vec, Float3 onNormal)
		{
			float temp = Dot(vec, onNormal);
			float sqr = vec.SqrMagnitude();
			temp = temp / sqr;
			return vec * temp;
		}

		Float3 Float3::ProjectOnPlane(Float3 vec, Float3 planeNormal)
		{
			return vec - Project(vec, planeNormal);
		}

		Float3 Float3::Reflect(Float3 vec, Float3 planeNormal)
		{
			return vec - (planeNormal * 2 * (Dot(vec, planeNormal)));
		}

		Float3 Float3::RotateTowards(Float3 current, Float3 target, float maxRadiansDelta)
		{
			float angle = XMConvertToRadians(Angle(current, target));
			if (angle > maxRadiansDelta)
				angle = maxRadiansDelta;
			XMMATRIX mat = XMMatrixRotationAxis(XMVector3Cross(XMLoadFloat3(&XMFLOAT3(current.x, current.y, current.z)), XMLoadFloat3(&XMFLOAT3(target.x, target.y, target.z))), angle);
			XMVECTOR temp = XMLoadFloat3(&XMFLOAT3(current.x, current.y, current.z));
			temp = XMVector3Transform(temp, mat);
			XMFLOAT3 vec;
			XMStoreFloat3(&vec, temp);
			return Float3(vec.x, vec.y, vec.z);
		}

		Float3 Float3::Scale(Float3 vec, Float3 scalar)
		{
			return Float3(vec.x * scalar.x, vec.y * scalar.y, vec.z * scalar.z);
		}

		float& Float3::operator[](int index)
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				break;
			}
		}

		Float3 Float3::operator -(Float3 right)
		{
			return Float3(x - right.x, y - right.y, z - right.z);
		}

		Float3& Float3::operator -=(Float3 right)
		{

			return (*this = *this - right);
		}

		bool Float3::operator !=(Float3 right)
		{
			return (x != right.x || y != right.y || z != right.z);
		}

		Float3 Float3::operator *(float right)
		{
			return Float3(x - right, y - right, z - right);
		}

		Float3& Float3::operator *=(float right)
		{
			return (*this = *this * right);
		}

		Float3 Float3::operator /(float right)
		{
			return Float3(x / right, y / right, z / right);
		}

		Float3& Float3::operator /=(float right)
		{
			return (*this = *this / right);
		}

		Float3 Float3::operator +(Float3 right)
		{
			return Float3(x + right.x, y + right.y, z + right.z);
		}

		Float3& Float3::operator +=(Float3 right)
		{
			return (*this = *this + right);
		}

		bool Float3::operator ==(Float3 right)
		{
			return (x == right.x && y == right.y && z == right.z);
		}
	}
}