#include "ComponentPanel.h"
#include "Editor.h"
#include <unordered_map>
namespace Editor
{
	using namespace System::Reflection;
	using namespace Runtime::InteropServices;
	using namespace System::Collections;
	void ComponentPanel::CollapseButton_Click(System::Object^ sender, EventArgs^ e)
	{
		if (CollapseButton->Text == ">")
		{
			CollapseButton->Text = "V";
			this->Size = System::Drawing::Size(this->Width, this->MaximumSize.Height);
			Editor::ButtonExpanded(Index, GOParent);
			for (int i = 0; i < this->Controls->Count; i++)
				this->Controls[i]->Visible = true;
		}
		else
		{
			CollapseButton->Text = ">";
			this->Size = System::Drawing::Size(this->Width, this->MinimumSize.Height);
			Editor::ButtonCollapsed(Index, GOParent);
			for (int i = 0; i < this->Controls->Count; i++)
				if(this->Controls[i] != this->CompLabel && this->Controls[i] != CollapseButton)
					this->Controls[i]->Visible = false;
		}
	}

	void ComponentPanel::CreatePanel(Panel^ InspectorBackgroundPanel, unsigned int Index)
	{
		System::Drawing::Point p = ComponentStartingLocation;
		p.Y += (int)Index * 30;
		InspectorBackgroundPanel->Controls->Add(this);
		this->Index = Index;
		this->Anchor = (System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right | System::Windows::Forms::AnchorStyles::Top);
		this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
		this->Location = p;
		this->MaximumSize = System::Drawing::Size(0, 200);
		this->MinimumSize = System::Drawing::Size(392, 30);
		this->Name = "ComponentPanel" + Index.ToString();
		this->Size = System::Drawing::Size(392, 30);
		this->TabIndex = 18;
		this->Visible = false;
		this->CompLabel->Text = gcnew System::String(Comp->GetCharName());
		this->CompLabel->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->CompLabel->Height = 20;
		this->CompLabel->ForeColor = Color::White;
		this->CollapseButton->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->CollapseButton->ForeColor = Color::White;
		this->AutoScroll = false;
		this->BringToFront();
		this->Invalidate();
	}
}