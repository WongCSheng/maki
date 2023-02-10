#pragma once
#include "../Engine/Texture/Sprite.h"
#include "../Game Object/Player.h"
#include "../src/Window.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void restartLevel();
	void nextLevel();
	void loadTile();
	void drawTile();

	void Readfile();

	void setRowsandCols(unsigned int inRow, unsigned int inCol);
	void setTileDimension(unsigned int Width, unsigned int Height);

	unsigned int getRows();
	unsigned int getCols();
	unsigned int getTileWidth();
	unsigned int getTileHeight();

	Sprite* tile;
	
	unsigned int rows, cols,
		tileWidth, tileHeight;
};