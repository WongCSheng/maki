#pragma once

#ifndef RENDERER_H_
#define RENDERER_H_

#include "../Headers/STL_Header.h"
#include "../SystemFrame.h"
//#include "../Mesh/model.h"

namespace Core
{
	//Forward Declaration
	class SystemFrame;

	struct vtx
	{
		unsigned int VAO;  //vertex array object
		unsigned int VBO;  // vertex buffer object
		unsigned int CBO;  // color buffer object
		unsigned int UVBO; // uv buffer object
	};
	
	class Renderer : public SystemFrame
	{
	public:
		Renderer();
		virtual ~Renderer();
		void Init();
		vtx Generate();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
		static Renderer* GetInstance()
		{
			static Renderer renderersystem;
			return &renderersystem;
		}
		void Delete(vtx& obj);
	private:
		/*std::vector<MeshFilter*> meshFilterComponents;
		std::vector<Material*> materialComponents;
		std::vector<MeshRenderer*> meshRendererComponents;*/
		//static Renderer* _instance;
		//std::vector<Model*> meshes;

	};
}

#endif