#pragma once
#include <string>
#include "../Renderer/Managers/InputLayoutManager.h"
#include <vector>
namespace MEExporter
{
	class FileExporter
	{
	private:

	public:
		FileExporter();
		~FileExporter();
		static bool LoadFBX(std::string _FileName, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
		static bool LoadOBJ(std::string _FileName, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies);
	};
}

