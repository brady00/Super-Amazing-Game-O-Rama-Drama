#pragma once
#include "Base/Component.h"
#include "RenderStructures.h"
#include "RenderSet/RenderShape.h"
#include "Behaviour/Animation.h"
#include <d3d11.h>
using namespace DirectX;
namespace MonkeyEngine
{
	namespace MEFileIO
	{
		class FileIO;
	}
	using namespace MERenderer;
	namespace MEObject
	{
		class __declspec(dllexport) CompRenderer : public MERenderer::RenderShape, public Component
		{
			friend class MEFileIO::FileIO;
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
			bool m_Enabled;

		public:
			CompRenderer();
			~CompRenderer();
			std::string& GetVertexFileName();
			Material& GetMaterial();
			void SetVertexFileName(std::string&);
			void SetMaterial(Material&);
			void(*foo)();
			bool GetEnabled();
			void SetEnabled(bool enable);
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
