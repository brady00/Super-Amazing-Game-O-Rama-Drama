#pragma once
#include <Windows.h>
#include "../../Renderer/Renderer.h"
#include <thread>
//#include <vld.h>
namespace MonkeyEngine
{
	class Scene;
	class MountainDew
	{
	private:
		//static Instance for Singleton
		static MountainDew *m_pGamePtr;
		//Windows Variables
		MountainDew() {};
		MountainDew(const MountainDew&) {};
		MountainDew(const MountainDew&&) {};
		MountainDew &operator=(const MountainDew&) {};
		MountainDew &operator=(const MountainDew&&) {};
		bool init = false;
		std::thread m_Thread;
	public:
		HINSTANCE m_hInst;
		HWND m_HWnd;
		LONG m_uiScreenHeight = 1080;
		LONG m_uiScreenWidth = 1920;
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
}
extern "C"
{
	__declspec(dllexport) void UpdateEngine();
}

extern "C"
{
	__declspec(dllexport) void ShutdownEngine();
}
