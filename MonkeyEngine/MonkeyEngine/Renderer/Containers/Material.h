#pragma once
#include <DirectXMath.h>
using namespace DirectX;
#include <string>
namespace MonkeyEngine
{
	namespace MEObject
	{
		class Material
		{
		public:
			std::string mName;
			XMFLOAT3 mAmbient;
			XMFLOAT3 mDiffuse;
			XMFLOAT3 mEmissive;
			double mTransparencyFactor;
			std::string mDiffuseMapName;
			std::string mEmissiveMapName;
			std::string mGlossMapName;
			std::string mNormalMapName;
			std::string mSpecularMapName;
			XMFLOAT3 mSpecular;
			XMFLOAT3 mReflection;
			double mSpecularPower;
			double mShininess;
			double mReflectionFactor;
		};
	}
}