#pragma once
#include <Windows.h>
class Time
{
private:
	static __int64 m_iTimeStart;
	static __int64 m_dPrevFrame;
public:
	static void Initialize();
	static void Update();
	static float DeltaTime;
	static float TimeSinceStart;
};

