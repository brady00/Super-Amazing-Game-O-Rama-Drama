#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
#include "ComponentPanel.h"
namespace Editor {

	/// <summary>
	/// Summary for TransformPanel
	/// </summary>
	public ref class TransformPanel : public ComponentPanel
	{
	public:
		TransformPanel(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TransformPanel()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			ComponentPanel::InitializeComponent();
		}
#pragma endregion
	public: void CreatePanel(Panel^ InspectorBackgroundPanel, unsigned int Index) override;
	};
}
