#pragma once
#include <d3d11.h>
#include <vector>
#pragma warning(disable: 4793)
#include <DirectXMath.h>
#include "Float3/Float3.h"
#ifdef RENDERSTRUCTURES_EXPORTS
#define RENDERSTRUCTURES_EXPORT __declspec(dllexport)
#else
#define RENDERSTRUCTURES_EXPORT __declspec(dllimport)
#endif
namespace MonkeyEngine
{
	using namespace MEMath;
	namespace MERenderer
	{
		class RenderState
		{
		public:
			enum RState { GAME_RENDERING = 0, EDITOR_RENDERING, VR_RENDERING, STATE_COUNT };
			static RState RENDERSTRUCTURES_EXPORT GetRenderState();
			static void RENDERSTRUCTURES_EXPORT SetRenderState(RState State);
			static RState state;
		};

		struct VERTEX_POS
		{
			Float3 position;
		};
		struct VERTEX_POSCOLOR
		{
			Float3 position;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSTEX
		{
			Float3 position;
			DirectX::XMFLOAT2 texcoord;
		};
		struct VERTEX_POSTEXCOLOR
		{
			Float3 position;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSNORMTEX
		{
			Float3 position;
			Float3 normal;
			DirectX::XMFLOAT2 texcoord;
		};
		struct VERTEX_POSNORMTEXCOLOR
		{
			Float3 position;
			Float3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSNORMTANTEX
		{
			Float3 position;
			Float3 normal;
			DirectX::XMFLOAT2 texcoord;
			Float3 tangent;
			float determinant;
		};
		struct VERTEX_POSNORMTANTEXCOLOR
		{
			Float3 position;
			Float3 normal;
			DirectX::XMFLOAT2 texcoord;
			Float3 tangent;
			float determinant;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSBONEWEIGHT
		{
			Float3 position;
			DirectX::XMINT4   bone;
			DirectX::XMFLOAT4 weights;
		};
		struct VERTEX_POSBONEWEIGHTCOLOR
		{
			Float3 position;
			DirectX::XMINT4   bone;
			DirectX::XMFLOAT4 weights;
			DirectX::XMFLOAT4 color;
		};
		struct VERTEX_POSBONEWEIGHTNORMTEX
		{
			Float3 position;
			DirectX::XMINT4   bones;
			DirectX::XMFLOAT4 weights;
			Float3 normal;
			DirectX::XMFLOAT2 texcoord;
			VERTEX_POSBONEWEIGHTNORMTEX() { bones.x = bones.y = bones.z = bones.w = -1; }

		};
		struct VERTEX_POSBONEWEIGHTNORMTEXCOLOR
		{
			Float3 position;
			DirectX::XMINT4   bones;
			DirectX::XMFLOAT4 weights;
			Float3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMFLOAT4 color;
			VERTEX_POSBONEWEIGHTNORMTEXCOLOR() { bones.x = bones.y = bones.z = bones.w = -1; }

		};
		struct VERTEX_POSBONEWEIGHTNORMTANTEX
		{
			Float3 position;
			Float3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMINT4   bones;
			DirectX::XMFLOAT4 weights;
			Float3 tangent;
			float determinant;
			Float3 binormal;
			VERTEX_POSBONEWEIGHTNORMTANTEX() { bones.x = bones.y = bones.z = bones.w = -1; }
		};
		struct VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR
		{
			Float3 position;
			Float3 normal;
			DirectX::XMFLOAT2 texcoord;
			DirectX::XMINT4   bones;
			DirectX::XMFLOAT4 weights;
			Float3 tangent;
			float determinant;
			Float3 binormal;
			DirectX::XMFLOAT4 color;
			VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR() { bones.x = bones.y = bones.z = bones.w = -1; }
		};
		class Material
		{
		private:

		public:
			std::string mName;
			Float3 mAmbient;
			Float3 mDiffuse;
			Float3 mEmissive;
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
			Float3 mSpecular;
			Float3 mReflection;
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