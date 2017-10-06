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
		String^ temp = gcnew String("MonkeyEngine.MEObject." + this->CompLabel->Text);
		Assembly^ ASSembly = Assembly::GetExecutingAssembly();
		AssemblyName^ name = AssemblyName::GetAssemblyName("MonkeyEngine.dll");
		//ComponentCreation?????
		//Components are managed but #pragma unmanaged
		//Component Factor will be managed using this to created componetns
		///Object^ obj = Type::GetType(temp)->GetConstructor(Type::EmptyTypes)->Invoke(gcnew cli::array<Object^>(0));
		///pin_ptr<Object^> pinnedPtr = &obj;
		///MonkeyEngine::MEObject::Component* temp = (MonkeyEngine::MEObject::Component*)pinnedPtr;
		String^ str = gcnew String("MonkeyEngine.MEObject." + this->CompLabel->Text);
		Type^ t = Type::GetType(str);
		for each(MemberInfo^ variable in t->GetMembers(static_cast<BindingFlags>(BindingFlags::Public | BindingFlags::Instance | BindingFlags::DeclaredOnly)))
		{
			mapToVariable.Add(variable->Name, variable);
		}
		/*for (int i = 0; i < Getters.Count; i++)
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