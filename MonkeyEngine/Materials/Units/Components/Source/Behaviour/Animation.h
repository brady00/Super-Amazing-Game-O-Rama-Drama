#pragma once
#include "Behaviour.h"
#pragma warning(disable: 4793)
#include <DirectXMath.h>
#include "RenderStructures.h"
using namespace DirectX;
namespace MonkeyEngine
{
	namespace MEObject
	{
		class Animation : public Behaviour
		{
		public:
			std::vector<MERenderer::Keyframe*> mKeyFrames;
			float mTimePassed;
			int mFrameCount;
			bool mLooping;
			std::string AnimationName;
		};
	}
}
