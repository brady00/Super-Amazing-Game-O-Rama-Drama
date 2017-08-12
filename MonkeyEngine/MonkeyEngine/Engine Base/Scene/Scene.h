#pragma once
#include "../../GameObject/GameObject.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class DebugCamera;
	}
	class Scene
	{
		friend class MountainDew;
	public:
		std::vector<MEObject::GameObject*> m_vObjects;
	private:
		MERenderer::DebugCamera* m_pDebugCamera; // Changed to Singleton
		void AddObject(MEObject::GameObject* _GameObject); 
	public:
		Scene();
		~Scene();

		void initialize(int _ScreenWidth, int _ScreenHeight);
		void Update();
		void Shutdown();

		std::vector<MEObject::GameObject*>& GetObjects();
		MERenderer::DebugCamera* GetDebugCamera();
	};
}
