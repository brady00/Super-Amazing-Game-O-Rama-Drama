#pragma once
#include "RenderToolsDLL.h"
#include "RenderNode.h"
#include "RenderSet.h"
#include <d3d11.h>
#include <string>
#include <unordered_map>
#include "RenderStructures.h"
namespace MEFileIO
{
	class FileIO;
}
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderShape;
		class RENDERTOOLS_EXPORT RenderTexture : public RenderNode
		{
			friend MEFileIO::FileIO;
		private:
			ID3D11SamplerState*	m_d3SamplerState;
			Material* m_Material;
			RenderSet* m_pRenderShapes;
		public:
			RenderTexture();
			~RenderTexture();
			void Draw(ID3D11DeviceContext* d3DeviceContext, unsigned int EngineState);
			bool Load(Material* _Material, ID3D11Device* d3Device);
			const std::string& GetTextureFileName();
			void AddShape(RenderShape*);
			bool LoadShape(RenderShape*& _Shape);
		};

	}
}