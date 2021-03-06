#pragma once
#pragma warning(disable: 4561)
#include "Object/Object.h"
#include "GameObject/GameObject.h"
#include "Registrar\Registrar.h"
#define REGISTER_CLASS(NAME, TYPE) \
	static Registrar<TYPE> registrar(NAME);
namespace MonkeyEngine
{
	namespace MEObject
	{
		class Transform;
		class Camera;
		class __declspec(dllexport) Component : public Object
		{
			friend class GameObject;
			friend class Camera;
		private:
		protected:
			GameObject* m_pGameObject;
		public:
			Component();
			virtual ~Component();
			Transform* GetTransform();
			std::vector<std::string>& GetTags();
			void BroadcastMessage(std::string _Message);
			void SendMessageUpwards(std::string _Message);
			void RecieveMessage(std::string _Message);
			bool CompareTag(std::string _Tag);
			GameObject* GetGameObject();
			template <typename CompType>
			CompType* GetComponent();
			template <typename CompType>
			CompType* GetComponentinCildren();
			template <typename CompType>
			CompType* GetComponentinParent();
			template <typename CompType>
			std::vector<CompType*> GetComponents();
			template <typename CompType>
			std::vector<CompType*> GetComponentsinCildren();
			template <typename CompType>
			std::vector<CompType*> GetComponentsinParent();
		private:
			virtual void Initialize() {};
			virtual void Update() {};
			virtual void ShutDown() {};
		};
	}
}
