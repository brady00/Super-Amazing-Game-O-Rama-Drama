#include "InputLayoutManager.h"
#include <fstream>

namespace MonkeyEngine
{
	namespace MERenderer
	{
		
		InputLayoutManager::InputLayoutManager(void)
		{
			for (VertexFormat index = VertexFormat(0); index < eVERTEX_MAX; index = VertexFormat(index + 1))
				m_pInputLayouts[index] = 0;
		}

		InputLayoutManager::~InputLayoutManager(void)
		{
			for (unsigned int i = 0; i < eVERTEX_MAX; i = i++)
			{
				if (m_pInputLayouts[i])
				{
					m_pInputLayouts[i]->Release();
					m_pInputLayouts[i] = 0;
				}
			}
		}

		InputLayoutManager* InputLayoutManager::GetInstance()
		{
			static InputLayoutManager m_pInstance;
			return &m_pInstance;
		}

		void InputLayoutManager::CreateLayouts(ID3D11Device* d3Device)
		{
			// VERTEX_POS
			std::ifstream load;
			load.open("Assets/ShaderCSO/POS_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			size_t vs_byte_code_size = size_t(load.tellg());
			char *vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POS_numElements = 1;
			D3D11_INPUT_ELEMENT_DESC vertexPosDesc[VERTEX_POS_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			d3Device->CreateInputLayout(vertexPosDesc, VERTEX_POS_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POS]);
			delete[] vs_byte_code;
			vs_byte_code_size = 0;

			// VERTEX_POSCOLOR
			load.open("Assets/ShaderCSO/POSCOLOR_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSCOLOR_numElements = 2;
			D3D11_INPUT_ELEMENT_DESC vertePosColorxDesc[VERTEX_POSCOLOR_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			d3Device->CreateInputLayout(vertePosColorxDesc, VERTEX_POSCOLOR_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSCOLOR]);
			delete[] vs_byte_code;

			//VERTEX_POSTEX
			load.open("Assets/ShaderCSO/POSTEX_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSTEX_numElements = 2;
			D3D11_INPUT_ELEMENT_DESC vertexPosTexDesc[VERTEX_POSTEX_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			};
			d3Device->CreateInputLayout(vertexPosTexDesc, VERTEX_POSTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSTEX]);
			delete[] vs_byte_code;

			//VERTEX_POSTEXCOLOR
			load.open("Assets/ShaderCSO/POSTEX_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSTEXCOLOR_numElements = 3;
			D3D11_INPUT_ELEMENT_DESC vertexPosTexColorDesc[VERTEX_POSTEXCOLOR_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			};
			d3Device->CreateInputLayout(vertexPosTexColorDesc, VERTEX_POSTEXCOLOR_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSTEXCOLOR]);
			delete[] vs_byte_code;

			//VERTEX_POSNORMTEX
			load.open("Assets/ShaderCSO/POSNORMTEX_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSNORMTEX_numElements = 3;
			D3D11_INPUT_ELEMENT_DESC vertexPosNormTexDesc[VERTEX_POSNORMTEX_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			//VERTEX_POSNORMTEXCOLOR
			load.open("Assets/ShaderCSO/POSNORMTEXCOLOR_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSNORMTEXCOLOR_numElements = 4;
			D3D11_INPUT_ELEMENT_DESC vertexPosNormTexColorDesc[VERTEX_POSNORMTEXCOLOR_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			d3Device->CreateInputLayout(vertexPosNormTexColorDesc, VERTEX_POSNORMTEXCOLOR_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSNORMTEXCOLOR]);
			delete[] vs_byte_code;

			//VERTEX_POSNORMTANTEX
			load.open("Assets/ShaderCSO/POSNORMTANTEX_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
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
			d3Device->CreateInputLayout(vertexPosNormTanTexDesc, VERTEX_POSNORMTANTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSNORMTANTEX]);
			delete[] vs_byte_code;

			//VERTEX_POSNORMTANTEXCOLOR
			load.open("Assets/ShaderCSO/POSNORMTANTEXCOLOR_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSNORMTANTEXCOLOR_numElements = 6;
			D3D11_INPUT_ELEMENT_DESC vertexPosNormTanTexColorDesc[VERTEX_POSNORMTANTEXCOLOR_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT", 1, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			d3Device->CreateInputLayout(vertexPosNormTanTexColorDesc, VERTEX_POSNORMTANTEXCOLOR_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSNORMTANTEXCOLOR]);
			delete[] vs_byte_code;

			//VERTEX_POSBONEWEIGHT
			load.open("Assets/ShaderCSO/POSBONEWEIGHT_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSBONEWEIGHT_numElements = 3;
			D3D11_INPUT_ELEMENT_DESC vertexPosBoneWeightDesc[VERTEX_POSBONEWEIGHT_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			d3Device->CreateInputLayout(vertexPosBoneWeightDesc, VERTEX_POSBONEWEIGHT_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHT]);
			delete[] vs_byte_code;

			//VERTEX_POSBONEWEIGHTCOLOR
			load.open("Assets/ShaderCSO/POSBONEWEIGHTCOLOR_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSBONEWEIGHTCOLOR_numElements = 4;
			D3D11_INPUT_ELEMENT_DESC vertexPosBoneWeightColorDesc[VERTEX_POSBONEWEIGHTCOLOR_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			d3Device->CreateInputLayout(vertexPosBoneWeightColorDesc, VERTEX_POSBONEWEIGHTCOLOR_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHTCOLOR]);
			delete[] vs_byte_code;

			//VERTEX_POSBONEWEIGHTNORMTEX
			load.open("Assets/ShaderCSO/POSBONEWEIGHTNORMTEX_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
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
			d3Device->CreateInputLayout(vertexPosBoneWeightNormTexDesc, VERTEX_POSBONEWEIGHTNORMTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHTNORMTEX]);
			delete[] vs_byte_code;

			//VERTEX_POSBONEWEIGHTNORMTEXCOLOR
			load.open("Assets/ShaderCSO/POSBONEWEIGHTNORMTEXCOLOR_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSBONEWEIGHTNORMTEXCOLOR_numElements = 6;
			D3D11_INPUT_ELEMENT_DESC vertexPosBoneWeightNormTexColorDesc[VERTEX_POSBONEWEIGHTNORMTEXCOLOR_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			d3Device->CreateInputLayout(vertexPosBoneWeightNormTexColorDesc, VERTEX_POSBONEWEIGHTNORMTEXCOLOR_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHTNORMTEXCOLOR]);
			delete[] vs_byte_code;

			//VERTEX_POSBONEWEIGHTNORMTANTEX
			load.open("Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSBONEWEIGHTNORMTANTEX_numElements = 8;
			D3D11_INPUT_ELEMENT_DESC vertexPosBoneWeightNormTanTexDesc[VERTEX_POSBONEWEIGHTNORMTANTEX_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT", 1, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			d3Device->CreateInputLayout(vertexPosBoneWeightNormTanTexDesc, VERTEX_POSBONEWEIGHTNORMTANTEX_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHTNORMTANTEX]);
			delete[] vs_byte_code;

			//VERTEX_POSBONEWEIGHTNORMTANTEX
			load.open("Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_VS.cso", std::ios_base::binary);
			load.seekg(0, std::ios_base::end);
			vs_byte_code_size = size_t(load.tellg());
			vs_byte_code = new char[vs_byte_code_size];
			load.seekg(0, std::ios_base::beg);
			load.read(vs_byte_code, vs_byte_code_size);
			load.close();

			const UINT VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR_numElements = 9;
			D3D11_INPUT_ELEMENT_DESC vertexPosBoneWeightNormTanTexColorDesc[VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR_numElements] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT", 1, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLORR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			d3Device->CreateInputLayout(vertexPosBoneWeightNormTanTexColorDesc, VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR_numElements, vs_byte_code, vs_byte_code_size, &m_pInputLayouts[eVERTEX_POSBONEWEIGHTNORMTANTEXCOLOR]);
			delete[] vs_byte_code;
		}

		ID3D11InputLayout* InputLayoutManager::GetInputLayout(VertexFormat index)
		{
			return m_pInputLayouts[index];
		}
	}
}
