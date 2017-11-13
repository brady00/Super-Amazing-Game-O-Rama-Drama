#pragma once
#include "RenderToolsDLL.h"
#include "RenderToolsDLL.h"
#include <string>
#include <d3d11.h>
#include <unordered_map>
#pragma warning(disable: 4793)
#include <DirectXMath.h>
#include "RenderStructures.h"
#include "RenderToolsDLL.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		enum VertexFormat {
			eVERTEX_POS = 0,
			eVERTEX_POSCOLOR,
			eVERTEX_POSTEX,
			eVERTEX_POSTEXCOLOR,
			eVERTEX_POSNORMTEX,
			eVERTEX_POSNORMTEXCOLOR,
			eVERTEX_POSNORMTANTEX,
			eVERTEX_POSNORMTANTEXCOLOR,
			eVERTEX_POSBONEWEIGHT,
			eVERTEX_POSBONEWEIGHTCOLOR,
			eVERTEX_POSBONEWEIGHTNORMTEX,
			eVERTEX_POSBONEWEIGHTNORMTEXCOLOR,
			eVERTEX_POSBONEWEIGHTNORMTANTEX,
			eVERTEX_POSBONEWEIGHTNORMTANTEXCOLOR,
			eVERTEX_MAX
		};

		class RENDERTOOLS_EXPORT InputLayoutManager
		{
		private:
			InputLayoutManager();
			InputLayoutManager(const InputLayoutManager &) {}
			InputLayoutManager(const InputLayoutManager &&) {}
			InputLayoutManager &operator=(const InputLayoutManager &) { return *this; }
			InputLayoutManager &operator=(const InputLayoutManager &&) { return *this; }
			~InputLayoutManager();
			ID3D11InputLayout* m_pInputLayouts[eVERTEX_MAX];
		public:
			//in: void			
			//out: InputLayoutManager*								
			//	The only instance of the InputLayoutManager
			//desc: returns the only instance of the InputLayoutManager
			static InputLayoutManager* GetInstance();
			//in: ID3D11Device*
			//	The current Renderer's Device
			//out: void								
			//desc: Creates all of the InputLayouts used by the Engine
			void CreateLayouts(ID3D11Device* d3Device);
			//in: VertexFormat
			//	The VertexFormat used to define the InputLayout
			//out: ID3D11InputLayout*
			//	The ID3D11InputLayout defined by the VertexFormat
			//desc: Gets the ID3D11InputLayout defined by the VertexFormat
			ID3D11InputLayout* GetInputLayout(VertexFormat index);
		};

	}
}