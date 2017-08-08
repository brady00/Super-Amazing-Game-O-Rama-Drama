#include "MyForm.h"
#include "Engine Base\Game Engine\MountainDew.h"
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
	}

	void MyForm::Timer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		UpdateEngine();
		this->Invalidate();
	}
}