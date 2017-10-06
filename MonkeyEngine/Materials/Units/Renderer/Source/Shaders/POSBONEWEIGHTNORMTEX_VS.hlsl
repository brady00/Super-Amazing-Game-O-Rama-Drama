#include "VertexLayouts.hlsli"
float4 main( VERTEX_POSBONEWEIGHTNORMTEX pos) : SV_POSITION
{
	return float4(pos.position,1);
}