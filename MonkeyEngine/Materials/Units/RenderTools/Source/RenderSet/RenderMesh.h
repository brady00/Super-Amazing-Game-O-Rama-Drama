#pragma once
#include "RenderToolsDLL.h"
#include "RenderNode.h"
#include "RenderSet.h"
#include <d3d11.h>
#include <vector>
#include <unordered_map>
#include "RenderStructures.h"
#include "Managers/VertexBufferManager.h"
namespace MEFileIO
{
	class FileIO;
}
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderTexture;
		class RENDERTOOLS_EXPORT RenderMesh : public RenderNode
		{
			friend class MEFileIO::FileIO;
		private:

			void* m_vVerticies;
			unsigned int m_uiNumVerticies;
			unsigned int* m_vIndicies;
			unsigned int m_uiNumIndicies;
			unsigned int m_uiStartIndexLocation;
			int m_iBaseVertexLocationEditor;
			int m_iBaseVertexLocationGame;
			std::string m_sVertexFileName;
			RenderSet* m_pRenderTextures;
			VertexFormat m_eVertexFormat;
			Material* temp_Material;
			Skeleton temp_Skeleton;
		public:
			RenderMesh();
			~RenderMesh();
			const std::string& GetVertexFileName();
			void Draw(ID3D11DeviceContext* d3DeviceContext);
			RenderTexture* AddTexture(std::string _TextureFileName, ID3D11Device* d3Device);
			bool Load(std::string _VertexFileName, VertexFormat& _VertexFormat, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
			RenderTexture* TextureExsits(std::string _TextureFileName);
			bool LoadTexture(std::string _TextureFileName, RenderTexture*& _Texture, ID3D11Device* d3Device);
		};

	}
}
