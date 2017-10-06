#include "ComponentObjectFactory.h"
#include <cstdarg>
using namespace System;
using namespace System::Reflection;
namespace MonkeyEngine
{
	using namespace MEObject;
	namespace MEFileIO
	{
		ComponentObjectFactory* ComponentObjectFactory::m_pInstance = nullptr;

		ComponentObjectFactory::ComponentObjectFactory()
		{

		}

		ComponentObjectFactory::~ComponentObjectFactory()
		{

		}

		Component* ComponentObjectFactory::Create(string className)
		{
			Type^ t = Type::GetType(gcnew String(className.c_str()));
			System::Object^ obj = t->GetConstructor(Type::EmptyTypes)->Invoke(gcnew cli::array<System::Object^>(0));
			pin_ptr<System::Object^> pinnedPtr = &obj;
			return (MonkeyEngine::MEObject::Component*)pinnedPtr;
		}

		ComponentObjectFactory* ComponentObjectFactory::GetInstance()
		{
			if (!m_pInstance)
				m_pInstance = new ComponentObjectFactory;
			return m_pInstance;
		}

		void ComponentObjectFactory::DestroyInstance()
		{
			if (m_pInstance)
				delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
}