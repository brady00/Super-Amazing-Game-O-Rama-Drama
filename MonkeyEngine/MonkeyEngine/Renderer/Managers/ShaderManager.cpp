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
			for (unsigned int i = 0; i < eShader_VS_MAX; i++)
				ReleaseCOM(m_d3VertexShaders[i]);
			for (unsigned int i = 0; i < eShader_PS_MAX; i++)
				ReleaseCOM(m_d3PixelShaders[i]);
				/*ReleaseCOM(m_d3GeometryShaders[i]);
				ReleaseCOM(m_d3DomainShaders[i]);
				ReleaseCOM(m_d3HullShaders[i]);*/
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
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/POS_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POS]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/POSCOLOR_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSCOLOR]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/POSTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/POSNORMTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSNORMTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/POSNORMTANTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSNORMTANTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/POSBONEWEIGHT_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHT]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/POSBONEWEIGHTNORMTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHTNORMTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/POSBONEWEIGHTNORMTANTEX_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_POSBONEWEIGHTNORMTANTEX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/Skybox_VS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_d3VertexShaders[eShader_VS_SKYBOX]);
				delete[] byteCode;
				byteCode = nullptr;
			}
#pragma endregion
#pragma region PixelShaders
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/GBuffer_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_PS_GBUFFER]);
				delete[] byteCode;
			}
			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/Default_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_PS_DEFAULT]);
				delete[] byteCode;
			}

			if (LoadShaderData(&byteCode, byteCodeSize, "../MonkeyEngine/Assets/ShaderCSO/Skybox_PS.cso"))
			{
				HRESULT hr = Renderer::m_d3Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &m_d3PixelShaders[eShader_PS_SKYBOX]);
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

		//ID3D11GeometryShader* ShaderManager::GetGeometryShader(ShaderType _Type)
		//{
		//	return m_d3GeometryShaders[_Type];
		//}
		//
		//ID3D11DomainShader* ShaderManager::GetDomainShader(ShaderType _Type)
		//{
		//	return m_d3DomainShaders[_Type];
		//}
		//
		//ID3D11HullShader* ShaderManager::GetHullShader(ShaderType _Type)
		//{
		//	return m_d3HullShaders[_Type];
		//}

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