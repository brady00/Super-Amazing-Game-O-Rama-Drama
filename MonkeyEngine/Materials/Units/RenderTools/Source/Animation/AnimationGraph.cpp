#include "AnimationGraph.h"
#include "Time.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{
		AnimationGraph::AnimationGraph()
		{
		}


		AnimationGraph::~AnimationGraph()
		{
		}
		
		bool AnimationGraph::Update()
		{
			m_fCurrentAnimationElapsedTime += Time::DeltaTime;
			if (m_sNextAnimation != "")
				m_fNextAnimationElapsedTime += Time::DeltaTime;
			//m_vAnimations[m_sCurrentAnimation]->m_pAnimation->mTimePassed = m_fCurrentAnimationElapsedTime;
			Node* temp = m_vAnimations[m_sCurrentAnimation];
			for (unsigned int i = 0; i < temp->m_vEdges.size(); i++)
			{
				if (temp->m_vEdges[i].m_fCondition())
				{
					//m_sNextAnimation = temp->m_vEdges[i].m_pNext->m_pAnimation->AnimationName;
					m_fNextAnimationElapsedTime = 0.0f;
					//m_bNextAnimLooping = temp->m_vEdges[i].m_pNext->m_pAnimation->mLooping;
					return true;
				}
			}
			return false;
		}
	}
}