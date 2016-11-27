#include "Object.h"

namespace MEObject
{


	Object::Object()
	{

	}


	Object::~Object()
	{

	}

	string Object::GetName()
	{
		return m_sName;
	}

	void Object::SetName(std::string _Name)
	{
		m_sName = _Name;
	}

	unsigned int Object::GetFlags()
	{
		return m_uiFlags;
	}

	void Object::SetFlags(unsigned int _Flags)
	{
		m_uiFlags = _Flags;
	}

}
