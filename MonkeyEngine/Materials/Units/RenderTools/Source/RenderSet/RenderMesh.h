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
			RenderTexture* TextureExsits(std::string _TextureFileName);
			bool LoadTexture(std::string _TextureFileName, RenderTexture*& _Texture, ID3D11Device* d3Device);
		public:
			RenderMesh();
			~RenderMesh();
			//in: void
			//out: const string
			//	The Mesh's File Name
			//desc: Returns the File Name for this mesh
			const std::string& GetVertexFileName();
			//in: ID3D11DeviceContext*
			//	The current Renderers DeviceContext
			//out: void
			//desc: Sends the Vertex data to the Graphics Pipeline
			void Draw(ID3D11DeviceContext* d3DeviceContext);
			//in: string
			//	The File Name for the Texture to Add
			//in: ID3D11Device*
			//	The current Renderer's Device
			//out: RenderTexture*
			//	The RenderTexture Added, or found
			//desc: Looks for a RenderTexture that is the same as the one being added
			//	If found will return that RenderTexture otherwise will create a new one
			RenderTexture* AddTexture(std::string _TextureFileName, ID3D11Device* d3Device);
			//in: string
			//	The File Name for the Mesh
			//out: VertexFormat&
			//	The VertexFormat for this RenderMesh
			//in: ID3D11Device*
			//	The current Renderer's Device
			//in: ID3D11DeviceContext*
			//	The current Renderers DeviceContext
			//out: bool
			//	whether it was successfully loaded or not
			//desc: Used during Scene Loading to set up the Vertex and Index Buffers
			bool Load(std::string _VertexFileName, VertexFormat& _VertexFormat, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
		};

	}
}
