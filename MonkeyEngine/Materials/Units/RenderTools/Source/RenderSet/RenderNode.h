#pragma once
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderNode
		{
		private:
			RenderNode* m_pNext;
		public:
			RenderNode();
			virtual ~RenderNode();
			RenderNode* GetNext();
			void SetNext(RenderNode* _Next);
			virtual void Draw(ID3D11DeviceContext* d3DeviceContext) = 0;
		};
	}
}

