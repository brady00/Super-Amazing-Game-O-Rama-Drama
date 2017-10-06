#pragma once
#include "GameObject\GameObject.h"
#include "Base\Component.h"
namespace Editor {
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








	/// <summary>
	/// Summary for ComponentPanel
	/// </summary>
	public ref class ComponentPanel :  public System::Windows::Forms::Panel
	{
	public:
		ComponentPanel(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		ComponentPanel(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ComponentPanel()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		StringToVariableDictionary mapToVariable;
		/// <summary>
		/// Required designer variable.
		/// </summary>
	public: static const System::Drawing::Point ComponentStartingLocation = System::Drawing::Point(3,107);
	public: MonkeyEngine::MEObject::GameObject* GOParent;
	public: MonkeyEngine::MEObject::Component* Comp;
	public: unsigned int Index;
	private: System::Windows::Forms::Label ^CompLabel;
	private: System::Windows::Forms::Button ^CollapseButton;
	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			components = gcnew System::ComponentModel::Container();
			this->CollapseButton = gcnew System::Windows::Forms::Button();
			this->CompLabel = gcnew System::Windows::Forms::Label();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->CompLabel->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->CompLabel->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->CompLabel->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, ((System::Byte)(0)));
			this->CompLabel->Location = System::Drawing::Point(25, 5);
			this->CompLabel->Name = "label1";
			this->CompLabel->Size = System::Drawing::Size(200, 13);
			this->CompLabel->TabIndex = 3;
			this->CompLabel->Text = "Component";
			// 
			// CollapseButton
			// 
			this->CollapseButton->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->CollapseButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlDarkDark;
			this->CollapseButton->FlatAppearance->MouseDownBackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->CollapseButton->FlatAppearance->MouseOverBackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->CollapseButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CollapseButton->Location = System::Drawing::Point(0, 0);
			this->CollapseButton->Name = "CollapseButton";
			this->CollapseButton->Size = System::Drawing::Size(19, 23);
			this->CollapseButton->TabIndex = 1;
			this->CollapseButton->Text = ">";
			this->CollapseButton->UseVisualStyleBackColor = false;
			this->CollapseButton->Click += gcnew System::EventHandler(this, &ComponentPanel::CollapseButton_Click);
			// 
			// ComponentPanel
			// 
			this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->Controls->Add(this->CompLabel);
			this->Controls->Add(this->CollapseButton);
			this->Location = System::Drawing::Point(-1, 107);
			this->MaximumSize = System::Drawing::Size(335, 0);
			this->MinimumSize = System::Drawing::Size(335, 23);
			this->Name = "panel1";
			this->Size = System::Drawing::Size(335, 23);
			this->TabIndex = 18;
			this->ResumeLayout(false);
			this->PerformLayout();
		}

	private: void CollapseButton_Click(System::Object^ sender, System::EventArgs^ e);
	public: void CreatePanel(Panel^ InspectorBackgroundPanel, unsigned int Index);
#pragma endregion
	};
}
