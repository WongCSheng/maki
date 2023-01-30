#pragma once
#include "../Engine/Components/Texture/Sprite.h"
#include "../Game Object/Player.h"
#include "../src/Window.h"

namespace Core
{
	class SceneManager : public SystemFrame
	{
	public:
		SceneManager();
		~SceneManager();

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		static  void restartLevel();
		static  void nextLevel();
		/*HARD CODE FOR NOW, WILL MAKE IT COMPONENT BASED*/
		static  void loadTile(int x, int y);
		static  void loadIngr1(int x, int y);
		static  void loadIngr2(int x, int y);
		static  void loadTrap(int x, int y);
		static  void loadGoal1(int x, int y);
		static  void loadGoal2(int x, int y);
		static  void loadPauseOverlay(int x, int y);
		static  void drawTile();
		static  void drawIngr1();
		static  void drawIngr2();
		static  void drawTrap();
		static  void drawGoal1();
		static  void drawGoal2();
		static  void drawPauseOverlay();
		static  void destroyTile();
		static  void destroyIngr()
		static  void destroyTrap();
		static  void destroyGoal1();
		static  void destroyGoal2();
		static  void destroyPauseOverlay();

		static  void Readfile();

		static  void setRowsandCols(unsigned int inRow, unsigned int inCol);
		static  void setTileDimension(unsigned int Width, unsigned int Height);

		unsigned int getRows();
		unsigned int getCols();
		unsigned int getTileWidth();
		unsigned int getTileHeight();

		static inline Sprite* tile;
		static inline Sprite* ingredient1;
		static inline Sprite* ingredient2;
		static inline Sprite* trap;
		static inline Sprite* goal1;
		static inline Sprite* goal2;
		static inline Sprite* pause_overlay;
		static inline Sprite* menu;

		unsigned int rows, cols,
			tileWidth, tileHeight;
	};
}