#include "GameObject.h"
#include "Renderer/CompRenderer.h"
#include "Transform/Transform.h"
#include "Behaviour/Behaviour.h"
namespace MonkeyEngine
{
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
			m_pTransform->UpdateTransform();
			for (unsigned int i = 0; i < m_vUpdatableComponents.size(); i++)
				m_vUpdatableComponents[i]->Initialize();
			for (unsigned int i = 0; i < m_vScripts.size(); i++)
				m_vScripts[i]->Initialize();
		}

		void GameObject::Update()
		{
			if (!m_bActiveInHeirarchy)
				return;
			m_pTransform->Update();
			for (unsigned int i = 0; i < m_vUpdatableComponents.size(); i++)
				m_vUpdatableComponents[i]->Update();
			
			for (unsigned int i = 0; i < m_vScripts.size(); i++)
				if(((Behaviour*)m_vScripts[i])->GetEnabled())
					m_vScripts[i]->Update();
		}

		void GameObject::ShutDown()
		{
			m_pTransform->ShutDown();
			for (unsigned int i = 0; i < eNumComponents; i++)
				if(i != eSkinnedMeshRenderer && i != eMeshRenderer)
					for (unsigned int j = 0; j < m_vComponents[i].size(); j++)
					{
						m_vComponents[i][j]->ShutDown();
						delete m_vComponents[i][j];
					}
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

		void GameObject::RemoveTag(std::string _Tag)
		{
			for (unsigned int i = 0; i < m_vTags.size(); i++)
			{
				if (_Tag == m_vTags[i])
				{
					m_vTags.erase(m_vTags.begin() + i);
					break;
				}
			}
		}

		std::vector<std::string>& GameObject::GetTags()
		{
			return m_vTags;
		}

		Transform* GameObject::GetTransform()
		{
			return m_pTransform;
		}

		void GameObject::AddComponent(Component* _Component, COMPONENT_ID _ID)
		{
			if (_ID == eTransform)
				m_pTransform = (Transform*)_Component;
			else
			{
				m_vComponents[_ID].push_back(_Component);
				m_vUpdatableComponents.push_back(_Component);
			}
			_Component->m_pGameObject = this;
		}

		void GameObject::RemoveComponent(Component* _Component, COMPONENT_ID _ID)
		{
			for (unsigned int i = 0; i < m_vComponents[_ID].size(); i++)
			{
				if (m_vComponents[_ID][i] == _Component)
				{
					m_vComponents[_ID].erase(m_vComponents[_ID].begin() + i);
					break;
				}
			}
		}

		void GameObject::BroadcastMessage(std::string _Message)
		{
			SendMessageUpwards(_Message);
			SendMessageString(_Message);
			SendMessageDownwards(_Message);
		}

		void GameObject::SendMessageString(std::string _Message)
		{
			for (unsigned int i = 0; i < eNumComponents; i++)
				for (unsigned int j = 0; j < m_vComponents[i].size(); j++)
					m_vComponents[i][j]->RecieveMessage(_Message);
		}

		void GameObject::SendMessageUpwards(std::string _Message)
		{
			GameObject* parent = GetTransform()->GetParent()->GetGameObject();
			while (parent)
			{
				parent->RecieveMessage(_Message);
				parent = parent->GetTransform()->GetParent()->GetGameObject();
			}
		}

		void GameObject::SendMessageDownwards(std::string _Message)
		{
			std::vector<Transform*>& children = GetTransform()->GetChildren();
			for (unsigned int i = 0; i < children.size(); i++)
				children[i]->GetGameObject()->SendMessageDownwards(_Message);
		}

		void GameObject::RecieveMessage(std::string _Message)
		{
			SendMessageString(_Message);
			//do message things
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

		std::vector<Component*>& GameObject::GetAllComponents()
		{
			return m_vUpdatableComponents;
		}

		std::vector<Component*>& GameObject::GetAllScritps()
		{
			return m_vScripts;
		}

		template <>
		CompRenderer* GameObject::GetComponent()
		{
			if (m_vComponents[eCompRenderer].size() != 0)
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
}
