#include "GameObject.h"
#include "../Components/Renderer/CompRenderer.h"
#include "../Components/Transform/Transform.h"
#include "../Utils/ComponentObjectFactory.h"

namespace MEObject
{
	GameObject::GameObject()
	{
	}


	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
		m_pTransform->Initialize();
		for (unsigned int i = 0; i < eNumComponents; i++)
			for (unsigned int j = 0; j < m_vComponents[i].size(); j++)
				m_vComponents[i][j]->Update();
	}

	MEReturnValues::RETURNVALUE GameObject::Update()
	{
		m_pTransform->Update();
		for (unsigned int i = 0; i < eNumComponents; i++)
			for (unsigned int j = 0; j < m_vComponents[i].size(); j++)
				m_vComponents[i][j]->Update();
		return MEReturnValues::NOTHING;
	}

	void GameObject::ShutDown()
	{
		m_pTransform->ShutDown();
		for (unsigned int i = 0; i < eNumComponents; i++)
			for (unsigned int j = 0; j < m_vComponents[i].size(); j++)
				m_vComponents[i][j]->ShutDown();
	}

	void GameObject::SetActiveInHeirarchy()
	{
		bool active = false;
		if (m_pTransform->GetParent())
			m_bActiveInHeirarchy = m_pTransform->GetParent()->GetGameObject()->GetActive() && m_bActiveSelf;
		else
			m_bActiveInHeirarchy = m_bActiveSelf;
	}

	void GameObject::SetActive(bool _Active)
	{
		m_bActiveSelf = _Active;
		SetActiveInHeirarchy();
	}

	bool GameObject::GetActive()
	{
		return m_bActiveInHeirarchy;
	}

	void GameObject::SetStatic(bool _Static)
	{
		m_bIsStatic = _Static;
	}

	bool GameObject::GetStatic()
	{
		return m_bIsStatic;
	}

	void GameObject::SetLayer(unsigned int _Layer)
	{
		m_uiLayer = _Layer;
	}

	unsigned int GameObject::GetLayer()
	{
		return m_uiLayer;
	}

	void GameObject::SetScene(Scene* _Scene)
	{
		m_pScene = _Scene;
	}

	Scene* GameObject::GetScene()
	{
		return m_pScene;
	}

	void GameObject::AddTag(std::string _Tag)
	{
		m_vTags.push_back(_Tag);
	}

	std::vector<std::string>& GameObject::GetTags()
	{
		return m_vTags;
	}

	void GameObject::SetTrasform(Transform* _Transform)
	{
		m_pTransform = _Transform;
	}

	Transform* GameObject::GetTransform()
	{
		return m_pTransform;
	}

	template <>
	void GameObject::AddComponent<CompRenderer>(CompRenderer* _Component)
	{
		m_vComponents[eCompRenderer].push_back(_Component);
	}

	void GameObject::BroadcastMessage(std::string _Message)
	{

	}

	void GameObject::SendMessageString(std::string _Message)
	{

	}

	void GameObject::SendMessageUpwards(std::string _Message)
	{

	}

	bool GameObject::CompareTag(std::string _Tag)
	{
		for (unsigned int i = 0; i < m_vTags.size(); i++)
		{
			if (m_vTags[i] == _Tag)
				return true;
		}
		return false;
	}

	template <>
	CompRenderer* GameObject::GetComponent()
	{
		if(m_vComponents[eCompRenderer].size() != 0)
			return (CompRenderer*)m_vComponents[eCompRenderer][0];
		return nullptr;
	}

	template <typename CompType>
	CompType* GameObject::GetComponentinCildren()
	{
		if (m_pTransform->GetChild())
			return m_pTransform->GetChild()->GetGameObject()->GetComponent<CompType>();
		return nullptr;
	}

	template <typename CompType>
	CompType* GameObject::GetComponentinParent()
	{
		if (m_pTransform->GetParent())
			return m_pTransform->GetParent()->GetGameObject()->GetComponent<CompType>();
		return nullptr;
	}

	template <>
	std::vector<CompRenderer*> GameObject::GetComponents()
	{
		std::vector<CompRenderer*> temp;
		temp.reserve(m_vComponents[eCompRenderer].size());
		for (unsigned int i = 0; i < m_vComponents[eCompRenderer].size(); i++)
			temp.push_back((CompRenderer*)m_vComponents[eCompRenderer][i]);
		return temp;
	}

	template <typename CompType>
	std::vector<CompType*> GameObject::GetComponentsinCildren()
	{
		if (m_pTransform->GetChild())
			return m_pTransform->GetChild()->GetGameObject()->GetComponents();
		return std::vector<CompType*>();
	}

	template <typename CompType>
	std::vector<CompType*> GameObject::GetComponentsinParent()
	{
		if (m_pTransform->GetParent())
			m_pTransform->GetParent()->GetGameObject()->GetComponents();
		return std::vector<CompType*>();
	}
}