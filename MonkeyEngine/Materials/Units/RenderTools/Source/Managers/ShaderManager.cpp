#include "ShaderManager.h"
#include <fstream>
namespace MonkeyEngine
{
	namespace MERenderer
	{

		ShaderManager::ShaderManager()
		{

		}


		ShaderManager::~ShaderManager()
		{
			for (unsigned int i = 0; i < eShader_VS_MAX; i++)
			{
				if (m_d3VertexShaders[i])
				{
					m_d3VertexShaders[i]->Release();
					m_d3VertexShaders[i] = 0;
				}
			}
			for (unsigned int i = 0; i < eShader_PS_MAX; i++)
			{
				if (m_d3PixelShaders[i])
				{
					m_d3PixelShaders[i]->Release();
					m_d3PixelShaders[i] = 0;
				}
			}
		}

		ShaderManager* ShaderManager::GetInstance()
		{
			static ShaderManager m_pInstance;
			return &m_pInstance;
		}

		void ShaderManager::CreateShaders(ID3D11Device* d3Device)
		{
			for (unsigned int i = 0; i < eShader_VS_MAX; i++)
				m_d3VertexShaders[i] = nullptr;
			for (unsigned int i = 0; i < eShader_PS_MAX; i++)
				m_d3PixelShaders[i] = nullptr;
				/*m_d3GeometryShaders[i] = nullptr;
				m_d3DomainShaders[i] = nullptr;
				m_d3HullShaders[i] = nullptr;*/
			char *byteCode = nullptr;
			size_t byteCodeSize;
#pragma region VertexShaders
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POS_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POS]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSCOLOR_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSTEX_VS.cso"))
			{
				HRESULT hr =d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSTEXCOLOR_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSTEXCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTEX_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSNORMTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTEXCOLOR_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSNORMTEXCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTANTEX_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSNORMTANTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTANTEXCOLOR_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSNORMTANTEXCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHT_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHT]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTCOLOR_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHTCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTEX_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHTNORMTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTEXCOLOR_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHTNORMTEXCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHTNORMTANTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEXCOLOR_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHTNORMTANTEXCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/Skybox_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_SKYBOX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/SkyboxColor_VS.cso"))
			{
				HRESULT hr = d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_SKYBOXCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
#pragma endregion
#pragma region PixelShaders
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/GBuffer_PS.cso"))
			{
				HRESULT hr = d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_PS_GBUFFER]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/ColorGBufferBump_PS.cso"))
			{
				HRESULT hr = d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_PS_COLOR_GBUFFER_BUMP]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/TextureGBufferBump_PS.cso"))
			{
				HRESULT hr = d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_PS_TEXTURE_GBUFFER_BUMP]);
				delete[] byteCode;
			}

			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/Skybox_PS.cso"))
			{
				HRESULT hr = d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_PS_SKYBOX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/SkyboxColor_PS.cso"))
			{
				HRESULT hr = d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_PS_SKYBOXCOLOR]);
				delete[] byteCode;
			}
#pragma endregion


		}

		ID3D11VertexShader* ShaderManager::GetVertexShader(VertexShaderType _Type)
		{
			return m_d3VertexShaders[_Type];
		}

		ID3D11PixelShader* ShaderManager::GetPixelShader(PixelShaderType _Type)
		{
			return m_d3PixelShaders[_Type];
		}

		bool ShaderManager::LoadShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName)
		{
			std::ifstream load;
			load.open(fileName, std::ios_base::binary);
			if (!load.is_open())
				return false;
			load.seekg(0, std::ios_base::end);
			byteCodeSize = size_t(load.tellg());
			*byteCode = new char[byteCodeSize];
			load.seekg(0, std::ios_base::beg);
			load.read(*byteCode, byteCodeSize);
			load.close();
			return true;
		}
	}
}