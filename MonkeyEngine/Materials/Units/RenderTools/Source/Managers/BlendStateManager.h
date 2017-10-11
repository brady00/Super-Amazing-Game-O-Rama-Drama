#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RENDERTOOLS_EXPORT BlendStateManager
		{
		public:
			enum BStates { BS_Default = 0, BS_Alpha, BS_Additive, BS_COUNT };
		private:
			BlendStateManager();
			BlendStateManager(const BlendStateManager &) {}
			BlendStateManager(const BlendStateManager &&) {}
			BlendStateManager &operator=(const BlendStateManager &) { return *this; }
			BlendStateManager &operator=(const BlendStateManager &&) { return *this; }
			ID3D11BlendState* m_vBlendStates[BS_COUNT];
			BStates m_eCurrentState;
		public:
			~BlendStateManager();
			static BlendStateManager* GetInstance();
			void CreateStates(ID3D11Device* d3Device);
			bool ApplyState(BStates state, ID3D11DeviceContext* d3DeviceContext);
			ID3D11BlendState* GetState(BStates state);
			BStates GetCurrentState();
		};
	}
}
