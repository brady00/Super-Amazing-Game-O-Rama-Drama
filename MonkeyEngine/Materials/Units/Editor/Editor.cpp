#include "Editor.h"
#include "Engine Base/Game Engine/MountainDew.h"
#include "Transform/Transform.h"
#include "GameWindow.h"
#include "TransformPanel.h"
#include <unordered_map>
#include <string>
#include <vector>
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
using namespace Runtime::InteropServices;
using namespace System::Text;


[STAThread]
void Main(cli::array<String^>^ args)
{
	if (args->Length >= 2)
	{
		//Need to break here
	}
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Editor::Editor form;
	if (args->Length > 0)
		form.OpenFile = args[0];
	else
		form.OpenFile = "Assets/Scenes/Default.mes";
	Application::Run(%form);
}

namespace Editor
{
	std::vector<MonkeyEngine::MEObject::GameObject*> GameObjects;
	std::unordered_map<std::string, MonkeyEngine::MEObject::GameObject*> GameObjectMap;
	std::unordered_map<MonkeyEngine::MEObject::GameObject*, unsigned int> CompStartIndex;
	std::unordered_map<MonkeyEngine::MEObject::GameObject*, unsigned int> CompSize;
	float LoadingPercentage = 0.0f;
	bool LoadingSucceeded = false;
	string FileName;
	void Editor::ObjectTreeView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
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

