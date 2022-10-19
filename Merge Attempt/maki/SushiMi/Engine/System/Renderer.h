#pragma once

#ifndef RENDERER_H_
#define RENDERER_H_

#include "../Headers/STL_Header.h"
#include "SystemFrame.h"
#include "../Mesh/model.h"
#include "../Entity/ECS.h"


namespace Core
{
	//Forward Declaration
	class SystemFrame;
	
	class Renderer : public ::SystemFrame
	{
	public:
		Renderer();
		virtual ~Renderer();
		virtual void RegisterComponents(const Core::Component comp);
		virtual void Update(const double dt);
		virtual void CheckForNewComponents(void);

	private:
		/*std::vector<MeshFilter*> meshFilterComponents;
		std::vector<Material*> materialComponents;
		std::vector<MeshRenderer*> meshRendererComponents;*/

		std::vector<Model*> meshes;
	};
}

#endif