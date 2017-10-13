#pragma once
#include "../Base/Component.h"

namespace MonkeyEngine
{
	namespace MEObject
	{
		class __declspec(dllexport) Behaviour : public Component
		{
		private:
			bool m_bEnabled;
		public:
			virtual void Initialize() {};
			virtual void Update() {};
			virtual void ShutDown() {};
			bool GetEnabled();
			void Disable();
			void Enable();
			void SetEnabled(bool _Enabled);
		private:
		};
	}
}

