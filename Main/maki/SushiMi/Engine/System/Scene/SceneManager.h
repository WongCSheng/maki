#pragma once
#include "../Engine/Components/Texture/Sprite.h"
#include "../Game Object/Player.h"
#include "../../Window/Window.h"

namespace Core
{
	enum class ingredients //gGrids
	{
		start = 96,
		ground1,		//a
		ground2,		//b
		ground3,		//c
		player,			//d
		ingredients,
		avocado,		//f
		corn,			//g
		cucumber,		//h
		inari,			//i
		nori,			//j
		octopus,		//k
		rice,			//l
		roes,			//m
		salmon,			//n
		tamago,			//o
		tofu,			//p
		tuna,			//q
		soyasauce,		//r
		wasabi,			//s
		items,
		sinkhole,		//u
		filledsinkhole,	//v
		boxcover,		//w
		end
	};

	enum class pods	//pGrids
	{
		avocado_pod = 102,  //f
		corn_pod = 103,		//g
		cucumber_pod,		//h
		inari_pod,			//i
		nori_pod,			//j
		octopus_pod,		//k
		rice_pod,			//l
		roes_pod,			//m
		salmon_pod,			//n
		tamago_pod,			//o
		tofu_pod,			//p
		tuna_pod			//q
	};

	enum class wall_type //: std::uint16_t //gGrids
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

	enum class Collsion_Code //cGrids
	{
		Space = 0,
		Collide = 1,
		Others = 2
	};

	enum class RicePlain_Grass //rGrids
	{
		TopG1_1 = 97,	//a
		TopG1_2 = 98,	//b
		TopG1_3,		//c
		TopG2_1,		//d
		TopG2_2,		//e
		TopG2_3,		//f
		TopG2_4,		//g
		TopG3_1,		//h
		TopG3_2,		//i
		TopG3_3,		//j
		TopG3_4,		//k
		TopW0_1,		//l
		TopW0_2,		//m
		TopW0_3,		//n
		TopW0_4,		//o
		TopW0_5,		//p
		TopW0_6			//q
	};

	struct Basket
	{
		int sub;
		Transform starting_pos;
		Transform current_pos;
		Sprite* ingr;
	};
	
	class SceneManager : public SystemFrame
	{
	public:
		SceneManager();
		~SceneManager();

		static SceneManager* GetInstance()
		{
			static SceneManager scnManager;
			return &scnManager;
		}

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		static void restartLevel();
		static void nextLevel();
		/*HARD CODE FOR NOW, WILL MAKE IT COMPONENT BASED*/
		//static void loadTileTex(int x, int y, wall_type type, Texture tex);
		static void StoreTileCoor(int x, int y, std::pair<wall_type, Sprite*> tile, int counter);
		//static void loadIngrTex(int x, int y, int posX, int posY, const std::pair<ingredients, Sprite*> &ingredient, int counter);
		static void StoreIngrCoor(int x, int y, int posX, int posY, std::pair<ingredients, Sprite*> ingredient, int counter);
		static void StoreIngr_initPos(int x, int y, int posX, int posY, ingredients ingrposition, int counter);
		static void loadHowToOverlay(int x, int y);
		static void loadSettings();
		static void loadWinOverlay(int x, int y);
		static void loadCutscene(int x, int y);

		static void drawTile();
		static void drawIngr();
		static void drawHowToOverlay();
		static void drawSettings();
		static void drawWinOverlay();
		static void drawCutscene();


		static void destroyTile();
		static void destroyIngr();
		static void destroyHowToOverlay();
		static void destroySettings();
		static void destroyWinOverlay();
		static void destroyCutscene();

		static void Readfile(std::string filename);

		static void setRowsandCols(unsigned int inRow, unsigned int inCol);
		static void setTileDimension(unsigned int Width, unsigned int Height);

		unsigned int getRows();
		unsigned int getCols();
		unsigned int getTileWidth();
		unsigned int getTileHeight();
	
		//Map stuff
		static inline std::vector<wall_type, Sprite*> tilecontainer;
		static inline std::vector<Basket> ingredientcontainer;
		static inline std::vector<std::pair<int, Transform>> ingredient_starting_pos;
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

		unsigned int rows, cols,
			tileWidth, tileHeight;
	};
}