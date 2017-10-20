#pragma once

namespace Editor
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Reflection;
	using namespace System::Reflection::Emit;
	using namespace System::Diagnostics;
	public ref class StringToVariableDictionary : public DictionaryBase
	{
	public:

		property MemberInfo^ Item[String^]
		{
			MemberInfo^ get(String^ key)
		{
			return (dynamic_cast<MemberInfo^>(Dictionary[key]));
		}

		void set(String^ key, MemberInfo^ value)
		{
			Dictionary[key] = value;
		}
		}

			property ICollection^ Keys
		{
			ICollection^ get()
			{
				return (Dictionary->Keys);
			}
		}

		property ICollection^ Values
		{
			ICollection^ get()
			{
				return (Dictionary->Values);
			}
		}
		void Add(String^ key, MemberInfo^ value)
		{
			Dictionary->Add(key, value);
		}

		bool Contains(String^ key)
		{
			return (Dictionary->Contains(key));
		}

		void Remove(String^ key)
		{
			Dictionary->Remove(key);
		}


	protected:
		virtual void OnInsert(Object^ key, Object^ value) override
		{
			if (key->GetType() != Type::GetType("String"))
				throw gcnew ArgumentException("key must be of type String.", "key");
			if (value->GetType() != Type::GetType("MemberInfo"))
				throw gcnew ArgumentException("value must be of type MemberInfo.", "value");
		}

		virtual void OnRemove(Object^ key, Object^ /*value*/) override
		{
			if (key->GetType() != Type::GetType("System.String"))
				throw gcnew ArgumentException("key must be of type String.", "key");
		}

		virtual void OnSet(Object^ key, Object^ /*oldValue*/, Object^ newValue) override
		{
			if (key->GetType() != Type::GetType("System.String"))
				throw gcnew ArgumentException("key must be of type String.", "key");
			if (newValue->GetType() != Type::GetType("MemberInfo"))
				throw gcnew ArgumentException("newValue must be of type MemberInfo.", "newValue");
		}

		virtual void OnValidate(Object^ key, Object^ value) override
		{
			if (key->GetType() != Type::GetType("System.String"))
				throw gcnew ArgumentException("key must be of type String.", "key");
			if (value->GetType() != Type::GetType("MemberInfo"))
				throw gcnew ArgumentException("value must be of type MemberInfo.", "value");
		}

	};
}