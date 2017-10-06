#include "VertexLayouts.hlsli"
float4 main( VERTEX_POSNORMTANTEX pos ) : SV_POSITION
{
	return float4(pos.position,1);
}