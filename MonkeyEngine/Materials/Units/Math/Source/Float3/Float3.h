#pragma once
#include "MathDLL.h"
#include <limits>
#include <DirectXMath.h>
#include <algorithm>
using namespace DirectX;
namespace MonkeyEngine
{
	namespace MEMath
	{
		class MATH_EXPORT Float3
		{
		public:
			Float3();
			Float3(float x, float y, float z);
			Float3(float* xyz);
			~Float3();
			float Magnitude();
			Float3 Normalized();
			float SqrMagnitude();

			float& operator [](int index);
			Float3 operator -(Float3 right);
			Float3& operator -=(Float3 right);
			bool operator !=(Float3 right);
			Float3 operator *(float right);
			Float3& operator *=(float right);
			Float3 operator /(float right);
			Float3& operator /=(float right);
			Float3 operator +(Float3 right);
			Float3& operator +=(Float3 right);
			bool operator ==(Float3 right);

			float x, y, z;
			static const Float3 Back;
			static const Float3 Down;
			static const Float3 Forward;
			static const Float3 Left;
			static const Float3 NegativeInfinity;
			static const Float3 One;
			static const Float3 PositiveInfinity;
			static const Float3 Right;
			static const Float3 Up;
			static const Float3 Zero;

			static float Angle(Float3 from, Float3 to);
			static Float3 ClampMagnitude(Float3 from, float maxLength);
			static Float3 Cross(Float3 left, Float3 right);
			static float Distance(Float3 pointA, Float3 pointB);
			static float Dot(Float3 left, Float3 right);
			static Float3 Lerp(Float3 left, Float3 right, float ratio);
			static Float3 LerpUnclamped(Float3 left, Float3 right, float ratio);
			static Float3 Max(Float3 left, Float3 right);
			static Float3 Min(Float3 left, Float3 right);
			static Float3 MoveTowards(Float3 current, Float3 Target, float MaxDistanceDelta);
			static Float3 Normalize(Float3& vec);
			static void OrthoNormalize(Float3& normal, Float3& tangent);
			static void OrthoNormalize(Float3& normal, Float3& tangent, Float3& binormal);
			static Float3 Project(Float3 vec, Float3 onNormal);
			static Float3 ProjectOnPlane(Float3 vec, Float3 planeNormal);
			static Float3 Reflect(Float3 vec, Float3 planeNormal);
			static Float3 RotateTowards(Float3 current, Float3 target, float maxRadiansDelta);
			static Float3 Scale(Float3 vec, Float3 scalar);
		};
	}
}