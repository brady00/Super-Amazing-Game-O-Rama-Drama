#include "RenderSet.h"
#include "RenderNode.h"


namespace MERenderer
{
	RenderSet::RenderSet()
	{

	}


	RenderSet::~RenderSet()
	{

	}

	void RenderSet::Draw()
	{
		RenderNode* draw = m_pHead;
		while (m_pHead != nullptr)
		{
			draw->Draw();
			draw = draw->GetNext();
		}
	}

	void RenderSet::AddNode(RenderNode* _Node)
	{
		_Node->SetNext(m_pHead);
		m_pHead = _Node;
	}
}