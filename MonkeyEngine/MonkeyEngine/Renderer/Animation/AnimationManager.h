#pragma once
#include <vector>
#include <string>
#include "FBXClasses.h"
#include "../../Components/Behaviour/Animation.h"
#include "../../Components/Behaviour/Animator.h"
#include "Blender.h"

namespace MonkeyEngine
{
	using namespace MEObject;
	namespace MERenderer
	{

		class AnimationManager
		{
		private:
			std::vector<Animator> m_vAnimators;
			std::vector<Blender> m_vBlenders;
			std::vector<Skeleton> m_vBindPoses;
		public:
			AnimationManager();
			~AnimationManager();
		};
	}
}
