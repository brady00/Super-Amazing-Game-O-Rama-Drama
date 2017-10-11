#include "ComponentObjectFactory.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		ComponentObjectFactory* ComponentObjectFactory::m_pInstance = nullptr;

		ComponentObjectFactory::ComponentObjectFactory()
		{

		}

		ComponentObjectFactory::~ComponentObjectFactory()
		{

		}
		Component* ComponentObjectFactory::Create(std::string className)
		{
			Component * instance = nullptr;
			auto it = factoryFunctionRegistry.find(className);
			if (it != factoryFunctionRegistry.end())
				instance = it->second();
			if (instance != nullptr)
				return (Component*)instance;
			else
				return nullptr;
		}

		ComponentObjectFactory* ComponentObjectFactory::GetInstance()
		{
			if (!m_pInstance)
				m_pInstance = new ComponentObjectFactory();
			return m_pInstance;
		}

		void ComponentObjectFactory::RegisterFactoryFunction(string name, function<Component*(void)> classFactoryFunction)
		{
			factoryFunctionRegistry[name] = classFactoryFunction;
		}
	}
}