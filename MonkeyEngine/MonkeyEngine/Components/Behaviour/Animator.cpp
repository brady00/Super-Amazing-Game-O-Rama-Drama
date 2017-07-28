#include "Animator.h"


namespace MonkeyEngine
{
	namespace MEObject
	{
		void Animator::Update()
		{
			if (m_Animations.Update())
				m_pBlender->Play(m_Animations.m_sNextAnimation, m_Animations.m_sCurrentAnimation, m_Animations.m_fCurrentAnimationElapsedTime, m_Animations.m_fNextAnimationElapsedTime, m_Animations.m_bNextAnimLooping);
		}
	}
}