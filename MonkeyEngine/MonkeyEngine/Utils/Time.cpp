#include "Time.h"

__int64	Time::m_iTimeStart =0;
__int64	Time::m_dPrevFrame = 0;
float	Time::DeltaTime = 0;
float	Time::TimeSinceStart = 0;

void Time::Initialize()
{
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	QueryPerformanceCounter(&li);
	m_iTimeStart = li.QuadPart;
	m_dPrevFrame = m_iTimeStart;
}


void Time::Update()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	DeltaTime = (float)(double(li.QuadPart - m_dPrevFrame) / 10000.0);
	TimeSinceStart = (float)(double(li.QuadPart - m_iTimeStart) / 10000.0);
	m_dPrevFrame = li.QuadPart;
}
