#pragma once
#include "Base/Component.h"
#include "RenderStructures.h"
#include "RenderSet/RenderShape.h"
#include "Behaviour/Animation.h"
#include <d3d11.h>
using namespace DirectX;
namespace MonkeyEngine
{
	using namespace MERenderer;
	namespace MEObject
	{
		class CompRenderer : public MERenderer::RenderShape, public Component
		{
		protected:
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
			Material* m_Material;

			MERenderer::BlendStateManager::BStates& GetBlendState();
			MERenderer::RasterizerStateManager::RasterStates& GetRasterState();
			MERenderer::DepthStencilStateManager::DSStates& GetDepthStencilState();
			MERenderer::VERTEX*& GetVerticies();
			unsigned int& GetNumVerticies();
			unsigned int*& GetIndicies();
			unsigned int& GetiNumIndicies();
			unsigned int& GetStartIndexLocation();
			int& GetBaseVertexLocation();
			MERenderer::VertexFormat& GetVertexFormat();
			void SetBlendState(MERenderer::BlendStateManager::BStates*);
			void SetRasterState(MERenderer::RasterizerStateManager::RasterStates*);
			void SetDepthStencilState(MERenderer::DepthStencilStateManager::DSStates*);
			void SetVerticies(MERenderer::VERTEX*);
			void SetNumVerticies(unsigned int&);
			void SetIndicies(unsigned int*);
			void SetiNumIndicies(unsigned int&);
			void SetStartIndexLocation(unsigned int&);
			void SetBaseVertexLocation(int&);
			void SetVertexFormat(MERenderer::VertexFormat&);
		public:
			CompRenderer();
			~CompRenderer();
			std::string& GetVertexFileName();
			Material& GetMaterial();
			void SetVertexFileName(std::string&);
			void SetMaterial(Material&);
			void(*foo)();
			virtual void Draw(ID3D11DeviceContext* d3DeviceContext);
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
				Material* _Material,
				Skeleton _Skeleton);
		};
	}
}