#pragma once
#include "RenderNode.h"
#include "RenderSet.h"
#include <d3d11.h>
#include <vector>
#include <unordered_map>
#include "../Containers/Material.h"
#include "../Managers/VertexBufferManager.h"
#include "../../Components/Behaviour/Animation.h"
namespace MEFileIO
{
	class FileIO;
}
namespace MonkeyEngine
{
	namespace MERenderer
	{
		struct VERTEX;
		class RenderTexture;
		class RenderMesh : public RenderNode
		{
			friend class MEFileIO::FileIO;
		private:
			VERTEX* m_vVerticies;
			unsigned int m_uiNumVerticies;
			unsigned int* m_vIndicies;
			unsigned int m_uiNumIndicies;
			unsigned int m_uiStartIndexLocation;
			int m_iBaseVertexLocation;
			std::string m_sVertexFileName;
			RenderSet* m_pRenderTextures;
			VertexFormat m_eVertexFormat;
			Material* temp_Material;
			MEObject::Skeleton temp_Skeleton;
		public:
			RenderMesh();
			~RenderMesh();
			const std::string& GetVertexFileName();
			void Draw();
			RenderTexture* AddTexture(std::string _TextureFileName);
			bool Load(std::string _VertexFileName, VertexFormat& _VertexFormat);
			RenderTexture* TextureExsits(std::string _TextureFileName);
			bool LoadTexture(std::string _TextureFileName, RenderTexture*& _Texture);
		};

	}
}
