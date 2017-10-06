#pragma once
#include "Behaviour.h"
#include "Animation/Blender.h"
#include "Animation/AnimationGraph.h"
namespace MonkeyEngine
{
	using namespace MERenderer;
	namespace MEObject
	{
		class Animator : public Behaviour 
		{
		private:
			AnimationGraph m_Animations;
			Blender* m_pBlender;
			std::vector<DirectX::XMFLOAT4X4> m_CurrentSkeleton;
		public:
			Animator() {};
			~Animator() {};
		private:
			void Update();
		};
	}
}
