#pragma once
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
			ID3D11RasterizerState* m_vRasterStates[RS_COUNT];
			UINT m_vStencilRefs[RS_COUNT];
			RasterStates m_eCurrentState;
		public:
			~RasterizerStateManager(void);
			static RasterizerStateManager* GetInstance();
			static void DeleteInstance();
			void CreateStates(ID3D11Device* d3Device);
			bool ApplyState(RasterStates state, ID3D11DeviceContext* d3DeviceContext);
			RasterStates GetCurrentState();
		};
	}
}
