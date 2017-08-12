#pragma pack_matrix(row_major)
#include "VertexLayouts.hlsli"
#include "../ShaderBuffers/ConstantBuffers.h"

SKYBOX_VS_OUT main( VERTEX_POS fromVertexBuffer )
{
	SKYBOX_VS_OUT sendToRasterizer = (SKYBOX_VS_OUT)0;

	float4 localPos;
	localPos.x = fromVertexBuffer.position.x;
	localPos.y = fromVertexBuffer.position.y;
	localPos.z = fromVertexBuffer.position.z;
	localPos.w = 1;

	localPos = mul(localPos, world);
	localPos = mul(localPos, InvViewProj);
	//localPos = mul(localPos, projMatrix);

	sendToRasterizer.projectedCoordinate = localPos;

	sendToRasterizer.initialCoordinate = fromVertexBuffer.position;

	return sendToRasterizer;
}