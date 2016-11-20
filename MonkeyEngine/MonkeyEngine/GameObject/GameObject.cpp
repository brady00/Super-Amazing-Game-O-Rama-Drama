#include "GameObject.h"

namespace MEObject
{
	GameObject::GameObject()
	{
	}


	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
		
	}

	MEReturnValues::RETURNVALUE GameObject::Update()
	{
		for (unsigned int i = 0; i < NumComponents; i++)
			for (unsigned int j = 0; j < m_vComponents[i].size(); j++)
				m_vComponents[i][j]->Update();
		return MEReturnValues::NOTHING;
	}

	void GameObject::ShutDown()
	{
	
	}
}