#pragma once
#include <cstdio>
#include <fstream>

namespace MonkeyEngine
{
	struct Header
	{
		int size;
		bool used;
	};
	struct Footer
	{
		int size;
		bool used;
	};
	static void* m_pMemory = nullptr;
	static void* m_pEndMemory = nullptr;
	const float m_fPercentComplete = 0.75f;
	static bool init = false;
	void Initialize(std::size_t size);
	void* Allocate(std::size_t count);
	void DeAllocate(void* ptr);
	void Shutdown();

	//void* ::operator new  (std::size_t count);
	//void* ::operator new[](std::size_t count);
	//void ::operator delete(void* ptr);
	//void ::operator delete[](void* ptr);
}