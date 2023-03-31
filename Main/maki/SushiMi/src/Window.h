#pragma once
/*
File: Window.cpp
@author		louishetong.wang@digipen.edu 20%
co-Author:  thea.sea@digipen.edu 30%
co-Author:  Aurelia (fei.x@digipen.edu) 30%
co-Author:  w.chongsheng@digipen.edu  20%

Description:
*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "../Engine/System/SystemFrame.h"
#include "../Headers/Math_Header.h"


namespace Core
{
	/*forward declaration*/
	class Player;
	class Sprite;
	//extern Player* player;
	class ObjectFactory;

	class Window : public SystemFrame
	{
	public:
		Window(int width, int height);
		~Window();

		static Window* GetInstance(int width, int height)
		{
			static Window instance(width,height);
			return &instance;
		}


		float getDelta()
		{
			return static_cast<float>(delta);
		}

		void Init() {}
		void Update(const double) {}
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer) {}

		void Input();

		void Resize();

		void Mainloop();

		/*                                                             input key states
		----------------------------------------------------------------------------- */
		static inline bool keystate_left;
		static inline bool keystate_right;
		static inline bool keystate_up;
		static inline bool keystate_down;
		static inline bool keystate_R;
		static inline bool keystate_M;
		static inline bool keystate_tab;
		static inline bool keystate_space;
		static inline bool keystate_1;
		static inline bool keystate_2;
		static inline bool keystate_3;
		static inline bool keystate_4;
		static inline bool keystate_5;
		static inline bool keystate_6;
		static inline bool keystate_7;
		static inline bool keystate_8;
		static inline bool keystate_9;
		static inline bool keystate_0;
		static inline bool keystate_minus;
		static inline bool keystate_equal;
		static inline bool keystate_Y;
		static inline bool keystate_N;
		static inline bool keystate_J;
		static inline bool keystate_K;
		static inline bool keystate_L;
		static inline bool keystate_P;
		static inline bool keystate_T;
		static inline bool keystate_escape;
		static inline bool place_obj;
		static inline bool keystate_W;
		static inline bool keystate_A;
		static inline bool keystate_S;
		static inline bool keystate_D;
		static inline bool keystate_fps;
		static inline bool mouseLeft;
		static inline size_t curr_len = 0;
		static inline std::string realstring = "";

		static inline bool gameIsPaused;
		static inline bool areyousure_prompt;
		static inline bool isMenuState;
		
		bool isLevelSelection;
		bool isWalk;
		static inline bool loaded;
		static inline bool isPlayerinSinkhole;
		static inline bool isEndingloaded;

		static inline bool isTut1, isTut2, isLevel1, isLevel2, isLevel3, //Rice Plain Village
		isLevel4, isLevel5, isLevel6, //gunkan village
		isLevel7, isLevel8, isLevel9, isLevel10, //fishing village
		isLevel11, //maki city
		isTestLevel;


		bool isEndingCutscene;
		static inline bool finallevelclear;

		static inline bool isDialogue;
		static inline int dialogue_style;
		static inline bool show_fps;
		enum class dialogue
		{
			T1 = 0,
			T2,	//1
			L1,	//2
			L2,	//3
			L3,	//4
			L4,	//5
			L5, //6
			L6,	//7
			L7,	//8
			L8,	//9
			L9,	//10
			MAKI_CITY
		};

		static inline bool isQuestTab;
		static inline bool isWinCondition; //dont use this, Map.cpp has Map:isWin() that returns true or false
		static inline int questProgress;
		static inline int numQuests;

		enum class GameState {
			TUT1 = 0,
			TUT2,
			LEVEL1,
			LEVEL2,
			LEVEL3,
			LEVEL4,
			LEVEL5,
			LEVEL6,
			LEVEL7,
			LEVEL8,
			LEVEL9,
			LEVEL10,
			LEVEL11, //maki city
			MENU
		};
		static GameState level;

		bool isCutscene;
		static inline int CutscenePage;

		static inline bool isHowToPlay;
		static inline int HowToPlayPage;

		bool isSettings;
		static inline bool isCredits;

		static inline bool timetodeletegrid;

		void SetPaused(bool paused) //take in boolean
		{
			gameIsPaused = paused;

		}

		bool GetPaused(void)//check if game is paused
		{
			return gameIsPaused;
		}

		/*
		 * Checks for win conditions in the level
		 */
		void checkWin(std::string level);

		/*
		 *	checks for the ingredient pushed into the right box
		 */
		int checkCombination(std::string ingredient, std::string box, std::vector<std::string> container);

		/*
		 *	 Helper function to convert game states to string for parsing
		 */
		std::string EnumToString(GameState);

		/*
		 *  update ingredients' position to draw on quest tab at fixed position
		 */
		void updateChop(int position, gfxVector2 pos);

		/*	resets quest tab	*/
		static void resetQuest();

		// set all other states false
		void setAllStatesFalse()
		{
			isDialogue = false;
			isEndingCutscene = false;
			isCutscene = false;
			isMenuState = false;
			isQuestTab = false;
			isHowToPlay = false;
			isLevelSelection = false;
			gameIsPaused = false;
			keystate_M = false;
			isTut1 = false;
			isTut2 = false;
			isLevel1 = false;
			isLevel2 = false;
			isLevel3 = false;
			isLevel4 = false;
			isLevel5 = false;
			isLevel6 = false;
			isLevel7 = false;
			isLevel8 = false;
			isLevel9 = false;
			isLevel10 = false;
			isLevel11 = false;
			isTestLevel = false;
			areyousure_prompt = false;
			loaded = false;
			keystate_M = false; 
		}

		static std::vector<std::string> currentQuestIngredient;
		static std::array<std::pair<std::string, int>, 5> winningBoxes;
		static std::map<std::string, gfxVector2> questDrawItems;

		//for editor
#ifdef EDITOR
		static inline Sprite* ingredient; //for imguiObjectCursor


#endif

		//static inline void ImGuiToObjContainer(ObjectFactory*);

		static inline Player* player;
		static inline GLFWwindow* window_ptr; //moved from private to public for access in main.cpp
		/*static inline Sprite* obj;
		static inline Sprite* sp;*/
		/*static inline Sprite* ingredient1;
		static inline Sprite* ingredient2;
		static inline Sprite* goal1;
		static inline Sprite* goal2;
		static inline Sprite* trap;*/
		static inline Sprite* pause_overlay;
		//void ImGuiToObjContainer(ObjectFactory* c);
	
		static inline const char* levelprogress;

		struct ScreenDimensions {
			static inline int screenwidth;
			static inline int screenheight;
		};

	private:
		int m_width, m_height;
		double starttime, endtime, delta, fps;
	};

	class pseudomain
	{
	public:
		static void draw();
		static void update();
		static void init();
		static void cleanup();
	};
#define Get_Delta()				Window::GetInstance(0, 0)->getDelta()
}
