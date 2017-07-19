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

		class Animation : public Behaviour
		{
		public:
			std::vector<Joint> mJoints;
			float mTimePassed;
			bool mLooping;
		};
	}
}
