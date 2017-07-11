#pragma once
#include "../../GameObject/GameObject.h"
namespace MERenderer
{
	class DebugCamera;
}
class Scene
{
	friend class MountainDew;
private:
	std::vector<MEObject::GameObject*> m_vObjects;
	MERenderer::DebugCamera* m_pDebugCamera;
public:
	Scene();
	~Scene();

	void initialize(int _ScreenWidth, int _ScreenHeight);
	MEReturnValues::RETURNVALUE Update();
	void Shutdown();
};

