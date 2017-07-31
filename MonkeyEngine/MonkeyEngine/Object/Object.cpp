#include "Object.h"
namespace MonkeyEngine
{
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
}

char GetObjectNameChar(MonkeyEngine::MEObject::Object* _object, unsigned int _index)
{
	return _object->GetName()[_index];
}

unsigned int GetObjectNameSize(MonkeyEngine::MEObject::Object* _object)
{
	return (unsigned int)_object->GetName().size();
}

void SetObjectName(MonkeyEngine::MEObject::Object* _object, const char* _Name)
{
	_object->SetName(_Name);
}

unsigned int GetObjectFlags(MonkeyEngine::MEObject::Object* _object)
{
	return _object->GetFlags();
}

void SetObjectFlags(MonkeyEngine::MEObject::Object* _object, unsigned int _Flags)
{
	_object->SetFlags(_Flags);
}
