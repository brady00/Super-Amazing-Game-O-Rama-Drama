#include "Float3.h"

namespace MEMath
{
	Float3 Float3::Cross(Float3 _Float3)
	{
		return Float3(y * _Float3.z - z * _Float3.y, z * _Float3.x - x * _Float3.z, x * _Float3.y - y *_Float3.x);
	}
	float Float3::Dot(Float3 _Float3)
	{
		return (x * _Float3.x + y * _Float3.y + z * _Float3.z);
	}
	Float3 Float3::Subtract(Float3 _Float3)
	{
		return Float3(x - _Float3.x, y - _Float3.y, z - _Float3.z);
	}
	Float3 Float3::Subtract(float _Float)
	{
		return Float3(x - _Float, y - _Float, z - _Float);
	}
	Float3 Float3::Add(Float3 _Float3)
	{
		return Float3(x + _Float3.x, y + _Float3.y, z + _Float3.z);
	}
	Float3 Float3::Add(float _Float)
	{
		return Float3(x + _Float, y + _Float, z + _Float);
	}
	Float3 Float3::Divide(Float3 _Float3)
	{
		return Float3(x / _Float3.x, y / _Float3.y, z / _Float3.z);
	}
	Float3 Float3::Divide(float _Float)
	{
		return Float3(x / _Float, y / _Float, z / _Float);
	}
	Float3 Float3::Multiply(Float3 _Float3)
	{
		return Float3(x * _Float3.x, y * _Float3.y, z * _Float3.z);
	}
	Float3 Float3::Multiply(float _Float)
	{
		return Float3(x * _Float, y * _Float, z * _Float);
	}
	Float3 Float3::Power(Float3 _Float3)
	{
		return Float3(powf(x, _Float3.x), powf(y, _Float3.y), powf(z, _Float3.z));
	}
	Float3 Float3::Power(float _Float)
	{
		return Float3(powf(x, _Float), powf(y, _Float), powf(z, _Float));
	}
	Float3 Float3::Reciprocal()
	{
		return Float3(1.0f / x, 1.0f / y, 1.0f / z);
	}
	Float3 Float3::Abs()
	{
		return Float3(fabsf(x), fabsf(y), fabsf(z));
	}
	Float3 Float3::Ceiling()
	{
		return Float3(ceilf(x), ceilf(y), ceilf(z));
	}
	Float3 Float3::Floor()
	{
		return Float3(floorf(x), floorf(y), floorf(z));
	}
	Float3 Float3::Max(Float3 _Float3)
	{
		return Float3(fmaxf(x, _Float3.x), fmaxf(y, _Float3.y), fmaxf(z, _Float3.z));
	}
	Float3 Float3::Min(Float3 _Float3)
	{
		return Float3(fminf(x, _Float3.x), fminf(y, _Float3.y), fminf(z, _Float3.z));
	}
	Float3 Float3::Clamp(float _Min, float _Max)
	{
		return Float3(fminf(fmaxf(x, _Min), _Max), fminf(fmaxf(y, _Min), _Max), fminf(fmaxf(z, _Min), _Max));
	}
	Float3 Float3::IsInfinite()
	{
		return Float3((x == +INFINITY || x == -INFINITY) ? (float)0xFFFFFFFF : 0.0f, (y == +INFINITY || y == -INFINITY) ? (float)0xFFFFFFFF : 0.0f, (z == +INFINITY || z == -INFINITY) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::IsNaN()
	{
		return Float3(_isnan(x) ? (float)0xFFFFFFFF : 0.0f, _isnan(y) ? (float)0xFFFFFFFF : 0.0f, _isnan(z) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::Mod(Float3 _Float3)
	{
		return Float3(fmodf(x, _Float3.x), fmodf(y, _Float3.y), fmodf(z, _Float3.z));
	}
	Float3 Float3::Round()
	{
		return Float3(roundf(x), roundf(y), roundf(z));
	}
	Float3 Float3::Saturate()
	{
		return Clamp(0.0f, 1.0f);
	}
	Float3 Float3::Scale(float _Scalar)
	{
		return 	Multiply(_Scalar);
	}
	Float3 Float3::Sqrt()
	{
		return 	Float3(sqrtf(x), sqrtf(y), sqrtf(z));
	}
	Float3 Float3::Truncate()
	{
		return Float3(truncf(x), truncf(y), truncf(z));
	}
	Float3 Float3::Equal(Float3 _Float3)
	{
		return 	Float3((x == _Float3.x) ? (float)0xFFFFFFFF : 0.0f, (y == _Float3.y) ? (float)0xFFFFFFFF : 0.0f, (z == _Float3.z) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::NotEqual(Float3 _Float3)
	{
		return Float3((x != _Float3.x) ? (float)0xFFFFFFFF : 0.0f, (y != _Float3.y) ? (float)0xFFFFFFFF : 0.0f, (z != _Float3.z) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::GreaterThan(Float3 _Float3)
	{
		return 	Float3((x > _Float3.x) ? (float)0xFFFFFFFF : 0.0f, (y > _Float3.y) ? (float)0xFFFFFFFF : 0.0f, (z > _Float3.z) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::GreaterOrEqual(Float3 _Float3)
	{
		return 	Float3((x >= _Float3.x) ? (float)0xFFFFFFFF : 0.0f, (y >= _Float3.y) ? (float)0xFFFFFFFF : 0.0f, (z >= _Float3.z) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::LessThan(Float3 _Float3)
	{
		return 	Float3((x < _Float3.x) ? (float)0xFFFFFFFF : 0.0f, (y < _Float3.y) ? (float)0xFFFFFFFF : 0.0f, (z < _Float3.z) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::LessOrEqual(Float3 _Float3)
	{
		return Float3((x <= _Float3.x) ? (float)0xFFFFFFFF : 0.0f, (y <= _Float3.y) ? (float)0xFFFFFFFF : 0.0f, (z <= _Float3.z) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::NearEqual(Float3 _Float3, float _Threshold)
	{
		return Float3((fabsf(x - _Float3.x) <= _Threshold) ? (float)0xFFFFFFFF : 0.0f, (fabsf(y - _Float3.y) <= _Threshold) ? (float)0xFFFFFFFF : 0.0f, (fabsf(z - _Float3.z) <= _Threshold) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::InBounds(float _Min, float _Max)
	{
		return 	Float3((x >= _Min && x <= _Max) ? (float)0xFFFFFFFF : 0.0f, (y >= _Min && y <= _Max) ? (float)0xFFFFFFFF : 0.0f, (z >= _Min && z <= _Max) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float3 Float3::Lerp(Float3 _Float3, float _Ratio)
	{
		return 	Float3(x + (_Float3.x - x) * _Ratio, y + (_Float3.y - y) * _Ratio, z + (_Float3.z - z) * _Ratio);
	}
	Float3 Float3::Cos()
	{
		return 	Float3(cosf(x), cosf(y), cosf(z));
	}
	Float3 Float3::ACos()
	{
		return 	Float3(acosf(x), acosf(y), acosf(z));
	}
	Float3 Float3::Sin()
	{
		return 	Float3(sinf(x), sinf(y), sinf(z));
	}
	Float3 Float3::ASin()
	{
		return 	Float3(asinf(x), asinf(y), asinf(z));
	}
	Float3 Float3::Tan()
	{
		return 	Float3(tanf(x), tanf(y), tanf(z));
	}
	Float3 Float3::ATan()
	{
		return 	Float3(atanf(x), atanf(y), atanf(z));
	}
	float Float3::Length()
	{
		Float3 temp = Multiply(*this);
		return sqrtf(temp.x + temp.y + temp.z);
	}
	float Float3::LengthSqr()
	{
		Float3 temp = Multiply(*this);
		return (temp.x + temp.y + temp.z);
	}
	bool Float3::LengthEqual(Float3 _Float3)
	{
		return LengthSqr() == _Float3.LengthSqr();
	}
	bool Float3::LengthNotEqual(Float3 _Float3)
	{
		return LengthSqr() != _Float3.LengthSqr();
	}
	bool Float3::LengthGreaterThan(Float3 _Float3)
	{
		return LengthSqr() > _Float3.LengthSqr();
	}
	bool Float3::LengthGreaterOrEqual(Float3 _Float3)
	{
		return LengthSqr() >= _Float3.LengthSqr();
	}
	bool Float3::LengthLessThan(Float3 _Float3)
	{
		return LengthSqr() < _Float3.LengthSqr();
	}
	bool Float3::LengthLessOrEqual(Float3 _Float3)
	{
		return LengthSqr() <= _Float3.LengthSqr();
	}
	bool Float3::LenghtNearEqaul(Float3 _Float3, float _Threshold)
	{
		return fabsf(LengthSqr() - _Float3.LengthSqr()) <= _Threshold * _Threshold;
	}
	void Float3::Normailze()
	{
		float lengthsqr = LengthSqr();
		Float3 mult = Multiply(*this);
		*this = mult.Divide(lengthsqr);
	}
	Float3 Float3::Normalized()
	{
		float lengthsqr = LengthSqr();
		Float3 mult = Multiply(*this);
		return mult.Divide(lengthsqr);
	}
	float Float3::AngleBetween(Float3 _Float3)//////Not Written
	{
		return 0.0f;
	}
	Float3 Float3::Reflect(/*Plane _Plane*/)//////Not Written
	{
		return Float3();
	}
}
