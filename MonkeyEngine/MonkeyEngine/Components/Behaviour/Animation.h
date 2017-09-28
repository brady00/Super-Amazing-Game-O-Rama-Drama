#pragma once
#include "Behaviour.h"
#include "../../Renderer/Animation/FBXClasses.h"
namespace MonkeyEngine
{
	namespace MEObject
	{

		struct Keyframe
		{
			unsigned int mFrameNum;
			std::vector<XMFLOAT4X4> mOffsets;
		};
		struct Bone
		{
			std::string mName;
			XMFLOAT4X4 Offset;
			int mParentIndex;
			XMFLOAT4X4 Local;
			XMFLOAT4X4 InverseBindpose;
			FbxNode* pNode;
		};

		class Skeleton
		{
		public:
			std::vector<Bone> mJoints;
		};

		class Animation : public Behaviour
		{
		public:
			std::vector<Keyframe*> mKeyFrames;
			float mTimePassed;
			int mFrameCount;
			bool mLooping;
			std::string AnimationName;
		};
	}
}
