#pragma once
#include "RenderNode.h"
#include <string>
namespace MERenderer
{
	class RenderSet;
	class Mesh;
	class RenderContext : public RenderNode
	{
	private:
		RenderSet* m_pRenderTextures;
		Mesh* m_pMesh;
	public:
		RenderContext();
		RenderContext(Mesh* _Mesh);
		~RenderContext();

		Mesh* GetMesh();
		void SetMesh(Mesh* _Mesh);

		void Draw();
		bool AddTexture(std::string _Texture);
		bool TextureExists(std::string _Texture);
		bool LoadMesh(std::string _VertexFileName, std::string _TextureFileName);
	private:
		ID3D11ShaderResourceView* LoadTexture(std::string _FileName);
	};
}

