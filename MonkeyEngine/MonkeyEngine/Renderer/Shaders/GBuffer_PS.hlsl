#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"

Texture2D ShaderTexture[2];
SamplerState Sampler;

float4 main(TwoDVertexOut vertIn) : SV_TARGET
{
	return ShaderTexture[0].Sample(Sampler, vertIn.texCoord);
}