#pragma once
#include <string>
#include "../Utils/ReturnValues.h"
using namespace std;
namespace MEObject
{
	class Object
	{
		friend class GameObject;
	private:
		string m_sName;
		unsigned int m_uiFlags;
	public:
		Object();
		~Object();
	private:
		virtual void Initialize() {};
		virtual MEReturnValues::RETURNVALUE Update() { return MEReturnValues::NOTHING; };
		virtual void ShutDown() {};
	};

}
 