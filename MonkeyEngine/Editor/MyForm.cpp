#include "MyForm.h"
//#include "Engine Base\Game Engine\MountainDew.h"
#include "../MonkeyEngine/Engine Base/Game Engine/MountainDew.h"
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
			//Components = GameObjectMap[NameBox->Text]->Components;
			//GameObjectMap[NameBox->Text]->GUIActivate();
			//if (PrevSelectedObject != null)
			//	GameObjectMap[PrevSelectedObject->Text]->GUIDeactivate();
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
		for (unsigned int i = 0; i < GameObjects.size(); i++)
		{
			System::String^ ObjectName = gcnew System::String(GameObjects[i]->GetCharName());
			ObjectTreeView->Nodes->Add(ObjectName);
			/*for (unsigned int j = 0; j < GameObjects[i]->GetAllComponents().size(); j++)
			{
				Object.Components[j].CreatePanel(InspectorBackgroundPanel, j);
			}*/
			GameObjectMap[std::string(GameObjects[i]->GetCharName())] = GameObjects[i];
		}
	}

	void MyForm::Timer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		UpdateEngine();
		this->Invalidate();
	}

	void MyForm::RenderingPanel_SizeChanged(System::Object ^ sender, System::EventArgs ^ e)
	{
		ResizeEngine(RenderingPanel->Width, RenderingPanel->Height);
		//UpdateEngine();
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
}