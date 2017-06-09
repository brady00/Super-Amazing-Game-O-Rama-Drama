#pragma once
#include "SharedDefines.h"

#pragma region World Matrix Constant buffer
CONSTANT_BUFFER_BEGIN(cbPerObject, b0)
	float4x4	world;
#ifdef __cplusplus
	const static int REGISTER_SLOT = 0;
#endif
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Camera Constant Buffer
CONSTANT_BUFFER_BEGIN(cbPerCamera, b1)
	float4x4	ViewProj;
	float4x4	InvViewProj;
	float3		CameraPos;
	float		FarDist;
	float2		ScreenSize;
	float		PlaneX;
	float		PlaneY;
	float3		CameraDir;
#ifdef __cplusplus
	const static int REGISTER_SLOT = 1;
#endif
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Miscellanious Constant Buffer
CONSTANT_BUFFER_BEGIN(cbMisc, b2)
	float2	HalfPixel;
	float	ShadowDepthOffset;
	float	ShadowDirOffset;
	float	DisplacementScale;
	float	MaxTessDistance;
	float	MinTessDistance;
	float	MaxTessFactor;
	float	MinTessFactor;
#ifdef __cplusplus
	const static int REGISTER_SLOT = 2;
#endif
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Debug Constant Buffer
CONSTANT_BUFFER_BEGIN(cbDebug, b3)
	float LineWidth;
#ifdef __cplusplus
	const static int REGISTER_SLOT = 3;
#endif
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Post Process Constant Buffer
CONSTANT_BUFFER_BEGIN(cbPostProcess, b4)
	float TexCoordScale;
	float FocusDistance;
	float FocusRange;
	float EdgeWidth;
	float EdgeIntensity;
	float Theta;
	float Scale;
	float Fade;
#ifdef __cplusplus
	const static int REGISTER_SLOT = 4;
#endif
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Skinned Object Constant Buffer
CONSTANT_BUFFER_BEGIN(cbPerSkinnedObject, b5)
#ifdef __cplusplus
	const static int REGISTER_SLOT = 5;
#endif	
	const static int NUM_BONES = 50;
	float4x4	World;
	float4x4	BoneMatricies[NUM_BONES];
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Tile Constant Buffer
CONSTANT_BUFFER_BEGIN(cbPerTileFrame, b6)
#ifdef __cplusplus
	const static int REGISTER_SLOT = 6;
#endif	
	float4x4	TileWorld;
	float4x4	TileView;
	float4x4	TileProj;
	float4x4	TileMVP;
	float		TileSize;
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Terrain Constant Buffer
CONSTANT_BUFFER_BEGIN(cbTerrain, b7)
#ifdef __cplusplus
	const static int REGISTER_SLOT = 7;
#endif	
	float	TessellatedTriWidth;
	float	TerrainHeightCoordFactor;
	float	TerrainDiffuseCoordFactor;
	float	TerrainHeightScale;
	float2	TerrainCameraPosOffsetXZ;
	float	TerrainHeightOffset;
	int		ShowTiles;
	int		ShowTerrainTransistions;
	int		TerrainTest;
CONSTANT_BUFFER_END
#pragma endregion