#pragma once
#include <atlcomcli.h>
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RasterizerStateManager
		{
		public:
			enum RasterStates { RS_Default = 0, RS_LINE, RS_CCW, RS_NOCULL, RS_COUNT };
		private:
			RasterizerStateManager();
			RasterizerStateManager(const RasterizerStateManager &) {}
			RasterizerStateManager(const RasterizerStateManager &&) {}
			RasterizerStateManager &operator=(const RasterizerStateManager &) {}
			RasterizerStateManager &operator=(const RasterizerStateManager &&) {}
			static RasterizerStateManager *m_pInstance;
			CComPtr<ID3D11RasterizerState> m_vRasterStates[RS_COUNT];
			UINT m_vStencilRefs[RS_COUNT];
			RasterStates m_eCurrentState;
			void CreateStates();
		public:
			~RasterizerStateManager(void);
			static RasterizerStateManager* GetInstance();
			static void DeleteInstance();
			bool ApplyState(RasterStates state);
			RasterStates GetCurrentState();
		};
	}
}
