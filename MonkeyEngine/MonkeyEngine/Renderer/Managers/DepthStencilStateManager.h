#pragma once
#include <atlcomcli.h>
#include <d3d11.h>
namespace MERenderer
{
	class DepthStencilStateManager
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
		DepthStencilStateManager &operator=(const DepthStencilStateManager &) {}
		DepthStencilStateManager &operator=(const DepthStencilStateManager &&) {}
		static DepthStencilStateManager *m_pInstance;
		CComPtr<ID3D11DepthStencilState > m_vDepthStates[DSS_COUNT];
		UINT m_vStencilRefs[DSS_COUNT];
		DSStates m_eCurrentState;
		void CreateStates();
	public:
		~DepthStencilStateManager(void);
		static DepthStencilStateManager* GetInstance();
		static void DeleteInstance();
		bool ApplyState(DSStates state);
		DSStates GetCurrentState();
	};
}

