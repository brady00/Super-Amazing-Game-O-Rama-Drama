#include "RenderShape.h"
#include "../Renderer.h"
#include "../Managers/ConstantBufferManager.h"

namespace MERenderer
{
	RenderShape::RenderShape() : m_pRenderComponent(nullptr), m_pAnimationComponent(nullptr)
	{
		m_XMWorldMatrix = XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
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
		cbPerObject temp = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetBufferValue();
		temp.World = m_XMWorldMatrix;
		ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().Update(&temp, sizeof(temp));
		//drawindexed
		Renderer::m_d3DeviceContext->DrawIndexed(0, 0, 0);
	}

	bool RenderShape::Load(MEObject::RenderComponent* _RenderComp, MEObject::AnimationComponent* _AnimationComp)
	{
		if (_RenderComp == nullptr && _AnimationComp == nullptr)
			return false;
		if (m_pRenderComponent != _RenderComp)
		{
			//if (m_pRenderComponent)
			//	delete m_pRenderComponent;
			m_pRenderComponent = _RenderComp;
		}
		if (m_pAnimationComponent != _AnimationComp)
		{
			//if (m_pAnimationComponent)
			//	delete m_pAnimationComponent;
			m_pAnimationComponent = _AnimationComp;
		}
		return true;
	}
}