#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RENDERTOOLS_EXPORT ShaderManager
		{
		public:
			enum VertexShaderType {
				eShader_VS_POS = 0,
				eShader_VS_POSCOLOR,
				eShader_VS_POSTEX,
				eShader_VS_POSTEXCOLOR,
				eShader_VS_POSNORMTEX,
				eShader_VS_POSNORMTEXCOLOR,
				eShader_VS_POSNORMTANTEX,
				eShader_VS_POSNORMTANTEXCOLOR,
				eShader_VS_POSBONEWEIGHT,
				eShader_VS_POSBONEWEIGHTCOLOR,
				eShader_VS_POSBONEWEIGHTNORMTEX,
				eShader_VS_POSBONEWEIGHTNORMTEXCOLOR,
				eShader_VS_POSBONEWEIGHTNORMTANTEX,
				eShader_VS_POSBONEWEIGHTNORMTANTEXCOLOR,
				eShader_VS_SKYBOX,
				eShader_VS_SKYBOXCOLOR,
				eShader_VS_MAX
			};
			enum PixelShaderType {
				eShader_PS_COLOR_GBUFFER_BUMP = 0,
				eShader_PS_TEXTURE_GBUFFER_BUMP = 0,
				eShader_PS_GBUFFER,
				eShader_PS_SKYBOX,
				eShader_PS_SKYBOXCOLOR,
				eShader_PS_MAX
			};
		private:
			ShaderManager();
			ShaderManager(const ShaderManager &) {}
			ShaderManager(const ShaderManager &&) {}
			ShaderManager &operator=(const ShaderManager &) { return *this; }
			ShaderManager &operator=(const ShaderManager &&) { return *this; }
			ID3D11VertexShader* m_d3VertexShaders[eShader_VS_MAX];
			ID3D11PixelShader* m_d3PixelShaders[eShader_PS_MAX];
		public:
			~ShaderManager();
			static ShaderManager* GetInstance();
			void CreateShaders(ID3D11Device* d3Device);
			ID3D11VertexShader* GetVertexShader(VertexShaderType _Type);
			ID3D11PixelShader* GetPixelShader(PixelShaderType _Type);
			bool LoadShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);
		};
	}
}
