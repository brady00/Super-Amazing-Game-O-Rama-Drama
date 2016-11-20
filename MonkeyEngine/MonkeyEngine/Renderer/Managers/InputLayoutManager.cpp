#include "InputLayoutManager.h"
#include <fstream>
#include "../Renderer.h"

namespace MERenderer
{
	std::string MERenderer::VertexFormatString[] = 
	{ 
		"VERTEX_POS", 
		"VERTEX_POSCOLOR", 
		"VERTEX_POSTEX",
		"VERTEX_POSNORMTEX", 
		"VERTEX_POSNORMTANTEX", 
		"VERTEX_POSBONEWEIGHT", 
		"VERTEX_POSBONEWEIGHTNORMTEX",
		"VERTEX_POSBONEWEIGHTNORMTANTEX" 
	};
	InputLayoutManager* InputLayoutManager::m_pInstance = nullptr;
	InputLayoutManager::InputLayoutManager(void)
	{
		for (VertexFormat index = VertexFormat(0); index < eVERTEX_MAX; index = VertexFormat(index + 1))
			m_pInputLayouts[index] = 0;
	}

	InputLayoutManager::~InputLayoutManager(void)
	{
		for (unsigned int i = 0; i < eVERTEX_MAX; i = i++)
			ReleaseCOM(m_pInputLayouts[i]);
	}

	InputLayoutManager* InputLayoutManager::GetInstance()
	{
		if (0 == m_pInstance)
		{
			m_pInstance = new InputLayoutManager;
			m_pInstance->Initialize();
		}
		return m_pInstance;
	}
	void InputLayoutManager::DeleteInstance()
	{
		delete m_pInstance;
		m_pInstance = 0;
	}

	void InputLayoutManager::Initialize()
	{
		std::ifstream load;
		load.open("POS_VS.cso", std::ios_base::binary);
		//load.open("POS_VS.cso",std::ios_base::binary);
		load.seekg(0, std::ios_base::end);
		size_t vs_byte_code_size = size_t(load.tellg());
		char *vs_byte_code = new char[vs_byte_code_size];
		load.seekg(0, std::ios_base::beg);
		load.read(vs_byte_code, vs_byte_code_size);
		load.close();

		// VERTEX_POS
		const UINT VERTEX_POS_numElements = 1;
		D3D11_INPUT_ELEMENT_DESC vertexPosDesc[VERTEX_POS_numElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		Renderer::m_d3Device->CreateInputLayout(vertexPosDesc, VERTEX_POS_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POS]);
		delete[] vs_byte_code;

		// VERTEX_POSCOLOR
		load.open("POSCOLOR_VS.cso",std::ios_base::binary);
		load.seekg(0,std::ios_base::end);
		vs_byte_code_size = size_t(load.tellg());
		vs_byte_code = new char[vs_byte_code_size];
		load.seekg(0,std::ios_base::beg);
		load.read(vs_byte_code, vs_byte_code_size);
		load.close();

		const UINT VERTEX_POSCOLOR_numElements = 2;
		D3D11_INPUT_ELEMENT_DESC vertePosColorxDesc[VERTEX_POSCOLOR_numElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		Renderer::m_d3Device->CreateInputLayout(vertePosColorxDesc, VERTEX_POSCOLOR_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSCOLOR]);
		delete[] vs_byte_code;

		//VERTEX_POSTEX
		load.open("POSTEX_VS.cso",std::ios_base::binary);
		load.seekg(0,std::ios_base::end);
		vs_byte_code_size = size_t(load.tellg());
		vs_byte_code = new char[vs_byte_code_size];
		load.seekg(0,std::ios_base::beg);
		load.read(vs_byte_code, vs_byte_code_size);
		load.close();

		const UINT VERTEX_POSTEX_numElements = 2;
		D3D11_INPUT_ELEMENT_DESC vertexPosTexDesc[VERTEX_POSTEX_numElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		};
		Renderer::m_d3Device->CreateInputLayout(vertexPosTexDesc, VERTEX_POSTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSTEX]);
		delete[] vs_byte_code;

		//VERTEX_POSNORMTEX
		load.open("POSNORMTEX_VS.cso",std::ios_base::binary);
		load.seekg(0,std::ios_base::end);
		vs_byte_code_size = size_t(load.tellg());
		vs_byte_code = new char[vs_byte_code_size];
		load.seekg(0,std::ios_base::beg);
		load.read(vs_byte_code, vs_byte_code_size);
		load.close();

