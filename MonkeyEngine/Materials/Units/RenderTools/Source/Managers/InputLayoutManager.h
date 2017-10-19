#pragma once
#include "RenderToolsDLL.h"
#include "RenderToolsDLL.h"
#include <string>
#include <d3d11.h>
#include <unordered_map>
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
			//static InputLayoutManager* m_pInstance;
		public:
			void CreateLayouts(ID3D11Device* d3Device);
			~InputLayoutManager();
			static InputLayoutManager* GetInstance();
			ID3D11InputLayout* GetInputLayout(VertexFormat index);
			ID3D11InputLayout* m_pInputLayouts[eVERTEX_MAX];
		};

	}
}