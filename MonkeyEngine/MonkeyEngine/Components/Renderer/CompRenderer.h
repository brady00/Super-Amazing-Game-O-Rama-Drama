#pragma once
#include "../Base/Component.h"
#include "../../Renderer/RenderSet/RenderShape.h"
using namespace DirectX;
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

	class CompRenderer : public Component, public MERenderer::RenderShape
	{
	private:
		MERenderer::BlendStateManager::BStates* m_BlendState;
		MERenderer::RasterizerStateManager::RasterStates* m_RasterState;
		MERenderer::DepthStencilStateManager::DSStates* m_DSState;
		MERenderer::VERTEX* m_vVerticies;
		unsigned int* m_uiNumVerticies;
		unsigned int* m_vIndicies;
		unsigned int* m_uiNumIndicies;
		unsigned int* m_uiStartIndexLocation;
		int* m_iBaseVertexLocation;
		std::string* m_sVertexFileName;
		MERenderer::VertexFormat* m_eVertexFormat;
		Material m_Material; 

	public:
		CompRenderer();
		~CompRenderer();

		MERenderer::BlendStateManager::BStates& GetBlendState();
		MERenderer::RasterizerStateManager::RasterStates& GetRasterState();
		MERenderer::DepthStencilStateManager::DSStates& GetDepthStencilState();
		MERenderer::VERTEX*& GetVerticies();
		unsigned int& GetNumVerticies();
		unsigned int*& GetIndicies();
		unsigned int& GetiNumIndicies();
		unsigned int& GetStartIndexLocation();
		int& GetBaseVertexLocation();
		std::string& GetVertexFileName();
		MERenderer::VertexFormat& GetVertexFormat();
		std::string& GetTextureFileName();
		Material& GetMaterial();

		void SetBlendState(MERenderer::BlendStateManager::BStates*);
		void SetRasterState(MERenderer::RasterizerStateManager::RasterStates*);
		void SetDepthStencilState(MERenderer::DepthStencilStateManager::DSStates*);
		void SetVerticies(MERenderer::VERTEX*);
		void SetNumVerticies(unsigned int&);
		void SetIndicies(unsigned int*);
		void SetiNumIndicies(unsigned int&);
		void SetStartIndexLocation(unsigned int&);
		void SetBaseVertexLocation(int&);
		void SetVertexFileName(std::string&);
		void SetVertexFormat(MERenderer::VertexFormat&);
		void SetMaterial(Material&);
		virtual void Draw();
		virtual bool Load(MERenderer::BlendStateManager::BStates* m_BlendState, 
						 MERenderer::RasterizerStateManager::RasterStates* m_RasterState,
						 MERenderer::DepthStencilStateManager::DSStates* m_DSState,
						 MERenderer::VERTEX* m_vVerticies,
						 unsigned int* m_uiNumVerticies,
						 unsigned int* m_vIndicies,
						 unsigned int* m_uiNumIndicies,
						 unsigned int* m_uiStartIndexLocation,
						 int* m_iBaseVertexLocation,
						 std::string* m_sVertexFileName,
						 MERenderer::VertexFormat* m_eVertexFormat,
						 std::string* m_TextureFileName );
	private:
		void Initialize();
	};
}

