#pragma once
#include <string>
#include <functional>
#include "Factory\ComponentObjectFactory.h"

namespace MonkeyEngine
{
	namespace MEObject
	{
		class Component;
		template<class t>
		class Registrar
		{
		public:
			Registrar(std::string className);
			Registrar();
			~Registrar();
		};

		template<class T>
		Registrar<T>::Registrar()
		{

		}

		template<class T>
		Registrar<T>::Registrar(std::string className)
		{
			ComponentObjectFactory::GetInstance()->RegisterFactoryFunction(className, [](void)->Component*{return new T();});
		}

		template<class T>
		Registrar<T>::~Registrar()
		{
		}
	}
}