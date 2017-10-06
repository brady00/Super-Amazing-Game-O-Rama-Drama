#pragma once
#include <d3d11.h>
#include <vector>
#include <DirectXMath.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		struct VERTEX
		{

		};
		struct VERTEX_POS : public VERTEX
		{
			DirectX::XMFLOAT3 position;
		};
		struct VERTEX_POSCOLOR : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSTEX : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 texcoord;
		};
		struct VERTEX_POSNORMTEX : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
		};
		struct VERTEX_POSNORMTANTEX : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT3 tangent;
			float determinant;
		};
		struct VERTEX_POSBONEWEIGHT : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMINT4   bone;
			DirectX::XMFLOAT4 weights;
		};
		struct VERTEX_POSBONEWEIGHTNORMTEX : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMINT4   bones;
			DirectX::XMFLOAT4 weights;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
			VERTEX_POSBONEWEIGHTNORMTEX() { bones.x = bones.y = bones.z = bones.w = -1; }

		};
		struct VERTEX_POSBONEWEIGHTNORMTANTEX : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMINT4   bones;
			DirectX::XMFLOAT4 weights;
			DirectX::XMFLOAT3 tangent;
			float determinant;
			DirectX::XMFLOAT3 binormal;
			VERTEX_POSBONEWEIGHTNORMTANTEX() { bones.x = bones.y = bones.z = bones.w = -1; }
		};
		class Material
		{
		private:

		public:
			std::string mName;
			DirectX::XMFLOAT3 mAmbient;
			DirectX::XMFLOAT3 mDiffuse;
			DirectX::XMFLOAT3 mEmissive;
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
			DirectX::XMFLOAT3 mSpecular;
			DirectX::XMFLOAT3 mReflection;
			double mSpecularPower;
			double mShininess;
			double mReflectionFactor;
		};
		struct Keyframe
		{
			unsigned int mFrameNum;
			std::vector<DirectX::XMFLOAT4X4> mOffsets;
		};
		struct Bone
		{
			std::string mName;
			DirectX::XMFLOAT4X4 Offset;
			int mParentIndex;
			DirectX::XMFLOAT4X4 Local;
			DirectX::XMFLOAT4X4 InverseBindpose;
		};

		class Skeleton
		{
		public:
			std::vector<Bone> mJoints;
		};
	}
}