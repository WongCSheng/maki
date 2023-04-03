/*
File:		SceneManager.h
@author		louishetong.wang@digipen.edu 40%
co-Author:  Aurelia (fei.x@digipen.edu) 20%
co-Author:  w.chongsheng@digipen.edu  40%

Description:
*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#pragma once
#include "../Engine/Components/Texture/Sprite.h"
#include "../Game Object/Player.h"
#include "../src/Window.h"

namespace Core
{
	//note: grid_number enums cannot overlap with animated enums
	enum class grid_number //Find a better way to identify all textures
	{
		start = 32,
		space = 33,		//!
		its_a_wall = 35,//#
		player = 37,	//%
		ingredients,	//&
		octopus,		//'
		roes,			//(
		tuna,			//)
		corn,			//*
		inari,			//+
		avocado,		//, (comma) 
		salmon,			//- (minus) //interact-able ends here
		cucumber,		//. (fullstop)
		tamago,			// slash (/)
		tofu,			//0
		rice,			//1
		nori,			//2 //the end of pushable ingredients //value in dec: 50
		tea,			//3
		soya,			//4
		wasabi,			//5
		boxcover,		//6		//54
		sinkhole,		//7
		filledsinkhole,	//8
	};

	enum class wall_type //: std::uint16_t
	{
		win = 59,			//;
		insidebox = 61,		//=
		no_longer_used = 63,//?
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
		Wall5,				//M
		Wall6,				//N
		Wall7,				//O
		Wall8,				//P
		Wall9,				//Q
		WaterWall,			//R
		Wall0_Gunkan,		//S
		last,				//T
		Gunkan_Ground_1_1,	//U
		Gunkan_Ground_1_2,	//V
		Gunkan_Ground_1_3,	//W
		Gunkan_Ground_1_4,	//X
		Gunkan_Ground_2_1,	//Y
		Gunkan_Ground_2_2,	//Z
		rice_box,			//[
		inari_box,			//backslash (\)
		avocado_box,		//]
		corn_box,			//^
		cucumber_box,		//_
		salmon_box,			//`
		nori_box,			//a //97
		octopus_box,		//b
		roes_box,			//c
		tamago_box,			//d
		tofu_box,			//e
		tuna_box,			//f
		WoodenPlatform,		//g
		ground1,			//h
		ground2,			//i
		Gunkan_Ground_2_3,	//j
		Gunkan_Ground_3_1,	//k 
		Gunkan_Ground_3_2,	//l
		Gunkan_Ground_3_3,	//m
		Gunkan_Ground_6_1,	//n
		Gunkan_Ground_6_2,	//o
		Gunkan_Ground_6_3,	//p
		Gunkan_Ground_6_4,	//q
		/*static tops*/
		Ground_Top_1,		//r
		Ground_Top_2,		//s
		Ground_Top_3,		//t
		Ground_Top_4,		//u
		Ground_Top_5,		//v
		Ground_Top_6,		//w
		Ground_Top_7,		//x
		Ground_Top_8,		//y
		Ground_Top_9,		//z
		Ground_Top_10,		//{
		Ground_Top_11,		//|
		Ground_Top_12,		//}
		Ground_Top_13,		//~
		Ground_Top_14,		//€
		Ground_Top_15,		//ü
	};

	enum class animated
	{
		RicePlant1 = 57,	//9 (should start from 7 since 5 is the last grid_number enum
		RicePlant2,			//: and we are reading both animations and ingredients on the 1st layer
		RicePlant3,			//;
		RicePlant4,			//<
		RicePlant5,			//=
		RiceWater1,			//>
		RiceWater2,			//?
		GunkanSign_Right,	//@
		GunkanSign_Left,	//A
		GunkanCorn,			//B
		GunkanCarrot,		//C
		GunkanCrow_Left,	//D
		GunkanCrow_Right,	//E
		FishingBoat,		//F
		FishingLog,			//G
		FishingSotong,		//H
		FishingNoot,		//I
		FishingCrab,		//J
		//fishing tops must be rendered above Bami and above fishing ground, hence it is on the same level as ingredient
		RicePlain_TopG2_1,  //K
		Fishing_Top_0_0,	//L
		Fishing_Top_1_1,	//M
		Fishing_Top_1_2,	//N
		Fishing_Top_1_3,	//O
		Fishing_Top_1_4,	//P
		Fishing_Top_2_1,	//Q
		Fishing_Top_2_2,	//R
		Fishing_Top_2_3,	//S
		Fishing_Top_2_4,	//T
		Fishing_Top_3_1,	//U
		Fishing_Top_3_2,	//V
		Fishing_Top_3_3,	//W
		Fishing_Top_3_4,	//X
		Fishing_LifeBuoy_Red,	//Y
		Fishing_LifeBuoy_Blue,	//Z
		Fishing_LifeBuoy_Green,	 //[
		Fishing_LifeBuoy_Orange,	//backslash (\)
		Fishing_Wood_1,				//]
		Fishing_Wood_2,				//^
		Fishing_Wood_3,				//_
		City_Crossing1,				//`
		City_Crossing2, 			//a
		City_Crossing3, 			//b
		City_Drain_Down,			//c
		City_Drain_Left,			//d
		City_Drain_Right,			//e
		City_Drain_Up,				//f
		City_Litter_1,				//g
		City_Litter_2,				//h
		City_Litter_3,				//i
		City_Litter_4,				//j
		City_Litter_5,				//k
		City_Litter_6,				//l
		City_Sewer,					//m
		City_SlowDownSign,			//n
									//o
									//p
									//q


	};							 
								 
	struct Basket				 
	{							 
		int IC;					 
		grid_number nametag;
		Transform init_value;
		std::pair<int, int> init_Grid_Pos;
		Sprite* spr;
		void Restart()
		{
			spr->transformation = init_value;
		}
	};
	
	class SceneManager : public SystemFrame
	{
	public:
		SceneManager();
		~SceneManager();

		void Init();
		void Update(const double );
		void RegisterGameObjects(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		static std::vector<std::pair<wall_type, Sprite*>> RetreiveTile() { return tilecontainer; };
		static std::vector<Basket> RetreiveIngredient() { return ingredientcontainer;};
		static void restartLevel();
		static void nextLevel();

		/*HARD CODE FOR NOW, WILL MAKE IT COMPONENT BASED*/
		static void loadTopAnimation(int x, int y, const std::pair<animated, Sprite*>& tile);
		static void loadTile(int x, int y, const std::pair<wall_type, Sprite*> &tile);
		static void loadIngr(int x, int y, int posX, int posY, const std::pair<grid_number, Sprite*> &ingredient);
		static void loadPlayer_Stuck(int x, int y);
		//static void loadHowToOverlay(int x, int y);
		static void loadSettings();
		static void loadWinOverlay(int x, int y);
		static void loadCutscene();
		static void loadLevelSelect(int x, int y);
		static void load_Dialogue(); //loads all region dialogue background
		static void load_Wood_BG(); //for fishing village
		static void load_City_BG(); //for maki city
		static void load_Bami_End_Room(); //Ending Cutscene
		static void load_Are_You_Sure(); //confirmation screen
		static void load_Particle(); //particle pos

		static void drawTut1();
		static void drawTut2();
		static void resetColor();

		static void drawTile();
		static void drawBox();
		static void drawTop();
		static void drawIngr();
		static bool activateSoya(Sprite* soya);
		static bool activateWasabi(Sprite* wasabi);
		static bool activateTea(Sprite* tea);
		static void drawInsideSinkHole();
		static void drawSinkHole();
		static void drawPlayer_Stuck();
		static void drawHowToOverlay(int page);
		static void drawSettings();
		static void drawWinOverlay();
		static void drawCutscene(int CutscenePage);
		static void drawLevelSelect();
		static void drawBlackOverlay();
		static void draw_Dialogue();
		static void draw_Wood_BG();
		static void draw_City_BG();	
		static void draw_Bami_End_Room();
		static void draw_Are_You_Sure();
		static void draw_Particle();

		static void drawEncourage();
		static void drawIngrStuck();
		static void drawGiveUp();

		static void loadRect(int x, int y);
		static void drawRect(float alpha);
		static void loadFader(int x, int y);
		static void drawFader(float alpha);
		static void FadeIn();
		static void FadeOut();
		static void set_target_pos(Sprite* boxcover);
		static void set_curr_pos(Sprite* boxcover);

		static void destroyTile();
		static void destroyIngr();
		static void destroyInsideSinkHole();
		static void destroyTop();
		static void destroyPlayer_Stuck();
		static void destroyHowToOverlay();
		static void destroySettings();
		static void destroyWinOverlay();
		static void destroyCutscene();
		static void destroyLevelSelect();
		static void destroy_Dialogue();
		static void destroy_Wood_BG();
		static void destroy_City_BG();
		static void destroy_Bami_End_Room();
		static void destroy_Are_You_Sure();
		static void destroy_Particle();
		static void destroy_fading();

	
		static void Readfile();

		static void setRowsandCols(unsigned int inRow, unsigned int inCol);
		static void setTileDimension(unsigned int Width, unsigned int Height);

		unsigned int getRows();
		unsigned int getCols();
		static inline unsigned int getTileWidth()
		{
			return tileWidth;
		}
		static inline unsigned int getTileHeight()
		{
			return tileHeight;
		}

		static inline std::vector< std::pair<wall_type, Sprite*>> boxcontainer;
		static inline std::vector<std::pair<animated, Sprite*>> topcontainer;
		static inline std::vector<std::pair<wall_type, Sprite*>> tilecontainer;
		static inline std::vector<Basket> ingredientcontainer;
		static inline std::unordered_map<grid_number, int> counter;
		static inline std::vector<std::pair<animated, Sprite*>> animatedcontainer;
		static inline std::vector<Basket> in_sinkhole;
		static inline std::vector<short> ICnum;
		static inline std::vector<std::pair<int, int>> win_condition;
		static unsigned int amt_of_win_conditions;

		//dialogue
		static inline Sprite* riceplain_dialogue, * gunkan_dialogue, * fishingvillage_dialogue, * makicity_dialogue;
		static inline int num_dialogue_clicks;

		static inline Sprite* wooden_bg, *city_bg;

		static inline Sprite* howtoplay_overlay1;
		static inline Sprite* howtoplay_overlay2;
		static inline Sprite* howtoplay_overlay3;
		static inline Sprite* howtoplay_overlay4;
		static inline Sprite* howtoplay_overlay5;
		static inline Sprite* howtoplay_overlay6;

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
		static inline Sprite* fader;

		static inline Sprite* Ending_Cutscene;
		static inline Sprite* are_you_sure;
		static inline Sprite* particle;

		static inline enum class particlePos
		{
			isRightofPlayer = 0,
			isLeftofPlayer, //1
			isAbovePlayer, //2
			isBelowPlayer //3

		}particleDisplay;

		static inline unsigned int rows, cols,
			tileWidth, tileHeight;

		
		// Black overlay alpha parameters
		inline static float targetAlpha = 0.0f;
		inline static float currentAlpha = 0.0f;

		// Font alpha parameters
		inline static float FtargetAlpha = 0.0f;
		inline static float FcurrentAlpha = 1.0f;

		// Font alpha parameters
		inline static float StargetAlpha = 0.0f;
		inline static float ScurrentAlpha = 1.0f;

		inline static float timer = 0.0f;
		// Boxcover targetpos and currpos
		inline static float currpos;
		inline static float targetpos;

		inline static int spacepressed;
		inline static bool up_key;
		inline static bool down_key;
		inline static bool left_key;
		inline static bool right_key;
		inline static bool r_key;
		
	};
}
