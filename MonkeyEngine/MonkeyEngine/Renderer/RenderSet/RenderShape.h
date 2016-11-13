#pragma once
#include "RenderNode.h"
namespace MERenderer
{
	class RenderShape : public RenderNode
	{
	private:

	public:
		RenderShape();
		~RenderShape();
		void* GetRenderComp();
		void* GetAnimationComp();
		void SetRenderComp(void* _RenderComp);
		void SetAnimationComp(void* _AnimationComp);
	};


}