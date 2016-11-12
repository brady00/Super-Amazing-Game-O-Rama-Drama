#pragma once
#include <Windows.h>
#include "../../Renderer/Renderer.h"

class MountainDew
{
private:
	//static Instance for Singleton
	static MountainDew *m_pGamePtr;
	//Windows Variables
	HINSTANCE m_hInst;										
	HWND m_HWnd;
	LONG m_uiScreenHeight = 1080;
	LONG m_uiScreenWidth = 1920;
	MERenderer::Renderer* m_pRenderer = nullptr;
	MountainDew() {};
	MountainDew(const MountainDew&) {};
	MountainDew(const MountainDew&&) {};
	MountainDew &operator=(const MountainDew&) {};
	MountainDew &operator=(const MountainDew&&) {};
public:
	static MountainDew* GetInstance() { if (!m_pGamePtr) m_pGamePtr = new MountainDew;  return m_pGamePtr; }
	static void DestroyInstance() { if (m_pGamePtr) delete m_pGamePtr; m_pGamePtr = m_pGamePtr; }
	void Initialize(HINSTANCE, int);
	void Update();
	~MountainDew() {};
};

