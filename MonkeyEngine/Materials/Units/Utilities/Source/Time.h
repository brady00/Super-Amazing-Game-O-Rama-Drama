#pragma once
#include <Windows.h>
namespace MonkeyEngine
{
	class  __declspec(dllexport) Time
	{
	private:
		static __int64 m_iTimeStart;
		static __int64 m_dPrevFrame;
		static float DeltaTime;
		static float TimeSinceStart;
	public:
		static void Initialize();
		static void Update();
		static float GetDeltaTime();
		static float GetTimeSinceStart();
	};
}
