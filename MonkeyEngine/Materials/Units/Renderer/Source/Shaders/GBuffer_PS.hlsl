#include "VertexLayouts.hlsli"
#include "ShaderBuffers/ConstantBuffers.h"

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
	//bool comp = (colors.x == normals.x && colors.y == normals.y && colors.z == normals.z);
	//if (!comp)
	//{
	//	lightDir = -(float3(0.0f, -1.0f, 0));
	//	float Dot = dot(normals.xyz, lightDir);
	//	lightIntensity = saturate(Dot);
	//	outputColor = saturate(colors * lightIntensity);
	//}
	//else
	//{
	//	outputColor = colors;
	//}
	//return outputColor;
	return colors;
}