#pragma once

#ifndef RENDERER_H_
#define RENDERER_H_

#include "../Headers/STL_Header.h"
#include "SystemFrame.h"
<<<<<<< HEAD
#include "../Mesh/model.h"
#include "../Components/Component.h"

=======
//#include "../Mesh/model.h"
>>>>>>> M3-submission-branch

namespace Core
{
	//Forward Declaration
	class SystemFrame;
<<<<<<< HEAD
=======

	struct vtx
	{
		unsigned int VAO;  //vertex array object
		unsigned int VBO;  // vertex buffer object
		unsigned int CBO;  // color buffer object
		unsigned int UVBO; // uv buffer object
	};
>>>>>>> M3-submission-branch
	
	class Renderer : public SystemFrame
	{
	public:
		Renderer();
		virtual ~Renderer();
		void Init();
<<<<<<< HEAD
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

=======
		vtx Generate();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
		static Renderer* GetInstance()
		{
			static Renderer renderersystem;
			return &renderersystem;
		}
		void Delete(vtx& obj);
>>>>>>> M3-submission-branch
	private:
		/*std::vector<MeshFilter*> meshFilterComponents;
		std::vector<Material*> materialComponents;
		std::vector<MeshRenderer*> meshRendererComponents;*/
<<<<<<< HEAD

		std::vector<Model*> meshes;
=======
		//static Renderer* _instance;
		//std::vector<Model*> meshes;

>>>>>>> M3-submission-branch
	};
}

#endif