#include "RenderSet.h"
#include "RenderNode.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{
		RenderSet::RenderSet() : m_pHead(nullptr)
		{

		}


		RenderSet::~RenderSet()
		{
			while (m_pHead != nullptr)
			{
				RenderNode* temp = m_pHead->GetNext();
				delete m_pHead;
				m_pHead = temp;
			}
		}

		void RenderSet::Draw()
		{
			RenderNode* draw = m_pHead;
			while (draw != nullptr)
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

		const RenderNode* RenderSet::getHead()
		{
			return m_pHead;
		}
	}
}