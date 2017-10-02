#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"
#include "../Engine Base/Settings/Settings.h"
#include "../Components/Renderer/CompRenderer.h"
#include "../Renderer/Managers/InputLayoutManager.h"
#include "../Libraries/XMLParser/tinyxml2.h"
#include "FBXLoader.h"
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
			static bool LoadFBX(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies, Material*& _Material, Skeleton& _Skelton);
			static bool LoadOBJ(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
			//scene
			static void LoadScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects, float& percentLoaded, bool& Success);
			// Settings
			static bool OutputSettings(std::string _FileName, std::vector<SettingData*> _SettingData);
			static bool LoadSettings(std::string _FileName, std::vector<SettingData*> &_SettingData);
		private:
			//components
			static const std::unordered_map<std::string, compFuntion> componentFunctions;
			static const std::unordered_map<std::string, MEObject::GameObject::COMPONENT_ID> componentIDS;

			//static void ProcessJointsAndAnimations(FbxNode* inNode);
		};
	}
}

