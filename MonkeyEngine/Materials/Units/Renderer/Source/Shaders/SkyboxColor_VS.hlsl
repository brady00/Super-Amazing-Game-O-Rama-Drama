#pragma pack_matrix(row_major)
#include "VertexLayouts.hlsli"
#include "ShaderBuffers/ConstantBuffers.h"

SKYBOXCOLOR_VS_OUT main( VERTEX_POSCOLOR fromVertexBuffer )
{
	SKYBOXCOLOR_VS_OUT sendToRasterizer = (SKYBOXCOLOR_VS_OUT)0;

	float4 temppos = mul(float4(fromVertexBuffer.position, 1), world);
	temppos = mul(temppos, InvViewProj);

	sendToRasterizer.projectedCoordinate = temppos;
	sendToRasterizer.color = fromVertexBuffer.color;
	sendToRasterizer.projectedCoordinate.z = sendToRasterizer.projectedCoordinate.w;
	return sendToRasterizer;
}