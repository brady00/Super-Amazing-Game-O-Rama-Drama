#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RENDERTOOLS_EXPORT RenderNode
		{
		private:
			RenderNode* m_pNext;
		public:
			RenderNode();
			virtual ~RenderNode();
			//in: void
			//out: RenderNode*
			//	The Next RenderNode in the list
			//desc: Gets the Next RenderNode in the list
			RenderNode* GetNext();
			//in: RenderNode*
			//	The Next RenderNode in the list
			//out: void
			//desc: Sets the Next RenderNode in the list
			void SetNext(RenderNode* _Next);
			//in: ID3D11DeviceContext*
			//	The current Renderers DeviceContext
			//out: void
			//desc: Sends the corresponding things to the Graphics Pipeline
			virtual void Draw(ID3D11DeviceContext* d3DeviceContext) = 0;
		};
	}
}

