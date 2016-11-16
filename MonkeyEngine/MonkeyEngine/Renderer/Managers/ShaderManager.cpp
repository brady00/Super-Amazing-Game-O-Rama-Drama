#include "ShaderManager.h"



namespace MERenderer
{
	ShaderManager::ShaderManager()
	{

	}


	ShaderManager::~ShaderManager()
	{

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

	}

	const ID3D11VertexShader* ShaderManager::GetVertexShader(ShaderType _Type)
	{
		return m_d3VertexShaders[_Type];
	}

	const ID3D11PixelShader* ShaderManager::GetPixelShader(ShaderType _Type)
	{
		return m_d3PixelShaders[_Type];
	}

	const ID3D11GeometryShader* ShaderManager::GetGeometryShader(ShaderType _Type)
	{
		return m_d3GeometryShaders[_Type];
	}

	const ID3D11DomainShader* ShaderManager::GetDomainShader(ShaderType _Type)
	{
		return m_d3DomainShaders[_Type];
	}

	const ID3D11HullShader* ShaderManager::GetHullShader(ShaderType _Type)
	{
		return m_d3HullShaders[_Type];
	}
}
