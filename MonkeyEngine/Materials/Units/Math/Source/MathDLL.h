#pragma once
#ifdef MATH_EXPORTS
#define MATH_EXPORT __declspec(dllexport)
#else
#define MATH_EXPORT __declspec(dllimport)
#endif