		const UINT VERTEX_POSNORMTEX_numElements = 3;
		D3D11_INPUT_ELEMENT_DESC vertexPosNormTexDesc[VERTEX_POSNORMTEX_numElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		Renderer::m_d3Device->CreateInputLayout(vertexPosNormTexDesc, VERTEX_POSNORMTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSNORMTEX]);
		delete[] vs_byte_code;

		//VERTEX_POSNORMTANTEX
		load.open("POSNORMTANTEX_VS.cso",std::ios_base::binary);
		load.seekg(0,std::ios_base::end);
		vs_byte_code_size = size_t(load.tellg());
		vs_byte_code = new char[vs_byte_code_size];
		load.seekg(0,std::ios_base::beg);
		load.read(vs_byte_code, vs_byte_code_size);
		load.close();

		const UINT VERTEX_POSNORMTANTEX_numElements = 5;
		D3D11_INPUT_ELEMENT_DESC vertexPosNormTanTexDesc[VERTEX_POSNORMTANTEX_numElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 1, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		Renderer::m_d3Device->CreateInputLayout(vertexPosNormTanTexDesc, VERTEX_POSNORMTANTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSNORMTANTEX]);
		delete[] vs_byte_code;

		//VERTEX_POSBONEWEIGHT
		load.open("POSBONEWEIGHT_VS.cso",std::ios_base::binary);
		load.seekg(0,std::ios_base::end);
		vs_byte_code_size = size_t(load.tellg());
		vs_byte_code = new char[vs_byte_code_size];
		load.seekg(0,std::ios_base::beg);
		load.read(vs_byte_code, vs_byte_code_size);
		load.close();

		const UINT VERTEX_POSBONEWEIGHT_numElements = 3;
		D3D11_INPUT_ELEMENT_DESC vertexPosBoneWeightDesc[VERTEX_POSBONEWEIGHT_numElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		Renderer::m_d3Device->CreateInputLayout(vertexPosBoneWeightDesc, VERTEX_POSBONEWEIGHT_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHT]);
		delete[] vs_byte_code;


		//VERTEX_POSBONEWEIGHTNORMTEX
		load.open("POSBONEWEIGHTNORMTEX_VS.cso",std::ios_base::binary);
		load.seekg(0,std::ios_base::end);
		vs_byte_code_size = size_t(load.tellg());
		vs_byte_code = new char[vs_byte_code_size];
		load.seekg(0,std::ios_base::beg);
		load.read(vs_byte_code, vs_byte_code_size);
		load.close();

		const UINT VERTEX_POSBONEWEIGHTNORMTEX_numElements = 5;
		D3D11_INPUT_ELEMENT_DESC vertexPosBoneWeightNormTexDesc[VERTEX_POSBONEWEIGHTNORMTEX_numElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		Renderer::m_d3Device->CreateInputLayout(vertexPosBoneWeightNormTexDesc, VERTEX_POSBONEWEIGHTNORMTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHTNORMTEX]);
		delete[] vs_byte_code;

		//VERTEX_POSBONEWEIGHTNORMTANTEX
		load.open("POSBONEWEIGHTNORMTANTEX_VS.cso",std::ios_base::binary);
		load.seekg(0,std::ios_base::end);
		vs_byte_code_size = size_t(load.tellg());
		vs_byte_code = new char[vs_byte_code_size];
		load.seekg(0,std::ios_base::beg);
		load.read(vs_byte_code, vs_byte_code_size);
		load.close();

		const UINT VERTEX_POSBONEWEIGHTNORMTANTEX_numElements = 7;
		D3D11_INPUT_ELEMENT_DESC vertexPosBoneWeightNormTanTexDesc[VERTEX_POSBONEWEIGHTNORMTANTEX_numElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 1, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		Renderer::m_d3Device->CreateInputLayout(vertexPosBoneWeightNormTanTexDesc, VERTEX_POSBONEWEIGHTNORMTANTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHTNORMTANTEX]);
		delete[] vs_byte_code;
	}

	ID3D11InputLayout* InputLayoutManager::GetInputLayout(VertexFormat index)
	{
		return m_pInputLayouts[index];
	}
}
