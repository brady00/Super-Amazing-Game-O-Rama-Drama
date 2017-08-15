#include "MyForm.h"
//#include "Engine Base\Game Engine\MountainDew.h"
#include "../MonkeyEngine/Engine Base/Game Engine/MountainDew.h"
//#include "Components\Transform\Transform.h"
#include "../MonkeyEngine/Components/Transform/Transform.h"
#include "ComponentPanel.h"
#include <unordered_map>
#include <string>
#include <vector>
using namespace System;
using namespace System::Windows::Forms;
using namespace Runtime::InteropServices;


[STAThread]
void Main(cli::array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Editor::MyForm form;
	Application::Run(%form);
}

namespace Editor
{
	std::vector<MonkeyEngine::MEObject::GameObject*> GameObjects;
	std::unordered_map<std::string, MonkeyEngine::MEObject::GameObject*> GameObjectMap;
	std::unordered_map<MonkeyEngine::MEObject::GameObject*, unsigned int> CompStartIndex;
	std::unordered_map<MonkeyEngine::MEObject::GameObject*, unsigned int> CompSize;

	void MyForm::ObjectTreeView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
	{
		if (ObjectTreeView->SelectedNode != PrevSelectedObject)
		{
			NameBox->Text = ObjectTreeView->SelectedNode->Text;
			std::string TextBoxName((const char*)(Marshal::StringToHGlobalAnsi(NameBox->Text)).ToPointer());
			ActiveBox->Checked = GameObjectMap[TextBoxName]->GetActive();
			StaticBox->Checked = GameObjectMap[TextBoxName]->GetStatic();
			LayerComboBox->SelectedIndex = (int)GameObjectMap[TextBoxName]->GetLayer();
			GUIActivate(GameObjectMap[TextBoxName]);
			if (PrevSelectedObject != nullptr)
			{
				std::string PrevTextBoxName((const char*)(Marshal::StringToHGlobalAnsi(PrevSelectedObject->Text)).ToPointer());
				GUIDeactivate(GameObjectMap[PrevTextBoxName]);
			}
			InspectorBackgroundPanel->Refresh();
			splitContainer1->Panel2->Refresh();
			PrevSelectedObject = ObjectTreeView->SelectedNode;
		}
	}

