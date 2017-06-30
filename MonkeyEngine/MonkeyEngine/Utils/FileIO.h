#pragma once
#include <string>
#include <vector>
#include "../GameObject/GameObject.h"
#include "../Renderer/Managers/InputLayoutManager.h"
#include "../Libraries/XMLParser/tinyxml2.h"
using namespace tinyxml2;

namespace MEFileIO
{
	class FileIO
	{
	private:
		//object
		static bool LoadGameObject(XMLElement* _ObjectRoot, MEObject::GameObject* _Object);
		//components
		//individual components
	public:
		FileIO();
		~FileIO();
		static bool LoadFBX(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
		static bool LoadOBJ(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
		//scene
		static bool LoadScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects);
	};
}

