#include "Behaviour.h"



namespace MEObject
{
	bool Behaviour::GetEnabled()
	{
		return m_bEnabled;
	}

	void Behaviour::Disable()
	{
		m_bEnabled = false;
	}

	void Behaviour::Enable()
	{
		m_bEnabled = true;
	}

	void Behaviour::SetEnabled(bool _Enabled)
	{
		m_bEnabled = _Enabled;
	}
}