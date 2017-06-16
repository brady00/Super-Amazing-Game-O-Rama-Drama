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

	void Component::SendMessageString(std::string _Message)
	{

	}

	void Component::SendMessageUpwards(std::string _Message)
	{

	}

	bool Component::CompareTag(std::string _Tag)
	{
		return m_pGameObject->CompareTag(_Tag);
	}

	GameObject* Component::GetGameObject()
	{
		return m_pGameObject;
	}

	template <typename CompType>
	CompType* Component::GetComponent()
	{
		return _pGameObject->GetComponent<CompType>();
	}

	template <typename CompType>
	CompType* Component::GetComponentinCildren()
	{
		return _pGameObject->GetComponentinCildren<CompType>();
	}

	template <typename CompType>
	CompType* Component::GetComponentinParent()
	{
		return _pGameObject->GetComponentinParent<CompType>();
	}

	template <typename CompType>
	std::vector<CompType*> Component::GetComponents()
	{
		return _pGameObject->GetComponents<CompType>();
	}

	template <typename CompType>
	std::vector<CompType*> Component::GetComponentsinCildren()
	{
		return _pGameObject->GetComponentsinCildren<CompType>();
	}

	template <typename CompType>
	std::vector<CompType*> Component::GetComponentsinParent()
	{
		return _pGameObject->GetComponentsinParent<CompType>();
	}
}