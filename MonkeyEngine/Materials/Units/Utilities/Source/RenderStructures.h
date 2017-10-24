#pragma once
#include <d3d11.h>
#include <vector>
#pragma warning(disable: 4793)
#include <DirectXMath.h>
#ifdef RENDERSTRUCTURES_EXPORTS
#define RENDERSTRUCTURES_EXPORT __declspec(dllexport)
#else
#define RENDERSTRUCTURES_EXPORT __declspec(dllimport)
#endif
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderState
		{
		public:
			enum RState { GAME_RENDERING = 0, EDITOR_RENDERING, VR_RENDERING, STATE_COUNT };
			static RState RENDERSTRUCTURES_EXPORT RenderState::GetRenderState();
			static void RENDERSTRUCTURES_EXPORT SetRenderState(RState State);
		private:
			static RState state;
		};
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
		struct VERTEX_POSTEXCOLOR : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSNORMTEX : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
		};
		struct VERTEX_POSNORMTEXCOLOR : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSNORMTANTEX : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT3 tangent;
			float determinant;
		};
		struct VERTEX_POSNORMTANTEXCOLOR : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT3 tangent;
			float determinant;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSBONEWEIGHT : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMINT4   bone;
			DirectX::XMFLOAT4 weights;
		};
		struct VERTEX_POSBONEWEIGHTCOLOR : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMINT4   bone;
			DirectX::XMFLOAT4 weights;
			DirectX::XMFLOAT4 color;
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
		struct VERTEX_POSBONEWEIGHTNORMTEXCOLOR : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMINT4   bones;
			DirectX::XMFLOAT4 weights;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT4 color;
			VERTEX_POSBONEWEIGHTNORMTEXCOLOR() { bones.x = bones.y = bones.z = bones.w = -1; }

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
		struct VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR : public VERTEX
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMINT4   bones;
			DirectX::XMFLOAT4 weights;
			DirectX::XMFLOAT3 tangent;
			float determinant;
			DirectX::XMFLOAT3 binormal;
			DirectX::XMFLOAT4 color;
			VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR() { bones.x = bones.y = bones.z = bones.w = -1; }
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

			DirectX::XMFLOAT4 Color;
			~Material()
			{
				if (m_d3DiffuseTexture)
					m_d3DiffuseTexture->Release();
				if (m_d3EmissiveTexture)
					m_d3EmissiveTexture->Release();
				if (m_d3GlossTexture)
					m_d3GlossTexture->Release();
				if (m_d3NormalTexture)
					m_d3NormalTexture->Release();
				if (m_d3SpecularTexture)
					m_d3SpecularTexture->Release();
			}
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