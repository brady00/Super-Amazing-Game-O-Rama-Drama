#pragma once
#include "../../Components/Behaviour/Animation.h"
#include <unordered_map>
namespace MonkeyEngine
{
	class Blender
	{
	private:
		std::unordered_map<std::string, MEObject::Animation*> m_vAnimations;
	public:
		Blender();
		~Blender();
		void Play(std::string _NextAnim, std::string _CurrentAnim, float _CurrentAnimTimePassed, float _NextAnimTimePassed, bool _Looping, std::vector<XMFLOAT4X4>& _outSkeleton) {};
	};
}
