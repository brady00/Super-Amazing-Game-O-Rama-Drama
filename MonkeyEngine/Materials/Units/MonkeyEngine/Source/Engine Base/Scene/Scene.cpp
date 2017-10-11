#include "Scene.h"
#include "DebugCamera/DebugCamera.h"
#include "Renderer.h"
namespace MonkeyEngine
{
	Scene::Scene()
	{
	}


	Scene::~Scene()
	{
	}

	void Scene::initialize(int _ScreenWidth, int _ScreenHeight)
	{
		//m_pDebugCamera = new MERenderer::DebugCamera;
		m_pDebugCamera = MERenderer::DebugCamera::GetInstance();
		m_pDebugCamera->Initialize(XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), 0.1f, 999999.9f, 90.0f, (float)_ScreenHeight, (float)_ScreenWidth);
		for (unsigned int i = 0; i < m_vObjects.size(); i++)
			m_vObjects[i]->Initialize();
	}

	void Scene::AddObject(MEObject::GameObject* _GameObject)
	{
		m_vObjects.push_back(_GameObject);
	}


	void Scene::Update()
	{
		unsigned int size = (unsigned int)m_vObjects.size();
		for (unsigned int i = 0; i < size; i++)
			if (m_vObjects[i]->GetActive())
				m_vObjects[i]->Update();
		m_pDebugCamera->Update(MERenderer::Renderer::GetDeviceContext());
	}

	void Scene::Shutdown()
	{
		delete m_pDebugCamera;
		for (unsigned int i = 0; i < m_vObjects.size(); i++)
		{
			m_vObjects[i]->ShutDown();
			delete m_vObjects[i];
			m_vObjects[i] = nullptr;
		}
	}

	std::vector<MEObject::GameObject*>& Scene::GetObjects()
	{
		return m_vObjects;
	}
	MERenderer::DebugCamera* Scene::GetDebugCamera()
	{
		return m_pDebugCamera;
	}
}