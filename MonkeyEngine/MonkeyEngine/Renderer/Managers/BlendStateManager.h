#pragma once
#include <atlcomcli.h>
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class BlendStateManager
		{
		public:
			enum BStates { BS_Default = 0, BS_Alpha, BS_Additive, BS_COUNT };
		private:
			BlendStateManager();
			BlendStateManager(const BlendStateManager &) {}
			BlendStateManager(const BlendStateManager &&) {}
			BlendStateManager &operator=(const BlendStateManager &) {}
			BlendStateManager &operator=(const BlendStateManager &&) {}
			static BlendStateManager* m_pInstance;
			CComPtr<ID3D11BlendState > m_vBlendStates[BS_COUNT];
			BStates m_eCurrentState;
			void CreateStates();
		public:
			~BlendStateManager();
			static BlendStateManager* GetInstance();
			static void DeleteInstance();
			bool ApplyState(BStates state);
			CComPtr<ID3D11BlendState > GetState(BStates state);
			BStates GetCurrentState();
		};
	}
}
