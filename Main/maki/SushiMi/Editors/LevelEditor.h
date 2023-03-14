/*!*****************************************************************************

\file       LevelEditor.h
\author     Thea Sea. thea.sea, 2102348
\par        DP email: thea.sea@digipen.edu
\par        Course: CSD2400/GAM200
\date       7-10-2022

\brief
This program is a header file for GameEditor.cpp that implements a Game Engine Editor using ImGui

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/
#pragma once

#include "../Headers/STL_Header.h"
#include "../Headers/ImGui_Header.h"
#include "../../glew/include/GL/glew.h"
#include "../Engine/System/Graphics/glhelper.h"
#include "../Engine/System/SystemFrame.h"
//#include "../Engine/Texture/Sprite.h"


namespace Core
{
	class Window;
	class Sprite;
	class ObjectFactory;

	//Object Enums for object selection:
	enum OBJECTTYPES
	{
		GRASS, //1
		PATH1,
		PATH2,
		PATH3,
		WALL1,
		WALL2,
		WALL3,
		AVOCADO,
		CORN,
		RICE,
		NORI
	};

	namespace Editor
	{		
		class LevelEditor : public SystemFrame
		{
		public:
			static LevelEditor* GetInstance()
			{
				//LevelEditor* instance = new LevelEditor(); //mem leak!!
				//return instance;

				//do this instead
				static LevelEditor instance;
				return &instance;
			}

			static void imguiEditorInit(void);
			static void imguiGraphicsTest(void);
			static void imguiEditorDraw(void);
			static void imguiShutDown(void);
			static inline bool loadnewlevel = 0;
			static inline int levelsave = 0;
			static inline std::string path, path2, imguiloadedmap;

			static void imguiCreateObj();
			static void imguiDestroyObj();
			static inline int imguiPlacedObjs = 0;
			
			static void AddToFactory(ObjectFactory* container);

			static inline const char* texpath = "../textures/Tiles/Wall/RicePlain_Wall3_2.jpg";

#ifdef  EDITOR
			static inline bool hierarchyload;

			struct addedobjinfo
			{
				std::string objname;
				char enum_;
				Sprite* spritepath;
				std::string filepath;
				int x;
				int y;
				int ID;

			}add_obj_info_here;


			static inline  std::vector<addedobjinfo> newobjarr;
			static inline  std::vector<addedobjinfo> TopLayerLegend; //aGrids and gGrids
			static inline  std::vector<addedobjinfo> BottomLayerLegend; //wGrids
			static inline  std::vector<addedobjinfo> Hierarchy_BottomLayer; //Display all the objects in Bottom Layer
			static inline  std::vector<addedobjinfo> Hierarchy_TopLayer; //Display all the objects in Top Layer
#endif //  EDITOR
			//obj placing
			static inline bool objplace = false;
			static void imguiObjectCursor(void);

			void Init() {}
			void Update(const double dt) { dt; }
			void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer) {}
			static inline std::string alphabet;
			static inline int xgrid, ygrid;

		private:

			inline static bool drawTexture = true;
			inline static float size = 1.0f;
			inline static float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
			//inline static GLuint VAO, VBO;
			inline static int width, height, nrChannels;
			//static inline bool m_BlockEvents = true;

		};
	}
}