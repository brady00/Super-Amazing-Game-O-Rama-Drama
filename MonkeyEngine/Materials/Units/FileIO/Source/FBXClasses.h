#pragma once
#pragma warning(disable: 4793)
#include "Float3/Float3.h"
namespace MonkeyEngine
{
	using namespace MEMath;
	namespace MERenderer
	{
		struct CtrlPoint
		{
			Float3 mPosition;
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