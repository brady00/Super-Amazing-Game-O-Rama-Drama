#pragma once
#include "MemoryOverloads.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "fbxsdk.h"
#include "FBXClasses.h"
#include "RenderStructures.h"
#include "Behaviour/Animation.h"
#include "RenderStructures.h"
namespace MonkeyEngine
{
	using namespace MEObject;
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
			void DisplayAnimation(FbxScene* pScene);
			void DisplayAnimation(Animation* pAnim, FbxAnimStack* pAnimStack, FbxScene* pScene);
			int startingIndex;
			int boneIndex;
			std::unordered_map<unsigned int, FbxNode*> BoneToNode;
		public:
			MERenderer::Material* m_Material;
			std::vector<unsigned int> m_Indices;
			std::vector<MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX> m_Verticies;
			std::vector<Animation*> m_Animations;
			MERenderer::Skeleton m_Skeleton;
			FBXLoader();
			~FBXLoader();
			bool LoadFBX(std::string _FileName);
		};
	}
}


