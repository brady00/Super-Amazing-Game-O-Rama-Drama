#pragma once
#include <DirectXMath.h>

namespace MEMath
{
	class Float3
	{
	public:
		union
		{
			float m[3];
			float x, y, z;
			float r, g, b;
		};
		inline Float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
		inline Float3(float* _m) : x(_m[0]), y(_m[1]), z(_m[2]) {};
		inline Float3(DirectX::XMFLOAT3 _Float3) : x(_Float3.x), y(_Float3.y), z(_Float3.z) {};
		inline Float3(DirectX::XMVECTOR _Vector3) { DirectX::XMFLOAT3 temp; DirectX::XMStoreFloat3(&temp, _Vector3); x = temp.x; y = temp.y; z = temp.z; }
		inline Float3() : x(0.0f), y(0.0f), z(0.0f) {};
		inline ~Float3() {};
		//////////////////////
		//OPERATOR OVERLOADS//
		//////////////////////
		inline operator DirectX::XMFLOAT3() const { return DirectX::XMFLOAT3(x,y,z); }
		inline operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(x,y,z)); }
		inline void operator=(DirectX::XMFLOAT3 _Float3) { *this = Float3(_Float3); }
		inline void operator=(DirectX::XMVECTOR _Float3) { *this = Float3(_Float3); }
		inline void operator=(Float3 _Float3) { x = _Float3.x; y = _Float3.y; z = _Float3.z; }
		inline Float3 operator+(Float3 _Float3) { return Add(_Float3); }
		inline Float3 operator+=(Float3 _Float3) { *this = Add(_Float3); return *this; }
		inline Float3 operator+(float _Float) { return Add(_Float); }
		inline Float3 operator+=(float _Float) { *this = Add(_Float); return *this; }
		inline Float3 operator-(Float3 _Float3) { return Subtract(_Float3); }
		inline Float3 operator-=(Float3 _Float3) { *this = Subtract(_Float3); return *this; }
		inline Float3 operator-(float _Float) { return Subtract(_Float); }
		inline Float3 operator-=(float _Float) { *this = Subtract(_Float); return *this; }
		inline Float3 operator*(Float3 _Float3) { return Multiply(_Float3); }
		inline Float3 operator*=(Float3 _Float3) { *this = Multiply(_Float3); return *this; }
		inline Float3 operator*(float _Float) { return Multiply(_Float); }
		inline Float3 operator*=(float _Float) { *this = Multiply(_Float); return *this; }
		inline Float3 operator/(Float3 _Float3) { return Divide(_Float3); }
		inline Float3 operator/=(Float3 _Float3) { *this = Divide(_Float3); return *this; }
		inline Float3 operator/(float _Float) { return Divide(_Float); }
		inline Float3 operator/=(float _Float) { *this = Divide(_Float); return *this; }
		//LengthOperator
		inline bool operator>(Float3 _Float3) { return LengthGreaterThan(_Float3); }
		inline bool operator>=(Float3 _Float3) { return LengthGreaterOrEqual(_Float3); }
		inline bool operator<(Float3 _Float3) { return LengthLessThan(_Float3); }
		inline bool operator<=(Float3 _Float3) { return LengthLessOrEqual(_Float3); }
		//Cross Product
		Float3 Cross(Float3 _Float3);
		//Dot Product
		float Dot(Float3 _Float3);
		//Subtract
		Float3 Subtract(Float3 _Float3);
		Float3 Subtract(float _Float);
		//Add
		Float3 Add(Float3 _Float3);
		Float3 Add(float _Float);
		//Divide
		Float3 Divide(Float3 _Float3);
		Float3 Divide(float _Float);
		//Multiply
		Float3 Multiply(Float3 _Float3);
		Float3 Multiply(float _Float);
		//Power
		Float3 Power(Float3 _Float3);
		Float3 Power(float _Float);
		//Reciprocal
		Float3 Reciprocal();
		//AbsoluteValue
		Float3 Abs();
		//Ceiling
		Float3 Ceiling();
		//Floor
		Float3 Floor();
		//Max
		Float3 Max(Float3 _Float3);
		//Min 
		Float3 Min(Float3 _Float3);
		//Clamp
		Float3 Clamp(float _Min, float _Max);
		//Is Infinite
		Float3 IsInfinite();
		//Is NaN
		Float3 IsNaN();
		//Mod
		Float3 Mod(Float3 _Float3);
		//Round
		Float3 Round();
		//Saturate
		Float3 Saturate();
		//Scale
		Float3 Scale(float _Scalar);
		//Square Root
		Float3 Sqrt();
		//Truncate
		Float3 Truncate();
		//Equal
		Float3 Equal(Float3 _Float3);
		//Not Equal
		Float3 NotEqual(Float3 _Float3);
		//Greater Than
		Float3 GreaterThan(Float3 _Float3);
		//Greater Than Or Equal Too
		Float3 GreaterOrEqual(Float3 _Float3);
		//Less Than
		Float3 LessThan(Float3 _Float3);
		//Less Than Or Equal Too
		Float3 LessOrEqual(Float3 _Float3);
		//Near Equal
		Float3 NearEqual(Float3 _Float3, float _Threshold);
		//In Bounds
		Float3 InBounds(float _Min, float _Max);
		//Lerp
		Float3 Lerp(Float3 _Float3, float _Ratio);
		//Cosine
		Float3 Cos();
		//Arccosine
		Float3 ACos();
		//Sine
		Float3 Sin();
		//Archsine
		Float3 ASin();
		//Tangent
		Float3 Tan();
		//Arctangent
		Float3 ATan();
		//Length
		float Length();
		float LengthSqr();
		bool LengthEqual(Float3 _Float3);
		bool LengthNotEqual(Float3 _Float3);
		bool LengthGreaterThan(Float3 _Float3);
		bool LengthGreaterOrEqual(Float3 _Float3);
		bool LengthLessThan(Float3 _Float3);
		bool LengthLessOrEqual(Float3 _Float3);
		bool LenghtNearEqaul(Float3 _Float3, float _Threshold);
		//Normailze
		void Normailze();
		//Normalized
		Float3 Normalized();
		//Angle Between
		float AngleBetween(Float3 _Float3);
		//Reflect
		Float3 Reflect(/*Plane _Plane*/);

		//Zero Vector
		inline static Float3 Zero() { return Float3(0, 0, 0); }
		//One Vector
		inline static Float3 One() { return Float3(1, 1, 1); }
		//False Vector
		inline static Float3 False() { return Float3(0, 0, 0); }
		//True Vector
		inline static Float3 True() { return Float3((float)0xFFFFFFFF, (float)0xFFFFFFFF, (float)0xFFFFFFFF); }
		//Epsilon Vector
		inline static Float3 Epsilon() { return Float3(FLT_EPSILON, FLT_EPSILON, FLT_EPSILON); }
		//Infinity Vector
		inline static Float3 Infinity() { return Float3(INFINITY, INFINITY, INFINITY); }
		//NaN Vector
		inline static Float3 NaN() { return Float3(NAN, NAN, NAN); }
	};

}
;