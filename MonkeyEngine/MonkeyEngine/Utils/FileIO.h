#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"
#include "../Engine Base/Settings/Settings.h"
#include "../Components/Renderer/CompRenderer.h"
#include "../Renderer/Managers/InputLayoutManager.h"
#include "../Libraries/XMLParser/tinyxml2.h"
#include "../Renderer/Animation/AnimationManager.h"
using namespace tinyxml2;
namespace MonkeyEngine
{
	using namespace MERenderer;
	namespace MEFileIO
	{
		typedef bool(*compFuntion)(XMLElement*, MEObject::Component*&);
		class FileIO
		{
		private:
			//object
			static bool LoadGameObject(XMLElement* _ObjectRoot, MEObject::GameObject* _Object);
			//individual components
			static bool LoadTranform(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
			static bool LoadMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
			static bool LoadSkinnedMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
		public:
			FileIO();
			~FileIO();
			static bool LoadFBX(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies, MEObject::Material*& _Material);
			static bool LoadOBJ(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
			//scene
			static bool LoadScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects);
			// Settings
			static bool OutputSettings(std::string _FileName, std::vector<SettingData*> _SettingData);
			static bool LoadSettings(std::string _FileName, std::vector<SettingData*> &_SettingData);
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
			static void CalculateModelVectors();
			static void CalculateTangentBinormal(MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX vertex1, MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX vertex2, MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX vertex3, XMFLOAT3& tangent, XMFLOAT3& binormal);
			static void CalculateNormal(XMFLOAT3 tangent, XMFLOAT3 binormal, XMFLOAT3& normal);
			//FBX Loading Variables
			static FbxManager* m_fbxManager;
			static FbxScene* m_fbxScene;
			static bool m_bHasAnimation;
			static std::vector<CtrlPoint*> m_mControlPoints;
			static unsigned int m_uiTriangleCount;
			static std::vector<Triangle> m_vTriangles;
			static std::vector<MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX> m_vVertices;
			static Skeleton m_Skeleton;
			static std::vector<Animation> m_Animations;
			static std::unordered_map<unsigned int, MEObject::Material*> m_mMaterialLookUp;
			static FbxLongLong m_lAnimationLength;
			static std::string m_sAnimationName;

		};
	}
}

