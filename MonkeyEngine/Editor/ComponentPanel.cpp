#include "ComponentPanel.h"
#include "MyForm.h"
namespace Editor
{
	void ComponentPanel::CollapseButton_Click(System::Object^ sender, EventArgs^ e)
	{
		if (CollapseButton->Text == ">")
		{
			CollapseButton->Text = "V";
			this->Size = System::Drawing::Size(this->MinimumSize.Width, 200);
			MyForm::ButtonExpanded(Index, Parent);
		}
		else
		{
			CollapseButton->Text = ">";
			this->Size = System::Drawing::Size(this->MinimumSize.Width, this->MinimumSize.Height);
			MyForm::ButtonCollapsed(Index, Parent);
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
		/*System::Reflection::BindingFlags bindingFlags = System::Reflection::BindingFlags::Instance | System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Public;
		if (Comp->GetName() == "Transform")
			FunctionNames = typeof(Tranform).GetMethods(bindingFlags).Select(field = > field.Name).ToList();
		else
			FunctionNames = new List<string>();
		foreach(string str in FunctionNames)
		{
			if (str.Contains("get_") && !str.Contains("_Name") && !str.Contains("_Flags"))
				Getters.Add(Comp.GetType().GetMethod(str));
			if (str.Contains("set_") && !str.Contains("_Name") && !str.Contains("_Flags"))
				Setters.Add(Comp.GetType().GetMethod(str));
		}

		for (int i = 0; i < Getters.Count; i++)
		{
			switch (Getters[i].ReturnType.Name)
			{
			case "Float3":
				compElem.Labels.Add(new Label());
				compElem.Labels.Add(new Label());
				compElem.Labels.Add(new Label());
				compElem.TextBoxes.Add(new TextBox());
				compElem.TextBoxes.Add(new TextBox());
				compElem.TextBoxes.Add(new TextBox());
				break;
			default:
				break;
			}
		}*/
		//String == textbox
		//Gameobject == Box
		//Type thisType = Comp.GetType();
		//MethodInfo theMethod = thisType.GetMethod(fieldNames[0]);
		//var temp = theMethod.Invoke(Comp, null);
	}
}