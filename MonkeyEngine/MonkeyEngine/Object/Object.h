#pragma once
#include <string>
#include "../ReturnValues.h"
using namespace std;
namespace MEObject
{
	class Object
	{
	private:
		string m_sName;
		unsigned int m_uiFlags;
	public:
		Object();
		~Object();
	protected:
		virtual void Initialize() {};
		virtual MEReturnValues::RETURNVALUE Update() { return MEReturnValues::NOTHING; };
		virtual void ShutDown() {};
	};

}
 