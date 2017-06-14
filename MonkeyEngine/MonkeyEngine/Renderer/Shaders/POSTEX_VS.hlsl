#pragma pack_matrix(row_major)
#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"

TwoDVertexOut main( VERTEX_POSTEX pos )
{
	TwoDVertexOut output = (TwoDVertexOut)0;
	//float4 temppos = mul(float4(pos.position, 1), world);
	//temppos = mul(temppos, InvViewProj);
	output.position = float4(pos.position, 1);
	output.texCoord = pos.texCoord;
	return output;
}