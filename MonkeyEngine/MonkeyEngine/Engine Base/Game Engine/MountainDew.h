#pragma once
#include <Windows.h>
#include "../../Renderer/Renderer.h"
#include "../Scene/Scene.h"

namespace MonkeyEngine
{
	class Scene;
	class Settings;
	class MountainDew
	{
	private:
		//static Instance for Singleton
		static MountainDew *m_pGamePtr;

		//Windows Variables
		Settings* m_pSettings;
		bool init = false;

		MountainDew() {};
		MountainDew(const MountainDew&) {};
		MountainDew(const MountainDew&&) {};
		MountainDew &operator=(const MountainDew&) {};
		MountainDew &operator=(const MountainDew&&) {};

	public:
		HINSTANCE m_hInst;
		HWND m_HWnd;
		MERenderer::Renderer* m_pRenderer = nullptr;
		Scene* m_pScene;
		bool m_bShuttingDown = false;

		static MountainDew* GetInstance() { if (!m_pGamePtr) m_pGamePtr = new MountainDew;  return m_pGamePtr; }
		static void DestroyInstance() { if (m_pGamePtr) delete m_pGamePtr; m_pGamePtr = m_pGamePtr; }
		void Initialize(HINSTANCE, int);
		void Update();
		void Shutdown();
		~MountainDew() {};
		void UpdateGame();
	};

}

void __declspec(dllexport) InitializeEngine(HWND window, int _ScreenWidth, int _ScreenHeight);
void __declspec(dllexport) ResizeEngine(int _ScreenWidth, int _ScreenHeight);
void __declspec(dllexport) UpdateEngine();
void __declspec(dllexport) ShutdownEngine();
void __declspec(dllexport) MouseDown_RenderingPanel(int key);
void __declspec(dllexport) MouseUp_RenderingPanel(int key);
void __declspec(dllexport) RunGameWindow();
void __declspec(dllexport) RunGameVR();
bool __declspec(dllexport) LoadScene(string& _FileName);
std::vector<MonkeyEngine::MEObject::GameObject*> __declspec(dllexport)&GetSceneObjects();

