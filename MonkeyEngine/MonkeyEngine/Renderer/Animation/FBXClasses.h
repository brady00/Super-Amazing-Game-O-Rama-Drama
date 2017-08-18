#pragma once
#include <DirectXMath.h>
#include "fbxsdk.h"
#pragma comment(lib, "libfbxsdk")
using namespace DirectX;
namespace MonkeyEngine
{
	namespace MERenderer
	{
		struct CtrlPoint
		{
			XMFLOAT3 mPosition;
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