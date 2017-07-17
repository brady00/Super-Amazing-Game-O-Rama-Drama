#include "MountainDew.h"
#include "../Scene/Scene.h"
#include "../../Utils/Time.h"
#include "../../Utils/FileIO.h"

MountainDew* MountainDew::m_pGamePtr = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR commandLine, int nCmdShow)
{
	MSG msg;
	MountainDew::GetInstance()->Initialize(hInstance, nCmdShow);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		MountainDew::GetInstance()->Update();
	}
	MountainDew::GetInstance()->Shutdown();
	MountainDew::DestroyInstance();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		MountainDew::GetInstance()->m_bShuttingDown = true;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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

	RECT window_size = { 0, 0, m_uiScreenWidth, m_uiScreenHeight };
	AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);
	m_HWnd = CreateWindow(L"Title", L"Monkey Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, window_size.right - window_size.left, window_size.bottom - window_size.top, NULL, NULL, m_hInst, NULL);
	DWORD temp;
	if (!m_HWnd)
	{
		temp = GetLastError();
	}
	ShowWindow(m_HWnd, nCmdShow);
	UpdateWindow(m_HWnd);
	m_pRenderer = new MERenderer::Renderer;
	m_pRenderer->Initialize(m_HWnd, m_uiScreenWidth, m_uiScreenHeight);
	Time::Initialize();
	std::vector<MEObject::GameObject*> objects;
	m_pScene = new Scene;
	m_pScene->initialize(m_uiScreenWidth, m_uiScreenHeight);
	MEFileIO::FileIO::LoadScene("Assets/Scenes/TestScene.mes", m_pScene->m_vObjects);
}

void MountainDew::Update()
{
	if (!init)
	{
		m_Thread = std::thread(&MountainDew::UpdateGame, this);
		init = true;
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		m_bShuttingDown = true;
		PostQuitMessage(0);
	}
	m_pRenderer->Update();
}

void MountainDew::Shutdown()
{
	//m_Thread.join();
	m_pScene->Shutdown();
	delete m_pScene;	m_pRenderer->Shutdown();
	delete m_pRenderer;
}
