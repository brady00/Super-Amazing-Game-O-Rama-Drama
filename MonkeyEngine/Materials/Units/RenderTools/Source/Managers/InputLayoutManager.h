#pragma once
#include "RenderToolsDLL.h"
#include "RenderToolsDLL.h"
#include <string>
#include <d3d11.h>
#include <DirectXMath.h>
#include "RenderStructures.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		enum VertexFormat {
			eVERTEX_POS = 0,
			eVERTEX_POSCOLOR,
			eVERTEX_POSTEX,
			eVERTEX_POSNORMTEX,
			eVERTEX_POSNORMTANTEX,
			eVERTEX_POSBONEWEIGHT,
			eVERTEX_POSBONEWEIGHTNORMTEX,
			eVERTEX_POSBONEWEIGHTNORMTANTEX,
			eVERTEX_MAX
		};
		extern std::string VertexFormatString[eVERTEX_MAX];
		class RENDERTOOLS_EXPORT InputLayoutManager
		{
		private:
			InputLayoutManager();
			InputLayoutManager(const InputLayoutManager &) {}
			InputLayoutManager(const InputLayoutManager &&) {}
			InputLayoutManager &operator=(const InputLayoutManager &) { return *this; }
			InputLayoutManager &operator=(const InputLayoutManager &&) { return *this; }
			//static InputLayoutManager* m_pInstance;
			ID3D11InputLayout* m_pInputLayouts[eVERTEX_MAX];
		public:
			void CreateLayouts(ID3D11Device* d3Device);
			~InputLayoutManager();
			static InputLayoutManager* GetInstance();
			ID3D11InputLayout* GetInputLayout(VertexFormat index);
		};

	}
}