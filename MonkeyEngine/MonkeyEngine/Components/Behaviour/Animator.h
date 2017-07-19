#pragma once
#include "Behaviour.h"
#include "../../Renderer/Animation/Blender.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		class Animator : public Behaviour 
		{
		private:
			//graph Animation Names
			Blender* m_pBlender;
		public:
			Animator() {};
			~Animator() {};
		};
	}
}
