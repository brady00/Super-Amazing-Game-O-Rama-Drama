#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Editor::MyForm form;
	Application::Run(%form);
}

namespace Editor
{
	void ObjectTreeView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
	{

	}

	void Form_OnLoad(System::Object^  sender, System::EventArgs^  e)
	{

	}
}