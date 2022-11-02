//******************************************************************************/
/*!
\file		Renderer.cpp
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Graphics render system.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/

#include "Renderer.h"

Core::Renderer::Renderer()
{
}

Core::Renderer::~Renderer()
{
}

void Core::Renderer::Init()
{
	/*for (unsigned i = 0; i < entities.size(); ++i)
	{
		Model* mesh = entities[i]->GetComponent<Model>();
		if (mesh != NULL)
		{
			meshes.push_back(mesh);
		}
	}*/
}

void Core::Renderer::Update(const double dt)
{

}

void Core::Renderer::RegisterComponent(std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer)
{

}