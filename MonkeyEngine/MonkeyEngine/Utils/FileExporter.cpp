#include "FileExporter.h"
#include <fstream>
#include <sstream>
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
		std::vector<XMFLOAT3> temp_vertices;
		std::vector<XMFLOAT2> temp_uvs;
		std::vector<XMFLOAT3> temp_normals;
		std::string finalPath(_FileName);
		std::vector< unsigned int > vertexIndices;
		std::vector< unsigned int > normalIndices;
		std::vector< unsigned int > uvIndices;
		FILE* file = fopen(finalPath.c_str(), "r");
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
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
	
				vertexIndices.push_back(vertexIndex[0] - 1);
				vertexIndices.push_back(vertexIndex[1] - 1);
				vertexIndices.push_back(vertexIndex[2] - 1);
				uvIndices.push_back(uvIndex[0] - 1);
				uvIndices.push_back(uvIndex[1] - 1);
				uvIndices.push_back(uvIndex[2] - 1);
				normalIndices.push_back(normalIndex[0] - 1);
				normalIndices.push_back(normalIndex[1] - 1);
				normalIndices.push_back(normalIndex[2] - 1);
			}
		}
		_Indicies = new unsigned int[temp_vertices.size()];
		unsigned int polygonCount = (unsigned int)vertexIndices.size();
		bool isDuplicate;
		bool isCreated = false;
		unsigned int selectedVertex;
		_Verticies = new MERenderer::VERTEX_POSNORMTEX[temp_vertices.size()];
		for (unsigned int i = 0; i < polygonCount; i+=3)
		{
			for (int i2 = 0; i2 < 3; i2++)
			{
				isDuplicate = false;
				isCreated = false;
				selectedVertex = vertexIndices[i + i2];

				for (int i3 = 0; i3 < temp_vertices.size(); i3++)
				{
					XMFLOAT3 temppos = ((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i3].position;
					XMFLOAT3 temppos2 = temp_vertices[selectedVertex];
					XMFLOAT3 tempnorm = ((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i3].normal;
					XMFLOAT3 tempnorm2 = temp_normals[normalIndices[i + i2]];
					XMFLOAT2 tempuv = ((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i3].texcoord;
					XMFLOAT2 tempuv2 = temp_uvs[uvIndices[i + i2]];
					if (temppos.x == temppos2.x && temppos.y == temppos2.y && temppos.z == temppos2.z &&
						tempnorm.x == tempnorm2.x && tempnorm.y == tempnorm2.y && tempnorm.z == tempnorm2.z &&
						tempuv.x == tempuv2.x && tempuv.y == tempuv2.y)
					{
						_Indicies[selectedVertex] = i3;
						isDuplicate = true;
						break;
					}
				}

				if (isDuplicate)
					continue;

				_Indicies[selectedVertex] = selectedVertex;

				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[selectedVertex].position = temp_vertices[selectedVertex];
				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[selectedVertex].normal = temp_normals[normalIndices[i + i2]];
				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[selectedVertex].texcoord = temp_uvs[uvIndices[i + i2]];
				_NumVerticies++;
			}
		}
		_NumIndicies = (unsigned int)temp_vertices.size();
		std::ofstream out;
		out.open(filepart + std::string(".Bobj"));
		if (out.is_open())
		{
			out.write((const char*)& _NumVerticies, sizeof(unsigned int));
			for(unsigned int i = 0; i < _NumVerticies; i++)
				out.write((const char*)&(_Verticies[i]), sizeof(MERenderer::VERTEX_POSNORMTEX));
			out.write((const char*)& _NumIndicies, sizeof(unsigned int));
			for (unsigned int i = 0; i < _NumIndicies; i++)
				out.write((const char*)(&_Indicies[i]), sizeof(unsigned int));
			out.close();
		}
		else
			return false;
		return true;
	}
}