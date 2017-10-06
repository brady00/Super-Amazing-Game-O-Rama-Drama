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
		private:

		public:
			std::string mName;
			XMFLOAT3 mAmbient;
			XMFLOAT3 mDiffuse;
			XMFLOAT3 mEmissive;
			double mTransparencyFactor;
			std::string mDiffuseMapName;
			ID3D11ShaderResourceView*	m_d3DiffuseTexture;
			std::string mEmissiveMapName;
			ID3D11ShaderResourceView*	m_d3EmissiveTexture;
			std::string mGlossMapName;
			ID3D11ShaderResourceView*	m_d3GlossTexture;
			std::string mNormalMapName;
			ID3D11ShaderResourceView*	m_d3NormalTexture;
			std::string mSpecularMapName;
			ID3D11ShaderResourceView*	m_d3SpecularTexture;
			XMFLOAT3 mSpecular;
			XMFLOAT3 mReflection;
			double mSpecularPower;
			double mShininess;
			double mReflectionFactor;
		};
	}
}