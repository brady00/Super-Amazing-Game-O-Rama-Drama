#pragma once
#include <cstdio>
#include <cstdlib>
void* operator new(std::size_t count);
void* operator new[](std::size_t count);
void operator delete(void* const ptr);
void operator delete[](void* ptr);