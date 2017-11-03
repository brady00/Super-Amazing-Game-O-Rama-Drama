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
		//in: void								
		//out: void								
		//desc: Initializes a Timer				
		static void Initialize();
		//in: void								
		//out: void								
		//desc: Updates a Timer					
		static void Update();
		//in: void                             
		//out: float                           
		//    The Change in time between frames
		//desc: Gets the Time change between   
		//    frames                           
		static float GetDeltaTime();
		//in: void								 
		//out: float							
		//    The Change in time since the start of the Program					
		//desc: Gets the Time change between frames							
		static float GetTimeSinceStart();
	};
}
