#include "Scene.h"
#include "DebugCamera/DebugCamera.h"
#include "Renderer.h"
#include "FileIO.h"
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
		m_pDebugCamera = MERenderer::DebugCamera::GetInstance();
		m_pDebugCamera->Initialize(Renderer::GetDevice(), Renderer::GetDeviceContext(), (float)_ScreenWidth, (float)_ScreenHeight);
		for (unsigned int i = 0; i < m_vObjects.size(); i++)
			m_vObjects[i]->Initialize();
	}

	void Scene::AddObject(MEObject::GameObject* _GameObject)
	{
		m_vObjects.push_back(_GameObject);
	}


	void Scene::Update()
	{
		if (RenderState::GetRenderState() == RenderState::GAME_RENDERING || RenderState::GetRenderState() == RenderState::VR_RENDERING)
		{
			unsigned int size = (unsigned int)m_vObjects.size();
			for (unsigned int i = 0; i < size; i++)
				if (m_vObjects[i]->GetActive())
					m_vObjects[i]->Update();
		}
		else
			m_pDebugCamera->Update(MERenderer::Renderer::GetDeviceContext());
	}

	void Scene::Shutdown()
	{
		for (unsigned int i = 0; i < m_vObjects.size(); i++)
		{
			m_vObjects[i]->ShutDown();
			delete m_vObjects[i];
			m_vObjects[i] = nullptr;
		}
		m_vObjects.clear();
	}

	std::vector<MEObject::GameObject*>& Scene::GetObjects()
	{
		return m_vObjects;
	}

	MERenderer::DebugCamera* Scene::GetDebugCamera()
	{
		return m_pDebugCamera;
	}

	void Scene::Load(string& _FileName, float& _percentLoaded, bool& Success)
	{
		if (m_vObjects.size() > 0)
			Shutdown();
		MEFileIO::FileIO::LoadScene(_FileName, m_vObjects, _percentLoaded, Success);
	}

	bool Scene::Save(string& _FileName)
	{
		return MEFileIO::FileIO::SaveScene(_FileName, m_vObjects);
	}
}