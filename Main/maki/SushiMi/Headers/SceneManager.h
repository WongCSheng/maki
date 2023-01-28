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
		static  void loadIngr(int x, int y);
		static  void loadTrap(int x, int y);
		static  void loadGoal(int x, int y);
		static  void drawTile();
		static  void drawIngr();
		static  void drawTrap();
		static  void drawGoal();
		static  void destroyTile();
		static  void destroyIngr();
		static  void destroyTrap();
		static  void destroyGoal();

		static  void Readfile();

		static  void setRowsandCols(unsigned int inRow, unsigned int inCol);
		static  void setTileDimension(unsigned int Width, unsigned int Height);

		unsigned int getRows();
		unsigned int getCols();
		unsigned int getTileWidth();
		unsigned int getTileHeight();

		static inline Sprite* tile;
		static inline Sprite* ingredient;
		static inline Sprite* trap;
		static inline Sprite* goal;

		unsigned int rows, cols,
			tileWidth, tileHeight;
	};
}