#pragma once
#include "../Engine/Texture/Sprite.h"
#include "../Game Object/Player.h"
#include "../src/Window.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

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

	static Sprite* tile;

	unsigned int rows, cols,
		tileWidth, tileHeight;
};