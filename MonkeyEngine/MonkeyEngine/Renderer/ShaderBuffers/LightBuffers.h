#pragma once

#include "SharedDefines.h"

struct _regAlign DirectionalLightCBuffer
{
	float4x4	viewProjection[3];
	float3		direction;
	int			enabled;
	float3		ambientColor;
	float		specularPower;
	float3		specularColor;
	float		specularIntensity;
	float3		diffuseColor;
	int			currentIndex;
};

struct _regAlign PointLightShadowDataCBuffer
{
	float4x4	viewProjection[6];
	float		planeX;
	float		planeY;
	float		shadowBias;
};

struct _regAlign PointLightCBuffer
{
	float4	position;
	float3	diffuseColor;
	int		enabled;
	float3	ambientColor;
	float	range;
	float3	specularColor;
	float	specularPower;
	float3	attenuation;
	float	specularIntensity;
};

struct _regAlign SpotLightShadowDataCBuffer
{
	float4x4 viewProjection;
};

struct _regAlign SpotLightCBuffer
{
	float3	position;
	float	exponent;
	float3	direction;
	int		enabled;
	float3	diffuseColor;
	float	cutoff;
	float3	ambientColor;
	float	specularPower;
	float3	specularColor;
	float	specularIntensity;
	float3	attenuation;
	float	range;
};

#pragma region Directional Light Constant Buffer
CONSTANT_BUFFER_BEGIN(cbDirectionalLight, b8)
	DirectionalLightCBuffer DirLight;
	const static int DIRECTIONAL_LIGHT_SHADOW_REGISTER_SLOT = 8;
CONSTANT_BUFFER_END
#pragma endregion  

#pragma region Point Light Shadow Constant Buffer
CONSTANT_BUFFER_BEGIN(cbPointLightShadowData, b9)
	PointLightShadowDataCBuffer pointLightShadowData;
	const static int POINT_LIGHT_SHADOW_REGISTER_SLOT = 9;
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Point Light Constant Buffer
CONSTANT_BUFFER_BEGIN(cbPointLight, b10)
	PointLightCBuffer pointLight;
	const static int POINT_LIGHT_REGISTER_SLOT = 10;
CONSTANT_BUFFER_END
#pragma endregion

#pragma	region Spot Light Shadow Constant Buffer
CONSTANT_BUFFER_BEGIN(cbSpotLightShadowData, b11)
	SpotLightShadowDataCBuffer spotLightShadowData;
	const static int SPOT_LIGHT_SHADOW_REGISTER_SLOT = 11;
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Spot Light Constant Buffer
CONSTANT_BUFFER_BEGIN(cbSpotLight, b12)
	SpotLightCBuffer spotLight;
	const static int SPOT_LIGHT_REGISTER_SLOT = 12;
CONSTANT_BUFFER_END
#pragma endregion

#pragma region Forward Lights Constant Buffer
	static const unsigned int NUM_FORWARD_LIGHTS = 8;
CONSTANT_BUFFER_BEGIN(cbForwardLights, b13)
	PointLightCBuffer forwardPointLights[NUM_FORWARD_LIGHTS];
	SpotLightCBuffer forwardSpotLights[NUM_FORWARD_LIGHTS];
	DirectionalLightCBuffer forwardDirLight;
	const static int FORWARD_LIGHTS_REGISTER_SLOT = 13;
CONSTANT_BUFFER_END
#pragma endregion