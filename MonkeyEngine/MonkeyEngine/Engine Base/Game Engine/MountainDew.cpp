#include "MountainDew.h"
#include "../Settings/Settings.h"
#include "../../Utils/Time.h"
#include "../../Utils/FileIO.h"

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
		InitializeEngine(m_HWnd, Settings::GetInstance()->GetScreenWidth(), Settings::GetInstance()->GetScreenHeight());
	}

	void MountainDew::Update()
	{
		Time::Update();
		m_pScene->Update();
		m_pRenderer->Update();
	}

	void MountainDew::Shutdown()
	{
		m_pScene->Shutdown();
		delete m_pScene;
		//m_pSettings->Shutdown(); // Called in Settings Destructor
		delete m_pSettings;
		m_pRenderer->Shutdown();
		delete m_pRenderer;
	}
}
using namespace MonkeyEngine;
void InitializeEngine(HWND window, int _ScreenWidth, int _ScreenHeight)
{
	int size = sizeof(window);
	MountainDew* temp = MountainDew::GetInstance();
	temp->m_pRenderer = new MERenderer::Renderer;
	temp->m_pRenderer->Initialize(window, _ScreenWidth, _ScreenHeight);
	Time::Initialize();
	Settings::GetInstance()->Initialize("../../../MonkeyEngine/Engine Base/Settings/config.txt");
	std::vector<MEObject::GameObject*> objects;
	temp->m_pScene = new Scene;
	temp->m_pScene->initialize(_ScreenWidth, _ScreenHeight);
	MEFileIO::FileIO::LoadScene("../MonkeyEngine/Assets/Scenes/TestScene.mes", temp->m_pScene->m_vObjects);
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

std::vector<MonkeyEngine::MEObject::GameObject*>& GetSceneObjects()
{
	return MountainDew::GetInstance()->m_pScene->GetObjects();
}