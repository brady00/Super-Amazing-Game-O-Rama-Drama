#include "TransformPanel.h"

namespace Editor
{
	void TransformPanel::CreatePanel(Panel^ InspectorBackgroundPanel, unsigned int Index)
	{
		ComponentPanel::CreatePanel(InspectorBackgroundPanel, Index);
		TextBox^ PosX, ^PosY, ^PosZ, ^RotX, ^RotY, ^RotZ, ^ScaX, ^ScaY, ^ScaZ;
		Windows::Forms::Label^ Position, ^PositionX, ^PositionY, ^PositionZ, ^Rotation, ^RotationX, ^RotationY, ^RotationZ, ^Scale, ^ScaleX, ^ScaleY, ^ScaleZ;
		Position = gcnew Windows::Forms::Label();
		Position->Text = "Position";
		Position->Location = Point(0, 0);
		Position->Anchor = System::Windows::Forms::AnchorStyles::Left;
		Rotation = gcnew Windows::Forms::Label();
		Rotation->Text = "Rotation";
		Rotation->Location = Point(0, 30);
		Scale = gcnew Windows::Forms::Label();
		Scale->Text = "Scale";
		Scale->Location = Point(0, 60);

	}
}