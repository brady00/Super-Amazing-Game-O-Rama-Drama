#pragma once

namespace MERenderer
{
	class RenderNode;
	class RenderSet
	{
	private:
		RenderNode* m_pHead;
	public:
		RenderSet();
		~RenderSet();

		void Draw();
		void AddNode(RenderNode* _Node);
	};
}

