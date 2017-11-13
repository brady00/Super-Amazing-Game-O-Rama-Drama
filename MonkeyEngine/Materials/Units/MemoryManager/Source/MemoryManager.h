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
		~MemoryManager() { Shutdown(); };
	public:
		bool m_bShuttingDown = false;
		//in: size_t
		//	The Amount of Bytes to Allocate
		//out: void
		//desc: Creates a pool of Dynamic Memory to use
		void Initialize(std::size_t size);
		//in: size_t
		//	The Amount of Bytes to Allocate
		//out: void*
		//	Memory Address of the allocated Memory
		//desc: Gives a chunk of Memory from the Allocated pool
		void* Allocate(std::size_t count);
		//in: void
		//out: void
		//desc: Deletes the Pool of Memory
		void Shutdown();
		//in: void*
		//	The Memory Address of the chunk of the Allocated pool to delete
		//out: void
		//desc: Deletes the chunk of the Allocated pool
		void DeAllocate(void* ptr);
		//in: void
		//out: MemoryManager*
		//	The Only instance of the MemoryManager
		//desc: Gets the Only Instance of the MemoryManager
		static MemoryManager* GetInstance();
		//in: void
		//out: bool
		//	Wether the Heap is in tact or not
		//desc: Validates that the Heap is not corrupted
		bool HeapWalk();
	};
}

