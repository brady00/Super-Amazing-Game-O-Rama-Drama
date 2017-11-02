#include "stdafx.h"
#include "RenderNode.h"


namespace MonkeyEngine
{
	namespace MERenderer
	{
		RenderNode::RenderNode() : m_pNext(nullptr)
		{

		}


		RenderNode::~RenderNode()
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
}