#pragma once
#include "Float4X4.h"
#include <DirectXMath.h>
#include "Quaternian.h"

namespace MEMath
{
	class Float4
	{
	public:
		union
		{
			float m[4];
			float x, y, z, w;
			float r, g, b, a;
		};
		inline Float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};
		inline Float4(float* _m) : x(_m[0]), y(_m[1]), z(_m[2]), w(m[3]) {};
		inline Float4(DirectX::XMFLOAT4 _Float4) : x(_Float4.x), y(_Float4.y), z(_Float4.z), w(_Float4.w) {};
		inline Float4(DirectX::XMVECTOR _Vector3) { DirectX::XMFLOAT4 temp; DirectX::XMStoreFloat4(&temp, _Vector3); x = temp.x; y = temp.y; z = temp.z; w = temp.w; }
		inline Float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
		inline ~Float4() {};
		//////////////////////
		//OPERATOR OVERLOADS//
		//////////////////////
		inline operator DirectX::XMFLOAT4() const { return DirectX::XMFLOAT4(x, y, z, w); }
		inline operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat4(&DirectX::XMFLOAT4(x, y, z, w)); }
		inline void operator=(DirectX::XMFLOAT4 _Float4) { *this = Float4(_Float4); }
		inline void operator=(DirectX::XMVECTOR _Float4) { *this = Float4(_Float4); }
		inline void operator=(Float4 _Float4) { x = _Float4.x; y = _Float4.y; z = _Float4.z; w = _Float4.w; }
		inline Float4 operator+(Float4 _Float4) { return Add(_Float4); }
		inline Float4 operator+=(Float4 _Float4) { *this = Add(_Float4); return *this; }
		inline Float4 operator+(float _Float) { return Add(_Float); }
		inline Float4 operator+=(float _Float) { *this = Add(_Float); return *this; }
		inline Float4 operator-(Float4 _Float4) { return Subtract(_Float4); }
		inline Float4 operator-=(Float4 _Float4) { *this = Subtract(_Float4); return *this; }
		inline Float4 operator-(float _Float) { return Subtract(_Float); }
		inline Float4 operator-=(float _Float) { *this = Subtract(_Float); return *this; }
		inline Float4 operator*(Float4 _Float4) { return Multiply(_Float4); }
		inline Float4 operator*=(Float4 _Float4) { *this = Multiply(_Float4); return *this; }
		inline Float4 operator*(float _Float) { return Multiply(_Float); }
		inline Float4 operator*=(float _Float) { *this = Multiply(_Float); return *this; }
		inline Float4 operator/(Float4 _Float4) { return Divide(_Float4); }
		inline Float4 operator/=(Float4 _Float4) { *this = Divide(_Float4); return *this; }
		inline Float4 operator/(float _Float) { return Divide(_Float); }
		inline Float4 operator/=(float _Float) { *this = Divide(_Float); return *this; }
		//LengthOperator
		inline bool operator>(Float4 _Float4) { return LengthGreaterThan(_Float4); }
		inline bool operator>=(Float4 _Float4) { return LengthGreaterOrEqual(_Float4); }
		inline bool operator<(Float4 _Float4) { return LengthLessThan(_Float4); }
		inline bool operator<=(Float4 _Float4) { return LengthLessOrEqual(_Float4); }
		//Dot Product
		float Dot(Float4 _Float4);
		//Subtract
		Float4 Subtract(Float4 _Float4);
		Float4 Subtract(float _Float);
		//Add
		Float4 Add(Float4 _Float4);
		Float4 Add(float _Float);
		//Divide
		Float4 Divide(Float4 _Float4);
		Float4 Divide(float _Float);
		//Multiply
		Float4 Multiply(Float4 _Float4);
		Float4 Multiply(float _Float);
		//Power
		Float4 Power(Float4 _Float4);
		Float4 Power(float _Float);
		//Reciprocal
		Float4 Reciprocal();
		//AbsoluteValue
		Float4 Abs();
		//Ceiling
		Float4 Ceiling();
		//Floor
		Float4 Floor();
		//Max
		Float4 Max(Float4 _Float4);
		//Min 
		Float4 Min(Float4 _Float4);
		//Clamp
		Float4 Clamp(float _Min, float _Max);
		//Is Infinite
		Float4 IsInfinite();
		//Is NaN
		Float4 IsNaN();
		//Mod
		Float4 Mod(Float4 _Float4);
		//Round
		Float4 Round();
		//Saturate
		Float4 Saturate();
		//Scale
		Float4 Scale(float _Scalar);
		//Square Root
		Float4 Sqrt();
		//Truncate
		Float4 Truncate();
		//Equal
		Float4 Equal(Float4 _Float4);
		//Not Equal
		Float4 NotEqual(Float4 _Float4);
		//Greater Than
		Float4 GreaterThan(Float4 _Float4);
		//Greater Than Or Equal Too
		Float4 GreaterOrEqual(Float4 _Float4);
		//Less Than
		Float4 LessThan(Float4 _Float4);
		//Less Than Or Equal Too
		Float4 LessOrEqual(Float4 _Float4);
		//Near Equal
		Float4 NearEqual(Float4 _Float4, float _Threshold);
		//In Bounds
		Float4 InBounds(float _Min, float _Max);
		//Lerp
		Float4 Lerp(Float4 _Float4, float _Ratio);
		//Cosine
		Float4 Cos();
		//Arccosine
		Float4 ACos();
		//Sine
		Float4 Sin();
		//Archsine
		Float4 ASin();
		//Tangent
		Float4 Tan();
		//Arctangent
		Float4 ATan();
		//Length
		float Length();
		float LengthSqr();
		bool LengthEqual(Float4 _Float4);
		bool LengthNotEqual(Float4 _Float4);
		bool LengthGreaterThan(Float4 _Float4);
		bool LengthGreaterOrEqual(Float4 _Float4);
		bool LengthLessThan(Float4 _Float4);
		bool LengthLessOrEqual(Float4 _Float4);
		bool LenghtNearEqaul(Float4 _Float4, float _Threshold);
		//Normailze
		void Normailze();
		//Normalized
		Float4 Normalized();
		////////////////////
		//STATIC FUNCTIONS//
		////////////////////
		//Zero Vector
		inline static Float4 Zero() { return Float4(0, 0, 0, 0); }
		//One Vector
		inline static Float4 One() { return Float4(1, 1, 1, 1); }
		//False Vector
		inline static Float4 False() { return Float4(0, 0, 0, 0); }
		//True Vector
		inline static Float4 True() { return Float4((float)0xFFFFFFFF, (float)0xFFFFFFFF, (float)0xFFFFFFFF, (float)0xFFFFFFFF); }
		//Epsilon Vector
		inline static Float4 Epsilon() { return Float4(FLT_EPSILON, FLT_EPSILON, FLT_EPSILON, FLT_EPSILON); }
		//Infinity Vector
		inline static Float4 Infinity() { return Float4(INFINITY, INFINITY, INFINITY, INFINITY); }
		//NaN Vector
		inline static Float4 NaN() { return Float4(NAN, NAN, NAN, NAN); }
	};
}

