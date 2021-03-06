#include "MountainDew.h"

#include <dxgi1_3.h>
#include <wrl.h>
#include <D3Dcompiler.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <openvr.h>
#include <atlcomcli.h>
#include "Settings.h"
#include "Time.h"
#include "FileIO.h"
#include "DebugCamera\DebugCamera.h"
#include "MemoryManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR commandLine, int nCmdShow)
{
	MSG msg;
	MonkeyEngine::MountainDew::GetInstance()->Initialize(hInstance, nCmdShow);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		MonkeyEngine::MountainDew::GetInstance()->Update();
	}
	MonkeyEngine::MountainDew::GetInstance()->Shutdown();
	MonkeyEngine::MountainDew::DestroyInstance();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		MonkeyEngine::MountainDew::GetInstance()->m_bShuttingDown = true;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
namespace MonkeyEngine
{
	MountainDew* MountainDew::m_pGamePtr = nullptr;
	void MountainDew::UpdateGame()
	{
		while (!m_bShuttingDown)
		{
			Time::Update();
			m_pScene->Update();
		}
	}

	void MountainDew::Initialize(HINSTANCE hInstance, int nCmdShow)
	{
		m_hInst = hInstance;
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_CLASSDC;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = m_hInst;
		wc.lpszClassName = L"Title";
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
		RegisterClassEx(&wc);

		RECT window_size = { 0, 0, Settings::GetInstance()->GetScreenWidth(), Settings::GetInstance()->GetScreenHeight() };
		AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);
		m_HWnd = CreateWindow(L"Title", L"Monkey Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, window_size.right - window_size.left, window_size.bottom - window_size.top, NULL, NULL, m_hInst, NULL);
		DWORD temp;
		if (!m_HWnd)
		{
			temp = GetLastError();
		}
		ShowWindow(m_HWnd, nCmdShow);
		UpdateWindow(m_HWnd);
		InitializeEngine(m_HWnd, Settings::GetInstance()->GetScreenWidth(), Settings::GetInstance()->GetScreenHeight(), "Assets/Scenes/Default.mes");
	}

	void MountainDew::Update()
	{
		Time::Update();
		m_pScene->Update();
		m_pRenderer->Update();
	}

	void MountainDew::Shutdown()
	{
		MemoryManager::GetInstance()->m_bShuttingDown = true;
		m_pScene->Shutdown();
		delete m_pScene;
		//m_pSettings->Shutdown(); // Called in Settings Destructor
		delete m_pSettings;
		m_pRenderer->Shutdown();
		delete m_pRenderer;
	}
}
using namespace MonkeyEngine;
void InitializeEngine(HWND window, int _ScreenWidth, int _ScreenHeight, const char* _SceneFileName)
{
	int size = sizeof(window);
	MountainDew* temp = MountainDew::GetInstance();
	temp->m_pRenderer = new MERenderer::Renderer;
	temp->m_pRenderer->Initialize(window, _ScreenWidth, _ScreenHeight);
	Time::Initialize();
	Settings::GetInstance()->Initialize();
	std::vector<MEObject::GameObject*> objects;
	temp->m_pScene = new Scene;
	float _percentLoaded = 0.0f;
	bool Success = false;
	MEFileIO::FileIO::LoadScene(std::string(_SceneFileName), MountainDew::GetInstance()->m_pScene->m_vObjects, _percentLoaded, Success);
	while (!Success || _percentLoaded != 1.0f) {}
	temp->m_pScene->initialize(_ScreenWidth, _ScreenHeight);
}

void LoadMonkeyEngineScene(string& _FileName, float& _percentLoaded, bool& Success)
{
	Renderer::Reset();
	MountainDew::GetInstance()->m_pScene->Load(_FileName, _percentLoaded, Success);
}

bool SaveMonkeyEngineScene(string& _FileName)
{
	return MountainDew::GetInstance()->m_pScene->Save(_FileName);
}

void ResizeEngine(int _ScreenWidth, int _ScreenHeight)
{
	MountainDew* temp = MountainDew::GetInstance();
	Renderer* renderer = temp->m_pRenderer;
	if (temp != nullptr)
		renderer->Resize((UINT)_ScreenWidth, (UINT)_ScreenHeight);
	DebugCamera* Cam = MountainDew::GetInstance()->m_pScene->GetDebugCamera();
	if(Cam)
		Cam->Resize((float)_ScreenHeight, (float)_ScreenWidth);
}

void UpdateEngine()
{
	MountainDew::GetInstance()->Update();
}

void ShutdownEngine()
{
	MountainDew::GetInstance()->Shutdown();
	MountainDew::DestroyInstance();
}

void MouseDown_RenderingPanel(int key)
{
	switch (key)
	{
	case VK_LBUTTON:
		break;
	case VK_RBUTTON:
		ShowCursor(false);
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		DebugCamera::GetInstance()->RightMouseDown(cursorPos);
		break;
	case VK_MBUTTON:
		break;
	}
}

void MouseUp_RenderingPanel(int key)
{
	switch (key)
	{
	case VK_LBUTTON:
		break;
	case VK_RBUTTON:
		ShowCursor(true);
		DebugCamera::GetInstance()->RightMouseUp();
		break;
	case VK_MBUTTON:
		break;
	}
}

void RunGameWindow()
{

}

void RunGameVR()
{
	// Loading the SteamVR Runtime
	vr::EVRInitError eError = vr::VRInitError_None;
	vr::IVRSystem* pHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None)
	{
		pHMD = NULL;
		//char buf[1024];
		//sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		LPCTSTR buf = _T("Unable to launch SteamVR");
		MessageBox(NULL, buf, NULL, MB_OK);
		return;
	}
}

std::vector<MonkeyEngine::MEObject::GameObject*>& GetSceneObjects()
{
	return MountainDew::GetInstance()->m_pScene->GetObjects();
}

void SetMonkeyEngineRenderState(RenderState::RState State)
{
	RenderState::SetRenderState(State);
}