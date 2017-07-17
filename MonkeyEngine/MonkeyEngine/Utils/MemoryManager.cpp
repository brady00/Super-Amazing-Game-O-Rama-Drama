#include "MemoryManager.h"
#include <cstdlib>
#include <cstring>

void Initialize(std::size_t size)
{
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

void* Allocate(std::size_t count)
{
	if (!init)
		Initialize(999999);
	bool Used = ((Header*)m_pMemory)->used;
	char* temp = (char*)m_pMemory;
	while (Used == true)
	{
		int size = ((Header*)temp)->size;
		temp += sizeof(Header);
		temp += size;
		temp += sizeof(Footer);
		int allocatesize = (int)count + sizeof(Header) + sizeof(Footer);
		if (((Header*)temp)->size == 0 || ((Header*)temp)->size > allocatesize)
			Used = ((Header*)temp)->used;
		else
			Used = true;
	}
	int size = ((Header*)temp)->size;
	if (size > 999999 || size <= 0)
		int x = 0;
	((Header*)temp)->size = (int)count;
	((Header*)temp)->used = true;
	void* Return = temp + sizeof(Header);
	temp += sizeof(Header);
	temp += count;
	((Footer*)temp)->size = (int)count;

	((Footer*)temp)->used = true;

	temp += sizeof(Footer);

	if (size - sizeof(Header) - count - sizeof(Footer) != 0)
	{
		((Header*)temp)->size = size;
		((Header*)temp)->size -= sizeof(Header);
		((Header*)temp)->size -= (int)count;
		((Header*)temp)->size -= sizeof(Footer);

		((Header*)temp)->used = false;
		if (((Header*)temp)->size <= 0)
			int x = 0;

		size_t headersize = ((Header*)temp)->size;

		temp += sizeof(Header);
		temp += headersize;
		((Footer*)temp)->size = size;
		((Footer*)temp)->size -= sizeof(Header);
		((Footer*)temp)->size -= (int)count;
		((Footer*)temp)->size -= sizeof(Footer);
	}
	else
		int x = 0;

	std::ofstream Output;
	Output.open("MemoryMangerDebug.txt", std::ios_base::app);
	Output << "Data Location: " << (void*)Return << " Data Size: " << count << "\n";
	Output.close();
	return Return;
}

void DeAllocate(void* ptr)
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
		LeftUsed = false;
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
		RightUsed = false;
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
}

void Shutdown()
{

}

void* ::operator new  (std::size_t count)
{
	return Allocate(count);
}

void* ::operator new[](std::size_t count)
{
	return Allocate(count);
}

void ::operator delete(void* ptr)
{
	DeAllocate(ptr);
}

void ::operator delete[](void* ptr)
{
	DeAllocate(ptr);
}