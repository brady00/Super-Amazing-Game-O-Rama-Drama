#pragma once
#include "Float3.h"
#include "Color.h"
#include "Float4X4.h"
#include "Quaternian.h"

namespace MEMath
{
	//TransformCoord
	Float3 TransformCoord(Float3 _Point, Float4X4 _Matrix);
	//Rotations
	Float3 Rotate(Float3 _Vector, Quaternian _Quaternian);
	Float3 InverseRotate(Float3 _Vector, Quaternian _Quaternian);
	Float3 RotateY(Float3 _Vector, float _Degrees);
	Float3 RotateX(Float3 _Vector, float _Degrees);
	Float3 RotateZ(Float3 _Vector, float _Degrees);
	//Multiply
	Float3 Multiply(Float3 _Vector, Float4X4 _Matrix);
	Float4 Multiply(Float4 _Vector, Float4X4 _Matrix);
	//Breaks down a general 3D transformation matrix into its scalar, rotational, and translational components.
	void Decompose(Float3& _Position, Quaternian& _Rotation, Float3& _Scale);
	//Builds a view matrix for a left - handed coordinate system using a camera position, an up direction, and a focal point.
	Float4X4 LookAtLH(Float3 _CameraPosition, Float3 _UpDirection, Float3 _FocalPoint);
	//Builds a view matrix for a right - handed coordinate system using a camera position, an up direction, and a focal point.
	Float4X4 LookAtRH(Float3 _CameraPosition, Float3 _UpDirection, Float3 _FocalPoint);
	//Builds a transformation matrix designed to reflect vectors through a given plane.
	Float4X4 Reflect(/*Plane _Plane*/);
	//Builds a matrix that rotates around an arbitrary axis.
	Float4X4 RotationAxis(Float3 _Axis, float _Angle);
	//Builds a matrix that rotates around an arbitrary normal vector.
	Float4X4 RotationNormal(Float3 _Axis, float _Angle);
	//Builds a rotation matrix from a quaternion.
	Float4X4 RotationQuaternion(Quaternian _Quat);
	//Builds a rotation matrix based on a vector containing the Euler angles(pitch, yaw, and roll).
	Float4X4 RotationRollPitchYawFromVector(Float3 _Vector);
	//Builds a scaling matrix from a 3D vector.
	Float4X4 ScalingFromVector(Float3 _Vector);
	//Builds a transformation matrix that flattens geometry into a plane.
	Float4X4 Shadow(/*Plane _ShadowPlane ,*/ Float3 _LightPosition, bool _PoitLight);
	//Builds a translation matrix from a vector.
	Float4X4 TranslationFromVector(Float3 _Vector);
}

