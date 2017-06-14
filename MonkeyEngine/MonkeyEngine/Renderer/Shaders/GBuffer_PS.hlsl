#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
SamplerState Sampler;

float4 main(TwoDVertexOut vertIn) : SV_TARGET
{
	float4 colors;
	float4 normals;
	float3 lightDir;
	float lightIntensity;
	float4 outputColor;
	
	colors = colorTexture.Sample(Sampler, vertIn.texCoord);
	normals = normalTexture.Sample(Sampler, vertIn.texCoord);
	lightDir = -float3(-0.5f, -0.5f, 0);
	lightIntensity = saturate(dot(normals.xyz, lightDir));
	outputColor = saturate(colors * lightIntensity);
	
	return outputColor;
}