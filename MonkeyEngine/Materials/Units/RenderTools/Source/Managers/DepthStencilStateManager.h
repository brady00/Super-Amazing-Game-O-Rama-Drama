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
			~DepthStencilStateManager(void);
			DepthStencilStateManager(const DepthStencilStateManager &) {}
			DepthStencilStateManager(const DepthStencilStateManager &&) {}
			DepthStencilStateManager &operator=(const DepthStencilStateManager &) { return *this; }
			DepthStencilStateManager &operator=(const DepthStencilStateManager &&) { return *this; }
			ID3D11DepthStencilState* m_vDepthStates[DSS_COUNT];
			UINT m_vStencilRefs[DSS_COUNT];
			DSStates m_eCurrentState;
		public:
			//in: void			
			//out: DepthStencilStateManager*								
			//	The only instance of the DepthStencilStateManager
			//desc: returns the only instance of the DepthStencilStateManager
			static DepthStencilStateManager* GetInstance();
			//in: ID3D11Device*
			//	The current Renderer's Device
			//out: void								
			//desc: Creates all of the DepthStencilStates used by the Engine
			void CreateStates(ID3D11Device* d3Device);
			//in: DSStates
			//	The DSStates to send to the Graphics Pipeline
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext
			//out: bool
			//	Whether changing the DepthStencilState succeeded or not
			//desc: Changes the DepthStencilState of the Graphics Pipeline
			bool ApplyState(DSStates state, ID3D11DeviceContext* d3DeviceContext);
			//in: void
			//out: DSStates
			//	The current DepthStencilState in the Graphics Pipeline
			//desc: Gets the current DepthStencilState of the Graphics Pipeline
			DSStates GetCurrentState();
		};
	}
}

