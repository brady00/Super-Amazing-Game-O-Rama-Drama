#pragma pack_matrix(row_major)
#include "VertexLayouts.hlsli"
#include "ShaderBuffers/ConstantBuffers.h"

SKYBOX_VS_OUT main( VERTEX_POS fromVertexBuffer )
{
	SKYBOX_VS_OUT sendToRasterizer = (SKYBOX_VS_OUT)0;

	float4 temppos = mul(float4(fromVertexBuffer.position, 1), world);
	temppos = mul(temppos, InvViewProj);

	sendToRasterizer.projectedCoordinate = temppos;
	sendToRasterizer.initialCoordinate = fromVertexBuffer.position;
	return sendToRasterizer;
}