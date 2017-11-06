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
			~BlendStateManager();
			BlendStateManager(const BlendStateManager &) {}
			BlendStateManager(const BlendStateManager &&) {}
			BlendStateManager &operator=(const BlendStateManager &) { return *this; }
			BlendStateManager &operator=(const BlendStateManager &&) { return *this; }
			ID3D11BlendState* m_vBlendStates[BS_COUNT];
			BStates m_eCurrentState;
		public:
			//in: void			
			//out: BlendStateManager*								
			//	The only instance of the BlendStateManager
			//desc: returns the only instance of the BlendStateManager
			static BlendStateManager* GetInstance();
			//in: ID3D11Device*
			//	The current Renderer's Device
			//out: void								
			//desc: Creates all of the BlendStates used by the Engine
			void CreateStates(ID3D11Device* d3Device);
			//in: BStates
			//	The BStates to send to the Graphics Pipeline
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext
			//out: bool
			//	Whether changing the BlendState succeeded or not
			//desc: Changes the BlendState of the Graphics Pipeline
			bool ApplyState(BStates state, ID3D11DeviceContext* d3DeviceContext);
			//in: BStates
			//	The BStates corresponding to the Blendstate needed
			//out: ID3D11BlendState*
			//	The BlendState corresponding to the BState
			//desc: Gets the BlendState corresponding to the BState
			ID3D11BlendState* GetState(BStates state);
			//in: void
			//out: BStates
			//	The current BlendState in the Graphics Pipeline
			//desc: Gets the current BlendState of the Graphics Pipeline
			BStates GetCurrentState();
		};
	}
}
