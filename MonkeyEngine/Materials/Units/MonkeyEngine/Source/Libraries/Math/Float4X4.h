#pragma once

class Float3;
class Quaternian;
class Float4X4
{
private:

public:
	Float4X4();
	~Float4X4();
	//Builds an affine transformation matrix.
	Float4X4 AffineTransformation();
	//Builds a 2D affine transformation matrix in the xy plane.
	Float4X4 AffineTransformation2D();
	//Computes the determinant of a matrix.
	Float3 Determinant();
	//Computes the inverse of a matrix.
	Float4X4 Inverse();
	//Tests whether a matrix is the identity matrix.
	bool IsIdentity();
	//Tests whether any of the elements of a matrix are positive or negative infinity.
	bool IsInfinite();
	//Tests whether any of the elements of a matrix are NaN.
	bool IsNaN();
	//Computes the product of two matrices.
	Float4X4 Multiply(Float4X4 _Mat);
	//Computes the transpose of the product of two matrices.
	Float4X4 MultiplyTranspose(Float4X4 _Mat);
	//Builds a left - handed perspective projection matrix based on a field of view.
	Float4X4 PerspectiveFovLH(float _FOVAngle, float _AspectRatio, float _NearZ, float _FarZ);
	//Builds a right - handed perspective projection matrix based on a field of view.
	Float4X4 PerspectiveFovRH(float _FOVAngle, float _AspectRatio, float _NearZ, float _FarZ);
	//Builds a rotation matrix based on a given pitch, yaw, and roll(Euler angles).
	Float4X4 RotationRollPitchYaw(float _Roll, float _Pitch, float _Yaw);
	//Builds a matrix that rotates around the x - axis.
	Float4X4 RotationX(float _Angle);
	//Builds a matrix that rotates around the y - axis.
	Float4X4 RotationY(float _Angle);
	//Builds a matrix that rotates around the z - axis.
	Float4X4 RotationZ(float _Angle);
	//Builds a matrix that scales along the x - axis, y - axis, and z - axis.
	Float4X4 Scaling(float _X, float _Y, float _Z);
	//Builds a translation matrix from the specified offsets.
	Float4X4 Translation(float _XOffset, float _YOffset, float _ZOffset);
	//Computes the transpose of a matrix.
	Float4X4 Transpose();
	//Builds the identity matrix.
	Float4X4 Identity();
};

