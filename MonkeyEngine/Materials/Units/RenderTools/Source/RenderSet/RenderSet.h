#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderNode;
		class RENDERTOOLS_EXPORT RenderSet
		{
		private:
			RenderNode* m_pHead;
		public:
			RenderSet();
			~RenderSet();
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext*
			//out: void					
			//desc: Calls Draw on the list of RenderNodes	
			void Draw(ID3D11DeviceContext* d3DeviceContext);
			//in: RenderNode*
			//	The RenderNode to add to the list of RenderNodes
			//out: void					
			//desc: Adds a RenderNode to the list of RenderNodes	
			void AddNode(RenderNode* _Node);
			//in: void
			//out: void					
			//desc: Clears the list of RenderNodes	
			void Clear();
			//in: void
			//out: RenderNode*
			//	The Head RenderNode of the list of RenderNodes
			//desc: Gets the Head of the RenderNode list
			const RenderNode* getHead();
		};
	}
}
