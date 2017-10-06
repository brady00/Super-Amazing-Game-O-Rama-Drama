#include "Float4.h"



namespace MEMath
{
	float Float4::Dot(Float4 _Float4)
	{
		return (x * _Float4.x + y * _Float4.y + z *_Float4.z + w * _Float4.w);
	}
	Float4 Float4::Subtract(Float4 _Float4)
	{
		return Float4(x - _Float4.x, y - _Float4.y, z - _Float4.z, w - _Float4.w);
	}
	Float4 Float4::Subtract(float _Float)
	{
		return Float4(x - _Float, y - _Float, z - _Float, w - _Float);
	}
	Float4 Float4::Add(Float4 _Float4)
	{
		return Float4(x + _Float4.x, y + _Float4.y, z + _Float4.z, w + _Float4.w);
	}
	Float4 Float4::Add(float _Float)
	{
		return Float4(x + _Float, y + _Float, z + _Float, w + _Float);
	}
	Float4 Float4::Divide(Float4 _Float4)
	{
		return Float4(x / _Float4.x, y / _Float4.y, z / _Float4.z, w / _Float4.w);
	}
	Float4 Float4::Divide(float _Float)
	{
		return Float4(x / _Float, y / _Float, z / _Float, w / _Float);
	}
	Float4 Float4::Multiply(Float4 _Float4)
	{
		return Float4(x * _Float4.x, y * _Float4.y, z * _Float4.z, w * _Float4.w);
	}
	Float4 Float4::Multiply(float _Float)
	{
		return Float4(x * _Float, y * _Float, z * _Float, w * _Float);
	}
	Float4 Float4::Power(Float4 _Float4)
	{
		return Float4(powf(x, _Float4.x), powf(y, _Float4.y), powf(z, _Float4.z), powf(w, _Float4.w));
	}
	Float4 Float4::Power(float _Float)
	{
		return Float4(powf(x, _Float), powf(y, _Float), powf(z, _Float), powf(w, _Float));
	}
	Float4 Float4::Reciprocal()
	{
		return Float4(1.0f / x, 1.0f / y, 1.0f / z, 1.0f / w);
	}
	Float4 Float4::Abs()
	{
		return Float4(fabsf(x), fabsf(y), fabsf(z), fabsf(w));
	}
	Float4 Float4::Ceiling()
	{
		return Float4(ceilf(x), ceilf(y), ceilf(z), ceilf(w));
	}
	Float4 Float4::Floor()
	{
		return Float4(floorf(x), floorf(y), floorf(z), floorf(w));
	}
	Float4 Float4::Max(Float4 _Float4)
	{
		return Float4(fmaxf(x, _Float4.x), fmaxf(y, _Float4.y), fmaxf(z, _Float4.z), fmaxf(w, _Float4.w));
	}
	Float4 Float4::Min(Float4 _Float4)
	{
		return Float4(fminf(x, _Float4.x), fminf(y, _Float4.y), fminf(z, _Float4.z), fminf(w, _Float4.w));
	}
	Float4 Float4::Clamp(float _Min, float _Max)
	{
		return Float4(fminf(fmaxf(x, _Min), _Max), fminf(fmaxf(y, _Min), _Max), fminf(fmaxf(z, _Min), _Max), fminf(fmaxf(w, _Min), _Max));
	}
	Float4 Float4::IsInfinite()
	{
		return Float4((x == +INFINITY || x == -INFINITY) ? (float)0xFFFFFFFF : 0.0f, (y == +INFINITY || y == -INFINITY) ? (float)0xFFFFFFFF : 0.0f, (z == +INFINITY || z == -INFINITY) ? (float)0xFFFFFFFF : 0.0f, (w == +INFINITY || w == -INFINITY) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::IsNaN()
	{
		return Float4(_isnan(x) ? (float)0xFFFFFFFF : 0.0f, _isnan(y) ? (float)0xFFFFFFFF : 0.0f, _isnan(z) ? (float)0xFFFFFFFF : 0.0f, _isnan(w) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::Mod(Float4 _Float4)
	{
		return Float4(fmodf(x, _Float4.x), fmodf(y, _Float4.y), fmodf(z, _Float4.z), fmodf(w, _Float4.w));
	}
	Float4 Float4::Round()
	{
		return Float4(roundf(x), roundf(y), roundf(z), roundf(w));
	}
	Float4 Float4::Saturate()
	{
		return Clamp(0.0f, 1.0f);
	}
	Float4 Float4::Scale(float _Scalar)
	{
		return Multiply(_Scalar);
	}
	Float4 Float4::Sqrt()
	{
		return Float4(sqrtf(x), sqrtf(y), sqrtf(z), sqrtf(w));
	}
	Float4 Float4::Truncate()
	{
		return Float4(truncf(x), truncf(y), truncf(z), truncf(w));
	}
	Float4 Float4::Equal(Float4 _Float4)
	{
		return Float4((x == _Float4.x) ? (float)0xFFFFFFFF : 0.0f, (y == _Float4.y) ? (float)0xFFFFFFFF : 0.0f, (z == _Float4.z) ? (float)0xFFFFFFFF : 0.0f, (w == _Float4.w) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::NotEqual(Float4 _Float4)
	{
		return Float4((x != _Float4.x) ? (float)0xFFFFFFFF : 0.0f, (y != _Float4.y) ? (float)0xFFFFFFFF : 0.0f, (z != _Float4.z) ? (float)0xFFFFFFFF : 0.0f, (w != _Float4.w) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::GreaterThan(Float4 _Float4)
	{
		return Float4((x > _Float4.x) ? (float)0xFFFFFFFF : 0.0f, (y > _Float4.y) ? (float)0xFFFFFFFF : 0.0f, (z > _Float4.z) ? (float)0xFFFFFFFF : 0.0f, (w > _Float4.w) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::GreaterOrEqual(Float4 _Float4)
	{
		return Float4((x >= _Float4.x) ? (float)0xFFFFFFFF : 0.0f, (y >= _Float4.y) ? (float)0xFFFFFFFF : 0.0f, (z >= _Float4.z) ? (float)0xFFFFFFFF : 0.0f, (w >= _Float4.w) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::LessThan(Float4 _Float4)
	{
		return Float4((x < _Float4.x) ? (float)0xFFFFFFFF : 0.0f, (y < _Float4.y) ? (float)0xFFFFFFFF : 0.0f, (z < _Float4.z) ? (float)0xFFFFFFFF : 0.0f, (w < _Float4.w) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::LessOrEqual(Float4 _Float4)
	{
		return Float4((x <= _Float4.x) ? (float)0xFFFFFFFF : 0.0f, (y <= _Float4.y) ? (float)0xFFFFFFFF : 0.0f, (z <= _Float4.z) ? (float)0xFFFFFFFF : 0.0f, (w <= _Float4.w) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::NearEqual(Float4 _Float4, float _Threshold)
	{
		return Float4((fabsf(x - _Float4.x) <= _Threshold) ? (float)0xFFFFFFFF : 0.0f, (fabsf(y - _Float4.y) <= _Threshold) ? (float)0xFFFFFFFF : 0.0f, (fabsf(z - _Float4.z) <= _Threshold) ? (float)0xFFFFFFFF : 0.0f, (fabsf(w - _Float4.w) <= _Threshold) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::InBounds(float _Min, float _Max)
	{
		return Float4((x >= _Max && x <= _Min) ? (float)0xFFFFFFFF : 0.0f, (y >= _Max && y <= _Min) ? (float)0xFFFFFFFF : 0.0f, (z >= _Max && z <= _Min) ? (float)0xFFFFFFFF : 0.0f, (w >= _Max && w <= _Min) ? (float)0xFFFFFFFF : 0.0f);
	}
	Float4 Float4::Lerp(Float4 _Float4, float _Ratio)
	{
		return Float4(x + (x - _Float4.x) * _Ratio, y + (y - _Float4.y) * _Ratio, z + (z - _Float4.z) * _Ratio, w + (w - _Float4.w) * _Ratio);
	}
	Float4 Float4::Cos()
	{
		return Float4(cosf(x), cosf(y), cosf(z), cosf(w));
	}
	Float4 Float4::ACos()
	{
		return Float4(acosf(x), acosf(y), acosf(z), acosf(w));
	}
	Float4 Float4::Sin()
	{
		return Float4(sinf(x), sinf(y), sinf(z), sinf(w));
	}
	Float4 Float4::ASin()
	{
		return Float4(asinf(x), asinf(y), asinf(z), asinf(w));
	}
	Float4 Float4::Tan()
	{
		return Float4(tanf(x), tanf(y), tanf(z), tanf(w));
	}
	Float4 Float4::ATan()
	{
		return Float4(atanf(x), atanf(y), atanf(z), atanf(w));
	}
	float Float4::Length()
	{
		Float4 temp = Multiply(*this);
		return sqrtf(temp.x + temp.y + temp.z + temp.w);
	}
	float Float4::LengthSqr()
	{
		Float4 temp = Multiply(*this);
		return (temp.x + temp.y + temp.z + temp.w);
	}
	bool Float4::LengthEqual(Float4 _Float4)
	{
		return LengthSqr() == _Float4.LengthSqr();
	}
	bool Float4::LengthNotEqual(Float4 _Float4)
	{
		return LengthSqr() != _Float4.LengthSqr();
	}
	bool Float4::LengthGreaterThan(Float4 _Float4)
	{
		return LengthSqr() > _Float4.LengthSqr();
	}
	bool Float4::LengthGreaterOrEqual(Float4 _Float4)
	{
		return LengthSqr() >= _Float4.LengthSqr();
	}
	bool Float4::LengthLessThan(Float4 _Float4)
	{
		return LengthSqr() < _Float4.LengthSqr();
	}
	bool Float4::LengthLessOrEqual(Float4 _Float4)
	{
		return LengthSqr() <= _Float4.LengthSqr();
	}
	bool Float4::LenghtNearEqaul(Float4 _Float4, float _Threshold)
	{
		return (fabsf(LengthSqr() - _Float4.LengthSqr()) <= _Threshold);
	}
	void Float4::Normailze()
	{
		float lengthsqr = LengthSqr();
		Float4 mult = Multiply(*this);
		*this = mult.Divide(lengthsqr);
	}
	Float4 Float4::Normalized()
	{
		float lengthsqr = LengthSqr();
		Float4 mult = Multiply(*this);
		return mult.Divide(lengthsqr);
	}
}