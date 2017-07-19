#pragma once
#include <DirectXMath.h>
#include "fbxsdk.h"
#pragma comment(lib, "libfbxsdk")
using namespace DirectX;
namespace MonkeyEngine
{
	namespace MERenderer
	{
		struct BlendingIndexWeightPair
		{
			unsigned int mBlendingIndex;
			double mBlendingWeight;

			BlendingIndexWeightPair() :
				mBlendingIndex(0),
				mBlendingWeight(0)
			{}
		};

		struct CtrlPoint
		{
			XMFLOAT3 mPosition;
			std::vector<BlendingIndexWeightPair> mBlendingInfo;

			CtrlPoint()
			{
				mBlendingInfo.reserve(4);
			}
		};

		struct Triangle
		{
			std::vector<unsigned int> mIndices;
			std::string mMaterialName;
			unsigned int mMaterialIndex;

			bool operator<(const Triangle& rhs)
			{
				return mMaterialIndex < rhs.mMaterialIndex;
			}
		};
	}
}