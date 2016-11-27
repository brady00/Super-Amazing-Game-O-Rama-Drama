#pragma once
#include "../Base/Component.h"
namespace MEObject
{
	class CompRenderer : public Component
	{
	private:

	public:
		CompRenderer();
		~CompRenderer();
		explicit operator Object*() { return this; };
		operator Object() { return *this; }
	};
}

