#pragma once
#include "RenderNode.h"
#include "RenderSet.h"
#include <d3d11.h>
#include <vector>
namespace MERenderer
{
	struct VERTEX;
	class RenderMesh : public RenderNode
	{
	private:
		VERTEX* m_vVerticies;
		unsigned int m_uiNumVerticies;
		unsigned int* m_vIndicies;
		unsigned int m_uiNumIndicies;
		std::string m_sVertexFileName;
		RenderSet* m_pRenderTextures;
	public:
		RenderMesh();
		~RenderMesh();
		const std::string& GetVertexFileName();
		void Draw();
		bool AddTexture(std::string _TextureFileName);
		bool Load(std::string _VertexFileName);
		bool TextureExsits(std::string _TextureFileName);
		bool LoadTexture(std::string _TextureFileName, RenderTexture*& _Texture);
	};

}
