#pragma once
#include <unordered_map>
#include <functional>
namespace MEObject
{
	class Component;
}
class ComponentObjectFactory
{
private:
	typedef std::function<MEObject::Component*()> Creator;
	typedef std::unordered_map<std::string, Creator> Creators;
	Creators m_mComponents;
	static ComponentObjectFactory* m_pInstance;
	void registerComponents();
public:
	ComponentObjectFactory();
	~ComponentObjectFactory();
	void Register(const std::string &className, const Creator &creator);
	MEObject::Component *Create(const std::string &className);
	static ComponentObjectFactory* GetInstance();
	static void DestroyInstance();
};
