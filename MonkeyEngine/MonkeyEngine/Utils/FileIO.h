#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"
#include "../Components/Renderer/CompRenderer.h"
#include "../Renderer/Managers/InputLayoutManager.h"
#include "../Libraries/XMLParser/tinyxml2.h"
#include "fbxsdk.h"
#pragma comment(lib, "libfbxsdk")
using namespace DirectX;
using namespace tinyxml2;
namespace MonkeyEngine
{
	namespace MEFileIO
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

		struct Skeleton
		{
			std::vector<Joint> mJoints;
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

		typedef bool(*compFuntion)(XMLElement*, MEObject::Component*&);
		class FileIO
		{
		private:
			//object
			static bool LoadGameObject(XMLElement* _ObjectRoot, MEObject::GameObject* _Object);
			//individual components
			static bool LoadTranform(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
			static bool LoadMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
		public:
			FileIO();
			~FileIO();
			static bool LoadFBX(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
			static bool LoadOBJ(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
			//scene
			static bool LoadScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects);
		private:
			//components
			static const std::unordered_map<std::string, compFuntion> componentFunctions;
			static const std::unordered_map<std::string, MEObject::GameObject::COMPONENT_ID> componentIDS;

			//FBX Loading Functions
			static void ProcessSkeletonHierarchy(FbxNode* inRootNode);
			static void ProcessGeometry(FbxNode* inNode);
			static void ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex);
			static void ProcessControlPoints(FbxNode* inNode);
			static void ProcessJointsAndAnimations(FbxNode* inNode);
			static unsigned int FindJointIndexUsingName(const std::string& inJointName);
			static void ProcessMesh(FbxNode* inNode);
			static void ReadUV(FbxMesh* inMesh, int inCtrlPointIndex, int inTextureUVIndex, int inUVLayer, XMFLOAT2& outUV);
			static void ReadNormal(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outNormal);
			static void ReadBinormal(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outBinormal);
			static void ReadTangent(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outTangent);
			static void Optimize();
			static int FindVertex(const MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX& inTargetVertex, const std::vector<MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX>& uniqueVertices);
			static void AssociateMaterialToMesh(FbxNode* inNode);
			static void ProcessMaterials(FbxNode* inNode);
			static void ProcessMaterialAttribute(FbxSurfaceMaterial* inMaterial, unsigned int inMaterialIndex);
			static void ProcessMaterialTexture(FbxSurfaceMaterial* inMaterial, MEObject::Material* ioMaterial);
			//FBX Loading Variables
			static FbxManager* m_fbxManager;
			static FbxScene* m_fbxScene;
			static bool m_bHasAnimation;
			static std::unordered_map<unsigned int, CtrlPoint*> m_mControlPoints;
			static unsigned int m_uiTriangleCount;
			static std::vector<Triangle> m_vTriangles;
			static std::vector<MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX> m_vVertices;
			static Skeleton m_Skeleton;
			static std::unordered_map<unsigned int, MEObject::Material*> m_mMaterialLookUp;
			static FbxLongLong m_lAnimationLength;
			static std::string m_sAnimationName;

		};
	}
}

