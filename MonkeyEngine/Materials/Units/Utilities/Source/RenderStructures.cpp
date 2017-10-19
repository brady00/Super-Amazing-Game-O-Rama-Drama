#include "RenderStructures.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{
		RenderState::RState RenderState::state = RState::EDITOR_RENDERING;

		RenderState::RState RenderState::GetRenderState()
		{
			return state;
		}
		void RenderState::SetRenderState(RenderState::RState State)
		{
			state = State;
		}

	}
}