#pragma once
#include <vector>
#include <string>
#include "RenderStructures.h"
#include "Blender.h"

namespace MonkeyEngine
{
	//using namespace MEObject;
	namespace MERenderer
	{

		class AnimationManager
		{
		private:
			//std::vector<Animator> m_vAnimators;
			//std::vector<Blender> m_vBlenders;
			std::vector<Skeleton> m_vBindPoses;
		public:
			AnimationManager();
			~AnimationManager();
		};
	}
}
