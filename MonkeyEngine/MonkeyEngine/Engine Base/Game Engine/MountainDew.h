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
		MountainDew() {};
		MountainDew(const MountainDew&) {};
		MountainDew(const MountainDew&&) {};
		MountainDew &operator=(const MountainDew&) {};
		MountainDew &operator=(const MountainDew&&) {};
		bool init = false;
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
extern "C"
{
	__declspec(dllexport) void InitializeEngine(HWND window, int _ScreenWidth, int _ScreenHeight);
	__declspec(dllexport) void ResizeEngine(int _ScreenWidth, int _ScreenHeight);
	__declspec(dllexport) void UpdateEngine();
	__declspec(dllexport) void ShutdownEngine();
	__declspec(dllexport) std::vector<MonkeyEngine::MEObject::GameObject*>& GetSceneObjects();
}
