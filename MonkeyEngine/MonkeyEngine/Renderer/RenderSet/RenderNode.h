#pragma once
#include <d3d11.h>
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
		virtual void Draw() = 0;
	};
}

