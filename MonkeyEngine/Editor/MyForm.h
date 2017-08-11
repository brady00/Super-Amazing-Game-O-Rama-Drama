#pragma once
//#include "GameObject\GameObject.h"
#include "../MonkeyEngine/GameObject/GameObject.h"
#include "ComponentPanel.h"
namespace Editor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: static cli::array<ComponentPanel^>^ CompPanels = gcnew cli::array<ComponentPanel^>(100);
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::SplitContainer^  splitContainer3;
	private: System::Windows::Forms::SplitContainer^  splitContainer4;
	private: System::Windows::Forms::Panel^  RenderingPanel;
	private: System::Windows::Forms::TreeView^  ObjectTreeView;
	private: System::Windows::Forms::Panel^  InspectorBackgroundPanel;
	private: System::Windows::Forms::Panel^  NameBackgroundPanel;
	private: System::Windows::Forms::Button^  RemoveTagButton;
	private: System::Windows::Forms::Button^  AddTagButton;
	private: System::Windows::Forms::Label^  LayerText;
	private: System::Windows::Forms::Label^  TagTex;
	private: System::Windows::Forms::ComboBox^  LayerComboBox;
	private: System::Windows::Forms::ComboBox^  TagComboBox;
	private: System::Windows::Forms::CheckBox^  StaticBox;
	private: System::Windows::Forms::CheckBox^  ActiveBox;
	private: System::Windows::Forms::TextBox^  NameBox;
	private: System::Windows::Forms::Panel^  BackgroundPanel;
	private: System::Windows::Forms::Timer^  Timer;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  printToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  printPreviewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  undoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  redoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  cutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pasteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^  selectAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  customizeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  contentsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  indexToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  searchToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::ComponentModel::IContainer^  components;



	private: TreeNode^ PrevSelectedObject;
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
			this->components = (gcnew System::ComponentModel::Container());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer4 = (gcnew System::Windows::Forms::SplitContainer());
			this->RenderingPanel = (gcnew System::Windows::Forms::Panel());
			this->ObjectTreeView = (gcnew System::Windows::Forms::TreeView());
			this->InspectorBackgroundPanel = (gcnew System::Windows::Forms::Panel());
			this->NameBackgroundPanel = (gcnew System::Windows::Forms::Panel());
			this->RemoveTagButton = (gcnew System::Windows::Forms::Button());
			this->AddTagButton = (gcnew System::Windows::Forms::Button());
			this->LayerText = (gcnew System::Windows::Forms::Label());
			this->TagTex = (gcnew System::Windows::Forms::Label());
			this->LayerComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TagComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->StaticBox = (gcnew System::Windows::Forms::CheckBox());
			this->ActiveBox = (gcnew System::Windows::Forms::CheckBox());
			this->NameBox = (gcnew System::Windows::Forms::TextBox());
			this->BackgroundPanel = (gcnew System::Windows::Forms::Panel());
			this->Timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->printToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->printPreviewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->cutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->selectAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contentsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->indexToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->searchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->BeginInit();
			this->splitContainer3->Panel1->SuspendLayout();
			this->splitContainer3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer4))->BeginInit();
			this->splitContainer4->Panel1->SuspendLayout();
			this->splitContainer4->Panel2->SuspendLayout();
			this->splitContainer4->SuspendLayout();
			this->InspectorBackgroundPanel->SuspendLayout();
			this->NameBackgroundPanel->SuspendLayout();
			this->BackgroundPanel->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->splitContainer2);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->InspectorBackgroundPanel);
			this->splitContainer1->Size = System::Drawing::Size(1904, 1017);
			this->splitContainer1->SplitterDistance = 1566;
			this->splitContainer1->TabIndex = 19;
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->splitContainer3);
			this->splitContainer2->Size = System::Drawing::Size(1566, 1017);
			this->splitContainer2->SplitterDistance = 218;
			this->splitContainer2->TabIndex = 3;
			// 
			// splitContainer3
			// 
			this->splitContainer3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer3->Location = System::Drawing::Point(0, 0);
			this->splitContainer3->Name = L"splitContainer3";
			this->splitContainer3->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer3.Panel1
			// 
			this->splitContainer3->Panel1->Controls->Add(this->splitContainer4);
			this->splitContainer3->Size = System::Drawing::Size(1344, 1017);
			this->splitContainer3->SplitterDistance = 772;
			this->splitContainer3->TabIndex = 5;
			// 
			// splitContainer4
			// 
			this->splitContainer4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer4->Location = System::Drawing::Point(0, 0);
			this->splitContainer4->Name = L"splitContainer4";
			// 
			// splitContainer4.Panel1
			// 
			this->splitContainer4->Panel1->Controls->Add(this->RenderingPanel);
			// 
			// splitContainer4.Panel2
			// 
			this->splitContainer4->Panel2->Controls->Add(this->ObjectTreeView);
			this->splitContainer4->Size = System::Drawing::Size(1344, 772);
			this->splitContainer4->SplitterDistance = 981;
			this->splitContainer4->TabIndex = 0;
			// 
			// RenderingPanel
			// 
			this->RenderingPanel->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->RenderingPanel->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->RenderingPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->RenderingPanel->Location = System::Drawing::Point(0, 0);
			this->RenderingPanel->Name = L"RenderingPanel";
			this->RenderingPanel->Size = System::Drawing::Size(981, 772);
			this->RenderingPanel->TabIndex = 11;
			this->RenderingPanel->SizeChanged += gcnew System::EventHandler(this, &MyForm::RenderingPanel_SizeChanged);
			// 
			// ObjectTreeView
			// 
			this->ObjectTreeView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ObjectTreeView->Location = System::Drawing::Point(0, 0);
			this->ObjectTreeView->Name = L"ObjectTreeView";
			this->ObjectTreeView->Size = System::Drawing::Size(359, 772);
			this->ObjectTreeView->TabIndex = 13;
			this->ObjectTreeView->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MyForm::ObjectTreeView_AfterSelect);
			// 
			// InspectorBackgroundPanel
			// 
			this->InspectorBackgroundPanel->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->InspectorBackgroundPanel->AutoScroll = true;
			this->InspectorBackgroundPanel->BackColor = System::Drawing::SystemColors::ControlDark;
			this->InspectorBackgroundPanel->Controls->Add(this->NameBackgroundPanel);
			this->InspectorBackgroundPanel->Location = System::Drawing::Point(-1, 0);
			this->InspectorBackgroundPanel->MinimumSize = System::Drawing::Size(324, 1017);
			this->InspectorBackgroundPanel->Name = L"InspectorBackgroundPanel";
			this->InspectorBackgroundPanel->Size = System::Drawing::Size(336, 1017);
			this->InspectorBackgroundPanel->TabIndex = 19;
			// 
			// NameBackgroundPanel
			// 
			this->NameBackgroundPanel->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->NameBackgroundPanel->Controls->Add(this->RemoveTagButton);
			this->NameBackgroundPanel->Controls->Add(this->AddTagButton);
			this->NameBackgroundPanel->Controls->Add(this->LayerText);
			this->NameBackgroundPanel->Controls->Add(this->TagTex);
			this->NameBackgroundPanel->Controls->Add(this->LayerComboBox);
			this->NameBackgroundPanel->Controls->Add(this->TagComboBox);
			this->NameBackgroundPanel->Controls->Add(this->StaticBox);
			this->NameBackgroundPanel->Controls->Add(this->ActiveBox);
			this->NameBackgroundPanel->Controls->Add(this->NameBox);
			this->NameBackgroundPanel->Location = System::Drawing::Point(1, 0);
			this->NameBackgroundPanel->Name = L"NameBackgroundPanel";
			this->NameBackgroundPanel->Size = System::Drawing::Size(335, 101);
			this->NameBackgroundPanel->TabIndex = 19;
			// 
			// RemoveTagButton
			// 
			this->RemoveTagButton->Location = System::Drawing::Point(109, 65);
			this->RemoveTagButton->Name = L"RemoveTagButton";
			this->RemoveTagButton->Size = System::Drawing::Size(62, 23);
			this->RemoveTagButton->TabIndex = 23;
			this->RemoveTagButton->Text = L"Remove";
			this->RemoveTagButton->UseVisualStyleBackColor = true;
			// 
			// AddTagButton
			// 
			this->AddTagButton->Location = System::Drawing::Point(46, 65);
			this->AddTagButton->Name = L"AddTagButton";
			this->AddTagButton->Size = System::Drawing::Size(57, 23);
			this->AddTagButton->TabIndex = 22;
			this->AddTagButton->Text = L"Add";
			this->AddTagButton->UseVisualStyleBackColor = true;
			// 
			// LayerText
			// 
			this->LayerText->AutoSize = true;
			this->LayerText->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->LayerText->Location = System::Drawing::Point(171, 41);
			this->LayerText->Name = L"LayerText";
			this->LayerText->Size = System::Drawing::Size(33, 13);
			this->LayerText->TabIndex = 21;
			this->LayerText->Text = L"Layer";
			// 
			// TagTex
			// 
			this->TagTex->AutoSize = true;
			this->TagTex->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->TagTex->Location = System::Drawing::Point(9, 41);
			this->TagTex->Name = L"TagTex";
			this->TagTex->Size = System::Drawing::Size(31, 13);
			this->TagTex->TabIndex = 20;
			this->TagTex->Text = L"Tags";
			// 
			// LayerComboBox
			// 
			this->LayerComboBox->FormattingEnabled = true;
			this->LayerComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Layer 1", L"Layer 2", L"Layer 3" });
			this->LayerComboBox->Location = System::Drawing::Point(210, 38);
			this->LayerComboBox->Name = L"LayerComboBox";
			this->LayerComboBox->Size = System::Drawing::Size(106, 21);
			this->LayerComboBox->TabIndex = 19;
			// 
			// TagComboBox
			// 
			this->TagComboBox->FormattingEnabled = true;
			this->TagComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Player", L"Enemy" });
			this->TagComboBox->Location = System::Drawing::Point(46, 38);
			this->TagComboBox->Name = L"TagComboBox";
			this->TagComboBox->Size = System::Drawing::Size(106, 21);
			this->TagComboBox->TabIndex = 18;
			// 
			// StaticBox
			// 
			this->StaticBox->AutoSize = true;
			this->StaticBox->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->StaticBox->Location = System::Drawing::Point(263, 16);
			this->StaticBox->Name = L"StaticBox";
			this->StaticBox->Size = System::Drawing::Size(53, 17);
			this->StaticBox->TabIndex = 17;
			this->StaticBox->Text = L"Static";
			this->StaticBox->UseVisualStyleBackColor = false;
			// 
			// ActiveBox
			// 
			this->ActiveBox->AutoSize = true;
			this->ActiveBox->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ActiveBox->Location = System::Drawing::Point(61, 16);
			this->ActiveBox->Name = L"ActiveBox";
			this->ActiveBox->Size = System::Drawing::Size(15, 14);
			this->ActiveBox->TabIndex = 16;
			this->ActiveBox->UseVisualStyleBackColor = false;
			// 
			// NameBox
			// 
			this->NameBox->Location = System::Drawing::Point(82, 13);
			this->NameBox->Name = L"NameBox";
			this->NameBox->Size = System::Drawing::Size(175, 20);
			this->NameBox->TabIndex = 15;
			// 
			// BackgroundPanel
			// 
			this->BackgroundPanel->Controls->Add(this->splitContainer1);
			this->BackgroundPanel->Location = System::Drawing::Point(0, 24);
			this->BackgroundPanel->Name = L"BackgroundPanel";
			this->BackgroundPanel->Size = System::Drawing::Size(1904, 1017);
			this->BackgroundPanel->TabIndex = 3;
			// 
			// Timer
			// 
			this->Timer->Interval = 1;
			this->Timer->Tick += gcnew System::EventHandler(this, &MyForm::Timer_Tick);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->editToolStripMenuItem, this->toolsToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1904, 24);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->newToolStripMenuItem,
					this->openToolStripMenuItem, this->toolStripSeparator, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->toolStripSeparator1,
					this->printToolStripMenuItem, this->printPreviewToolStripMenuItem, this->toolStripSeparator2, this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->newToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->newToolStripMenuItem->Text = L"&New";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->openToolStripMenuItem->Text = L"&Open";
			// 
			// toolStripSeparator
			// 
			this->toolStripSeparator->Name = L"toolStripSeparator";
			this->toolStripSeparator->Size = System::Drawing::Size(143, 6);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->saveToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->saveToolStripMenuItem->Text = L"&Save";
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->saveAsToolStripMenuItem->Text = L"Save &As";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(143, 6);
			// 
			// printToolStripMenuItem
			// 
			this->printToolStripMenuItem->Name = L"printToolStripMenuItem";
			this->printToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
			this->printToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->printToolStripMenuItem->Text = L"&Print";
			// 
			// printPreviewToolStripMenuItem
			// 
			this->printPreviewToolStripMenuItem->Name = L"printPreviewToolStripMenuItem";
			this->printPreviewToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->printPreviewToolStripMenuItem->Text = L"Print Pre&view";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(143, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->exitToolStripMenuItem->Text = L"E&xit";
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->undoToolStripMenuItem,
					this->redoToolStripMenuItem, this->toolStripSeparator3, this->cutToolStripMenuItem, this->copyToolStripMenuItem, this->pasteToolStripMenuItem,
					this->toolStripSeparator4, this->selectAllToolStripMenuItem
			});
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->editToolStripMenuItem->Text = L"&Edit";
			// 
			// undoToolStripMenuItem
			// 
			this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
			this->undoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
			this->undoToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->undoToolStripMenuItem->Text = L"&Undo";
			// 
			// redoToolStripMenuItem
			// 
			this->redoToolStripMenuItem->Name = L"redoToolStripMenuItem";
			this->redoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Y));
			this->redoToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->redoToolStripMenuItem->Text = L"&Redo";
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(141, 6);
			// 
			// cutToolStripMenuItem
			// 
			this->cutToolStripMenuItem->Name = L"cutToolStripMenuItem";
			this->cutToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->cutToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->cutToolStripMenuItem->Text = L"Cu&t";
			// 
			// copyToolStripMenuItem
			// 
			this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
			this->copyToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			this->copyToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->copyToolStripMenuItem->Text = L"&Copy";
			// 
			// pasteToolStripMenuItem
			// 
			this->pasteToolStripMenuItem->Name = L"pasteToolStripMenuItem";
			this->pasteToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::V));
			this->pasteToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->pasteToolStripMenuItem->Text = L"&Paste";
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(141, 6);
			// 
			// selectAllToolStripMenuItem
			// 
			this->selectAllToolStripMenuItem->Name = L"selectAllToolStripMenuItem";
			this->selectAllToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->selectAllToolStripMenuItem->Text = L"Select &All";
			// 
			// toolsToolStripMenuItem
			// 
			this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->customizeToolStripMenuItem,
					this->optionsToolStripMenuItem
			});
			this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
			this->toolsToolStripMenuItem->Size = System::Drawing::Size(47, 20);
			this->toolsToolStripMenuItem->Text = L"&Tools";
			// 
			// customizeToolStripMenuItem
			// 
			this->customizeToolStripMenuItem->Name = L"customizeToolStripMenuItem";
			this->customizeToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->customizeToolStripMenuItem->Text = L"&Customize";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->optionsToolStripMenuItem->Text = L"&Options";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->contentsToolStripMenuItem,
					this->indexToolStripMenuItem, this->searchToolStripMenuItem, this->toolStripSeparator5, this->aboutToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"&Help";
			// 
			// contentsToolStripMenuItem
			// 
			this->contentsToolStripMenuItem->Name = L"contentsToolStripMenuItem";
			this->contentsToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->contentsToolStripMenuItem->Text = L"&Contents";
			// 
			// indexToolStripMenuItem
			// 
			this->indexToolStripMenuItem->Name = L"indexToolStripMenuItem";
			this->indexToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->indexToolStripMenuItem->Text = L"&Index";
			// 
			// searchToolStripMenuItem
			// 
			this->searchToolStripMenuItem->Name = L"searchToolStripMenuItem";
			this->searchToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->searchToolStripMenuItem->Text = L"&Search";
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(119, 6);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->aboutToolStripMenuItem->Text = L"&About...";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1904, 1041);
			this->Controls->Add(this->BackgroundPanel);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::Form_OnLoad);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			this->splitContainer3->Panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->EndInit();
			this->splitContainer3->ResumeLayout(false);
			this->splitContainer4->Panel1->ResumeLayout(false);
			this->splitContainer4->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer4))->EndInit();
			this->splitContainer4->ResumeLayout(false);
			this->InspectorBackgroundPanel->ResumeLayout(false);
			this->NameBackgroundPanel->ResumeLayout(false);
			this->NameBackgroundPanel->PerformLayout();
			this->BackgroundPanel->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void GUIActivate(MonkeyEngine::MEObject::GameObject* _object);
	private: void GUIDeactivate(MonkeyEngine::MEObject::GameObject* _object);
	private: void ObjectTreeView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
	private: void Form_OnLoad(System::Object^  sender, System::EventArgs^  e);
	private: void Timer_Tick(System::Object^  sender, System::EventArgs^  e);
	private: void RenderingPanel_SizeChanged(System::Object^  sender, System::EventArgs^  e);
	public:	static void MyForm::ButtonCollapsed(unsigned int buttonIndex, MonkeyEngine::MEObject::GameObject* _Object);
	public: static void MyForm::ButtonExpanded(unsigned int buttonIndex, MonkeyEngine::MEObject::GameObject* _Object);
};
}
