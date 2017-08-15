#pragma once
#include "Behaviour.h"
#include "../../Renderer/Animation/FBXClasses.h"
namespace MonkeyEngine
{
	namespace MEObject
	{

		struct Keyframe
		{
			FbxLongLong mFrameNum;
			FbxAMatrix mGlobalTransform;
			Keyframe* mNext;

			Keyframe() :
				mNext(nullptr)
			{}
		};
		struct Bone
		{
			std::string mName;
			XMFLOAT4X4 Offset;
			XMFLOAT4X4 Local;
			int mParentIndex;
			XMFLOAT4X4 InverseBindpose;
		};

		struct Joint
		{
			std::string mName;
			int mParentIndex;
			FbxAMatrix mGlobalBindposeInverse;
			Keyframe* mAnimation;
			FbxNode* mNode;

			Joint() :
				mNode(nullptr),
				mAnimation(nullptr)
			{
				mGlobalBindposeInverse.SetIdentity();
				mParentIndex = -1;
			}

			~Joint()
			{
				while (mAnimation)
				{
					Keyframe* temp = mAnimation->mNext;
					delete mAnimation;
					mAnimation = temp;
				}
			}
		};

		class Skeleton
		{
		public:
			std::vector<Bone> mJoints;
		};

		class Animation : public Behaviour
		{
		public:
			std::vector<Joint> mJoints;
			float mTimePassed;
			float mDuration;
			bool mLooping;
			std::string mName;
		};
	}
}
