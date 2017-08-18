#pragma once
#include <string>
#include <vector>
#include "../Renderer/Animation/FBXClasses.h"
#include "../Renderer/Managers/VertexBufferManager.h"
#include "../Components/Behaviour/Animation.h"
#include "../Renderer/Containers/Material.h"
#include "fbxsdk.h"
#pragma comment(lib, "libfbxsdk")

namespace MonkeyEngine
{
	using namespace MEObject;
	using namespace MERenderer;
	namespace MEFileIO
	{
		class FBXLoader
		{
		private:
			bool InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);
			void DestroySdkObjects(FbxManager* pManager, bool pExitStatus);
			void DisplayContent(FbxScene* pScene);
			void DisplayContent(FbxNode* pNode, int depth);
			void DisplayMesh(FbxNode* pNode);
			void DisplayControlsPoints(FbxMesh* pMesh);
			void DisplayPolygons(FbxMesh* pMesh);
			void DisplayMaterial(FbxGeometry* pGeometry);
			void DisplayLink(FbxGeometry* pGeometry);
			int startingIndex;
		public:
			Material* m_Material;
			std::vector<unsigned int> m_Indices;
			std::vector<VERTEX_POSBONEWEIGHTNORMTANTEX> m_Verticies;
			std::vector<Animation*> m_Animations;
			Skeleton m_Skeleton;
			FBXLoader();
			~FBXLoader();
			bool LoadFBX(std::string _FileName);
		};
	}
}


