#include "MemoryManager.h"


namespace MonkeyEngine
{
	static int MemorySize = 0;
	static void* m_pMemory = nullptr;
	static void* m_pEndMemory = nullptr;
	const float m_fPercentComplete = 0.75f;
	static bool init = false;
	MemoryManager* MemoryManager::GetInstance()
	{
		static MemoryManager m_MemoryManager;
		return &m_MemoryManager;
	}

	void MemoryManager::Initialize(std::size_t size)
	{
		MemorySize = size;
		m_pMemory = std::malloc(size + sizeof(Header) + sizeof(Footer));
		((Header*)m_pMemory)->size = (int)size;
		((Header*)m_pMemory)->used = false;
		char* temp = (char*)m_pMemory;
		temp += sizeof(Header) + size;
		((Footer*)temp)->size = (int)size;
		((Footer*)temp)->used = false;
		m_pEndMemory = temp;
		temp -= size;
		memset(temp, 0, size);
		init = true;
		std::ofstream Output;
		Output.open("MemoryMangerDebug.txt");
		if (Output.is_open())
			Output << "Memory Start: " << m_pMemory << "\nMemory End: " << m_pEndMemory << "\n";
		Output.close();
	}
	void* MemoryManager::Allocate(std::size_t count)
	{
		if (!init)
			Initialize(100000000);
		bool Used = ((Header*)m_pMemory)->used;
		char* temp = (char*)m_pMemory;
		while (Used == true)
		{
			int size = ((Header*)temp)->size;
			temp += sizeof(Header);
			temp += size;
			temp += sizeof(Footer);
			int allocatesize = (int)count + sizeof(Header) + sizeof(Footer);
			if (((Header*)temp)->size > 9999999)
				int x = 0;
			if (((Header*)temp)->size == 0 || ((Header*)temp)->size > allocatesize)
				Used = ((Header*)temp)->used;
			else
				Used = true;
		}
		int size = ((Header*)temp)->size;
		((Header*)temp)->size = (int)count;
		((Header*)temp)->used = true;
		void* Return = temp + sizeof(Header);
		memset(Return, 7, count);
		temp += sizeof(Header);
		temp += count;
		((Footer*)temp)->size = (int)count;

		((Footer*)temp)->used = true;

		temp += sizeof(Footer);

		((Header*)temp)->size = size;
		((Header*)temp)->size -= sizeof(Header);
		((Header*)temp)->size -= (int)count;
		((Header*)temp)->size -= sizeof(Footer);

		((Header*)temp)->used = false;

		size_t headersize = ((Header*)temp)->size;

		temp += sizeof(Header);
		temp += headersize;
		((Footer*)temp)->size = size;
		((Footer*)temp)->size -= sizeof(Header);
		((Footer*)temp)->size -= (int)count;
		((Footer*)temp)->size -= sizeof(Footer);

		std::ofstream Output;
		Output.open("MemoryMangerDebug.txt", std::ios_base::app);
		Output << "Data Location: " << (void*)Return << " Data Size: " << count << "\n";
		Output.close();
		if (!HeapWalk())
			int x = 0;
		return Return;
	}
	void MemoryManager::Shutdown()
	{
		std::free(m_pMemory);
	}
	void MemoryManager::DeAllocate(void* ptr)
	{
		if (ptr == nullptr)
			return;
		bool LeftUsed, RightUsed;
		int LeftSize, MiddleSize, RightSize;
		char* temp = (char*)ptr;
		temp -= sizeof(Header);
		if ((void*)temp != m_pMemory)
		{
			temp -= sizeof(Footer);
			LeftSize = ((Footer*)temp)->size;
			LeftUsed = ((Footer*)temp)->used;
		}
		else
			LeftUsed = true;
		temp = (char*)ptr;
		temp -= sizeof(Header);
		MiddleSize = ((Header*)temp)->size;
		int size = ((Header*)temp)->size;
		temp += sizeof(Header) + size;
		if ((void*)temp != m_pEndMemory)
		{
			temp += sizeof(Footer);
			RightUsed = ((Header*)temp)->used;
			RightSize = ((Header*)temp)->size;
		}
		else
			RightUsed = true;
		memset(ptr, 6, MiddleSize);
		std::ofstream Output;
		Output.open("MemoryMangerDebug.txt", std::ios_base::app);
		Output << "Data Location: " << ptr << " Left used: " << LeftUsed << " Right Used: " << RightUsed << "\n";
		Output.close();
		if (!LeftUsed && !RightUsed)
		{
			temp = (char*)ptr;
			temp -= sizeof(Header);
			temp -= sizeof(Footer);
			size = ((Footer*)temp)->size;
			temp -= size;
			temp -= sizeof(Header);
			((Header*)temp)->size = LeftSize + sizeof(Footer) + sizeof(Header) + MiddleSize + sizeof(Footer) + sizeof(Header) + RightSize;
			((Header*)temp)->used = false;
			size = ((Header*)temp)->size;
			temp += sizeof(Header) + size;
			((Footer*)temp)->size = LeftSize + sizeof(Footer) + sizeof(Header) + MiddleSize + sizeof(Footer) + sizeof(Header) + RightSize;
			((Footer*)temp)->used = false;
		}
		else if (!LeftUsed)
		{
			temp = (char*)ptr;
			temp -= sizeof(Header);
			temp -= sizeof(Footer);
			size = ((Footer*)temp)->size;
			temp -= size;
			temp -= sizeof(Header);
			((Header*)temp)->size = LeftSize + sizeof(Footer) + sizeof(Header) + MiddleSize;
			((Header*)temp)->used = false;
			size = ((Header*)temp)->size;
			temp += sizeof(Header) + size;
			((Footer*)temp)->size = LeftSize + sizeof(Footer) + sizeof(Header) + MiddleSize;
			((Footer*)temp)->used = false;
		}
		else if (!RightUsed)
		{
			temp = (char*)ptr;
			temp -= sizeof(Header);
			((Header*)temp)->size = MiddleSize + sizeof(Footer) + sizeof(Header) + RightSize;
			((Header*)temp)->used = false;
			size = ((Header*)temp)->size;
			temp += sizeof(Header) + size;
			((Footer*)temp)->size = MiddleSize + sizeof(Footer) + sizeof(Header) + RightSize;
			((Footer*)temp)->used = false;
		}
		else
		{
			temp = (char*)ptr;
			temp -= sizeof(Header);
			((Header*)temp)->used = false;
			size = ((Header*)temp)->size;
			temp += sizeof(Header) + size;
			((Footer*)temp)->used = false;
			((Footer*)temp)->size = (int)size;
		}
		temp = (char*)m_pMemory;
		temp += sizeof(Header);
		if (((Header*)m_pMemory)->size == MemorySize && m_bShuttingDown)
			Shutdown();
		if (!HeapWalk())
			int x = 0;
	}

	bool MemoryManager::HeapWalk()
	{
		try
		{
			char* temp = (char*)m_pMemory;
			char* end = (char*)m_pEndMemory + sizeof(Footer);
			while (temp != end)
			{
				int size = ((Header*)temp)->size;

				temp += sizeof(Header);

				temp += size;
				if (((Footer*)temp)->size != size)
				{
					temp -= size;
					return false;
				}
				temp += sizeof(Footer);
			}
		}
		catch (std::exception e)
		{
			return false;
		}
		return true;
	}
}
