#pragma once
#include "RenderNode.h"
#include <DirectXMath.h>
namespace MEObject
{
	class RenderComponent;
	class AnimationComponent;
}
namespace MERenderer
{
	class RenderShape : public RenderNode
	{
	private:
		DirectX::XMFLOAT4X4 m_XMWorldMatrix;
		MEObject::RenderComponent* m_pRenderComponent;
		MEObject::AnimationComponent* m_pAnimationComponent;
	public:
		RenderShape();
		~RenderShape();
		MEObject::RenderComponent* GetRenderComp();
		MEObject::AnimationComponent* GetAnimationComp();
		void SetRenderComp(MEObject::RenderComponent* _RenderComp);
		void SetAnimationComp(MEObject::AnimationComponent* _AnimationComp);
		void Draw();
		bool Load(MEObject::RenderComponent* _RenderComp, MEObject::AnimationComponent* _AnimationComp);
	};


}