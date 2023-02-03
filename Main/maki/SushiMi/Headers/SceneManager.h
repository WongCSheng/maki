#pragma once
#include "../Engine/Components/Texture/Sprite.h"
#include "../Game Object/Player.h"
#include "../src/Window.h"

namespace Core
{
	enum class grid_number //Find a better way to identify all textures
	{
		start = 96,
		space = 97,		//a
		ground1,		//b
		ground2,		//c
		ground3,		//d
		player,			//e
		ingredients,
		rice,			//g
		tofu,			//h
		nori,			//i
		inari,			//j
		items,
		sinkhole,		//l
		filledsinkhole,	//m
		box1,			//n
		box2,			//o
		boxcover,		//p
		win,			//q
		temp,			//r
		end
	};

	enum class wall_type //: std::uint16_t
	{
		first = 63,
		left,
		topleftwall,				//A
		bottomleftwall,				//B
		middleleftwall,				//C
		middlelefttoprightwall,		//D
		middleleftbottomrightwall,	//E
		middlebottomlefttopwall,	//F
		right,
		toprightwall,				//H
		bottomrightwall,			//I
		middletoprightbottomwall,	//J
		middlerightwall,			//K
		topbottom,
		bottomwall,					//M
		middletopbottomwall,		//N
		middlewall,					//O
		last
	};

	enum class Bami //: std::uint16_t
	{

	};
	
	class SceneManager : public SystemFrame
	{
	public:
		SceneManager();
		~SceneManager();

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		static void restartLevel();
		static void nextLevel();
		/*HARD CODE FOR NOW, WILL MAKE IT COMPONENT BASED*/
		static void loadTile(int x, int y, const std::pair<wall_type, Sprite*> &tile);
		static void loadIngr(int x, int y, int posX, int posY, const std::pair<grid_number, Sprite*> &ingredient);
		static void loadIngr_initPos(int x, int y, int posX, int posY, const std::pair<grid_number, Sprite*>& ingrposition);
		/*static void loadIngr1(int x, int y);
		static void loadIngr2(int x, int y);
		static void loadTrap(int x, int y);
		static void loadGoal1(int x, int y);
		static void loadGoal2(int x, int y);
		static void loadCover1(int x, int y);
		static void loadCover2(int x, int y);*/
		static void loadPlayer_Stuck(int x, int y);
		static void loadHowToOverlay(int x, int y);
		static void loadSettings(int x, int y);
		static void loadWinOverlay(int x, int y);
		static void drawTile();
		static void drawIngr();

		/*static void drawIngr1();
		static void drawIngr2();
		static void drawTrap();
		static void drawGoal1();
		static void drawGoal2();
		static void drawCover1();
		static void drawCover2();*/
		static void drawPlayer_Stuck();
		static void drawHowToOverlay();
		static void drawSettings();
		static void drawWinOverlay();
		static void destroyTile();
		static void destroyIngr();
		/*static void destroyTrap();
		static void destroyGoal1();
		static void destroyGoal2();
		static void destroyCover1();
		static void destroyCover2();*/
		static void destroyPlayer_Stuck();
		static void destroyHowToOverlay();
		static void destroySettings();
		static void destroyWinOverlay();

		static void Readfile();

		static void setRowsandCols(unsigned int inRow, unsigned int inCol);
		static void setTileDimension(unsigned int Width, unsigned int Height);

		unsigned int getRows();
		unsigned int getCols();
		unsigned int getTileWidth();
		unsigned int getTileHeight();

	
		static inline std::vector<std::pair<wall_type, Sprite*>> tilecontainer;
		static inline std::vector<std::pair<grid_number, Sprite*>> ingredientcontainer;
		static inline std::vector<short> ICnum;
		static inline std::unordered_multimap<grid_number, Sprite*> ingredient_starting_pos;
		static inline std::vector<std::pair<int, int>> win_condition;
		static unsigned int amt_of_win_conditions;
		/*static inline Sprite* tile;
		static inline Sprite* ingredient1;
		static inline Sprite* ingredient2;
		static inline Sprite* trap;
		static inline Sprite* goal1;
		static inline Sprite* goal2;
		static inline Sprite* cover1;
		static inline Sprite* cover2;*/
		static inline Sprite* howtoplay_overlay1;
		static inline Sprite* howtoplay_overlay2;
		static inline Sprite* howtoplay_overlay3;
		static inline Sprite* howtoplay_overlay4;

		static inline Sprite* settings_page;
		static inline Sprite* credits_page;

		static inline Sprite* win_overlay;
		static inline Sprite* menu;
		static inline Sprite* player_stuck;

		unsigned int rows, cols,
			tileWidth, tileHeight;
	};
}