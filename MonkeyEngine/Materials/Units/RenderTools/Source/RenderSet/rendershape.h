#pragma once
#include "RenderToolsDLL.h"
#include "RenderNode.h"
#pragma warning(disable: 4793)
#include <DirectXMath.h>
#include "Managers/InputLayoutManager.h"
#include "Managers/BlendStateManager.h"
#include "Managers/RasterizerStateManager.h"
#include "Managers/DepthStencilStateManager.h"
#include "Managers/VertexBufferManager.h"
#include "RenderStructures.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		
		class _declspec(dllexport) RenderShape : public RenderNode
		{
		public:
			RenderShape() {};
			~RenderShape() {};
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext*
			//out: void					
			//desc: Draws the the object to the screen	
			virtual void Draw(ID3D11DeviceContext* d3DeviceContext) {};
		};


	}
}