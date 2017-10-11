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
			this->Size = System::Drawing::Size(this->MinimumSize.Width, 200);
			Editor::ButtonExpanded(Index, GOParent);
		}
		else
		{
			CollapseButton->Text = ">";
			this->Size = System::Drawing::Size(this->MinimumSize.Width, this->MinimumSize.Height);
			Editor::ButtonCollapsed(Index, GOParent);
		}
	}

	void ComponentPanel::CreatePanel(Panel^ InspectorBackgroundPanel, unsigned int Index)
	{
		System::Drawing::Point p = ComponentStartingLocation;
		p.Y += (int)Index * 23;
		InspectorBackgroundPanel->Controls->Add(this);
		this->Index = Index;
		this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
		this->Location = p;
		this->MaximumSize = System::Drawing::Size(335, 0);
		this->MinimumSize = System::Drawing::Size(335, 23);
		this->Name = "ComponentPanel" + Index.ToString();
		this->Size = System::Drawing::Size(335, 23);
		this->TabIndex = 18;
		this->Visible = false;
		this->CompLabel->Text = gcnew System::String(Comp->GetCharName());
		this->AutoScroll = false;
		this->BringToFront();
		this->Invalidate();
	}
}