#include "RenderShape.h"
#include "../Renderer.h"


namespace MERenderer
{
	RenderShape::RenderShape()
	{
	}


	RenderShape::~RenderShape()
	{
	}

	MEObject::RenderComponent* RenderShape::GetRenderComp()
	{
		return m_pRenderComponent;
	}

	MEObject::AnimationComponent* RenderShape::GetAnimationComp()
	{
		return m_pAnimationComponent;
	}

	void RenderShape::SetRenderComp(MEObject::RenderComponent* _RenderComp)
	{
		m_pRenderComponent = _RenderComp;
	}

	void RenderShape::SetAnimationComp(MEObject::AnimationComponent* _AnimationComp)
	{
		m_pAnimationComponent = _AnimationComp;
	}

	void RenderShape::Draw()
	{
		//setworld matrix
		//drawindexed5
	}

	bool RenderShape::Load(MEObject::RenderComponent* _RenderComp, MEObject::AnimationComponent* _AnimationComp)
	{
		if (m_pRenderComponent != _RenderComp)
		{
			if (m_pRenderComponent)
				delete m_pRenderComponent;
			m_pRenderComponent = _RenderComp;
		}
		if (m_pAnimationComponent != _AnimationComp)
		{
			if (m_pAnimationComponent)
				delete m_pAnimationComponent;
			m_pAnimationComponent = _AnimationComp;
		}
	}
}