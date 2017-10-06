#pragma once
#include <unordered_map>
#include <functional>
#include "Renderer/SkinnedMeshRenderer.h"
#include "Transform/Transform.h"

namespace MEObject
{
	class Component;
}
namespace MonkeyEngine
{
	namespace MEFileIO
	{
		class ComponentObjectFactory
		{
			friend class FileIO;
		private:
			typedef std::function<MEObject::Component*()> Creator;
			typedef std::unordered_map<std::string, Creator> Creators;
			Creators m_mComponents;
			static ComponentObjectFactory* m_pInstance;
			ComponentObjectFactory();
			~ComponentObjectFactory();
			MEObject::Component *Create(string className);
			static ComponentObjectFactory* GetInstance();
			static void DestroyInstance();
		};
	}
}