#pragma once
#include "../../GameObject/GameObject.h"
class Scene
{
private:
	std::vector<MEObject::GameObject*> m_vObjects;
public:
	Scene();
	~Scene();
};

