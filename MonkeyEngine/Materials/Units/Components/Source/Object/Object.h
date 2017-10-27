#pragma once
#pragma warning(disable: 4561)
#pragma warning(disable: 4793)
#pragma warning(disable: 4251)
#include <string>
#include "MemoryManager.h"
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
			void* operator new(std::size_t count)
			{
				return MonkeyEngine::MemoryManager::GetInstance()->Allocate(count);
			}
			void* operator new[](std::size_t count)
			{
				return MonkeyEngine::MemoryManager::GetInstance()->Allocate(count);
			}
			void operator delete(void* const ptr) noexcept
			{
				MonkeyEngine::MemoryManager::GetInstance()->DeAllocate(ptr);
			}
			void operator delete[](void* ptr)
			{
				MonkeyEngine::MemoryManager::GetInstance()->DeAllocate(ptr);
			}
		private:
			virtual void Initialize() {};
			virtual void Update() {};
			virtual void ShutDown() {};
		};
	}
}