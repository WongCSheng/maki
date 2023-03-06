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
		its_a_wall = 35,//#
		player = 37,	//%
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
		tea,			//3
		soya,			//4
		wasabi,			//5
		boxcover,		//6
		end
		
	};

	enum class wall_type //: std::uint16_t
	{
		sinkhole = 55,  //7
		filledsinkhole,	//8
		win,			//;
		insidebox,		//=
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
		Wall4_1,			//M to replace as it is repetitive
		Wall4_2,			//N to replace as it is repetitive
		Wall4_3,			//O to replace as it is repetitive
		Wall4_4,			//P to replace as it is repetitive
		Wall5,				//Q
		Wall5_1,			//R to replace as it is repetitive
		Wall5_2,			//S to replace as it is repetitive
		Wall5_3,			//T to replace as it is repetitive
		Wall5_4,			//U to replace as it is repetitive
		Wall6,				//V
		Wall6_1,			//W to replace as it is repetitive
		Wall6_2,			//X to replace as it is repetitive
		Wall6_3,			//Y to replace as it is repetitive
		Wall6_4,			//Z to replace as it is repetitive
		Wall7,				//[
		Wall7_1,			//backslash (\) to replace as it is repetitive
		Wall7_2,			//] to replace as it is repetitive
		Wall7_3,			//^ to replace as it is repetitive
		Wall7_4,			//_ to replace as it is repetitive
		Wall8,				//`
		Wall9,				//a
		Wall9_1,			//b to replace as it is repetitive
		Wall9_2,			//c to replace as it is repetitive
		Wall9_3,			//d to replace as it is repetitive
		Wall9_4,			//e to replace as it is repetitive
		Wall9_5,			//f (to replace as it is repetitive)
		Wall9_6,			//g  (to replace as it is repetitive)
		Wall9_7,			//h (to replace as it is repetitive)
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
		WoodenPlatform,		//~
		Player_OnWood,		//�
		ground0,			//"
		ground1,			//#
		ground2				//$
	};

	enum class animated
	{
		RicePlant1 = 45,	//0
		RicePlant2,
		RicePlant3,
		RicePlant4,
		RicePlant5,
		RiceWater1,
		RiceWater2,
		GunkanSign_Right,
		GunkanSign_Left,
		GunkanCorn,
		GunkanCarrot = 65, //A
		GunkanCrow_Left,   //B
		GunkanCrow_Right,  //C
		FishingBoat,	   //D
		FishingLog,		   //E
		FishingSotong,
		FishingNoot,
		FishingCrab
	};

	struct Basket
	{
		glm::vec2 init_Pos;
		std::pair<int, int> init_Grid_Pos;
		std::pair<grid_number, Sprite*> spr;
		void Restart()
		{
			spr.second->transformation.Position = init_Pos;
			spr.second->transformation.grid_pos = init_Grid_Pos;
		}
	};
	
	class SceneManager : public SystemFrame
	{
	public:
		SceneManager();
		~SceneManager();

		void Init();
		void Update(const double );
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		static std::vector<std::pair<wall_type, Sprite*>> RetreiveTile() { return tilecontainer; };
		static std::vector<Basket> RetreiveIngredient() { return ingredientcontainer;};
		static void restartLevel();
		static void nextLevel();

		/*HARD CODE FOR NOW, WILL MAKE IT COMPONENT BASED*/
		static void loadTile(int x, int y, const std::pair<wall_type, Sprite*> &tile);
		static void loadIngr(int x, int y, int posX, int posY, const std::pair<grid_number, Sprite*> &ingredient);
		//static void loadAnim(const std::pair<animated, Sprite*>& animate);
		//static void loadRice(int x, int y, int posX, int posY, const std::pair<Rice, Sprite*>& ingredient);
		static void loadPlayer_Stuck(int x, int y);
		static void loadHowToOverlay(int x, int y);
		static void loadSettings();
		static void loadWinOverlay(int x, int y);
		static void loadCutscene();
		static void loadLevelSelect(int x, int y);
		static void load_Dialogue(); //RP stands for Rice Plain
		static void load_Wood_BG(); //for fishing village

		static void drawTile();
		static void drawBox();
		static void drawIngr();
		//static void drawRice();
		static bool activateSoya();
		static bool activateWasabi();
		static bool activateTea();
		static void drawInsideSinkHole();
		static void drawPlayer_Stuck();
		static void drawHowToOverlay(int page);
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
		static void destroyInsideSinkHole();
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
		static inline std::vector<Basket> ingredientcontainer;
		static inline std::vector<std::pair<animated, Sprite*>> animatedcontainer;
		//static inline std::vector<std::pair<Rice, Sprite*>> ricecontainer;
		static inline std::vector<Basket> in_sinkhole;
		static inline std::vector<short> ICnum;
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

		
		// Black overlay alpha parameters
		inline static float targetAlpha = 0.0f;
		inline static float currentAlpha = 0.0f;
	};
}
