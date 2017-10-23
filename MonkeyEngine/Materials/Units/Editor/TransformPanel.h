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
		TextBox^ PosX, ^PosY, ^PosZ, ^RotX, ^RotY, ^RotZ, ^ScaX, ^ScaY, ^ScaZ;
		Windows::Forms::Label^ Position, ^PositionX, ^PositionY, ^PositionZ, ^Rotation, ^RotationX, ^RotationY, ^RotationZ, ^Scale, ^ScaleX, ^ScaleY, ^ScaleZ;
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

		}
#pragma endregion
	public: virtual void CreatePanel(Panel^ InspectorBackgroundPanel, unsigned int Index) override;
	private: void OnPosXChange(System::Object^  sender, System::EventArgs^  e);
	private: void OnPosYChange(System::Object^  sender, System::EventArgs^  e);
	private: void OnPosZChange(System::Object^  sender, System::EventArgs^  e);
	private: void OnRotXChange(System::Object^  sender, System::EventArgs^  e);
	private: void OnRotYChange(System::Object^  sender, System::EventArgs^  e);
	private: void OnRotZChange(System::Object^  sender, System::EventArgs^  e);
	private: void OnScaXChange(System::Object^  sender, System::EventArgs^  e);
	private: void OnScaYChange(System::Object^  sender, System::EventArgs^  e);
	private: void OnScaZChange(System::Object^  sender, System::EventArgs^  e);
	};
}
