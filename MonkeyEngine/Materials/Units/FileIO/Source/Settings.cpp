#include "Settings.h"
#include "FileIO.h"
#include "DebugCamera\DebugCamera.h"

namespace MonkeyEngine
{
	Settings* Settings::m_pSettingsPtr = nullptr;

	Settings* Settings::GetInstance()
	{
		if (!m_pSettingsPtr) 
			m_pSettingsPtr = new Settings;  
		return m_pSettingsPtr; 
	}

	void Settings::DestroyInstance()
	{
		if (m_pSettingsPtr)
			delete m_pSettingsPtr; 
		m_pSettingsPtr = m_pSettingsPtr; 
	}

	Settings::Settings()
	{
		// Fill vector with defaults

		// Video
		SettingData* ScreenWidth = new SettingData("ScreenWidth", "1920");					// Screen Width
		m_SettingData.push_back(ScreenWidth);

		SettingData* ScreenHeight = new SettingData("ScreenHeight", "1080");				// Screen Height
		m_SettingData.push_back(ScreenHeight);

		// Controls
		SettingData* MouseSensitivity = new SettingData("MouseSensitivity", "2.5");			// Mouse Sensitivity
		m_SettingData.push_back(MouseSensitivity);

		SettingData* MovementSpeed = new SettingData("MovementSpeed", "1.0");				// Movement Speed
		m_SettingData.push_back(MovementSpeed);
	}

	Settings::~Settings()
	{
		Shutdown();
	}

	void Settings::Initialize()
	{
		// Load Settings from config file
		MEFileIO::FileIO::LoadSettings(m_SettingData);

		// Fill out data members with vector's values
		for (unsigned int i = 0; i < m_SettingData.size(); i++)
		{
			// Video
			if (m_SettingData[i]->Name == "ScreenWidth")									// Screen Width
				SetScreenWidth((LONG)std::stol(m_SettingData[i]->Value, nullptr, 10));

			else if (m_SettingData[i]->Name == "ScreenHeight")								// Screen Height
				SetScreenHeight((LONG)std::stol(m_SettingData[i]->Value, nullptr, 10));

			// Controls
			else if (m_SettingData[i]->Name == "MouseSensitivity")							// Mouse Sensitivity
				SetMouseSensitivity((float)std::stof(m_SettingData[i]->Value, nullptr));

			else if (m_SettingData[i]->Name == "MovementSpeed")								// Movement Speed
				SetMovementSpeed((float)std::stof(m_SettingData[i]->Value, nullptr));

			else
				continue;

			delete m_SettingData[i];
			m_SettingData[i] = nullptr;
		}

		// Set Singleton
		m_pSettingsPtr = this;
		DebugCamera::GetInstance()->SetMovementSpeed(m_MovementSpeed);
		DebugCamera::GetInstance()->SetMouseSensitivity(m_MouseSensitivity);
	}

	void Settings::Shutdown()
	{
		for (unsigned int i = 0; i < m_SettingData.size(); i++)
		{
			delete m_SettingData[i];
			m_SettingData[i] = nullptr;
		}
		m_SettingData.clear();

		//DestroyInstance();
	}
}