#pragma once
#include "../../Components/Behaviour/Animation.h"
#include <unordered_map>
namespace MonkeyEngine
{
	using namespace MEObject;
	namespace MERenderer
	{
		struct Node;	// Forward Declaration

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
			float m_fCurrentAnimationElapsedTime;
			float m_fNextAnimationElapsedTime;

		public:
			AnimationGraph();
			~AnimationGraph();
			bool Update();
			std::string m_sCurrentAnimation;
			std::string m_sNextAnimation;
		};
	}
}
