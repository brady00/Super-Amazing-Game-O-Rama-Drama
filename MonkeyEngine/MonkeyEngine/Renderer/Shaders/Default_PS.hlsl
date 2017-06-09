#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"

Texture2D ShaderTexture;
SamplerState Sampler;

float4 main(TwoDVertexOut vertIn) : SV_TARGET
{
	return ShaderTexture.Sample(Sampler, vertIn.texCoord);
}