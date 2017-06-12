#pragma once
#include "../../GameObject/GameObject.h"
class Scene
{
	friend class MountainDew;
private:
	std::vector<MEObject::GameObject*> m_vObjects;
public:
	Scene();
	~Scene();

	void initialize();
	MEReturnValues::RETURNVALUE Update();
	void Shutdown();
};

