#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RENDERTOOLS_EXPORT RasterizerStateManager
		{
		public:
			enum RasterStates { RS_Default = 0, RS_LINE, RS_CCW, RS_NOCULL, RS_COUNT };
		private:
			RasterizerStateManager();
			~RasterizerStateManager(void);
			RasterizerStateManager(const RasterizerStateManager &) {}
			RasterizerStateManager(const RasterizerStateManager &&) {}
			RasterizerStateManager &operator=(const RasterizerStateManager &) { return *this; }
			RasterizerStateManager &operator=(const RasterizerStateManager &&) { return *this; }
			ID3D11RasterizerState* m_vRasterStates[RS_COUNT];
			UINT m_vStencilRefs[RS_COUNT];
			RasterStates m_eCurrentState;
		public:
			//in: void			
			//out: RasterizerStateManager*								
			//	The only instance of the RasterizerStateManager
			//desc: returns the only instance of the RasterizerStateManager
			static RasterizerStateManager* GetInstance();
			//in: ID3D11Device*
			//	The current Renderer's Device
			//out: void								
			//desc: Creates all of the RasterizerStates used by the Engine
			void CreateStates(ID3D11Device* d3Device);
			//in: RasterStates
			//	The RasterState to send to the Graphics Pipeline
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext
			//out: bool
			//	Whether changing the RasterizerState succeeded or not
			//desc: Changes the RasterizerState of the Graphics Pipeline
			bool ApplyState(RasterStates state, ID3D11DeviceContext* d3DeviceContext);
			//in: void
			//out: RasterStates
			//	The current RasterizerState in the Graphics Pipeline
			//desc: Gets the current RasterizerState of the Graphics Pipeline
			RasterStates GetCurrentState();
		};
	}
}
