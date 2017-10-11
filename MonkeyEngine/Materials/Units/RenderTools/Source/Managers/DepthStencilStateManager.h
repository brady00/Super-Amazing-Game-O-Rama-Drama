#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RENDERTOOLS_EXPORT DepthStencilStateManager
		{
		public:
			enum DSStates {
				DSS_Default = 0,
				DSS_LessEqual,
				DSS_NoDepth,
				DSS_DeferredLight1,
				DSS_DeferredLight2,
				DSS_LightOutsideFinal,
				DSS_LightInsideFinal,
				DSS_COUNT
			};
		private:
			DepthStencilStateManager();
			DepthStencilStateManager(const DepthStencilStateManager &) {}
			DepthStencilStateManager(const DepthStencilStateManager &&) {}
			DepthStencilStateManager &operator=(const DepthStencilStateManager &) { return *this; }
			DepthStencilStateManager &operator=(const DepthStencilStateManager &&) { return *this; }
			ID3D11DepthStencilState* m_vDepthStates[DSS_COUNT];
			UINT m_vStencilRefs[DSS_COUNT];
			DSStates m_eCurrentState;
		public:
			~DepthStencilStateManager(void);
			static DepthStencilStateManager* GetInstance();
			void CreateStates(ID3D11Device* d3Device);
			bool ApplyState(DSStates state, ID3D11DeviceContext* d3DeviceContext);
			DSStates GetCurrentState();
		};
	}
}

