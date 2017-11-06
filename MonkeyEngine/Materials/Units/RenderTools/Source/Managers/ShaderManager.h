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
			bool LoadShaderData(char **byteCode, size_t &byteCodeSize, const char *fileName);
		public:
			~ShaderManager();
			//in: void			
			//out: ShaderManager*								
			//	The only instance of the ShaderManager
			//desc: returns the only instance of the ShaderManager
			static ShaderManager* GetInstance();
			//in: ID3D11Device*
			//	The current Renderer's Device
			//out: void								
			//desc: Creates all of the Shaders used by the Engine
			void CreateShaders(ID3D11Device* d3Device);
			//in: VertexShaderType
			//	The VertexShaderType used to define the VertexShader
			//out: ID3D11VertexShader*
			//	The VertexShader defined by the VertexShaderType
			//desc: Gets the VertexShader defined by the VertexShaderType
			ID3D11VertexShader* GetVertexShader(VertexShaderType _Type);
			//in: PixelShaderType
			//	The PixelShaderType used to define the PixelShader
			//out: ID3D11PixelShader*
			//	The VertexShader defined by the PixelShaderType
			//desc: Gets the PixelShader defined by the PixelShaderType
			ID3D11PixelShader* GetPixelShader(PixelShaderType _Type);
		};
	}
}
