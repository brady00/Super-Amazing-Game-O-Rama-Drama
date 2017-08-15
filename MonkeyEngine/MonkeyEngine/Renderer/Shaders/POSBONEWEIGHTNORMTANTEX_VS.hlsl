#pragma row_major
#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"


GBufferVertexOut main( VERTEX_POSBONEWEIGHTNORMTANTEX vertIn )
{
	GBufferVertexOut vertOut = (GBufferVertexOut)0;
	float4 temppos = mul(float4(vertIn.position, 1), World);
	temppos = mul(temppos, InvViewProj);
	vertOut.position = temppos;
	vertOut.texCoord = vertIn.texCoord;
	vertOut.normal = normalize(mul(vertIn.normal, (float3x3)World));
	return vertOut;

//	VS_OUTPUT OUT = (VS_OUTPUT)0;
//
//	float4 v = float4(0.0f, 0.0f, 0.0f, 1.0f);
//	float3 norm = float3(0.0f, 0.0f, 0.0f);
//	float lastWeight = 0.0f;
//
//	IN.normal = normalize(IN.normal);
//
//	for (int i = 0; i < MaxNumAffectingBones - 1; i++)
//	{
//		//Multiply position by bone matrix
//		v += IN.weights * mul(IN.position, BoneMatrices[IN.boneIndices]);
//		norm += IN.weights * mul(IN.normal, BoneMatrices[IN.boneIndices]);
//
//		//Sum up the weights
//		lastWeight += IN.weights;
//	}
//	//Make sure weights add up to 1
//	lastWeight = 1.0f - lastWeight;
//
//	//Apply last bone
//	v += lastWeight * mul(IN.position, BoneMatrices[IN.boneIndices[MaxNumAffectingBones - 1]]);
//	norm += lastWeight * mul(IN.normal, BoneMatrices[IN.boneIndices[MaxNumAffectingBones - 1]]);
//
//	//Get the world position of the vertex
//	v.w = 1.0f;
//	float4 posWorld = mul(v, matWorld);
//	OUT.position = mul(posWorld, matVP);
//	//Output texture coordinate is same as input
//	OUT.tex0 = IN.tex0;
//
//	//Calculate Lighting
//	norm = normalize(norm);
//	norm = mul(norm, matWorld);
//	OUT.shade = max(dot(norm, normalize(lightPos - posWorld)), 0.2f);
//
//	return OUT;
}