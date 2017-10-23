#pragma once
#include "GameObject\GameObject.h"
#include "Base\Component.h"
#include "StringToVariableDictionary.h"
namespace Editor {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Reflection;
	using namespace System::Reflection::Emit;
	using namespace System::Diagnostics;
	using namespace Windows::Forms;
	enum PanelMode { DEBUG = 0, DEFAULT };
	/// <summary>
	/// Summary for ComponentPanel
	/// </summary>
	public ref class ComponentPanel : public System::Windows::Forms::UserControl
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
	public: static const System::Drawing::Point ComponentStartingLocation = System::Drawing::Point(0, 100);
	public: MonkeyEngine::MEObject::GameObject* GOParent;
	public: MonkeyEngine::MEObject::Component* Comp;
	public: unsigned int Index;
	protected: System::Windows::Forms::Label ^CompLabel;
	protected: System::Windows::Forms::Button ^CollapseButton;
	protected: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			   /// <summary>
			   /// Required method for Designer support - do not modify
			   /// the contents of this method with the code editor.
			   /// </summary>
	protected: void InitializeComponent(void)
	{
		this->CollapseButton = (gcnew System::Windows::Forms::Button());
		this->CompLabel = (gcnew System::Windows::Forms::Label());
		this->SuspendLayout();
		// 
		// CollapseButton
		// 
		this->CollapseButton->BackColor = System::Drawing::SystemColors::ControlDarkDark;
		this->CollapseButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::ControlDarkDark;
		this->CollapseButton->FlatAppearance->MouseDownBackColor = System::Drawing::SystemColors::ControlDarkDark;
		this->CollapseButton->FlatAppearance->MouseOverBackColor = System::Drawing::SystemColors::ControlDarkDark;
		this->CollapseButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->CollapseButton->Location = System::Drawing::Point(0, 0);
		this->CollapseButton->Name = L"CollapseButton";
		this->CollapseButton->Size = System::Drawing::Size(19, 23);
		this->CollapseButton->TabIndex = 1;
		this->CollapseButton->Text = L">";
		this->CollapseButton->UseVisualStyleBackColor = false;
		this->CollapseButton->Click += gcnew System::EventHandler(this, &ComponentPanel::CollapseButton_Click);
		// 
		// CompLabel
		// 
		this->CompLabel->BackColor = System::Drawing::SystemColors::ControlDarkDark;
		this->CompLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->CompLabel->Location = System::Drawing::Point(25, 5);
		this->CompLabel->Name = L"CompLabel";
		this->CompLabel->Size = System::Drawing::Size(200, 13);
		this->CompLabel->TabIndex = 3;
		this->CompLabel->Text = L"Component";
		// 
		// ComponentPanel
		// 
		this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
		this->Controls->Add(this->CompLabel);
		this->Controls->Add(this->CollapseButton);
		this->Location = System::Drawing::Point(-1, 107);
		this->MaximumSize = System::Drawing::Size(335, 0);
		this->MinimumSize = System::Drawing::Size(335, 23);
		this->Name = L"ComponentPanel";
		this->Size = System::Drawing::Size(335, 23);
		this->ResumeLayout(false);

	}

	private: void CollapseButton_Click(System::Object^ sender, System::EventArgs^ e);
	public: virtual void CreatePanel(Panel^ InspectorBackgroundPanel, unsigned int Index);
#pragma endregion
	};
}
