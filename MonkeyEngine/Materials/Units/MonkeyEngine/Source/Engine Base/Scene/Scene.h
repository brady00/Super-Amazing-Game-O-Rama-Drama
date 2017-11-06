#pragma once
#include "GameObject/GameObject.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class DebugCamera;
	}
	class Scene
	{
		friend class MountainDew;
	public:
		std::vector<MEObject::GameObject*> m_vObjects;
	private:
		MERenderer::DebugCamera* m_pDebugCamera;
		void AddObject(MEObject::GameObject* _GameObject); 
	public:
		Scene();
		~Scene();
		//in: UINT
		//	The Width of the Screen
		//in: UINT
		//	The Height of the Screen
		//out: void
		//desc: Initializes all objects in the Scene, and the DebugCamera
		void initialize(int _ScreenWidth, int _ScreenHeight);
		//in: void
		//out: void
		//desc: Updates all Objects in the Scene, and the Active Camera
		void Update();
		//in: void
		//out: void
		//desc: Shuts down all Objects in the Scene, and cleans up any memory
		void Shutdown();
		//in: string&
		//	The File Name of the .MES file
		//out: float&
		//	Percentage of the Load, used for Loading Screen Purposes
		//out: bool&
		//	Whether the Load Succeeded or Failed
		//out: void
		//desc: Loads a .MES file into the scene
		void Load(string& _FileName, float& _percentLoaded, bool& Success);
		//in: string&
		//	The .MES File to save too
		//out: bool
		//	Whether the Save Succeeded or Failed
		//desc: Saves a scene to a .MES file
		bool Save(string& _FileName);
		//out: vector<GameObject*>&
		//	The list of GameObjects in the Scene
		//desc: Gets the list of GameObjects in a Scene
		std::vector<MEObject::GameObject*>& GetObjects();
		//out: DebugCamera*
		//	The DebugCamera of this Scene
		//desc: Gets the DebugCamera of this Scene
		MERenderer::DebugCamera* GetDebugCamera();
	};
}
