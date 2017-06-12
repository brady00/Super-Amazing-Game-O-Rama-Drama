#include "RenderShape.h"
#include "../Renderer.h"
#include "../Managers/ConstantBufferManager.h"

namespace MERenderer
{
	RenderShape::RenderShape() : m_pRenderComponent(nullptr), m_pAnimationComponent(nullptr)
	{
		m_XMWorldMatrix = XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 10, 1);
	}


	RenderShape::~RenderShape()
	{
		
	}

	MEObject::CompRenderer* RenderShape::GetRenderComp()
	{
		return m_pRenderComponent;
	}

	MEObject::Animator* RenderShape::GetAnimationComp()
	{
		return m_pAnimationComponent;
	}

	void RenderShape::SetRenderComp(MEObject::CompRenderer* _RenderComp)
	{
		m_pRenderComponent = _RenderComp;
	}

	void RenderShape::SetAnimationComp(MEObject::Animator* _AnimationComp)
	{
		m_pAnimationComponent = _AnimationComp;
	}

	void RenderShape::Draw()
	{
		cbPerObject temp = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetBufferValue();
		temp.world = m_XMWorldMatrix;
		ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().Update(&temp, sizeof(temp));
		ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetConstantBuffer();
		Renderer::m_d3DeviceContext->VSSetConstantBuffers(temp.REGISTER_SLOT, 1, &buf);
		//drawindexed
		if(true)
			Renderer::m_d3DeviceContext->Draw(13932, 0);
		else
			Renderer::m_d3DeviceContext->DrawIndexed(2383, 0, 0);
	}

	bool RenderShape::Load(MEObject::CompRenderer* _RenderComp, MEObject::Animator* _AnimationComp)
	{
		//if (_RenderComp == nullptr && _AnimationComp == nullptr)
		//	return false;
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