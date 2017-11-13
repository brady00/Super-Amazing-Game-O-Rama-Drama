#include "CriticalRegion.h"

namespace MonkeyEngine
{
	std::unordered_map<void*, std::mutex*> CriticalRegion::threads;

	void CriticalRegion::Enter(void* obj)
	{
		if (!threads[obj])
			threads[obj] = new std::mutex();
		threads[obj]->lock();
	}

	void CriticalRegion::Exit(void* obj)
	{
		if (threads[obj])
			threads[obj]->unlock();
	}
}