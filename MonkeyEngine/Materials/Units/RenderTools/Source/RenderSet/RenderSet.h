#pragma once
#include <d3d11.h>
namespace MonkeyEngine
{
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

			void Draw(ID3D11DeviceContext* d3DeviceContext);
			void AddNode(RenderNode* _Node);
			const RenderNode* getHead();
		};
	}
}
