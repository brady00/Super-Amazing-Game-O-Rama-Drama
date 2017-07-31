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

extern "C"
{
	__declspec(dllexport) char GetObjectNameChar(MonkeyEngine::MEObject::Object* _object, unsigned int _index);
	__declspec(dllexport) unsigned int GetObjectNameSize(MonkeyEngine::MEObject::Object* _object);
	__declspec(dllexport) void SetObjectName(MonkeyEngine::MEObject::Object* _object, const char* _Name);
	__declspec(dllexport) unsigned int GetObjectFlags(MonkeyEngine::MEObject::Object* _object);
	__declspec(dllexport) void SetObjectFlags(MonkeyEngine::MEObject::Object* _object, unsigned int _Flags);
}