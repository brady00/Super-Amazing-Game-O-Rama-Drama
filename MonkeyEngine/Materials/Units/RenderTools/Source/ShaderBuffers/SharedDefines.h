#pragma once

#ifdef __cplusplus
	#pragma once
	#include <DirectXMath.h>
	typedef unsigned int		uint;
	typedef DirectX::XMFLOAT2	float2;
	typedef DirectX::XMFLOAT3	float3;
	typedef DirectX::XMFLOAT4	float4;
	typedef DirectX::XMFLOAT4X4	float4x4;
	#define _regAlign __declspec(align(16))
	#define SEMANTIC(s_name)
	#define CONSTANT_BUFFER_BEGIN(cb_name, reg) struct _regAlign cb_name {
	#define CONSTANT_BUFFER_END };
#else
	#pragma pack_matrix(row_major)
	#define _regAlign 
	#define SEMANTIC(s_name) : s_name
	#define CONSTANT_BUFFER_BEGIN(cb_name, reg) cbuffer cb_name : register(reg){
	#define CONSTANT_BUFFER_END }
#endif