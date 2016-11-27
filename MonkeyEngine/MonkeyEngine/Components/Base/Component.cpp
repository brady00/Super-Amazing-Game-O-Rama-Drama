#include "Component.h"



namespace MEObject
{
	Component::Component()
	{

	}


	Component::~Component()
	{

	}

	Transform* Component::GetTransform()
	{
		return m_pGameObject->GetTransform();
	}

	std::vector<std::string>& Component::GetTags()
	{
		return m_pGameObject->GetTags();
	}

	void Component::BroadcastMessage(std::string _Message)
	{

	}

	void Component::SendMessage(std::string _Message)
	{

	}

	void Component::SendMessageUpwards(std::string _Message)
	{

	}

	bool Component::CompareTag(std::string _Tag)
	{
		return m_pGameObject->CompareTag(_Tag);
	}

	template <typename CompType>
	CompType* Component::GetComponent()
	{
		m_pGameObject->
	}

	template <typename CompType>
	CompType* Component::GetComponentinCildren()
	{

	}

	template <typename CompType>
	CompType* Component::GetComponentinParent()
	{

	}

	template <typename CompType>
	std::vector<CompType*> Component::GetComponents()
	{

	}

	template <typename CompType>
	std::vector<CompType*> Component::GetComponentsinCildren()
	{

	}

	template <typename CompType>
	std::vector<CompType*> Component::GetComponentsinParent()
	{

	}
}