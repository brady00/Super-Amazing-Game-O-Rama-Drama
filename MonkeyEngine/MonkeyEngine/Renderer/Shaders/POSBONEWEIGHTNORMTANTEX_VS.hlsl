#pragma row_major
#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"


GBufferVertexOut main( VERTEX_POSBONEWEIGHTNORMTANTEX vertIn )
{
	GBufferVertexOut vertOut = (GBufferVertexOut)0;
	float4 temppos = mul(float4(vertIn.position, 1), world);
	temppos = mul(temppos, InvViewProj);
	vertOut.position = temppos;
	vertOut.texCoord = vertIn.texCoord;
	vertOut.normal = normalize(mul(vertIn.normal, (float3x3)world));
	return vertOut;
}