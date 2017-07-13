#pragma once
#include <cstdio>
#include <fstream>

struct Header
{
	std::size_t size;
	bool used;
};
struct Footer
{
	std::size_t size;
	bool used;
};
struct MemStruct
{
	Header* m_Header;
	void* m_Data;
	Footer* m_Footer;
};
static void* m_pMemory = nullptr;
static void* m_pEndMemory = nullptr;
const float m_fPercentComplete = 0.75f;
static bool init = false; 
void Initialize(std::size_t size);
void* Allocate(std::size_t count);
void DeAllocate(void* ptr);
void Shutdown();

void* ::operator new  (std::size_t count);
void* ::operator new[](std::size_t count);
void ::operator delete(void* ptr);
void ::operator delete[](void* ptr);