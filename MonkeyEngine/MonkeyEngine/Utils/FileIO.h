#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"
#include "../Renderer/Managers/InputLayoutManager.h"
#include "../Libraries/XMLParser/tinyxml2.h"
using namespace tinyxml2;

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
		static bool LoadRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object);
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
	};
}

