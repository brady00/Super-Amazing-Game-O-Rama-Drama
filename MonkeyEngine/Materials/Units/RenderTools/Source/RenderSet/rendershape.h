#pragma once
#include "RenderToolsDLL.h"
#include "RenderNode.h"
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
		
		class RenderShape : public RenderNode
		{
		public:
			RenderShape() {};
			~RenderShape() {};
			virtual void Draw(ID3D11DeviceContext* d3DeviceContext) {};
		};


	}
}