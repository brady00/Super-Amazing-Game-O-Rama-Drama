#pragma once
//#include "Behaviour/Animation.h"
#pragma warning(disable: 4793)
#include <DirectXMath.h>
#include <vector>
#include <unordered_map>
namespace MonkeyEngine
{
	class Blender
	{
	private:
		//std::unordered_map<std::string, MEObject::Animation*> m_vAnimations;
	public:
		Blender();
		~Blender();
		void Play(std::string _NextAnim, std::string _CurrentAnim, float _CurrentAnimTimePassed, float _NextAnimTimePassed, bool _Looping, std::vector<DirectX::XMFLOAT4X4>& _outSkeleton) {};
	};
}
