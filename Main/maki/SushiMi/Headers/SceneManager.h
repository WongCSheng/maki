#pragma once
#include "../Engine/Components/Texture/Sprite.h"
#include "../Game Object/Player.h"
#include "../src/Window.h"

namespace Core
{
	enum class grid_number //Find a better way to identify all textures
	{
		start = 32,
		space = 33,		//!
		ground0,		//"
		ground1,		//#
		ground2,		//$
		player,			//%
		ingredients,	//&
		avocado,		//'
		cucumber,		//(
		corn,			//)
		inari,			//*
		octopus,		//+
		rice,			//, (comma)
		roes,			//- (minus)
		salmon,			//. (fullstop)
		tamago,			// slash (/)
		tofu,			//0
		tuna,			//1
		nori,			//2
		items,			//3
		soya,			//4
		wasabi,			//5
		boxcover,		//6
		end
		
	};

	enum class wall_type //: std::uint16_t
	{
		sinkhole = 55,  //7
		filledsinkhole,	//8
		empty,			//9
		empty2,			//:
		win,			//;
		temp,			//<
		insidebox,		//=
		inbox2,			//>
		sinkhole_gunkan,//?
		first = 64,
		Wall0,				//A
		Wall0_1,			//B
		Wall1,				//C
		Wall2,				//D
		Wall2_1,			//E
		Wall2_2,			//F
		Wall2_3,			//G
		Wall3,				//H
		Wall3_1,			//I
		Wall3_2,			//J
		Wall3_3,			//K
		Wall4,				//L
		Wall4_1,			//M
		Wall4_2,			//N
		Wall4_3,			//O
		Wall4_4,			//P
		Wall5,				//Q
		Wall5_1,			//R
		Wall5_2,			//S
		Wall5_3,			//T
		Wall5_4,			//U
		Wall6,				//V
		Wall6_1,			//W
		Wall6_2,			//X
		Wall6_3,			//Y
		Wall6_4,			//Z
		Wall7,				//[
		Wall7_1,			//backslash (\)
		Wall7_2,			//]
		Wall7_3,			//^
		Wall7_4,			//_
		Wall8,				//`
		Wall9,				//a
		Wall9_1,			//b
		Wall9_2,			//c
		Wall9_3,			//d
		Wall9_4,			//e
		Wall9_5,			//f
		Wall9_6,			//g
		Wall9_7,			//h
		WaterWall,			//i
		Wall0_Gunkan,		//j
		Wall1_Gunkan,		//k
		Wall1_1_Gunkan,		//l
		Wall2_Gunkan,		//m
		Wall2_1_Gunkan,		//n
		Wall3_Gunkan,		//o
		Wall3_1_Gunkan,		//p
		last,				//q
		rice_box,			//r
		inari_box,			//s
		avocado_box,		//t
		corn_box,			//u
		cucumber_box,		//v
		salmon_box,			//w total 12 boxes
		nori_box,			//x
		octopus_box,		//y
		roes_box,			//z
		tamago_box,			//{
		tofu_box,			//| (bitwise OR)
		tuna_box,			//}
		//Water,		//� or ~
		WoodenPlatform,		//~
		Player_OnWood		//�

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
		static void loadLevelSelect(int x, int y);
		static void load_Dialogue(); //RP stands for Rice Plain
		static void load_Wood_BG(); //for fishing village

		static void drawTile();
		static void drawBox();
		static void drawIngr();
		static void drawPlayer_Stuck();
		static void drawHowToOverlay();
		static void drawSettings();
		static void drawWinOverlay();
		static void drawCutscene();
		static void drawLevelSelect();
		static void drawBlackOverlay();
		static void draw_Dialogue();
		static void draw_Wood_BG();

		static void loadRect(int x, int y);
		static void drawRect(float alpha);
		static void FadeIn();
		static void FadeOut();


		static void destroyTile();
		static void destroyIngr();
		static void destroyPlayer_Stuck();
		static void destroyHowToOverlay();
		static void destroySettings();
		static void destroyWinOverlay();
		static void destroyCutscene();
		static void destroyLevelSelect();
		static void destroy_Dialogue();
		static void destroy_Wood_BG();

	
		static void Readfile();

		static void setRowsandCols(unsigned int inRow, unsigned int inCol);
		static void setTileDimension(unsigned int Width, unsigned int Height);

		unsigned int getRows();
		unsigned int getCols();
		static inline unsigned int getTileWidth();
		static inline unsigned int getTileHeight();

	
		static inline std::vector<std::pair<wall_type, Sprite*>> tilecontainer;
		static inline std::vector<std::pair<grid_number, Sprite*>> ingredientcontainer;
		static inline std::vector<short> ICnum;
		static inline std::unordered_multimap<grid_number, Sprite*> ingredient_starting_pos;
		static inline std::vector<std::pair<int, int>> win_condition;
		static unsigned int amt_of_win_conditions;

		//dialogue
		static inline Sprite* riceplain_dialogue, * gunkan_dialogue, * fishingvillage_dialogue;
		static inline int num_dialogue_clicks;

		static inline Sprite* wooden_bg;

		static inline Sprite* howtoplay_overlay1;
		static inline Sprite* howtoplay_overlay2;
		static inline Sprite* howtoplay_overlay3;
		static inline Sprite* howtoplay_overlay4;
		static inline Sprite* howtoplay_overlay5;

		static inline Sprite* frame1;
		static inline Sprite* frame2;
		static inline Sprite* frame3;
		static inline Sprite* frame4;
		static inline Sprite* frame5;
		static inline Sprite* frame6;
		static inline Sprite* frame7;
		static inline Sprite* frame8;

		static inline Sprite* level_select;

		static inline Sprite* settings_page;
		static inline Sprite* credits_page;

		static inline Sprite* win_overlay;
		static inline Sprite* menu;
		static inline Sprite* player_stuck;

		static inline Sprite* rec;

		static inline unsigned int rows, cols,
			tileWidth, tileHeight;

		double inline static starttime,endtime,delta;
		
		// Black overlay alpha parameters
		inline static float targetAlpha = 0.0f;
		inline static float currentAlpha = 0.0f;
	};
}