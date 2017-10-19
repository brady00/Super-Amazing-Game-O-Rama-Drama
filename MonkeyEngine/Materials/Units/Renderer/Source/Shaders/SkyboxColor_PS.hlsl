#include "VertexLayouts.hlsli"
#include "ShaderBuffers/ConstantBuffers.h"

textureCUBE Texture : register (t0);
SamplerState Sampler : register(s0);

float4 main(float4 color : COLOR) : SV_TARGET
{
	return color;
}