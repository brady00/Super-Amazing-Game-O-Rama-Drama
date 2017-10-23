#pragma once
#pragma warning(disable: 4561)
#include "GameObject/GameObject.h"
#include "ComponentPanel.h"
namespace Editor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	enum LoadingDataType { Scene, FBX };

	/// <summary>
	/// Summary for Editor
	/// </summary>
	public ref class Editor : public System::Windows::Forms::Form
	{
	public:
		Editor(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->WindowState = FormWindowState::Maximized; // Maximize Form on start
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Editor()
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
	private: System::Windows::Forms::Timer^  MainWindowRenderingTimer;
	private: System::Windows::Forms::Timer^  LoadingTimer;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
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
	private: System::Windows::Forms::ToolStripMenuItem^  gameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  RunInWindowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  RunInVRToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ToolStripMenuItem^  sceneToolStripMenuItem;
	private: System::Windows::Forms::Panel^  LoadingPanel;
	private: System::Windows::Forms::Label^  LoadingLabel;
	private: System::Windows::Forms::Panel^  LoadingBackground;
	private: System::Windows::Forms::Panel^  LoadingForeground;
	private: System::Windows::Forms::Button^  StopButton;

	private: System::Windows::Forms::Button^  PauseButton;

	private: System::Windows::Forms::Button^  PlayButton;


















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
				 this->StopButton = (gcnew System::Windows::Forms::Button());
				 this->PauseButton = (gcnew System::Windows::Forms::Button());
				 this->PlayButton = (gcnew System::Windows::Forms::Button());
				 this->LoadingPanel = (gcnew System::Windows::Forms::Panel());
				 this->LoadingBackground = (gcnew System::Windows::Forms::Panel());
				 this->LoadingForeground = (gcnew System::Windows::Forms::Panel());
				 this->LoadingLabel = (gcnew System::Windows::Forms::Label());
				 this->MainWindowRenderingTimer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->sceneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
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
				 this->gameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->RunInWindowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->RunInVRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->contentsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->indexToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->searchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->LoadingTimer = (gcnew System::Windows::Forms::Timer(this->components));
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
				 this->LoadingPanel->SuspendLayout();
				 this->LoadingBackground->SuspendLayout();
				 this->menuStrip1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // splitContainer1
				 // 
				 this->splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					 | System::Windows::Forms::AnchorStyles::Left)
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->splitContainer1->BackColor = System::Drawing::SystemColors::AppWorkspace;
				 this->splitContainer1->Location = System::Drawing::Point(0, 32);
				 this->splitContainer1->Name = L"splitContainer1";
				 // 
				 // splitContainer1.Panel1
				 // 
				 this->splitContainer1->Panel1->Controls->Add(this->splitContainer2);
				 // 
				 // splitContainer1.Panel2
				 // 
				 this->splitContainer1->Panel2->Controls->Add(this->InspectorBackgroundPanel);
				 this->splitContainer1->Panel2MinSize = 378;
				 this->splitContainer1->Size = System::Drawing::Size(2221, 985);
				 this->splitContainer1->SplitterDistance = 1824;
				 this->splitContainer1->SplitterWidth = 5;
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
				 this->splitContainer2->Size = System::Drawing::Size(1824, 985);
				 this->splitContainer2->SplitterDistance = 253;
				 this->splitContainer2->SplitterWidth = 5;
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
				 this->splitContainer3->Size = System::Drawing::Size(1566, 985);
				 this->splitContainer3->SplitterDistance = 768;
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
				 this->splitContainer4->Size = System::Drawing::Size(1566, 768);
				 this->splitContainer4->SplitterDistance = 1316;
				 this->splitContainer4->SplitterWidth = 5;
				 this->splitContainer4->TabIndex = 0;
				 // 
				 // RenderingPanel
				 // 
				 this->RenderingPanel->BackColor = System::Drawing::SystemColors::ActiveCaption;
				 this->RenderingPanel->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->RenderingPanel->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->RenderingPanel->Location = System::Drawing::Point(0, 0);
				 this->RenderingPanel->Name = L"RenderingPanel";
				 this->RenderingPanel->Size = System::Drawing::Size(1316, 768);
				 this->RenderingPanel->TabIndex = 11;
				 this->RenderingPanel->SizeChanged += gcnew System::EventHandler(this, &Editor::RenderingPanel_SizeChanged);
				 this->RenderingPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Editor::RenderingPanel_MouseDown);
				 this->RenderingPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Editor::RenderingPanel_MouseUp);
				 // 
				 // ObjectTreeView
				 // 
				 this->ObjectTreeView->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->ObjectTreeView->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ObjectTreeView->Location = System::Drawing::Point(0, 0);
				 this->ObjectTreeView->Name = L"ObjectTreeView";
				 this->ObjectTreeView->Size = System::Drawing::Size(245, 768);
				 this->ObjectTreeView->TabIndex = 13;
				 this->ObjectTreeView->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Editor::ObjectTreeView_AfterSelect);
				 // 
				 // InspectorBackgroundPanel
				 // 
				 this->InspectorBackgroundPanel->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
				 this->InspectorBackgroundPanel->AutoScroll = true;
				 this->InspectorBackgroundPanel->AutoScrollMargin = System::Drawing::Size(0, 10);
				 this->InspectorBackgroundPanel->AutoScrollMinSize = System::Drawing::Size(324, 0);
				 this->InspectorBackgroundPanel->BackColor = System::Drawing::SystemColors::ControlDark;
				 this->InspectorBackgroundPanel->Controls->Add(this->NameBackgroundPanel);
				 this->InspectorBackgroundPanel->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->InspectorBackgroundPanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->InspectorBackgroundPanel->Location = System::Drawing::Point(0, 0);
				 this->InspectorBackgroundPanel->MinimumSize = System::Drawing::Size(378, 1017);
				 this->InspectorBackgroundPanel->Name = L"InspectorBackgroundPanel";
				 this->InspectorBackgroundPanel->Size = System::Drawing::Size(392, 1017);
				 this->InspectorBackgroundPanel->TabIndex = 19;
				 // 
				 // NameBackgroundPanel
				 // 
				 this->NameBackgroundPanel->BackColor = System::Drawing::Color::Silver;
				 this->NameBackgroundPanel->Controls->Add(this->RemoveTagButton);
				 this->NameBackgroundPanel->Controls->Add(this->AddTagButton);
				 this->NameBackgroundPanel->Controls->Add(this->LayerText);
				 this->NameBackgroundPanel->Controls->Add(this->TagTex);
				 this->NameBackgroundPanel->Controls->Add(this->LayerComboBox);
				 this->NameBackgroundPanel->Controls->Add(this->TagComboBox);
				 this->NameBackgroundPanel->Controls->Add(this->StaticBox);
				 this->NameBackgroundPanel->Controls->Add(this->ActiveBox);
				 this->NameBackgroundPanel->Controls->Add(this->NameBox);
				 this->NameBackgroundPanel->Dock = System::Windows::Forms::DockStyle::Top;
				 this->NameBackgroundPanel->Location = System::Drawing::Point(0, 0);
				 this->NameBackgroundPanel->Name = L"NameBackgroundPanel";
				 this->NameBackgroundPanel->Size = System::Drawing::Size(392, 101);
				 this->NameBackgroundPanel->TabIndex = 19;
				 // 
				 // RemoveTagButton
				 // 
				 this->RemoveTagButton->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->RemoveTagButton->Location = System::Drawing::Point(127, 72);
				 this->RemoveTagButton->Name = L"RemoveTagButton";
				 this->RemoveTagButton->Size = System::Drawing::Size(59, 26);
				 this->RemoveTagButton->TabIndex = 23;
				 this->RemoveTagButton->Text = L"Rem";
				 this->RemoveTagButton->UseVisualStyleBackColor = true;
				 // 
				 // AddTagButton
				 // 
				 this->AddTagButton->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->AddTagButton->Location = System::Drawing::Point(54, 72);
				 this->AddTagButton->Name = L"AddTagButton";
				 this->AddTagButton->Size = System::Drawing::Size(67, 26);
				 this->AddTagButton->TabIndex = 22;
				 this->AddTagButton->Text = L"Add";
				 this->AddTagButton->UseVisualStyleBackColor = true;
				 // 
				 // LayerText
				 // 
				 this->LayerText->AutoSize = true;
				 this->LayerText->BackColor = System::Drawing::Color::Silver;
				 this->LayerText->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->LayerText->Location = System::Drawing::Point(181, 39);
				 this->LayerText->Name = L"LayerText";
				 this->LayerText->Size = System::Drawing::Size(49, 20);
				 this->LayerText->TabIndex = 21;
				 this->LayerText->Text = L"Layer";
				 // 
				 // TagTex
				 // 
				 this->TagTex->AutoSize = true;
				 this->TagTex->BackColor = System::Drawing::Color::Silver;
				 this->TagTex->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->TagTex->Location = System::Drawing::Point(2, 39);
				 this->TagTex->Name = L"TagTex";
				 this->TagTex->Size = System::Drawing::Size(44, 20);
				 this->TagTex->TabIndex = 20;
				 this->TagTex->Text = L"Tags";
				 // 
				 // LayerComboBox
				 // 
				 this->LayerComboBox->FormattingEnabled = true;
				 this->LayerComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Layer 1", L"Layer 2", L"Layer 3" });
				 this->LayerComboBox->Location = System::Drawing::Point(245, 38);
				 this->LayerComboBox->Name = L"LayerComboBox";
				 this->LayerComboBox->Size = System::Drawing::Size(144, 28);
				 this->LayerComboBox->TabIndex = 19;
				 // 
				 // TagComboBox
				 // 
				 this->TagComboBox->FormattingEnabled = true;
				 this->TagComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Player", L"Enemy" });
				 this->TagComboBox->Location = System::Drawing::Point(54, 38);
				 this->TagComboBox->Name = L"TagComboBox";
				 this->TagComboBox->Size = System::Drawing::Size(123, 28);
				 this->TagComboBox->TabIndex = 18;
				 // 
				 // StaticBox
				 // 
				 this->StaticBox->AutoSize = true;
				 this->StaticBox->BackColor = System::Drawing::Color::Silver;
				 this->StaticBox->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->StaticBox->Location = System::Drawing::Point(319, 13);
				 this->StaticBox->Name = L"StaticBox";
				 this->StaticBox->Size = System::Drawing::Size(70, 24);
				 this->StaticBox->TabIndex = 17;
				 this->StaticBox->Text = L"Static";
				 this->StaticBox->UseVisualStyleBackColor = false;
				 // 
				 // ActiveBox
				 // 
				 this->ActiveBox->AutoSize = true;
				 this->ActiveBox->BackColor = System::Drawing::SystemColors::ControlDark;
				 this->ActiveBox->Location = System::Drawing::Point(65, 20);
				 this->ActiveBox->Name = L"ActiveBox";
				 this->ActiveBox->Size = System::Drawing::Size(15, 14);
				 this->ActiveBox->TabIndex = 16;
				 this->ActiveBox->UseVisualStyleBackColor = false;
				 // 
				 // NameBox
				 // 
				 this->NameBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->NameBox->Location = System::Drawing::Point(103, 13);
				 this->NameBox->Name = L"NameBox";
				 this->NameBox->Size = System::Drawing::Size(210, 26);
				 this->NameBox->TabIndex = 15;
				 // 
				 // BackgroundPanel
				 // 
				 this->BackgroundPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
				 this->BackgroundPanel->Controls->Add(this->StopButton);
				 this->BackgroundPanel->Controls->Add(this->PauseButton);
				 this->BackgroundPanel->Controls->Add(this->PlayButton);
				 this->BackgroundPanel->Controls->Add(this->LoadingPanel);
				 this->BackgroundPanel->Controls->Add(this->splitContainer1);
				 this->BackgroundPanel->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->BackgroundPanel->Location = System::Drawing::Point(0, 24);
				 this->BackgroundPanel->Name = L"BackgroundPanel";
				 this->BackgroundPanel->Size = System::Drawing::Size(2221, 1017);
				 this->BackgroundPanel->TabIndex = 3;
				 // 
				 // StopButton
				 // 
				 this->StopButton->Anchor = System::Windows::Forms::AnchorStyles::Top;
				 this->StopButton->Location = System::Drawing::Point(1157, 3);
				 this->StopButton->Name = L"StopButton";
				 this->StopButton->Size = System::Drawing::Size(55, 23);
				 this->StopButton->TabIndex = 26;
				 this->StopButton->Text = L"Stop";
				 this->StopButton->UseVisualStyleBackColor = true;
				 this->StopButton->Click += gcnew System::EventHandler(this, &Editor::StopButton_Click);
				 // 
				 // PauseButton
				 // 
				 this->PauseButton->Anchor = System::Windows::Forms::AnchorStyles::Top;
				 this->PauseButton->Location = System::Drawing::Point(1095, 3);
				 this->PauseButton->Name = L"PauseButton";
				 this->PauseButton->Size = System::Drawing::Size(55, 23);
				 this->PauseButton->TabIndex = 25;
				 this->PauseButton->Text = L"Pause";
				 this->PauseButton->UseVisualStyleBackColor = true;
				 // 
				 // PlayButton
				 // 
				 this->PlayButton->Anchor = System::Windows::Forms::AnchorStyles::Top;
				 this->PlayButton->Location = System::Drawing::Point(1042, 3);
				 this->PlayButton->Name = L"PlayButton";
				 this->PlayButton->Size = System::Drawing::Size(47, 23);
				 this->PlayButton->TabIndex = 24;
				 this->PlayButton->Text = L"Play";
				 this->PlayButton->UseVisualStyleBackColor = true;
				 this->PlayButton->Click += gcnew System::EventHandler(this, &Editor::PlayButton_Click);
				 // 
				 // LoadingPanel
				 // 
				 this->LoadingPanel->BackColor = System::Drawing::Color::Gray;
				 this->LoadingPanel->Controls->Add(this->LoadingBackground);
				 this->LoadingPanel->Controls->Add(this->LoadingLabel);
				 this->LoadingPanel->Location = System::Drawing::Point(591, 352);
				 this->LoadingPanel->Name = L"LoadingPanel";
				 this->LoadingPanel->Size = System::Drawing::Size(277, 113);
				 this->LoadingPanel->TabIndex = 20;
				 this->LoadingPanel->Visible = false;
				 // 
				 // LoadingBackground
				 // 
				 this->LoadingBackground->BackColor = System::Drawing::Color::SeaShell;
				 this->LoadingBackground->Controls->Add(this->LoadingForeground);
				 this->LoadingBackground->Location = System::Drawing::Point(28, 65);
				 this->LoadingBackground->Name = L"LoadingBackground";
				 this->LoadingBackground->Size = System::Drawing::Size(225, 23);
				 this->LoadingBackground->TabIndex = 3;
				 // 
				 // LoadingForeground
				 // 
				 this->LoadingForeground->BackColor = System::Drawing::Color::Lime;
				 this->LoadingForeground->Location = System::Drawing::Point(0, 0);
				 this->LoadingForeground->MaximumSize = System::Drawing::Size(225, 0);
				 this->LoadingForeground->Name = L"LoadingForeground";
				 this->LoadingForeground->Size = System::Drawing::Size(225, 0);
				 this->LoadingForeground->TabIndex = 5;
				 // 
				 // LoadingLabel
				 // 
				 this->LoadingLabel->AutoSize = true;
				 this->LoadingLabel->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->LoadingLabel->ForeColor = System::Drawing::Color::White;
				 this->LoadingLabel->Location = System::Drawing::Point(63, 35);
				 this->LoadingLabel->Name = L"LoadingLabel";
				 this->LoadingLabel->Size = System::Drawing::Size(133, 15);
				 this->LoadingLabel->TabIndex = 1;
				 this->LoadingLabel->Text = L"Loading Please Wait...";
				 this->LoadingLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // MainWindowRenderingTimer
				 // 
				 this->MainWindowRenderingTimer->Interval = 1;
				 this->MainWindowRenderingTimer->Tick += gcnew System::EventHandler(this, &Editor::MainWindowRenderingTimer_Tick);
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
					 this->fileToolStripMenuItem,
						 this->editToolStripMenuItem, this->toolsToolStripMenuItem, this->gameToolStripMenuItem, this->helpToolStripMenuItem
				 });
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Padding = System::Windows::Forms::Padding(7, 2, 0, 2);
				 this->menuStrip1->Size = System::Drawing::Size(2221, 24);
				 this->menuStrip1->TabIndex = 4;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // fileToolStripMenuItem
				 // 
				 this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
					 this->newToolStripMenuItem,
						 this->openToolStripMenuItem, this->toolStripSeparator, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->toolStripSeparator1,
						 this->exitToolStripMenuItem
				 });
				 this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
				 this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
				 this->fileToolStripMenuItem->Text = L"&File";
				 // 
				 // newToolStripMenuItem
				 // 
				 this->newToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->sceneToolStripMenuItem });
				 this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
				 this->newToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
				 this->newToolStripMenuItem->ShowShortcutKeys = false;
				 this->newToolStripMenuItem->Size = System::Drawing::Size(114, 22);
				 this->newToolStripMenuItem->Text = L"&New";
				 // 
				 // sceneToolStripMenuItem
				 // 
				 this->sceneToolStripMenuItem->Name = L"sceneToolStripMenuItem";
				 this->sceneToolStripMenuItem->Size = System::Drawing::Size(105, 22);
				 this->sceneToolStripMenuItem->Text = L"Scene";
				 // 
				 // openToolStripMenuItem
				 // 
				 this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
				 this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
				 this->openToolStripMenuItem->ShowShortcutKeys = false;
				 this->openToolStripMenuItem->Size = System::Drawing::Size(114, 22);
				 this->openToolStripMenuItem->Text = L"&Open";
				 this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Editor::openToolStripMenuItem_Click);
				 // 
				 // toolStripSeparator
				 // 
				 this->toolStripSeparator->Name = L"toolStripSeparator";
				 this->toolStripSeparator->Size = System::Drawing::Size(111, 6);
				 // 
				 // saveToolStripMenuItem
				 // 
				 this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
				 this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
				 this->saveToolStripMenuItem->ShowShortcutKeys = false;
				 this->saveToolStripMenuItem->Size = System::Drawing::Size(114, 22);
				 this->saveToolStripMenuItem->Text = L"&Save";
				 // 
				 // saveAsToolStripMenuItem
				 // 
				 this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
				 this->saveAsToolStripMenuItem->Size = System::Drawing::Size(114, 22);
				 this->saveAsToolStripMenuItem->Text = L"Save &As";
				 // 
				 // toolStripSeparator1
				 // 
				 this->toolStripSeparator1->Name = L"toolStripSeparator1";
				 this->toolStripSeparator1->Size = System::Drawing::Size(111, 6);
				 // 
				 // exitToolStripMenuItem
				 // 
				 this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
				 this->exitToolStripMenuItem->Size = System::Drawing::Size(114, 22);
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
				 // gameToolStripMenuItem
				 // 
				 this->gameToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->RunInWindowToolStripMenuItem,
						 this->RunInVRToolStripMenuItem
				 });
				 this->gameToolStripMenuItem->Name = L"gameToolStripMenuItem";
				 this->gameToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::G));
				 this->gameToolStripMenuItem->Size = System::Drawing::Size(50, 20);
				 this->gameToolStripMenuItem->Text = L"&Game";
				 // 
				 // RunInWindowToolStripMenuItem
				 // 
				 this->RunInWindowToolStripMenuItem->Checked = true;
				 this->RunInWindowToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->RunInWindowToolStripMenuItem->Name = L"RunInWindowToolStripMenuItem";
				 this->RunInWindowToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R));
				 this->RunInWindowToolStripMenuItem->Size = System::Drawing::Size(196, 22);
				 this->RunInWindowToolStripMenuItem->Text = L"&Run in Window";
				 this->RunInWindowToolStripMenuItem->Click += gcnew System::EventHandler(this, &Editor::RunInWindowToolStripMenuItem_Click);
				 // 
				 // RunInVRToolStripMenuItem
				 // 
				 this->RunInVRToolStripMenuItem->Name = L"RunInVRToolStripMenuItem";
				 this->RunInVRToolStripMenuItem->Size = System::Drawing::Size(196, 22);
				 this->RunInVRToolStripMenuItem->Text = L"Run in VR";
				 this->RunInVRToolStripMenuItem->Click += gcnew System::EventHandler(this, &Editor::RunInVRToolStripMenuItem_Click);
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
				 // openFileDialog
				 // 
				 this->openFileDialog->DefaultExt = L"mes";
				 this->openFileDialog->FileName = L"openFileDialog";
				 // 
				 // LoadingTimer
				 // 
				 this->LoadingTimer->Interval = 1;
				 this->LoadingTimer->Tick += gcnew System::EventHandler(this, &Editor::LoadingTimer_Tick);
				 // 
				 // Editor
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(7, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(2221, 1041);
				 this->Controls->Add(this->BackgroundPanel);
				 this->Controls->Add(this->menuStrip1);
				 this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->MainMenuStrip = this->menuStrip1;
				 this->Name = L"Editor";
				 this->Text = L"Monkey Engine";
				 this->Load += gcnew System::EventHandler(this, &Editor::Form_OnLoad);
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
				 this->LoadingPanel->ResumeLayout(false);
				 this->LoadingPanel->PerformLayout();
				 this->LoadingBackground->ResumeLayout(false);
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
	private: void MainWindowRenderingTimer_Tick(System::Object^  sender, System::EventArgs^  e);
	private: void LoadingTimer_Tick(System::Object^  sender, System::EventArgs^  e);
	private: void RunInWindowToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: void RunInVRToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: void RenderingPanel_SizeChanged(System::Object^  sender, System::EventArgs^  e);
	private: void RenderingPanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: void RenderingPanel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	public:	static void Editor::ButtonCollapsed(unsigned int buttonIndex, MonkeyEngine::MEObject::GameObject* _Object);
	public: static void Editor::ButtonExpanded(unsigned int buttonIndex, MonkeyEngine::MEObject::GameObject* _Object);
	private: void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: void LoadHelper();
	public: String^ OpenFile;
	private: void PlayButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: void StopButton_Click(System::Object^  sender, System::EventArgs^  e);
};
}
