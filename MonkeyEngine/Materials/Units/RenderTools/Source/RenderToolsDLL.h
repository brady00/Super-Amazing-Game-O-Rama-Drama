#pragma once
#include "MemoryOverloads.h"
#ifdef RENDERTOOLS_EXPORTS
#define RENDERTOOLS_EXPORT __declspec(dllexport)
#else
#define RENDERTOOLS_EXPORT __declspec(dllimport)
#endif