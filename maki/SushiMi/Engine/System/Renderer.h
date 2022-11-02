//******************************************************************************/
/*!
\file		Renderer.cpp
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Header for Graphics render system.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/

#pragma once

#ifndef RENDERER_H_
#define RENDERER_H_

#include "SystemFrame.h"
#include "../Mesh/model.h"
#include "../Components/Component.h"


namespace Core
{
	//Forward Declaration
	class SystemFrame;

	class Renderer : public SystemFrame
	{
	public:
		Renderer();
		virtual ~Renderer();
		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer);

	private:
		/*std::vector<MeshFilter*> meshFilterComponents;
		std::vector<Material*> materialComponents;
		std::vector<MeshRenderer*> meshRendererComponents;*/

		std::vector<Model*> meshes;
	};
}

#endif