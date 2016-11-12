#include "RenderNode.h"



namespace MERenderer
{
	RenderNode::RenderNode()
	{

	}


	RenderNode::~RenderNode()
	{

	}

	void RenderNode::Draw()
	{

	}

	RenderNode* RenderNode::GetNext()
	{ 
		return m_pNext; 
	}

	void RenderNode::SetNext(RenderNode* _Next)
	{
		m_pNext = _Next;
	}

}