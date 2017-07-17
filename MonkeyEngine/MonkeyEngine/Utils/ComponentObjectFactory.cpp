#include "ComponentObjectFactory.h"

namespace MEFileIO
{
	ComponentObjectFactory* ComponentObjectFactory::m_pInstance = nullptr;

	ComponentObjectFactory::ComponentObjectFactory()
	{

	}

	ComponentObjectFactory::~ComponentObjectFactory()
	{

	}

	void ComponentObjectFactory::Register(const std::string &className, const Creator &creator)
	{
		m_mComponents[className] = creator;
	}

	MEObject::Component* ComponentObjectFactory::Create(const std::string &className)
	{
		return m_mComponents[className]();
	}

	void ComponentObjectFactory::registerComponents()
	{
		ComponentObjectFactory::GetInstance()->Register("MeshRenderer", [] {return new MEObject::MeshRenderer; });
		ComponentObjectFactory::GetInstance()->Register("Transform", [] {return new MEObject::Transform; });
	}

	ComponentObjectFactory* ComponentObjectFactory::GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new ComponentObjectFactory;
			m_pInstance->registerComponents();
		}
		return m_pInstance;
	}

	void ComponentObjectFactory::DestroyInstance()
	{
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}
}