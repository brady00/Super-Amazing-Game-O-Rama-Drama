#include "VertexLayouts.hlsli"
#include "ShaderBuffers/ConstantBuffers.h"
#include "ShaderBuffers/LightBuffers.h"

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
	//normals = normalTexture.Sample(Sampler, vertIn.texCoord);
	
	//lightDir = -DirLight.direction;
	//float Dot = dot(normals.xyz, lightDir);
	//lightIntensity = saturate(Dot);
	//outputColor = saturate(colors * lightIntensity);

	//return outputColor;
	return colors;
}