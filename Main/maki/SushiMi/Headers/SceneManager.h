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
		nori,			//2 //the end of pushable ingredients
		tea,			//3
		soya,			//4
		wasabi,			//5
		boxcover,		//6
		//fishing tops must be rendered above Bami and above fishing ground, hence it is on the same level as ingredient
		Fishing_Top_0_0,	//7
		Fishing_Top_1_1,	//8
		Fishing_Top_1_2,	//9
		Fishing_Top_1_3,	//:
		Fishing_Top_1_4,	//;
		Fishing_Top_2_1,	//<
		Fishing_Top_2_2,	//=
		Fishing_Top_2_3,	//>
		Fishing_Top_2_4,	//?
		Fishing_Top_3_1,	//@
		Fishing_Top_3_2,	//A
		Fishing_Top_3_3,	//B
		Fishing_Top_3_4,	//C
		Fishing_Top_3_5,	//D
		Fishing_Top_3_6,	//E
		
		
	};

	enum class wall_type //: std::uint16_t
	{
		sinkhole = 55,  //7
		filledsinkhole,	//8
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
		Wall5,				//Q = M
		Wall6,				//V = N
		Wall7,				//[ = O
		Wall8,				//` = P
		Wall9,				//a = Q
		WaterWall,			//i = R
		Wall0_Gunkan,		//j = S
		last,				//k = T
		Gunkan_Ground_1_1,	//l = U
		Gunkan_Ground_1_2,		//m = V
		Gunkan_Ground_1_3,		//n = W
		Gunkan_Ground_1_4,		//o = X
		Gunkan_Ground_2_1,		//p = Y
		Gunkan_Ground_2_2,				//q = Z
		rice_box,			//r = [
		inari_box,			//s = backslash (\)
		avocado_box,		//t = ]
		corn_box,			//u = ^
		cucumber_box,		//v = _
		salmon_box,			//w = `
		nori_box,			//x = a
		octopus_box,		//y = b
		roes_box,			//z = c
		tamago_box,			//{ = d
		tofu_box,			//| (bitwise OR) = e
		tuna_box,			//} = f
		WoodenPlatform,		//~ = g
		ground1,			//# = j
		ground2,			//$ = k
		Gunkan_Ground_2_3,	//l
		Gunkan_Ground_3_1,	//m 
		Gunkan_Ground_3_2,	//n
		Gunkan_Ground_3_3,	//o
		Gunkan_Ground_6_1,	//p
		Gunkan_Ground_6_2,	//q
		Gunkan_Ground_6_3,	//r
		Gunkan_Ground_6_4,	//s
		Wall6_1,			//W to replace as it is repetitive
		Wall6_2,			//X to replace as it is repetitive
		Wall6_3,			//Y to replace as it is repetitive
		Wall6_4,			//Z to replace as it is repetitive
		Wall7_1,			//backslash (\) to replace as it is repetitive
		Wall7_2,			//] to replace as it is repetitive
		Wall7_3,			//^ to replace as it is repetitive
		Wall7_4,			//_ to replace as it is repetitive
		Wall9_1,			//b to replace as it is repetitive
		Wall9_2,			//c to replace as it is repetitive
		Wall9_3,			//d to replace as it is repetitive
		Wall9_4,			//e to replace as it is repetitive
		Wall9_5,			//f (to replace as it is repetitive)
		Wall9_6,			//g  (to replace as it is repetitive)
		Wall9_7,			//h (to replace as it is repetitive)
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
		int IC;
		grid_number nametag;
		glm::vec2 init_Pos;
		std::pair<int, int> init_Grid_Pos;
		Sprite* spr;
		void Restart()
		{
			spr->transformation.Position = init_Pos;
			spr->transformation.grid_pos = init_Grid_Pos;
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
		static void loadTile(int x, int y, const std::pair<wall_type, Sprite*> &tile);
		static void loadIngr(int x, int y, int posX, int posY, const std::pair<grid_number, Sprite*> &ingredient);
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
		static bool activateSoya(Sprite* soya);
		static bool activateWasabi(Sprite* wasabi);
		static bool activateTea(Sprite* tea);
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
		static inline std::unordered_map<grid_number, int> counter;
		static inline std::vector<std::pair<animated, Sprite*>> animatedcontainer;
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

		static inline unsigned int rows, cols,
			tileWidth, tileHeight;

		
		// Black overlay alpha parameters
		inline static float targetAlpha = 0.0f;
		inline static float currentAlpha = 0.0f;
	};
}
