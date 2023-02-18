#pragma once
#include "../Engine/Components/Texture/Sprite.h"
#include "../Game Object/Player.h"
#include "../../Window/Window.h"

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
		temp1,			//q
		temp,			//r
		inbox1,			//s
		inbox2,			//t
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
		topbottom,					//M
		bottomwall,					//N
		middletopbottomwall,		//O
		middlewall,					//P
		last
	};

	enum class Collsion_Code
	{
		Space = 0,
		Collide = 1,
		Others = 2
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
		static void loadPlayer_Stuck(int x, int y);
		static void loadHowToOverlay(int x, int y);
		static void loadSettings();
		static void loadWinOverlay(int x, int y);
		static void loadCutscene(int x, int y);

		static void drawTile();
		static void drawIngr();
		static void drawPlayer_Stuck();
		static void drawHowToOverlay();
		static void drawSettings();
		static void drawWinOverlay();
		static void drawCutscene();


		static void destroyTile();
		static void destroyIngr();
		static void destroyPlayer_Stuck();
		static void destroyHowToOverlay();
		static void destroySettings();
		static void destroyWinOverlay();
		static void destroyCutscene();

		static void Readfile();

		static void setRowsandCols(unsigned int inRow, unsigned int inCol);
		static void setTileDimension(unsigned int Width, unsigned int Height);

		unsigned int getRows();
		unsigned int getCols();
		unsigned int getTileWidth();
		unsigned int getTileHeight();

		std::vector<wall_type, Sprite*> tilecontainer;
		std::vector<grid_number, Sprite*> ingredientcontainer;
		std::vector<grid_number, Sprite*> ingredient_starting_pos;
	
		static inline std::vector<std::pair<wall_type, Sprite*>> tilecontainer;
		static inline std::vector<std::pair<grid_number, Sprite*>> ingredientcontainer;
		static inline std::vector<short> ICnum;
		static inline std::unordered_multimap<grid_number, Sprite*> ingredient_starting_pos;
		static inline std::vector<std::pair<int, int>> win_condition;
		static unsigned int amt_of_win_conditions;
		static inline Sprite* howtoplay_overlay1;
		static inline Sprite* howtoplay_overlay2;
		static inline Sprite* howtoplay_overlay3;
		static inline Sprite* howtoplay_overlay4;

		static inline Sprite* frame1;
		static inline Sprite* frame2;
		static inline Sprite* frame3;
		static inline Sprite* frame4;
		static inline Sprite* frame5;
		static inline Sprite* frame6;
		static inline Sprite* frame7;
		static inline Sprite* frame8;


		static inline Sprite* settings_page;
		static inline Sprite* credits_page;

		static inline Sprite* win_overlay;
		static inline Sprite* menu;
		static inline Sprite* player_stuck;

		unsigned int rows, cols,
			tileWidth, tileHeight;
	};
}