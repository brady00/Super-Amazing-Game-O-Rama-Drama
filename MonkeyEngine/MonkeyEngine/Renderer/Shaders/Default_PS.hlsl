#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"

Texture2D ShaderTexture;
SamplerState Sampler;

ForwardFragOut main(GBufferVertexOut vertIn)
{
	ForwardFragOut output = (ForwardFragOut)0;
	output.diffuse = ShaderTexture.Sample(Sampler, vertIn.texCoord);
	output.normal = float4(vertIn.normal,1);
	return output;
}