#include "VertexLayouts.hlsli"
#include "ShaderBuffers/ConstantBuffers.h"

textureCUBE Texture : register (t0);
SamplerState Sampler : register(s0);

float4 main(float3 initialCoordinate : POSITION) : SV_TARGET
{
	return Texture.Sample(Sampler, initialCoordinate);
}