	void MyForm::Form_OnLoad(System::Object^  sender, System::EventArgs^  e)
	{
		InitializeEngine((HWND)(void*)RenderingPanel->Handle, RenderingPanel->Width, RenderingPanel->Height);
		Timer->Start();
		this->DoubleBuffered = true;
		this->SetStyle(ControlStyles::DoubleBuffer, true);
		this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
		this->SetStyle(ControlStyles::UserPaint, true);
		this->SetStyle(ControlStyles::SupportsTransparentBackColor, false);
		this->SetStyle(ControlStyles::Opaque, false);
		this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);
		this->SetStyle(ControlStyles::ResizeRedraw, true);
		GameObjects = GetSceneObjects();
		unsigned int compIndex = 0;
		for (unsigned int i = 0; i < GameObjects.size(); i++)
		{
			CompStartIndex[GameObjects[i]] = compIndex;
			System::String^ ObjectName = gcnew System::String(GameObjects[i]->GetCharName());
			ObjectTreeView->Nodes->Add(ObjectName);
			std::vector<MonkeyEngine::MEObject::Component*>& comps = GameObjects[i]->GetAllComponents();
			std::vector<MonkeyEngine::MEObject::Component*>& scripts = GameObjects[i]->GetAllScritps();
			MonkeyEngine::MEObject::Component* transform = (MonkeyEngine::MEObject::Component*)GameObjects[i]->GetTransform();
			CompSize[GameObjects[i]] = comps.size() + scripts.size() + 1;
			CompPanels[compIndex] = gcnew ComponentPanel();
			CompPanels[compIndex]->Comp = transform;
			CompPanels[compIndex]->Parent = GameObjects[i];
			CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, 0);
			compIndex++;
			for (unsigned int j = 0; j < comps.size(); j++)
			{
				CompPanels[compIndex] = gcnew ComponentPanel();
				CompPanels[compIndex]->Parent = GameObjects[i];
				CompPanels[compIndex]->Comp = comps[j];
				CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, j + 1);
				compIndex++;
			}
			for (unsigned int j = 0; j < scripts.size(); j++)
			{
				CompPanels[compIndex] = gcnew ComponentPanel();
				CompPanels[compIndex]->Parent = GameObjects[i];
				CompPanels[compIndex]->Comp = scripts[j];
				CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, j + 1 + comps.size());
				compIndex++;
			}
			GameObjectMap[std::string(GameObjects[i]->GetCharName())] = GameObjects[i];
		}
	}

	void MyForm::Timer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		UpdateEngine();
		this->Invalidate();
	}

	void MyForm::RunInWindowToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		
	}

	void MyForm::RunInVRToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		RunGameVR();
	}

	void MyForm::RenderingPanel_SizeChanged(System::Object ^ sender, System::EventArgs ^ e)
	{
		ResizeEngine(RenderingPanel->Width, RenderingPanel->Height);
		//UpdateEngine();
	}

	void MyForm::RenderingPanel_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
	{
		int key = 0;
		switch (e->Button)
		{
		case System::Windows::Forms::MouseButtons::Left:
			key = VK_LBUTTON;
			break;
		case System::Windows::Forms::MouseButtons::Right:
			key = VK_RBUTTON;
			break;
		case System::Windows::Forms::MouseButtons::Middle:
			key = VK_MBUTTON;
			break;
		}
		MouseDown_RenderingPanel(key);
	}

	void MyForm::RenderingPanel_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
	{
		int key = 0;
		switch (e->Button)
		{
		case System::Windows::Forms::MouseButtons::Left:
			key = VK_LBUTTON;
			break;
		case System::Windows::Forms::MouseButtons::Right:
			key = VK_RBUTTON;
			break;
		case System::Windows::Forms::MouseButtons::Middle:
			key = VK_MBUTTON;
			break;
		}
		MouseUp_RenderingPanel(key);
	}

	void MyForm::ButtonCollapsed(unsigned int buttonIndex, MonkeyEngine::MEObject::GameObject* _Object)
	{
		unsigned int startIndex = CompStartIndex[_Object];
		unsigned int Size = CompSize[_Object];
		for (unsigned int i = buttonIndex + 1; i < Size; i++)
		{
			CompPanels[i + startIndex]->Location = Point(CompPanels[buttonIndex + startIndex]->Location.X, CompPanels[i - 1 + startIndex]->Location.Y + CompPanels[i - 1 + startIndex]->Size.Height);
		}
	}

	void MyForm::ButtonExpanded(unsigned int buttonIndex, MonkeyEngine::MEObject::GameObject* _Object)
	{
		unsigned int startIndex = CompStartIndex[_Object];
		unsigned int Size = CompSize[_Object];
		for (unsigned int i = buttonIndex + 1; i < Size; i++)
		{
			CompPanels[i + startIndex]->Location = Point(CompPanels[buttonIndex + startIndex]->Location.X, CompPanels[i + startIndex]->Location.Y + CompPanels[buttonIndex + startIndex]->Size.Height - CompPanels[buttonIndex + startIndex]->MinimumSize.Height);
		}
	}

	void MyForm::GUIActivate(MonkeyEngine::MEObject::GameObject* _object)
	{
		for (unsigned int i = CompStartIndex[_object]; i < CompStartIndex[_object] + CompSize[_object]; i++)
			CompPanels[i]->Show();
	}

	void MyForm::GUIDeactivate(MonkeyEngine::MEObject::GameObject* _object)
	{
		for (unsigned int i = CompStartIndex[_object]; i < CompStartIndex[_object] + CompSize[_object]; i++)
			CompPanels[i]->Hide();
	}
}