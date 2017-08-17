#pragma once
#include <string>
#include "fbxsdk.h"
#pragma comment(lib, "libfbxsdk")

namespace MonkeyEngine
{
	namespace MEFileIO
	{
		class FBXLoader
		{
		private:
			bool InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);
			void DestroySdkObjects(FbxManager* pManager, bool pExitStatus);
		public:
			FBXLoader();
			~FBXLoader();
			bool LoadFBX(std::string _FileName);
		};
	}
}


