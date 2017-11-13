#include "MemoryOverloads.h"
#include "MemoryManager.h"
void* operator new(std::size_t count)
{
	return MonkeyEngine::MemoryManager::GetInstance()->Allocate(count);
}
void* operator new[](std::size_t count)
{
	return MonkeyEngine::MemoryManager::GetInstance()->Allocate(count + 4);
}
void operator delete(void* const ptr)
{
	MonkeyEngine::MemoryManager::GetInstance()->DeAllocate(ptr);
}
void operator delete[](void* ptr)
{
	MonkeyEngine::MemoryManager::GetInstance()->DeAllocate(ptr);
}