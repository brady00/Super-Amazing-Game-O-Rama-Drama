#pragma once
#include "RenderNode.h"
#include <DirectXMath.h>
namespace MEObject
{
	class CompRenderer;
	class Animator;
}
namespace MERenderer
{
	class RenderShape : public RenderNode
	{
	private:
		DirectX::XMFLOAT4X4 m_XMWorldMatrix;
		MEObject::CompRenderer* m_pRenderComponent;
		MEObject::Animator* m_pAnimationComponent;
	public:
		RenderShape();
		~RenderShape();
		MEObject::CompRenderer* GetRenderComp();
		MEObject::Animator* GetAnimationComp();
		void SetRenderComp(MEObject::CompRenderer* _RenderComp);
		void SetAnimationComp(MEObject::Animator* _AnimationComp);
		void Draw();
		bool Load(MEObject::CompRenderer* _RenderComp, MEObject::Animator* _AnimationComp);
	};


}