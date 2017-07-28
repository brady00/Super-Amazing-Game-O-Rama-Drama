#pragma once
#include "../../Components/Behaviour/Animation.h"
#include <unordered_map>
namespace MonkeyEngine
{
	using namespace MEObject;
	namespace MERenderer
	{
		struct Node;
		struct Edge
		{
			Node* m_pNext;
			bool(*m_fCondition)(void);
		};
		struct Node
		{
			std::vector<Edge> m_vEdges;
			Animation* m_pAnimation;
		};
		class AnimationGraph
		{
		private:
			Node* m_pBaseAnimation;
			std::unordered_map<std::string, Node*> m_vAnimations;

		public:
			AnimationGraph();
			~AnimationGraph();
			bool Update();
			std::string m_sCurrentAnimation;
			std::string m_sNextAnimation;
			float m_fCurrentAnimationElapsedTime;
			float m_fNextAnimationElapsedTime;
			bool m_bCurrentAnimLooping;
			bool m_bNextAnimLooping;
		};
	}
}
