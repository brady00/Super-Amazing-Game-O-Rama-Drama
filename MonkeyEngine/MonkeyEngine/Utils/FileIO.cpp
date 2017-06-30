#include "FileIO.h"
#include <fstream>
#include "ComponentObjectFactory.h"
using namespace DirectX;
namespace MEFileIO
{
	const std::unordered_map<std::string, compFuntion> FileIO::componentFunctions =
	{
		{"Transform", &FileIO::LoadTranform},
		{"Renderer", &FileIO::LoadRenderer}
	};

	const std::unordered_map<std::string, MEObject::GameObject::COMPONENT_ID> FileIO::componentIDS =
	{
		{ "Transform", MEObject::GameObject::COMPONENT_ID::eTransform },
		{ "Renderer", MEObject::GameObject::COMPONENT_ID::eCompRenderer }
	};

	FileIO::FileIO()
	{

	}

	FileIO::~FileIO()
	{

	}

	bool FileIO::LoadFBX(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
	{
		return true;
	}

	bool FileIO::LoadOBJ(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
	{
		std::string filepart;
		std::ifstream FileIn;
		filepart.append(_FileName.c_str(), _FileName.length() - 4);
		FileIn.open(filepart + ".Bobj", std::ios_base::binary);
		if (FileIn.is_open())
		{
			FileIn.read((char*)& _NumVerticies, sizeof(unsigned int));
			_Verticies = new MERenderer::VERTEX_POSNORMTEX[_NumVerticies];
			for (unsigned int i = 0; i < _NumVerticies; i++)
			{
				FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position), sizeof(DirectX::XMFLOAT3));
				FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal), sizeof(DirectX::XMFLOAT3));
				FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord), sizeof(DirectX::XMFLOAT2));
			}
			return true;
		}
		std::string finalPath(_FileName);
		std::vector<XMFLOAT3> temp_vertices;
		std::vector<XMFLOAT2> temp_uvs;
		std::vector<XMFLOAT3> temp_normals;
		std::vector< unsigned int > vertexIndices;
		std::vector< unsigned int > normalIndices;
		std::vector< unsigned int > uvIndices;
		FILE* file = nullptr;
		fopen_s(&file, finalPath.c_str(), "r");
		if (file == NULL)
			return false;
		while (true)
		{
			char lineheader[128];
			int res = fscanf_s(file, "%s", lineheader, 128);
			if (res == EOF)
				break;

			if (strcmp(lineheader, "v") == 0)
			{
				XMFLOAT3 vertex;
				fscanf_s(file, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineheader, "vt") == 0)
			{
				XMFLOAT2 vertexuv;
				fscanf_s(file, "%f %f\n", &vertexuv.x, &vertexuv.y);
				vertexuv.x = vertexuv.x;
				vertexuv.y = 1 - vertexuv.y;
				temp_uvs.push_back(vertexuv);
			}
			else if (strcmp(lineheader, "vn") == 0)
			{
				XMFLOAT3 vertexn;
				fscanf_s(file, "%f %f %f \n", &vertexn.x, &vertexn.y, &vertexn.z);
				temp_normals.push_back(vertexn);
			}
			else if (strcmp(lineheader, "f") == 0)
			{
				std::string m_vertex1, m_vertex2, m_vertex3;
				unsigned int m_vertexindex[3], m_UVIndex[3], normalIndex[3];
				int matches = fscanf_s(file, " %i/%i/%i %i/%i/%i %i/%i/%i \n", 
					&m_vertexindex[0], &m_UVIndex[0], &normalIndex[0], 
					&m_vertexindex[1], &m_UVIndex[1], &normalIndex[1],
					&m_vertexindex[2], &m_UVIndex[2], &normalIndex[2]);
				if (matches != 9)
					return false;

				vertexIndices.push_back(m_vertexindex[0] - 1);
				vertexIndices.push_back(m_vertexindex[1] - 1);
				vertexIndices.push_back(m_vertexindex[2] - 1);
				normalIndices.push_back(normalIndex[0] - 1);
				normalIndices.push_back(normalIndex[1] - 1);
				normalIndices.push_back(normalIndex[2] - 1);
				uvIndices.push_back(m_UVIndex[0] - 1);
				uvIndices.push_back(m_UVIndex[1] - 1);
				uvIndices.push_back(m_UVIndex[2] - 1);
			}
		}
		_Verticies = new MERenderer::VERTEX_POSNORMTEX[vertexIndices.size()];
		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position = temp_vertices[vertexIndices[i]];
			((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal = temp_normals[normalIndices[i]];
			((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord = temp_uvs[uvIndices[i]];
		}

		_NumVerticies = (unsigned int)vertexIndices.size();
		_NumIndicies = 0;

		std::ofstream out;
		out.open(filepart + std::string(".Bobj"), std::ios_base::binary);
		if (out.is_open())
		{
			out.write((const char*)& _NumVerticies, sizeof(unsigned int));
			for (unsigned int i = 0; i < _NumVerticies; i++)
			{
				out.write((const char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position), sizeof(DirectX::XMFLOAT3));
				out.write((const char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal), sizeof(DirectX::XMFLOAT3));
				out.write((const char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord), sizeof(DirectX::XMFLOAT2));
			}
			out.close();
		}
		else
			return false;
		return true;
	}

	bool FileIO::LoadScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(_FileName.c_str());
		XMLElement* root = doc.FirstChildElement();
		if (!root)
			return false;
		XMLElement* child = root->FirstChildElement();
		while (child)
		{
			switch (child->Name()[0])
			{
				//Scene Specific data
			case 'G':
			{
				//Objects
				MEObject::GameObject* Object = new MEObject::GameObject;
				LoadGameObject(child, Object);
			}
			default:
				break;
			}
			child = child->NextSiblingElement();
		}
		return true;
	}

	bool FileIO::LoadGameObject(XMLElement* _ObjectRoot, MEObject::GameObject* _Object)
	{
		XMLElement* child = _ObjectRoot->FirstChildElement();
		while (child)
		{
			MEObject::Component* comp = nullptr;
			if (componentFunctions.at(std::string(child->Name()))(child, comp))
				_Object->AddComponent(comp, componentIDS.at(std::string(child->Name())));
			child = child->NextSiblingElement();
		}
		_Object->SetActive(_ObjectRoot->BoolAttribute("Active"));
		_Object->SetLayer(_ObjectRoot->IntAttribute("Layer"));
		_Object->SetName(_ObjectRoot->Attribute("Name"));
		_Object->SetStatic(_ObjectRoot->BoolAttribute("Static"));
		return true;
	}

	bool FileIO::LoadTranform(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
	{
		XMFLOAT3 pos, rot, scale;
		XMLElement* child = _ObjectRoot->FirstChildElement();
		if (child && !strcmp(child->Name(), "Position"))
		{
			pos.x = child->FloatAttribute("X");
			pos.y = child->FloatAttribute("Y");
			pos.z = child->FloatAttribute("Z");
		}
		else
			return false;
		child = child->NextSiblingElement();
		if (child && !strcmp(child->Name(), "Rotation"))
		{
			rot.x = child->FloatAttribute("X");
			rot.y = child->FloatAttribute("Y");
			rot.z = child->FloatAttribute("Z");
		}
		else
			return false;
		child = child->NextSiblingElement();
		if (child && !strcmp(child->Name(), "Scale"))
		{
			scale.x = child->FloatAttribute("X");
			scale.y = child->FloatAttribute("Y");
			scale.z = child->FloatAttribute("Z");
		}
		else
			return false;
		_Object = new MEObject::Transform(pos, rot, scale);
		return true;
	}
	bool FileIO::LoadRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
	{
		return false;
	}
}