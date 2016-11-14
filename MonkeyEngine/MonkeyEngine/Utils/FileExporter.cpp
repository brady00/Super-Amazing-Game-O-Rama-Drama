#include "FileExporter.h"
using namespace DirectX;
namespace MEExporter
{

	FileExporter::FileExporter()
	{

	}


	FileExporter::~FileExporter()
	{

	}

	bool FileExporter::LoadFBX(std::string _FileName, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
	{
		return true;
	}

	bool FileExporter::LoadOBJ(std::string _FileName, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
	{
		std::string finalPath(_FileName);
		std::vector<XMFLOAT3> temp_vertices;
		std::vector<XMFLOAT2> temp_uvs;
		std::vector<XMFLOAT3> temp_normals;
		std::vector< unsigned int > vertexIndices;
		FILE* file = nullptr;
		fopen_s(&file, finalPath.c_str(), "r");
		if (file == NULL)
			return false;
		temp_vertices.reserve(99999);
		temp_uvs.reserve(99999);
		temp_normals.reserve(99999);
		vertexIndices.reserve(99999);
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
		_Verticies = new MERenderer::VERTEX_POSNORMTEX[temp_vertices.size()];
		_NumVerticies = (unsigned int)temp_vertices.size();
		for (unsigned int i = 0; i < temp_vertices.size(); i++)
		{
			((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position = temp_vertices[i];
			((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal = temp_normals[i];
			((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord = temp_uvs[i];
		}
		_Indicies = new unsigned int[vertexIndices.size()];
		_NumIndicies = (unsigned int)vertexIndices.size();
		for (unsigned int i = 0; i < temp_vertices.size(); i++)
			_Indicies[i] = vertexIndices[i];
		return true;
	}
}