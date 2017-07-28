#pragma once
#include <string>
using namespace std;
namespace MonkeyEngine
{
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
			virtual ~Object();
			string GetName();
			void SetName(std::string _Name);
			unsigned int GetFlags();
			void SetFlags(unsigned int _Flags);
		private:
			virtual void Initialize() {};
			virtual void Update() {};
			virtual void ShutDown() {};
		};
	}
}