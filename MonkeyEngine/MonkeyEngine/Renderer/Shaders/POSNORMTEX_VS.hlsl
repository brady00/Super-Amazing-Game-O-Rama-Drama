#pragma pack_matrix(row_major)
#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"



TwoDVertexOut main( VERTEX_POSNORMTEX vertIn )
{
	TwoDVertexOut vertOut;
	//loat4 temppos = mul(float4(vertIn.position,1), world);
	vertOut.position = float4(vertIn.position,1);
	vertOut.texCoord = vertIn.texCoord;
	return vertOut;
}