#include "MyForm.h"
#include "Engine Base\Game Engine\MountainDew.h"
#include "ComponentPanel.h"
#include <unordered_map>
#include <string>
#include <vector>
using namespace System;
using namespace System::Windows::Forms;


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
	std::unordered_map<MonkeyEngine::MEObject::GameObject*, unsigned int> StartIndex;

	void MyForm::ObjectTreeView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
	{

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
			System::String^ ObjectName = gcnew System::String(GameObjects[i]->GetName().c_str());
			ObjectTreeView->Nodes->Add(ObjectName);
			/*for (unsigned int j = 0; j < GameObjects[i]->GetAllComponents().size(); j++)
			{
				Object.Components[j].CreatePanel(InspectorBackgroundPanel, j);
			}*/
			GameObjectMap[GameObjects[i]->GetName()] = GameObjects[i];
		}
	}

	void MyForm::Timer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		UpdateEngine();
		this->Invalidate();
	}
}