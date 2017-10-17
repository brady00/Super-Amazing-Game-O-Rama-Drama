#ifdef __cplusplus
#pragma row_major
#endif
#include "VertexLayouts.hlsli"
#include "ShaderBuffers/ConstantBuffers.h"


GBufferVertexOut main( VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR vertIn )
{
	GBufferVertexOut vertOut = (GBufferVertexOut)0;
	float4 temppos = mul(float4(vertIn.position, 1), World);
	temppos = mul(temppos, InvViewProj);
	vertOut.position = temppos;
	vertOut.texCoord = vertIn.texCoord;
	vertOut.normal = normalize(mul(vertIn.normal, (float3x3)World));
	vertOut.color = vertIn.color;
	return vertOut;
}