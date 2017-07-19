#include "ShaderManager.h"
#include <fstream>
#include "../Renderer.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		ShaderManager* ShaderManager::m_pInstance = nullptr;

		ShaderManager::ShaderManager()
		{

		}


		ShaderManager::~ShaderManager()
		{
			for (unsigned int i = 0; i < eShader_MAX; i++)
			{
				ReleaseCOM(m_d3VertexShaders[i]);
				ReleaseCOM(m_d3PixelShaders[i]);
				ReleaseCOM(m_d3GeometryShaders[i]);
				ReleaseCOM(m_d3DomainShaders[i]);
				ReleaseCOM(m_d3HullShaders[i]);
			}
		}

		ShaderManager* ShaderManager::GetInstance()
		{
			if (m_pInstance == nullptr)
			{
				m_pInstance = new ShaderManager;
				m_pInstance->CreateShaders();
			}
			return m_pInstance;
		}

		void ShaderManager::DeleteInstance()
		{
			if (m_pInstance)
				delete m_pInstance;
			m_pInstance = nullptr;
		}

		void ShaderManager::CreateShaders()
		{
			for (unsigned int i = 0; i < eShader_MAX; i++)
			{
				m_d3VertexShaders[i] = nullptr;
				m_d3PixelShaders[i] = nullptr;
				m_d3GeometryShaders[i] = nullptr;
				m_d3DomainShaders[i] = nullptr;
				m_d3HullShaders[i] = nullptr;
			}
			char *byteCode = nullptr;
			size_t byteCodeSize;
#pragma region VertexShaders
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POS_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_POS]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSCOLOR_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_POSCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_POSTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_POSNORMTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTANTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_POSNORMTANTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHT_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_POSBONEWEIGHT]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_POSBONEWEIGHTNORMTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_POSBONEWEIGHTNORMTANTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
#pragma endregion
#pragma region PixelShaders
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POS_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_POS]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSCOLOR_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_POSCOLOR]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/GBuffer_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_POSTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/Default_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_POSNORMTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTANTEX_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_POSNORMTANTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHT_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_POSBONEWEIGHT]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTEX_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_POSBONEWEIGHTNORMTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_POSBONEWEIGHTNORMTANTEX]);
				delete[] byteCode;
			}
#pragma endregion
#pragma region GeometryShaders
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POS_GS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateGeometryShader(byteCode, byteCodeSize, nullptr, &m_d3GeometryShaders[eShader_POS]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSCOLOR_GS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateGeometryShader(byteCode, byteCodeSize, nullptr, &m_d3GeometryShaders[eShader_POSCOLOR]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSTEX_GS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateGeometryShader(byteCode, byteCodeSize, nullptr, &m_d3GeometryShaders[eShader_POSTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTEX_GS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateGeometryShader(byteCode, byteCodeSize, nullptr, &m_d3GeometryShaders[eShader_POSNORMTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTANTEX_GS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateGeometryShader(byteCode, byteCodeSize, nullptr, &m_d3GeometryShaders[eShader_POSNORMTANTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHT_GS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateGeometryShader(byteCode, byteCodeSize, nullptr, &m_d3GeometryShaders[eShader_POSBONEWEIGHT]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTEX_GS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateGeometryShader(byteCode, byteCodeSize, nullptr, &m_d3GeometryShaders[eShader_POSBONEWEIGHTNORMTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_GS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateGeometryShader(byteCode, byteCodeSize, nullptr, &m_d3GeometryShaders[eShader_POSBONEWEIGHTNORMTANTEX]);
				delete[] byteCode;
			}
#pragma endregion
#pragma region DomainShaders
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POS_DS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateDomainShader(byteCode, byteCodeSize, nullptr, &m_d3DomainShaders[eShader_POS]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSCOLOR_DS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateDomainShader(byteCode, byteCodeSize, nullptr, &m_d3DomainShaders[eShader_POSCOLOR]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSTEX_DS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateDomainShader(byteCode, byteCodeSize, nullptr, &m_d3DomainShaders[eShader_POSTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTEX_DS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateDomainShader(byteCode, byteCodeSize, nullptr, &m_d3DomainShaders[eShader_POSNORMTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTANTEX_DS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateDomainShader(byteCode, byteCodeSize, nullptr, &m_d3DomainShaders[eShader_POSNORMTANTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHT_DS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateDomainShader(byteCode, byteCodeSize, nullptr, &m_d3DomainShaders[eShader_POSBONEWEIGHT]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTEX_DS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateDomainShader(byteCode, byteCodeSize, nullptr, &m_d3DomainShaders[eShader_POSBONEWEIGHTNORMTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_DS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateDomainShader(byteCode, byteCodeSize, nullptr, &m_d3DomainShaders[eShader_POSBONEWEIGHTNORMTANTEX]);
				delete[] byteCode;
			}
#pragma endregion
#pragma region HullShaders
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POS_HS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateHullShader(byteCode, byteCodeSize, nullptr, &m_d3HullShaders[eShader_POS]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSCOLOR_HS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateHullShader(byteCode, byteCodeSize, nullptr, &m_d3HullShaders[eShader_POSCOLOR]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSTEX_HS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateHullShader(byteCode, byteCodeSize, nullptr, &m_d3HullShaders[eShader_POSTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTEX_HS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateHullShader(byteCode, byteCodeSize, nullptr, &m_d3HullShaders[eShader_POSNORMTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSNORMTANTEX_HS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateHullShader(byteCode, byteCodeSize, nullptr, &m_d3HullShaders[eShader_POSNORMTANTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHT_HS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateHullShader(byteCode, byteCodeSize, nullptr, &m_d3HullShaders[eShader_POSBONEWEIGHT]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTEX_HS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateHullShader(byteCode, byteCodeSize, nullptr, &m_d3HullShaders[eShader_POSBONEWEIGHTNORMTEX]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_HS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateHullShader(byteCode, byteCodeSize, nullptr, &m_d3HullShaders[eShader_POSBONEWEIGHTNORMTANTEX]);
				delete[] byteCode;
			}
#pragma endregion

		}

		ID3D11VertexShader* ShaderManager::GetVertexShader(ShaderType _Type)
		{
			return m_d3VertexShaders[_Type];
		}

		ID3D11PixelShader* ShaderManager::GetPixelShader(ShaderType _Type)
		{
			return m_d3PixelShaders[_Type];
		}

		ID3D11GeometryShader* ShaderManager::GetGeometryShader(ShaderType _Type)
		{
			return m_d3GeometryShaders[_Type];
		}

		ID3D11DomainShader* ShaderManager::GetDomainShader(ShaderType _Type)
		{
			return m_d3DomainShaders[_Type];
		}

		ID3D11HullShader* ShaderManager::GetHullShader(ShaderType _Type)
		{
			return m_d3HullShaders[_Type];
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