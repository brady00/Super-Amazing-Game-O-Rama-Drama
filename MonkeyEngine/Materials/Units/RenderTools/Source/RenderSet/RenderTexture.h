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
			//in: ID3D11DeviceContext*			
			//	The Current Renderer's Device Context								
			//out: void								
			//desc: Updates the ShaderResourceViews on the rendering pipeline			
			void Draw(ID3D11DeviceContext* d3DeviceContext);
			//in: Material*							
			//	A material to make into	ShaderResourceViews					
			//in: ID3D11Device*						
			//	The Current Renderer's Device*		
			//out: bool								
			//	Whether it succeeded or not			
			//desc: Used during Scene Loading to set up the ShaderResourceViews			
			bool Load(Material* _Material, ID3D11Device* d3Device);
			//in: void								
			//out: const string						
			//	The Diffuse Texture Name			
			//desc: Gets the Diffuse Texture Name	
			const std::string& GetTextureFileName();
			//in: RenderShape*
			//	A RenderShape that is added to the list of RenderShapes
			//out: void					
			//desc: Adds a RenderShape to the list of RenderShapes	
			void AddShape(RenderShape*);
		};

	}
}