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
		struct BindPose
		{
			std::vector<Joint> mJoints;
		};

		class AnimationManager
		{
		private:
			std::vector<Animator> m_vAnimators;
			std::vector<Blender> m_vBlenders;
			std::vector<BindPose> m_vBindPoses;
		public:
			AnimationManager();
			~AnimationManager();
		};
	}
}
