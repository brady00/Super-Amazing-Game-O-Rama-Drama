#pragma once
#include "RenderNode.h"
#include "RenderSet.h"
#include <d3d11.h>
#include <string>
#include "../Containers/Material.h"
#include <unordered_map>
namespace MEFileIO
{
	class FileIO;
}
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderShape;
		class RenderTexture : public RenderNode
		{
			friend MEFileIO::FileIO;
		private:
			ID3D11SamplerState*			m_d3SamplerState;
			MEObject::Material* m_Material;
			RenderSet* m_pRenderShapes;
		public:
			RenderTexture();
			~RenderTexture();
			void Draw();
			bool Load(MEObject::Material* _Material);
			const std::string& GetTextureFileName();
			void AddShape(RenderShape*);
			bool LoadShape(RenderShape*& _Shape);
		};

	}
}