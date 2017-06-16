#include "ComponentObjectFactory.h"

#include "../Components/Renderer/CompRenderer.h"
#include "../Components/Transform/Transform.h"
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
	ComponentObjectFactory::GetInstance()->Register("CompRenderer", [] {return new MEObject::CompRenderer; });
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
