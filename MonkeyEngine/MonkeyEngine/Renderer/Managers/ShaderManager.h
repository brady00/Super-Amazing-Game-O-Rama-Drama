#pragma once
#include <d3d11.h>
namespace MERenderer
{
	class ShaderManager
	{
	public:
		enum ShaderType{
			eShader_POS = 0,
			eShader_POSCOLOR,
			eShader_POSTEX,
			eShader_POSNORMTEX,
			eShader_POSNORMTANTEX,
			eShader_POSBONEWEIGHT,
			eShader_POSBONEWEIGHTNORMTEX,
			eShader_POSBONEWEIGHTNORMTANTEX,
			eShader_MAX
		};
	private:
		ShaderManager();
		ShaderManager(const ShaderManager &) {}
		ShaderManager(const ShaderManager &&) {}
		ShaderManager &operator=(const ShaderManager &) {}
		ShaderManager &operator=(const ShaderManager &&) {}
		static ShaderManager* m_pInstance;
		ID3D11VertexShader* m_d3VertexShaders[eShader_MAX];
		ID3D11PixelShader* m_d3PixelShaders[eShader_MAX];
		ID3D11GeometryShader* m_d3GeometryShaders[eShader_MAX];
		ID3D11DomainShader* m_d3DomainShaders[eShader_MAX];
		ID3D11HullShader* m_d3HullShaders[eShader_MAX];
		void CreateShaders();
	public:
		~ShaderManager();
		static ShaderManager* GetInstance();
		static void DeleteInstance();
		ID3D11VertexShader* GetVertexShader(ShaderType _Type);
		ID3D11PixelShader* GetPixelShader(ShaderType _Type);
		ID3D11GeometryShader* GetGeometryShader(ShaderType _Type);
		ID3D11DomainShader* GetDomainShader(ShaderType _Type);
		ID3D11HullShader* GetHullShader(ShaderType _Type);
		bool LoadShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);
	};
}

