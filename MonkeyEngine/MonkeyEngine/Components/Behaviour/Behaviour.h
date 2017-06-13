#pragma once
#include "../Base/Component.h"
namespace MEObject
{
	class Behaviour : public Component
	{
	private:
		bool m_bEnabled;
	public:
		virtual void Initialize() {};
		virtual MEReturnValues::RETURNVALUE Update() { return MEReturnValues::NOTHING; };
		virtual void ShutDown() {};
		bool GetEnabled();
		void Disable();
		void Enable();
		void SetEnabled(bool _Enabled);
	};
}

