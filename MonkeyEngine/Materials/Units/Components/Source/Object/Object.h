#pragma once
#pragma warning(disable: 4251)
#include <string>
using namespace std;
namespace MonkeyEngine
{
	namespace MEObject
	{
		class __declspec(dllexport) Object
		{
			friend class GameObject;
		protected:
			string m_sName;
			unsigned int m_uiFlags;
		public:
			Object();
			virtual ~Object();
			string GetName();
			const char *GetCharName();
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