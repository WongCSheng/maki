/*
GameObject.cpp
*/

#include "GameObject.h"

namespace Object
{
	GameObjectProperty::GameObjectProperty()
	{
		ComponentContainer = new Core::Component[1000];
		ID = 0;
	}

	GameObjectProperty::~GameObjectProperty()
	{
		delete[] ComponentContainer;
	}

	void GameObjectProperty::Init()
	{
		for (int i = 0; i < 1000; ++i)
		{
			ComponentContainer[i].owner = this;
			ComponentContainer[i].Init();
		}
	}
}