#pragma once
#include "MemoryOverloads.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "GameObject/GameObject.h"
#include "tinyxml2.h"
#include "FBXLoader.h"
#include "Settings.h"
#include "Managers\InputLayoutManager.h"
using namespace tinyxml2;
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderMesh;
	}
	using namespace MERenderer;
	namespace MEFileIO
	{
		typedef bool(*compFuntion)(XMLElement*, MEObject::Component*&);
		class __declspec(dllexport) FileIO
		{
		private:
			//object
			static bool LoadGameObject(XMLElement* _ObjectRoot, MEObject::GameObject* _Object, float& percentLoaded, int ChildAmount);
			static bool SaveGameObject(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::GameObject* _Object);
			//individual components
			static bool LoadTranform(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
			static bool SaveTranform(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object);
			static bool LoadMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
			static bool SaveMeshRenderer(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object);
			static bool LoadSkinnedMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
			static bool SaveSkinnedMeshRenderer(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object);
			static bool LoadCamera(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
			static bool SaveCamera(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object);
			static bool LoadDebugCamera(XMLElement* _ObjectRoot);
			static bool SaveDebugCamera(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc);
			static bool LoadSkybox(XMLElement* _ObjectRoot, MEObject::Component* _Object);
			static bool SaveSkybox(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object);
			static bool LoadVertexBuffer(VertexFormat format, MERenderer::RenderMesh* mesh, Material* material);
		public:
			FileIO();
			~FileIO();
			static bool LoadFBX(std::string _FileName, MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies, Material*& _Material, Skeleton& _Skelton);
			static bool LoadOBJ(std::string _FileName, MERenderer::VERTEX_POSNORMTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
			//scene
			static void LoadScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects, float& percentLoaded, bool& Success);
			static bool SaveScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects);
			// Settings
			static bool OutputSettings(std::string _FileName, std::vector<SettingData*> _SettingData);
			static bool LoadSettings(std::vector<SettingData*> &_SettingData);
		private:
			//components
			static const std::unordered_map<std::string, compFuntion> componentFunctions;
			static const std::unordered_map<std::string, MEObject::GameObject::COMPONENT_ID> componentIDS;
		};
	}
}

