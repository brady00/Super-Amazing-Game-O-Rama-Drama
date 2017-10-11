#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include "Base\component.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		class __declspec(dllexport) ComponentObjectFactory
		{
		private:
			unordered_map<string, function<Component*(void)>> factoryFunctionRegistry;
			static ComponentObjectFactory* m_pInstance;
			ComponentObjectFactory();
			~ComponentObjectFactory();
		public:
			Component* Create(std::string className);
			static ComponentObjectFactory* GetInstance();
			void RegisterFactoryFunction(string name, function<Component*(void)> classFactoryFunction);
		};
	}
}