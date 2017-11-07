#pragma once
#include <Windows.h>
#include "Renderer.h"
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
		~MountainDew() {};
		MountainDew(const MountainDew&) {};
		MountainDew(const MountainDew&&) {};
		MountainDew &operator=(const MountainDew&) { return *this; };
		MountainDew &operator=(const MountainDew&&) { return *this; };

	public:
		HINSTANCE m_hInst;
		HWND m_HWnd;
		MERenderer::Renderer* m_pRenderer = nullptr;
		Scene* m_pScene;
		bool m_bShuttingDown = false;
		//in: void
		//out: MountainDew*
		//	The One and Only MounatinDew instance
		//desc: Gets the One and only MountainDew instance
		static MountainDew* GetInstance() { if (!m_pGamePtr) m_pGamePtr = new MountainDew;  return m_pGamePtr; }
		//in: void
		//out: void
		//desc: Deletes the One and only MountainDew instance
		static void DestroyInstance() { if (m_pGamePtr) delete m_pGamePtr; m_pGamePtr = m_pGamePtr; }
		//in: HINSTANCE
		//	The Handle for the Window
		//out: int
		//	The binary flags for the Window
		//desc: Creates a windows and Initializes the Renderer, and the Scene
		void Initialize(HINSTANCE, int);
		//in: void
		//out: void
		//desc: Updates the Scene and then the Renderer
		void Update();
		//in: void
		//out: void
		//desc: Cleans up all memory
		void Shutdown();
		//in: void
		//out: void
		//desc: Meant to be threaded, used to updated DeltaTime, and the Game, but not the Renderer
		void UpdateGame();
	};

}
//in: HWND
//	The Handle for the Window
//in: int
//	The Width of the Screen
//in: int
//	The Height of the Screen
//out: const char*
//	The .MES file to load
//desc: Initializes the Renderer, and the Scene
void __declspec(dllexport) InitializeEngine(HWND window, int _ScreenWidth, int _ScreenHeight, const char* _SceneFileName);
//in: int
//	The Width of the Screen
//out: int
//	The Height of the Screen
//desc: Reinitializes the Renderer with the new Screen width and height
void __declspec(dllexport) ResizeEngine(int _ScreenWidth, int _ScreenHeight);
//in: void
//out: void
//desc: Updates the Scene and then the Renderer
void __declspec(dllexport) UpdateEngine();
//in: void
//out: void
//desc: Cleans up all Memory
void __declspec(dllexport) ShutdownEngine();
//in: int
//	The Mouse Key that is Down
//out: void
//desc: Called when the Mouse is Down on the RenderingPanel of the Editor
void __declspec(dllexport) MouseDown_RenderingPanel(int key);
//in: int
//	The Mouse Key that is Up
//out: void
//desc: Called when Mouse is Up on the RenderingPanel of the Editor
void __declspec(dllexport) MouseUp_RenderingPanel(int key);
//in: void
//out: void
//desc: Runs the Game in a seperate Window
void __declspec(dllexport) RunGameWindow();
//in: void
//out: void
//desc: Runs the Game in a seperate VR Window
void __declspec(dllexport) RunGameVR();
//in: RState
//	The new State of the Renderer
//out: void
//desc: Sets the State of the Renderer
void __declspec(dllexport) SetMonkeyEngineRenderState(RenderState::RState State);
//in: string&
//	The name of the .MES file to be loaded
//out: float&
//	The percent done with the Load
//out: bool&
//	Whether the load Succeeded or Failed
//out: void
//desc: Loads a .MES file into a Scene
void __declspec(dllexport) LoadMonkeyEngineScene(string& _FileName, float& percentLoaded, bool& Success);
//in: string&
//	The name of the .MES file to be loaded
//out: bool
//	Whether the Save Succeeded or Failed
//desc: Saves a .MES file from the Scene
bool __declspec(dllexport) SaveMonkeyEngineScene(string& _FileName);
//in: void
//out: vector<GameObject*>
//	The GameObjects in the Scene
//desc: Gets the GameObjects in the Scene
std::vector<MonkeyEngine::MEObject::GameObject*> __declspec(dllexport)&GetSceneObjects();

