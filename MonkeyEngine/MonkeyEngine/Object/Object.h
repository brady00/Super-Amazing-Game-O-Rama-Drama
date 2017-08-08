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
		protected:
			string m_sName;
			unsigned int m_uiFlags;
		public:
			Object();
			virtual ~Object();
			string __declspec(dllexport) GetName();
			void __declspec(dllexport) SetName(std::string _Name);
			unsigned int __declspec(dllexport) GetFlags();
			void __declspec(dllexport) SetFlags(unsigned int _Flags);
		private:
			virtual void Initialize() {};
			virtual void Update() {};
			virtual void ShutDown() {};
		};
	}
}