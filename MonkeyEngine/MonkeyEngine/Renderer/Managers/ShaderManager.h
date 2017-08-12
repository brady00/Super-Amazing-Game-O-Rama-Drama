#pragma once
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class ShaderManager
		{
		public:
			enum VertexShaderType {
				eShader_VS_POS = 0,
				eShader_VS_POSCOLOR,
				eShader_VS_POSTEX,
				eShader_VS_POSNORMTEX,
				eShader_VS_POSNORMTANTEX,
				eShader_VS_POSBONEWEIGHT,
				eShader_VS_POSBONEWEIGHTNORMTEX,
				eShader_VS_POSBONEWEIGHTNORMTANTEX,
				eShader_VS_SKYBOX,
				eShader_VS_MAX
			};
			enum PixelShaderType {
				eShader_PS_DEFAULT = 0,
				eShader_PS_GBUFFER,
				eShader_PS_SKYBOX,
				eShader_PS_MAX
			};
		private:
			ShaderManager();
			ShaderManager(const ShaderManager &) {}
			ShaderManager(const ShaderManager &&) {}
			ShaderManager &operator=(const ShaderManager &) {}
			ShaderManager &operator=(const ShaderManager &&) {}
			static ShaderManager* m_pInstance;
			ID3D11VertexShader* m_d3VertexShaders[eShader_VS_MAX];
			ID3D11PixelShader* m_d3PixelShaders[eShader_PS_MAX];
			/*ID3D11GeometryShader* m_d3GeometryShaders[eShader_MAX];
			ID3D11DomainShader* m_d3DomainShaders[eShader_MAX];
			ID3D11HullShader* m_d3HullShaders[eShader_MAX];*/
			void CreateShaders();
		public:
			~ShaderManager();
			static ShaderManager* GetInstance();
			static void DeleteInstance();
			ID3D11VertexShader* GetVertexShader(VertexShaderType _Type);
			ID3D11PixelShader* GetPixelShader(PixelShaderType _Type);
			/*ID3D11GeometryShader* GetGeometryShader(ShaderType _Type);
			ID3D11DomainShader* GetDomainShader(ShaderType _Type);
			ID3D11HullShader* GetHullShader(ShaderType _Type);*/
			bool LoadShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);
		};
	}
}
