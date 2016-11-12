#pragma once
#include "RenderNode.h"
#include "RenderSet.h"
#include <d3d11.h>
#include <string>
namespace MERenderer
{
	class RenderTexture : public RenderNode
	{
	private:
		ID3D11ShaderResourceView* m_d3DiffuseTexture;
		//normal map
		//other mapping
		std::string m_TextureFileName;
		RenderSet* m_pRenderShapes;
	public:
		RenderTexture();
		~RenderTexture();
		void Draw();
		bool Load(std::string _TextureFileName);
		const std::string& GetVertexFileName();
		bool AddTexture(std::string _TextureFileName);
		bool TextureExsits(std::string _TextureFileName);
		ID3D11ShaderResourceView* GetDiffuseTexture();
	};

}
