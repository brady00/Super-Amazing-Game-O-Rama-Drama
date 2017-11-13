#pragma once
#include <thread>
#include <mutex>
#include <unordered_map>
#ifdef CRITICALREGION_EXPORTS
#define CRITICALREGION_EXPORT __declspec(dllexport)
#else
#define CRITICALREGION_EXPORT __declspec(dllimport)
#endif
namespace MonkeyEngine
{
	class __declspec(dllexport) CriticalRegion
	{
	private:
		static std::unordered_map<void*, std::mutex*> threads;
	public:
		static void Enter(void* obj);
		static void Exit(void* obj);
	};
}