	void Editor::Form_OnLoad(System::Object^  sender, System::EventArgs^  e)
	{
		const char* File = (const char*)(Marshal::StringToHGlobalAnsi(OpenFile )).ToPointer();
		InitializeEngine((HWND)(void*)RenderingPanel->Handle, RenderingPanel->Width, RenderingPanel->Height, File);
		MainWindowRenderingTimer->Start();
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
			CompSize[GameObjects[i]] = (unsigned int)comps.size() + (unsigned int)scripts.size() + 1;
			CompPanels[compIndex] = gcnew TransformPanel();
			CompPanels[compIndex]->Comp = transform;
			CompPanels[compIndex]->GOParent = GameObjects[i];
			CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, 0);
			compIndex++;
			for (unsigned int j = 0; j < comps.size(); j++)
			{
				//CreateComponent(GameObjects[i], comps[j], j+1, inspectorbackground panel)
				//switch comps[j]->GetName() to create TransformPanel
				CompPanels[compIndex] = gcnew ComponentPanel();
				CompPanels[compIndex]->GOParent = GameObjects[i];
				CompPanels[compIndex]->Comp = comps[j];
				CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, j + 1);
				compIndex++;
			}
			for (unsigned int j = 0; j < scripts.size(); j++)
			{
				CompPanels[compIndex] = gcnew ComponentPanel();
				CompPanels[compIndex]->GOParent = GameObjects[i];
				CompPanels[compIndex]->Comp = scripts[j];
				CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, j + 1 + (unsigned int)comps.size());
				compIndex++;
			}
			GameObjectMap[std::string(GameObjects[i]->GetCharName())] = GameObjects[i];
		}
	}

	void Editor::MainWindowRenderingTimer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		UpdateEngine();
		this->Invalidate();
	}

	void Editor::LoadingTimer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		LoadingForeground->Size = System::Drawing::Size((int)(LoadingForeground->MaximumSize.Width * LoadingPercentage), 23);
		LoadingBackground->Refresh();
		LoadingForeground->Refresh();
		LoadingPanel->Refresh();
		//DO LOADING SCREEN STUFF HERE
		if (LoadingSucceeded && LoadingPercentage == 1.0f)
		{
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
				CompSize[GameObjects[i]] = (unsigned int)comps.size() + (unsigned int)scripts.size() + 1;
				CompPanels[compIndex] = gcnew ComponentPanel();
				CompPanels[compIndex]->Comp = transform;
				CompPanels[compIndex]->GOParent = GameObjects[i];
				CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, 0);
				compIndex++;
				for (unsigned int j = 0; j < comps.size(); j++)
				{
					CompPanels[compIndex] = gcnew ComponentPanel();
					CompPanels[compIndex]->GOParent = GameObjects[i];
					CompPanels[compIndex]->Comp = comps[j];
					CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, j + 1);
					compIndex++;
				}
				for (unsigned int j = 0; j < scripts.size(); j++)
				{
					CompPanels[compIndex] = gcnew ComponentPanel();
					CompPanels[compIndex]->GOParent = GameObjects[i];
					CompPanels[compIndex]->Comp = scripts[j];
					CompPanels[compIndex]->CreatePanel(InspectorBackgroundPanel, j + 1 + (unsigned int)comps.size());
					compIndex++;
				}
				GameObjectMap[std::string(GameObjects[i]->GetCharName())] = GameObjects[i];
			}
			LoadingPanel->Hide();
			LoadingTimer->Stop();
			MainWindowRenderingTimer->Start();
			LoadingSucceeded = false;
			LoadingPercentage = 0.0f;
		}
	}

	void Editor::RunInWindowToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		GameWindow^ win = gcnew GameWindow();
		win->Show();
	}

	void Editor::RunInVRToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		//Check Box to Play Button
		GameWindow^ win = gcnew GameWindow();
		win->Show();
		RunGameVR();
	}

	void Editor::RenderingPanel_SizeChanged(System::Object ^ sender, System::EventArgs ^ e)
	{

	}

	void Editor::RenderingPanel_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
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

	void Editor::RenderingPanel_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
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

	void Editor::ButtonCollapsed(unsigned int buttonIndex, MonkeyEngine::MEObject::GameObject* _Object)
	{
		unsigned int startIndex = CompStartIndex[_Object];
		unsigned int Size = CompSize[_Object];
		for (unsigned int i = buttonIndex + 1; i < Size; i++)
		{
			CompPanels[i + startIndex]->Location = Point(CompPanels[buttonIndex + startIndex]->Location.X, CompPanels[i - 1 + startIndex]->Location.Y + CompPanels[i - 1 + startIndex]->Size.Height);
		}
	}

	void Editor::ButtonExpanded(unsigned int buttonIndex, MonkeyEngine::MEObject::GameObject* _Object)
	{
		unsigned int startIndex = CompStartIndex[_Object];
		unsigned int Size = CompSize[_Object];
		for (unsigned int i = buttonIndex + 1; i < Size; i++)
		{
			CompPanels[i + startIndex]->Location = Point(CompPanels[buttonIndex + startIndex]->Location.X, CompPanels[i + startIndex]->Location.Y + CompPanels[buttonIndex + startIndex]->Size.Height - CompPanels[buttonIndex + startIndex]->MinimumSize.Height);
		}
	}

	void Editor::GUIActivate(MonkeyEngine::MEObject::GameObject* _object)
	{
		for (unsigned int i = CompStartIndex[_object]; i < CompStartIndex[_object] + CompSize[_object]; i++)
			CompPanels[i]->Show();
	}

	void Editor::GUIDeactivate(MonkeyEngine::MEObject::GameObject* _object)
	{
		for (unsigned int i = CompStartIndex[_object]; i < CompStartIndex[_object] + CompSize[_object]; i++)
			CompPanels[i]->Hide();
	}

	void Editor::LoadHelper()
	{
		LoadMonkeyEngineScene(FileName, LoadingPercentage, LoadingSucceeded);
	}

	void Editor::openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			FileName = string((const char*)(Marshal::StringToHGlobalAnsi(openFileDialog->FileName)).ToPointer());
			MainWindowRenderingTimer->Stop();
			LoadingTimer->Start();
			ThreadStart^ params = gcnew ThreadStart(this, &Editor::LoadHelper);
			Thread^ tempThread = gcnew Thread(params);
			LoadingPanel->Location = Point((int)((this->Width / 2.0f) - (LoadingPanel->Width / 2.0f)), (int)((this->Height / 2.0f) - (LoadingPanel->Height / 2.0f)));
			LoadingPanel->Show();
			tempThread->Start();
		}
	}
	
	void Editor::PlayButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SetMonkeyEngineRenderState(RenderState::GAME_RENDERING);
	}
	
	void Editor::StopButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SetMonkeyEngineRenderState(RenderState::EDITOR_RENDERING);
	}

}