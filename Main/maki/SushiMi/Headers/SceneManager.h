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
		static  void loadTile();
		static  void drawTile();
		static  void destroyTile();

		static  void Readfile();

		static  void setRowsandCols(unsigned int inRow, unsigned int inCol);
		static  void setTileDimension(unsigned int Width, unsigned int Height);

		unsigned int getRows();
		unsigned int getCols();
		unsigned int getTileWidth();
		unsigned int getTileHeight();

		static inline Sprite* tile;

		unsigned int rows, cols,
			tileWidth, tileHeight;
	};
}