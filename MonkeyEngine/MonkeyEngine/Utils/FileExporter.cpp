#include "FileExporter.h"
#include <fstream>
using namespace DirectX;
namespace MEExporter
{

	FileExporter::FileExporter()
	{

	}

	FileExporter::~FileExporter()
	{

	}

	bool FileExporter::LoadFBX(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
	{
		return true;
	}

	bool FileExporter::LoadOBJ(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
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
				FileIn.read((char*)&(_Verticies[i]), sizeof(MERenderer::VERTEX_POSNORMTEX));
			FileIn.read((char*)& _NumIndicies, sizeof(unsigned int));
			_Indicies = new unsigned int[_NumIndicies];
			for (unsigned int i = 0; i < _NumIndicies; i++)
				FileIn.read((char*)(&_Indicies[i]), sizeof(unsigned int));
			return true;
		}
		std::string finalPath(_FileName);
		std::vector<XMFLOAT3> temp_vertices;
		std::vector<XMFLOAT2> temp_uvs;
		std::vector<XMFLOAT3> temp_normals;
		std::vector< unsigned int > vertexIndices;
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
				int matches = fscanf_s(file, " %d/%d/%d %d/%d/%d %d/%d/%d \n", &m_vertexindex[0], &m_UVIndex[0], &normalIndex[0], &m_vertexindex[1], &m_UVIndex[1], &normalIndex[1], &m_vertexindex[2], &m_UVIndex[2], &normalIndex[2]);
				if (matches != 9)
					return false;

				vertexIndices.push_back(m_vertexindex[0]);
				vertexIndices.push_back(m_vertexindex[1]);
				vertexIndices.push_back(m_vertexindex[2]);
			}
		}
		switch (_VertexFormat)
		{
		case MERenderer::eVERTEX_POS:
			_Verticies = new MERenderer::VERTEX_POS[temp_vertices.size()];
			for (unsigned int i = 0; i < temp_vertices.size(); i++)
			{
				((MERenderer::VERTEX_POS*)_Verticies)[i].position = temp_vertices[i];
			}
			break;
		case MERenderer::eVERTEX_POSCOLOR:
			_Verticies = new MERenderer::VERTEX_POSCOLOR[temp_vertices.size()];
			for (unsigned int i = 0; i < temp_vertices.size(); i++)
			{
				((MERenderer::VERTEX_POSCOLOR*)_Verticies)[i].position = temp_vertices[i];
				((MERenderer::VERTEX_POSCOLOR*)_Verticies)[i].color = XMFLOAT4(1, 1, 1, 1);
			}
			break;
		case MERenderer::eVERTEX_POSTEX:
			_Verticies = new MERenderer::VERTEX_POSTEX[temp_vertices.size()];
			for (unsigned int i = 0; i < temp_vertices.size(); i++)
			{
				((MERenderer::VERTEX_POSTEX*)_Verticies)[i].position = temp_vertices[i];
				((MERenderer::VERTEX_POSTEX*)_Verticies)[i].texcoord = temp_uvs[i];
			}
			break;
		case MERenderer::eVERTEX_POSNORMTEX:
			_Verticies = new MERenderer::VERTEX_POSNORMTEX[temp_vertices.size()];
			for (unsigned int i = 0; i < temp_vertices.size(); i++)
			{
				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position = temp_vertices[i];
				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal = temp_normals[i];
				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord = temp_uvs[i];
			}
			break;
		case MERenderer::eVERTEX_POSNORMTANTEX:
		case MERenderer::eVERTEX_POSBONEWEIGHT:
		case MERenderer::eVERTEX_POSBONEWEIGHTNORMTEX:
		case MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX:
		case MERenderer::eVERTEX_MAX:
		default:
			return false;
		}

		_NumVerticies = (unsigned int)temp_vertices.size();
		_Indicies = new unsigned int[vertexIndices.size()];
		_NumIndicies = (unsigned int)vertexIndices.size();
		for (unsigned int i = 0; i < temp_vertices.size(); i++)
			_Indicies[i] = vertexIndices[i];
		std::string filepart;
		filepart.append(finalPath.c_str(), finalPath.length() - 4);
		std::ofstream out;
		out.open(filepart + std::string(".Bobj"));
		if (out.is_open())
		{
			out.write((char*)& _NumVerticies, sizeof(unsigned int));
			for (unsigned int i = 0; i < _NumVerticies; i++)
				out.write((char*)&(_Verticies[i]), sizeof(MERenderer::VERTEX_POSNORMTEX));
			out.write((char*)& _NumIndicies, sizeof(unsigned int));
			for (unsigned int i = 0; i < _NumIndicies; i++)
				out.write((char*)(&_Indicies[i]), sizeof(unsigned int));
			out.close();
		}
		else
			return false;
		return true;
	}
}