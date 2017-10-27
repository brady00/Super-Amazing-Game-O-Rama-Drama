#pragma once
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cstring>

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
	class __declspec(dllexport) MemoryManager
	{
	private:
		MemoryManager() {};
		~MemoryManager() {};
	public:
		void Initialize(std::size_t size);
		void* Allocate(std::size_t count);
		void Shutdown();
		void DeAllocate(void* ptr);
		static MemoryManager* GetInstance();
	};
}

