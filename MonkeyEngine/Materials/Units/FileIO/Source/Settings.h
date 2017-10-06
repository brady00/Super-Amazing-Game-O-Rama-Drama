#pragma once
#include <string>
#include <vector>
#include <Windows.h>
namespace MonkeyEngine
{
	struct SettingData
	{
		std::string Name;
		std::string Value;

		SettingData() {};
		SettingData(std::string _Name, std::string _Value)
		{
			Name = _Name;
			Value = _Value;
		};
	};

	class Settings
	{
	private:
		// Static Instance for Singleton
		static Settings *m_pSettingsPtr;

		std::vector<SettingData*> m_SettingData;
		// Video
		LONG m_ScreenWidth;
		LONG m_ScreenHeight;
		// Controls
		float m_MouseSensitivity;
		float m_MovementSpeed;

	public:
		Settings();
		~Settings();

		static Settings* GetInstance() { if (!m_pSettingsPtr) m_pSettingsPtr = new Settings;  return m_pSettingsPtr; }
		static void DestroyInstance() { if (m_pSettingsPtr) delete m_pSettingsPtr; m_pSettingsPtr = m_pSettingsPtr; }

		void Initialize();
		void Shutdown();
		
		// Accessors
		LONG GetScreenWidth() { return m_ScreenWidth; };
		LONG GetScreenHeight() { return m_ScreenHeight; };
		float GetMouseSensitivity() { return m_MouseSensitivity; };
		float GetMovementSpeed() { return m_MovementSpeed; };

		// Mutators
		void SetScreenWidth(LONG p_value) { m_ScreenWidth = p_value; };
		void SetScreenHeight(LONG p_value) { m_ScreenHeight = p_value; };
		void SetMouseSensitivity(float p_value) { m_MouseSensitivity = p_value; };
		void SetMovementSpeed(float p_value) { m_MovementSpeed = p_value; };
	};
}