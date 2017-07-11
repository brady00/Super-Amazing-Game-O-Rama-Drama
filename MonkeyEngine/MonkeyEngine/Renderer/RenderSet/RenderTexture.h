#pragma once
#include "RenderNode.h"
#include "RenderSet.h"
#include <d3d11.h>
#include <string>
#include "../Containers/Material.h"
namespace MEFileIO
{
	class FileIO;
}
namespace MERenderer
{
	class RenderShape;
	class RenderTexture : public RenderNode
	{
		friend MEFileIO::FileIO;
	private:
		ID3D11ShaderResourceView*	m_d3DiffuseTexture;
		ID3D11SamplerState*			m_d3SamplerState;
		//normal map
		//other mapping
		MEObject::Material* m_Material;
		RenderSet* m_pRenderShapes;
	public:
		RenderTexture();
		~RenderTexture();
		void Draw();
		bool Load(std::string _TextureFileName);
		const std::string& GetTextureFileName();
		void AddShape(RenderShape*);
		ID3D11ShaderResourceView* GetDiffuseTexture();
		void SetDiffuseTexture(ID3D11ShaderResourceView* _Diffuse);
		bool LoadShape(RenderShape*& _Shape);
	};

}
