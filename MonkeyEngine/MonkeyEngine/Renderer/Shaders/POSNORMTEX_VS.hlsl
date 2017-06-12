#pragma pack_matrix(row_major)
#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"



TwoDVertexOut main( VERTEX_POSNORMTEX vertIn )
{
	TwoDVertexOut vertOut;
	float4 temppos = mul(float4(vertIn.position, 1), world);
	temppos = mul(temppos, InvViewProj);
	vertOut.position = temppos;
	vertOut.texCoord = vertIn.texCoord;
	return vertOut;
}