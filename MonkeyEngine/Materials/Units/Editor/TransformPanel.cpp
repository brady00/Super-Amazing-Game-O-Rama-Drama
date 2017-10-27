#include "TransformPanel.h"
#include "Transform\Transform.h"

namespace Editor
{
	void TransformPanel::CreatePanel(Panel^ InspectorBackgroundPanel, unsigned int Index)
	{
		XMFLOAT3 pos, rot, scale;
		pos = ((MonkeyEngine::MEObject::Transform*)Comp)->GetPosition();
		rot = ((MonkeyEngine::MEObject::Transform*)Comp)->GetRotation();
		scale = ((MonkeyEngine::MEObject::Transform*)Comp)->GetScale();
		ComponentPanel::CreatePanel(InspectorBackgroundPanel, Index);
		PosX = gcnew TextBox;
		PosY = gcnew TextBox;
		PosZ = gcnew TextBox;
		PositionX = gcnew Windows::Forms::Label();
		PositionY = gcnew Windows::Forms::Label();
		PositionZ = gcnew Windows::Forms::Label();
		PosX->Location = Point(250, -5);
		PosY->Location = Point(300, -5);
		PosZ->Location = Point(350, -5);
		PositionX->Location = Point(230, -5);
		PositionY->Location = Point(280, -5);
		PositionZ->Location = Point(330, -5);
		PosX->Anchor = System::Windows::Forms::AnchorStyles::Right;
		PosY->Anchor = System::Windows::Forms::AnchorStyles::Right;
		PosZ->Anchor = System::Windows::Forms::AnchorStyles::Right;
		PositionX->Anchor = System::Windows::Forms::AnchorStyles::Right;
		PositionY->Anchor = System::Windows::Forms::AnchorStyles::Right;
		PositionZ->Anchor = System::Windows::Forms::AnchorStyles::Right;
		PosX->Visible = false;
		PosY->Visible = false;
		PosZ->Visible = false;
		PositionX->Visible = false;
		PositionY->Visible = false;
		PositionZ->Visible = false;
		PosX->Width = PosX->Width / 3.0f;
		PosY->Width = PosY->Width / 3.0f;
		PosZ->Width = PosZ->Width / 3.0f;
		PositionX->Width = 20;
		PositionY->Width = 20;
		PositionZ->Width = 20;
		if (pos.x - (int)pos.x == 0)
			PosX->Text = gcnew String(std::string(std::to_string((int)pos.x)).c_str());
		else
			PosX->Text = gcnew String(std::string(std::to_string((float)pos.x)).c_str());
		if (pos.y - (int)pos.y == 0)
			PosY->Text = gcnew String(std::string(std::to_string((int)pos.y)).c_str());
		else
			PosY->Text = gcnew String(std::string(std::to_string((float)pos.y)).c_str());
		if (pos.z - (int)pos.z == 0)
			PosZ->Text = gcnew String(std::string(std::to_string((int)pos.z)).c_str());
		else
			PosZ->Text = gcnew String(std::string(std::to_string((float)pos.z)).c_str());
		PositionX->Text = "X";
		PositionY->Text = "Y";
		PositionZ->Text = "Z";
		PositionX->ForeColor = Color::White;
		PositionY->ForeColor = Color::White;
		PositionZ->ForeColor = Color::White;

		Position = gcnew Windows::Forms::Label();
		Position->Text = "Position";
		Position->Location = Point(0, 0);
		Position->Anchor = System::Windows::Forms::AnchorStyles::Left;
		Position->Visible = false;
		Position->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		Position->ForeColor = Color::White;

		RotX = gcnew TextBox;
		RotY = gcnew TextBox;
		RotZ = gcnew TextBox;
		RotationX = gcnew Windows::Forms::Label();
		RotationY = gcnew Windows::Forms::Label();
		RotationZ = gcnew Windows::Forms::Label();
		RotX->Location = Point(250, 15);
		RotY->Location = Point(300, 15);
		RotZ->Location = Point(350, 15);
		RotationX->Location = Point(230, 15);
		RotationY->Location = Point(280, 15);
		RotationZ->Location = Point(330, 15);
		RotX->Anchor = System::Windows::Forms::AnchorStyles::Right;
		RotY->Anchor = System::Windows::Forms::AnchorStyles::Right;
		RotZ->Anchor = System::Windows::Forms::AnchorStyles::Right;
		RotationX->Anchor = System::Windows::Forms::AnchorStyles::Right;
		RotationY->Anchor = System::Windows::Forms::AnchorStyles::Right;
		RotationZ->Anchor = System::Windows::Forms::AnchorStyles::Right;
		RotX->Visible = false;
		RotY->Visible = false;
		RotZ->Visible = false;
		RotationX->Visible = false;
		RotationY->Visible = false;
		RotationZ->Visible = false;
		RotX->Width = RotX->Width / 3.0f;
		RotY->Width = RotY->Width / 3.0f;
		RotZ->Width = RotZ->Width / 3.0f;
		RotationX->Width = 20;
		RotationY->Width = 20;
		RotationZ->Width = 20;
		if (rot.x - (int)rot.x == 0)
			RotX->Text = gcnew String(std::string(std::to_string((int)rot.x)).c_str());
		else
			RotX->Text = gcnew String(std::string(std::to_string((float)rot.x)).c_str());
		if (rot.y - (int)rot.y == 0)
			RotY->Text = gcnew String(std::string(std::to_string((int)rot.y)).c_str());
		else
			RotY->Text = gcnew String(std::string(std::to_string((float)rot.y)).c_str());
		if (rot.z - (int)rot.z == 0)
			RotZ->Text = gcnew String(std::string(std::to_string((int)rot.z)).c_str());
		else
			RotZ->Text = gcnew String(std::string(std::to_string((float)rot.z)).c_str());
		RotationX->Text = "X";
		RotationY->Text = "Y";
		RotationZ->Text = "Z";
		RotationX->ForeColor = Color::White;
		RotationY->ForeColor = Color::White;
		RotationZ->ForeColor = Color::White;

		Rotation = gcnew Windows::Forms::Label();
		Rotation->Text = "Rotation";
		Rotation->Location = Point(0, 20);
		Rotation->Anchor = System::Windows::Forms::AnchorStyles::Left;
		Rotation->Visible = false;
		Rotation->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		Rotation->ForeColor = Color::White;

		ScaX = gcnew TextBox;
		ScaY = gcnew TextBox;
		ScaZ = gcnew TextBox;
		ScaleX = gcnew Windows::Forms::Label();
		ScaleY = gcnew Windows::Forms::Label();
		ScaleZ = gcnew Windows::Forms::Label();
		ScaX->Location = Point(250, 35);
		ScaY->Location = Point(300, 35);
		ScaZ->Location = Point(350, 35);
		ScaleX->Location = Point(230, 35);
		ScaleY->Location = Point(280, 35);
		ScaleZ->Location = Point(330, 35);
		ScaX->Anchor = System::Windows::Forms::AnchorStyles::Right;
		ScaY->Anchor = System::Windows::Forms::AnchorStyles::Right;
		ScaZ->Anchor = System::Windows::Forms::AnchorStyles::Right;
		ScaleX->Anchor = System::Windows::Forms::AnchorStyles::Right;
		ScaleY->Anchor = System::Windows::Forms::AnchorStyles::Right;
		ScaleZ->Anchor = System::Windows::Forms::AnchorStyles::Right;
		ScaX->Visible = false;
		ScaY->Visible = false;
		ScaZ->Visible = false;
		ScaleX->Visible = false;
		ScaleY->Visible = false;
		ScaleZ->Visible = false;
		ScaX->Width = ScaX->Width / 3.0f;
		ScaY->Width = ScaY->Width / 3.0f;
		ScaZ->Width = ScaZ->Width / 3.0f;
		ScaleX->Width = 20;
		ScaleY->Width = 20;
		ScaleZ->Width = 20;
		if (scale.x - (int)scale.x == 0)
			ScaX->Text = gcnew String(std::string(std::to_string((int)scale.x)).c_str());
		else
			ScaX->Text = gcnew String(std::string(std::to_string((float)scale.x)).c_str());
		if (scale.y - (int)scale.y == 0)
			ScaY->Text = gcnew String(std::string(std::to_string((int)scale.y)).c_str());
		else
			ScaY->Text = gcnew String(std::string(std::to_string((float)scale.y)).c_str());
		if (scale.z - (int)scale.z == 0)
			ScaZ->Text = gcnew String(std::string(std::to_string((int)scale.z)).c_str());
		else
			ScaZ->Text = gcnew String(std::string(std::to_string((float)scale.z)).c_str());
		ScaleX->Text = "X";
		ScaleY->Text = "Y";
		ScaleZ->Text = "Z";
		ScaleX->ForeColor = Color::White;
		ScaleY->ForeColor = Color::White;
		ScaleZ->ForeColor = Color::White;

		Scale = gcnew Windows::Forms::Label();
		Scale->Text = "Scale";
		Scale->Location = Point(0, 40);
		Scale->Anchor = System::Windows::Forms::AnchorStyles::Left;
		Scale->Visible = false;
		Scale->Font = (gcnew System::Drawing::Font(L"Adobe Fan Heiti Std B", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		Scale->ForeColor = Color::White;

		PosX->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);
		PosY->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);
		PosZ->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);
		RotX->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);
		RotY->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);
		RotZ->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);
		ScaX->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);
		ScaY->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);
		ScaZ->KeyDown += gcnew KeyEventHandler(this, &TransformPanel::OnKeyDown);

		PosX->TextChanged += gcnew EventHandler(this, &TransformPanel::OnPosXChange);
		PosY->TextChanged += gcnew EventHandler(this, &TransformPanel::OnPosYChange);
		PosZ->TextChanged += gcnew EventHandler(this, &TransformPanel::OnPosZChange);
		RotX->TextChanged += gcnew EventHandler(this, &TransformPanel::OnRotXChange);
		RotY->TextChanged += gcnew EventHandler(this, &TransformPanel::OnRotYChange);
		RotZ->TextChanged += gcnew EventHandler(this, &TransformPanel::OnRotZChange);
		ScaX->TextChanged += gcnew EventHandler(this, &TransformPanel::OnScaXChange);
		ScaY->TextChanged += gcnew EventHandler(this, &TransformPanel::OnScaYChange);
		ScaZ->TextChanged += gcnew EventHandler(this, &TransformPanel::OnScaZChange);

		this->Controls->Add(Scale);
		this->Controls->Add(ScaleX);
		this->Controls->Add(ScaX);
		this->Controls->Add(ScaleY);
		this->Controls->Add(ScaY);
		this->Controls->Add(ScaleZ);
		this->Controls->Add(ScaZ);
		this->Controls->Add(Rotation);
		this->Controls->Add(RotationX);
		this->Controls->Add(RotX);
		this->Controls->Add(RotationY);
		this->Controls->Add(RotY);
		this->Controls->Add(RotationZ);
		this->Controls->Add(RotZ);
		this->Controls->Add(Position);
		this->Controls->Add(PositionX);
		this->Controls->Add(PosX);
		this->Controls->Add(PositionY);
		this->Controls->Add(PosY);
		this->Controls->Add(PositionZ);
		this->Controls->Add(PosZ);
		this->MaximumSize = System::Drawing::Size(0, 80);
	}

	void TransformPanel::OnKeyDown(System::Object^  sender, KeyEventArgs^  e)
	{
		if (!((e->KeyCode >= Keys::D0 && e->KeyCode <= Keys::D9) ||
			(e->KeyCode >= Keys::NumPad0 && e->KeyCode <= Keys::NumPad9) ||
			e->KeyCode == Keys::Decimal || e->KeyCode == Keys::Back || e->KeyCode == Keys::Subtract))
			e->SuppressKeyPress = true;
	}

	void TransformPanel::OnPosXChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(PosX->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetPosition().x = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}

	void TransformPanel::OnPosYChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(PosY->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetPosition().y = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}

	void TransformPanel::OnPosZChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(PosZ->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetPosition().z = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}

	void TransformPanel::OnRotXChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(RotX->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetRotation().x = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}

	void TransformPanel::OnRotYChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(RotY->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetRotation().y = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}

	void TransformPanel::OnRotZChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(RotZ->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetRotation().z = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}

	void TransformPanel::OnScaXChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(ScaX->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetScale().x = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}

	void TransformPanel::OnScaYChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(ScaY->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetScale().y = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}

	void TransformPanel::OnScaZChange(System::Object^  sender, EventArgs^  e)
	{
		try
		{
			double temp = System::Convert::ToDouble(ScaZ->Text);
			((MonkeyEngine::MEObject::Transform*)Comp)->GetScale().z = temp;
			return;
		}
		catch (System::FormatException^ exception) {}
	}
}