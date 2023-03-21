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
#include "Window.h"
#include "../Engine/Input/Input.h"
#include "../../imgui/imgui.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Editors/imfilebrowser.h"
#include "../Headers/SceneManager.h"
#include "../Game Object/Player.h"
#include "../Game Object/GameObject.h"
#include "../Engine/Components/Texture/Sprite.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Camera/Camera2D.h"
#include "../Headers/SceneManager.h"
#include "../Engine/Audio/AudioEngine.h"
#include "../Engine/TileMap/Map.h"
#include "../Engine/Core/Core.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "Engine/Font/Font.h"
#include "../Level State/LevelsHeader.h"

namespace Core
{
	static Core::MainSystem* CoreSystem;
	//static int width, height;
	std::ifstream fin;						// retrieve the current level dialogue file
	std::vector<Basket> CurrentIngredients; // retreive the current level loaded ingredients
	std::vector<std::pair< grid_number, wall_type>> stack;
	static bool keystate_fps = false;
	//std::vector<std::pair<wall_type, Sprite*>> tilecontainer;
	//std::vector<std::pair<grid_number, Sprite*>> ingredientcontainer;

	static std::string walkingsfx;

	std::vector<std::string> Window::currentQuestIngredient;
	std::array<std::pair<std::string, int>, 3> Window::winningBoxes;
	Window::GameState Window::level;

	std::map<std::string, gfxVector2> Window::questDrawItems;
	/*																  game states
	----------------------------------------------------------------------------- */


	void mouseCallBack([[maybe_unused]] GLFWwindow* window_ptr, int button, int action, [[maybe_unused]] int mod)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			Window::mouseLeft = (button == GLFW_MOUSE_BUTTON_LEFT) ? true : false;
			break;
		}

		switch (action)
		{
		case GLFW_PRESS:
			Window::mouseLeft = (action == GLFW_PRESS) ? true : false;
			break;

		case GLFW_RELEASE:
			Window::mouseLeft = false;
			break;
		}
	}


	//SceneManager* scnmanager = new SceneManager(); //this is dangerous!! write it in a function so that the new is deleted!!

	/*					key  callback function  , helper function for controlling input
		----------------------------------------------------------------------------- */
	void keyCallBack([[maybe_unused]] GLFWwindow* window_ptr, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mod)
	{
		if (GLFW_REPEAT == action)
		{
			Window::keystate_left = (key == GLFW_KEY_LEFT) ? true : false;
			Window::keystate_tab = (key == GLFW_KEY_TAB) ? true : false;
			Window::keystate_right = (key == GLFW_KEY_RIGHT) ? true : false;
			Window::keystate_up = (key == GLFW_KEY_UP) ? true : false;
			Window::keystate_down = (key == GLFW_KEY_DOWN) ? true : false;
			Window::keystate_R = (key == GLFW_KEY_R) ? true : false;
			Window::keystate_M = (key == GLFW_KEY_M) ? true : false;
			Window::keystate_escape = (key == GLFW_KEY_ESCAPE) ? true : false;
		}
		else if (GLFW_RELEASE == action)
		{
			Window::keystate_left = false;
			Window::keystate_right = false;
			Window::keystate_up = false;
			Window::keystate_down = false;
			Window::keystate_R = false;
			Window::keystate_M = false;
			Window::keystate_escape = false;
			Window::keystate_tab = false;
			Window::keystate_space = false;
			Window::keystate_fps = false;
		}
		else if (GLFW_PRESS == action)
		{
			Window::keystate_M = (key == GLFW_KEY_M) ? true : false;
			Window::keystate_left = (key == GLFW_KEY_LEFT) ? true : false;
			Window::keystate_right = (key == GLFW_KEY_RIGHT) ? true : false;
			Window::keystate_up = (key == GLFW_KEY_UP) ? true : false;;
			Window::keystate_down = (key == GLFW_KEY_DOWN) ? true : false;
			Window::keystate_R = (key == GLFW_KEY_R) ? true : false;
			Window::keystate_T = (key == GLFW_KEY_T) ? true : false;
			Window::keystate_tab = (key == GLFW_KEY_TAB) ? true : false;
			Window::keystate_escape = (key == GLFW_KEY_ESCAPE) ? true : false;
			Window::keystate_space = (key == GLFW_KEY_SPACE) ? true : false;
			Window::keystate_fps = (key == GLFW_KEY_F) ? true : false;	//toggle on or off fps

			Window::keystate_Y = (key == GLFW_KEY_Y) ? true : false;	//yes
			Window::keystate_N = (key == GLFW_KEY_N) ? true : false;	//no

			Window::keystate_P = (key == GLFW_KEY_P) ? true : false;	//play ending cutscene
			Window::keystate_J = (key == GLFW_KEY_J) ? true : false;	//test level
			Window::keystate_K = (key == GLFW_KEY_K) ? true : false;	//tut1
			Window::keystate_L = (key == GLFW_KEY_L) ? true : false;	//tut2
			Window::keystate_1 = (key == GLFW_KEY_1) ? true : false;	//level1
			Window::keystate_2 = (key == GLFW_KEY_2) ? true : false;	//level2
			Window::keystate_3 = (key == GLFW_KEY_3) ? true : false;	//level3
			Window::keystate_4 = (key == GLFW_KEY_4) ? true : false;	//level4
			Window::keystate_5 = (key == GLFW_KEY_5) ? true : false;	//level5
			Window::keystate_6 = (key == GLFW_KEY_6) ? true : false;	//level6
			Window::keystate_7 = (key == GLFW_KEY_7) ? true : false;	//level7
			Window::keystate_8 = (key == GLFW_KEY_8) ? true : false;	//level8
			Window::keystate_9 = (key == GLFW_KEY_9) ? true : false;	//level9
			Window::keystate_0 = (key == GLFW_KEY_0) ? true : false;	//level10
			Window::keystate_minus = (key == GLFW_KEY_MINUS) ? true : false;	//level11 (maki city)

			Window::keystate_W = (key == GLFW_KEY_W) ? true : false;	//up
			Window::keystate_A = (key == GLFW_KEY_A) ? true : false;	//left
			Window::keystate_S = (key == GLFW_KEY_S) ? true : false;	//down
			Window::keystate_D = (key == GLFW_KEY_D) ? true : false;	//right

		}
	}
	void Window::checkWin(std::string currentlevel)
	{
		std::vector<std::string> levelBoxes;
		//	load current level boxes for quest
		//if (Map::maki_city != 1) //@ aurelia delete this later, cause this was put here as game crashes when Quest_Lv11.json doesnt exist
		levelBoxes = Sprite::quest_boxes.at(currentlevel);

		//	checking through each ingredient loaded in the level
		for (auto& ingredient : Map::loadedIngredients)
		{
			Sprite* sIngredient = ingredient.second;	//current ingredient to check
			float ingredientRow = round((sIngredient->transformation.Position.x / static_cast<float>(Map::windowDim.first)) * static_cast<float>(Map::max_grid_cols_x));
			float ingredientCol = round((sIngredient->transformation.Position.y / static_cast<float>(Map::windowDim.second)) * static_cast<float>(Map::max_grid_rows_y));
			std::pair<float, float> ingredientCoordinates(ingredientRow, ingredientCol);

			//	check through each boxes loaded in the level
			for (auto& box : Map::loadedBoxes)
			{
				Sprite* sBox = box.second;	//current box to check
				float BoxRow = round((sBox->transformation.Position.x / static_cast<float>(Map::windowDim.first)) * static_cast<float>(Map::max_grid_cols_x));
				float BoxCol = round((sBox->transformation.Position.y / static_cast<float>(Map::windowDim.second)) * static_cast<float>(Map::max_grid_rows_y));
				std::pair<float, float> boxCoordinates(BoxRow, BoxCol);

				//	check if any ingredient matches box position 
				if (ingredientCoordinates == boxCoordinates)
				{
					//	check if combination is valid
					int state = checkCombination(ingredient.first, box.first);

					for (size_t i{}; i < levelBoxes.size(); ++i)
					{
						if (levelBoxes[i] == ingredient.first)
							winningBoxes[i] = { ingredient.first, state };
					}
				}
			}
		}
	}

	int Window::checkCombination(std::string ingredient, std::string box)
	{
		std::size_t found = box.find(ingredient);
		if (found != std::string::npos)
		{
			std::size_t found_salmon = ingredient.find("Salmon");
			if (found_salmon != std::string::npos)
			{
				//	ingredient contain add on sauce (tbc)
				//std::size_t found_wasabi = ingredient.find("Wasabi");
				if (found_salmon != std::string::npos)
				{
					if (Map::loadedIngredients.find("Salmon") != Map::loadedIngredients.end())
					{
						std::cout << "salmon with wasabi found\n";
					}
					
				}
			}
			else
			{
				return 1;
			}
		}
		else
			return 0;

		return 0;
	}

	void Window::updateChop(int position, gfxVector2 pos)
	{
		std::string chop;
		if (winningBoxes[position].second == 1 && (!(isTut1 || isTut2)))
		{
			switch (position)
			{
			case 0:
				chop = "done";
				break;
			case 1:
				chop = "done_2";
				break;
			case 2:
				chop = "done_3";
				break;
			}
			questDrawItems.insert({ chop, pos });
			
		}

		else if (winningBoxes[position].second == 0 && (!(isTut1 || isTut2)))
		{
			switch (position)
			{
			case 0:
				chop = "denied";
				break;
			case 1:
				chop = "denied_2";
				break;
			case 2:
				chop = "denied_3";
				break;
			}
			questDrawItems.insert({ chop, pos });
		}
		/*else if (winningBoxes[position].second == -1)
		{
			if((isTut1 || isTut2));
		
		}*/
	}
	

	void Window::resetQuest()
	{
		//reset quest tab
		Map::loadedIngredients.clear();
		Map::loadedBoxes.clear();

		for (size_t i{}; i < Window::winningBoxes.size(); ++i)
			winningBoxes[i] = { " ", -1 };

		questDrawItems.clear();
	}

	std::string Window::EnumToString(GameState Currentlevel)
	{
		/**
		 * IMPT!! Remember to add in additional level and ensure match to the name inside Json
		 */

		switch (Currentlevel)
		{
		case(GameState::TUT1):
			return "Quest_Tut1";
			break;

		case(GameState::TUT2):
			return "Quest_Tut2";
			break;

		case(GameState::LEVEL1):
			return "Quest_Lv1";
			break;

		case(GameState::LEVEL2):
			return "Quest_Lv2";
			break;

		case(GameState::LEVEL3):
			return "Quest_Lv3";
			break;

		case(GameState::LEVEL4):
			return "Quest_Lv4";
			break;

		case(GameState::LEVEL5):
			return "Quest_Lv5";
			break;

		case(GameState::LEVEL6):
			return "Quest_Lv6";
			break;

		case(GameState::LEVEL7):
			return "Quest_Lv7";
			break;

		case(GameState::LEVEL8):
			return "Quest_Lv8";
			break;

		case(GameState::LEVEL9):
			return "Quest_Lv9";
			break;

		case(GameState::LEVEL10):
			return "Quest_Lv10";
			break;

		case(GameState::LEVEL11):
			return "Quest_Lv11";
			break;

		default:
			return "";
		}

	}

	Window::Window(int _width, int _height)
		:m_width(_width),
		m_height(_height),
		isCutscene(0),
		isHowToPlay(0),
		isLevelSelection(0),
		isSettings(0),
		isWalk(0),
		isEndingCutscene(0)

	{
		starttime = endtime = delta = fps = 0;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, true);

		window_ptr = glfwCreateWindow(_width, _height, "SushiMi", NULL, NULL);
		if (window_ptr == nullptr)
		{
			std::cout << "erorr initilize glfw" << std::endl;
			return;
		}

		glfwMakeContextCurrent(window_ptr);
		/*std::cout << "GLEW Error: " << */glewGetErrorString(glewInit())/* << std::endl*/;  //it says "No error"

		//initialize key&mouse callback functions
		glfwSetKeyCallback(window_ptr, keyCallBack);
		glfwSetMouseButtonCallback(window_ptr, mouseCallBack);
		/*if (glewInit())
		{
			std::cout << "erorr initilize glew" << std::endl;
			return;
		}*/
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		Core::LevelLoadPath = "../Data/generated.json"; //initialise Bami position

		starttime = 0;
		endtime = 0;

		delta = 0;
		Shaders = std::make_unique<ShaderLibrary>();
		camera = std::make_unique<Camera>(0, 0);

		timetodeletegrid = false;
		isMenuState = true;
#ifdef EDITOR

		//the first level displayed on the map's launch
		Editor::LevelEditor::imguiloadedmap = "../TileMap/level1.txt";

#endif


		player = Core::Deserialize(*Core::LevelLoadPathPtr);
#ifndef EDITOR

		SceneManager::howtoplay_overlay1 = new Sprite("../textures/How To Play/HowToPlayBox_1.png");
		SceneManager::howtoplay_overlay2 = new Sprite("../textures/How To Play/HowToPlayBox_2.png");
		SceneManager::howtoplay_overlay3 = new Sprite("../textures/How To Play/HowToPlayBox_3.png");
		SceneManager::howtoplay_overlay4 = new Sprite("../textures/How To Play/HowToPlayBox_4.png");
		SceneManager::howtoplay_overlay5 = new Sprite("../textures/How To Play/HowToPlayBox_5.png");
		SceneManager::howtoplay_overlay6 = new Sprite("../textures/How To Play/HowToPlayBox_6.png");

		SceneManager::frame1 = new Sprite("../Textures/Cutscene/frame1.jpg");
		SceneManager::frame2 = new Sprite("../Textures/Cutscene/frame2.jpg");
		SceneManager::frame3 = new Sprite("../Textures/Cutscene/frame3.jpg");
		SceneManager::frame4 = new Sprite("../Textures/Cutscene/frame4.jpg");
		SceneManager::frame5 = new Sprite("../Textures/Cutscene/frame5.jpg");
		SceneManager::frame6 = new Sprite("../Textures/Cutscene/frame6.jpg");
		SceneManager::frame7 = new Sprite("../Textures/Cutscene/frame7.jpg");
		SceneManager::frame8 = new Sprite("../Textures/Cutscene/frame8.jpg");

		SceneManager::level_select = new Sprite("../textures/Level Selection Map/all_unlocked.png");

		SceneManager::settings_page = new Sprite("../textures/Settings/settings.png");
		SceneManager::credits_page = new Sprite("../textures/Credits/credits.png");

		SceneManager::wooden_bg = new Sprite("../textures/Tiles/Ground_FishingVillage/ground_backdrop.jpg");
		SceneManager::city_bg = new Sprite("../textures/Tiles/Maki_City/Ground/city_backdrop.png");

		SceneManager::riceplain_dialogue = new Sprite("../textures/UI/DialogueBox_RicePlain.png");
		SceneManager::gunkan_dialogue = new Sprite("../textures/UI/DialogueBox_Gunkan.png");
		SceneManager::fishingvillage_dialogue = new Sprite("../textures/UI/DialogueBox_FishingVillage.png");
		SceneManager::makicity_dialogue = new Sprite("../textures/UI/DialogueBox_MakiCity.png");

		SceneManager::win_overlay = new Sprite("../textures/Victory.png");
		//SceneManager::cover1 = new Sprite("../textures/Tiles/Pods/PodCover_3.png");
		//SceneManager::player_stuck = new Sprite("../textures/Bami/Sinking/BaMi_Sinking_1.png");
		SceneManager::rec = new Sprite("../textures/bg.jpg");

		SceneManager::Bami_End_Room_Cutscene = new Sprite("../textures/spritesheet/ricespritesheet.png"); //placeholder
		//SceneManager::Bami_End_Room_Cutscene->isSpriteSheet = 0;
		//SceneManager::Bami_End_Room_Cutscene->Add_animation("../textures/spritesheet/Bami_Idle.txt");
		//SceneManager::Bami_End_Room_Cutscene->curr_anim = AnimationType::Idle;
		SceneManager::are_you_sure = new Sprite("../textures/UI/AREYOUSURE.png");

		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		gameIsPaused = false;
		isMenuState = true;
		isHowToPlay = false;
		isSettings = false;
		isCredits = false;
		isLevelSelection = false;
		isWalk = false;
		isLevel1 = false;
		isLevel2 = false;
		isLevel3 = false;
		isLevel4 = false;
		isLevel5 = false;
		isLevel6 = false;
		isLevel7 = false;
		isQuestTab = false;
		isWinCondition = false;
		isPlayerinSinkhole = false;
		loaded = false;
		HowToPlayPage = 0;
		areyousure_prompt = false;
		CutscenePage = 0;
#endif // !EDITOR

		//player = new Player();

		/*sp = new Sprite("../textures/level1.jpg");
		sp->transformation.scale = glm::vec2(2000, 2000);
		sp->transformation.position = glm::vec2(0);*/

		/*Editor::LevelEditor::AddToFactory(CoreSystem)*/
		//SceneManager::loadTile(); //scene manager

		////the moving ingredient
		//ingredient = new Sprite(Editor::LevelEditor::texpath);
		//ingredient->transformation.scale = glm::vec2(100, 100);
		//ingredient->transformation.position = glm::vec2(15, 20);

	}

	Window::~Window()
	{
		timetodeletegrid = true;
		Map::ResetMap();
#ifndef EDITOR
		if (fin)
		{
			fin.close();
		}
		SceneManager::destroyHowToOverlay(); //delete How to play overlay
		SceneManager::destroySettings();
		SceneManager::destroyWinOverlay(); //delete Win Overlay
		SceneManager::destroyCutscene();
		SceneManager::destroyPlayer_Stuck();
		SceneManager::destroyLevelSelect();
		SceneManager::destroy_Dialogue();
		SceneManager::destroy_Wood_BG();
		SceneManager::destroy_City_BG();
		SceneManager::destroy_Bami_End_Room();
		SceneManager::destroy_Are_You_Sure();

		//JSONSerializer::Serialize(player, "../Data/generated.json");
#endif

		delete player;
		delete SceneManager::rec; // delete rectangle
		glfwTerminate();
		Editor::LevelEditor::imguiDestroyObj();
	}

	void Window::Input()
	{
#ifndef EDITOR

		if (keystate_fps)
		{
			if (show_fps == false)
			{
				show_fps = true;
			}
			else if (show_fps == true)
			{
				show_fps = false;
			}
			keystate_fps = false;
		}

		if (keystate_M)
		{
			isMenuState = true;
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
			SceneManager::num_dialogue_clicks = 0; //do not show dialogue in menu

		}

		//Play End Cutscene
		if (keystate_P)
		{
			isEndingCutscene = true;
			isCutscene = false;
			isMenuState = false;
			gameIsPaused = false;
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
			SceneManager::num_dialogue_clicks = 0; //do not show dialogue in end cutscene


		}

		if (keystate_tab)
		{
			gameIsPaused = false;
			// if i press tab
			// isquestab(false) = true;
			// off the tab state

			// if i pres tab again
			// isquestab(true) = false;
			// off the tab state
			areyousure_prompt = false;

			isQuestTab = !isQuestTab;
			keystate_tab = false;
		}

		if (keystate_J)
		{
			keystate_J = true;
			std::cout << "you have loaded test level for debugging" << std::endl;
			if (keystate_J)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
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
				isTestLevel = true;
				areyousure_prompt = false;
				loaded = false;

				SceneManager::restartLevel();

				keystate_J = false;
			}
		}
		if (keystate_K)
		{
			keystate_K = true;
			std::cout << "you have loaded tutorial 1" << std::endl;
			if (keystate_K)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = true;
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

				SceneManager::restartLevel();


				keystate_K = false;
			}
		}
		if (keystate_L)
		{
			keystate_L = true;
			std::cout << "you have loaded tutorial 2" << std::endl;
			if (keystate_L)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = true;
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

				SceneManager::restartLevel();

				keystate_L = false;
			}
		}
		if (keystate_1)
		{
			keystate_1 = true;
			std::cout << "you have loaded level 1" << std::endl;
			if (keystate_1)
			{
				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = false;
				isLevel1 = true;
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

				SceneManager::restartLevel();

				keystate_1 = false;
			}
		}
		if (keystate_2)
		{
			keystate_2 = true;
			std::cout << "you have loaded level 2" << std::endl;
			if (keystate_2)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = false;
				isLevel1 = false;
				isLevel2 = true;
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

				SceneManager::restartLevel();

				keystate_2 = false;
			}
		}
		if (keystate_3)
		{
			keystate_3 = true;
			std::cout << "you have loaded level 3" << std::endl;
			if (keystate_3)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = false;
				isLevel1 = false;
				isLevel2 = false;
				isLevel3 = true;
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

				SceneManager::restartLevel();
				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


				keystate_3 = false;
			}
		}
		if (keystate_4)
		{
			keystate_4 = true;
			std::cout << "you have loaded level 4" << std::endl;
			if (keystate_4)
			{
				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = false;
				isLevel1 = false;
				isLevel2 = false;
				isLevel3 = false;
				isLevel4 = true;
				isLevel5 = false;
				isLevel6 = false;
				isLevel7 = false;
				isLevel8 = false;
				isLevel9 = false;
				isLevel10 = false;
				isLevel11 = false;
				areyousure_prompt = false;
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();
				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


				keystate_4 = false;
			}
		}
		if (keystate_5)
		{
			keystate_5 = true;
			std::cout << "you have loaded level 5" << std::endl;
			if (keystate_5)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = false;
				isLevel1 = false;
				isLevel2 = false;
				isLevel3 = false;
				isLevel4 = false;
				isLevel5 = true;
				isLevel6 = false;
				isLevel7 = false;
				isLevel8 = false;
				isLevel9 = false;
				isLevel10 = false;
				isLevel11 = false;
				areyousure_prompt = false;
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();


				keystate_5 = false;
			}
		}
		if (keystate_6)
		{
			keystate_6 = true;
			std::cout << "you have loaded level 6" << std::endl;
			if (keystate_6)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = false;
				isLevel1 = false;
				isLevel2 = false;
				isLevel3 = false;
				isLevel4 = false;
				isLevel5 = false;
				isLevel6 = true;
				isLevel7 = false;
				isLevel8 = false;
				isLevel9 = false;
				isLevel10 = false;
				isLevel11 = false;
				isTestLevel = false;
				areyousure_prompt = false;
				loaded = false;

				SceneManager::restartLevel();
				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


				keystate_6 = false;
			}
		}
		if (keystate_7)
		{
			keystate_7 = true;
			std::cout << "you have loaded level 7" << std::endl;
			if (keystate_7)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = false;
				isLevel1 = false;
				isLevel2 = false;
				isLevel3 = false;
				isLevel4 = false;
				isLevel5 = false;
				isLevel6 = false;
				isLevel7 = true;
				isLevel8 = false;
				isLevel9 = false;
				areyousure_prompt = false;
				isLevel10 = false;
				isLevel11 = false;
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();
				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


				keystate_7 = false;
			}
		}
		if (keystate_8)
		{
			keystate_8 = true;
			std::cout << "you have loaded level 8" << std::endl;
			if (keystate_8)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
				isTut1 = false;
				isTut2 = false;
				isLevel1 = false;
				isLevel2 = false;
				isLevel3 = false;
				isLevel4 = false;
				isLevel5 = false;
				isLevel6 = false;
				isLevel7 = false;
				isLevel8 = true;  
				isLevel9 = false;
				isLevel10 = false;
				isLevel11 = false;
				areyousure_prompt = false;
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();

				keystate_8 = false;
			}
		}
		if (keystate_9)
		{
			keystate_9 = true;
			std::cout << "you have loaded level 9" << std::endl;
			if (keystate_9)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
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
				isLevel9 = true;
				isLevel10 = false;
				isLevel11 = false;
				areyousure_prompt = false;
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();

				keystate_9 = false;
			}
		}
		if (keystate_0)
		{
			keystate_0 = true;
			std::cout << "you have loaded level 10" << std::endl;
			if (keystate_0)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
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
				isLevel10 = true;
				isLevel11 = false;
				areyousure_prompt = false;
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();

				keystate_0 = false;
			}
		}
		if (keystate_minus)
		{
			keystate_minus = true;
			std::cout << "you have loaded level 11" << std::endl;
			if (keystate_minus)
			{

				isCutscene = false;
				isMenuState = false;
				isLevelSelection = false;
				gameIsPaused = false;
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
				isLevel11 = true;
				areyousure_prompt = false;
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();

				keystate_minus = false;
			}
		}
		if (keystate_T)
		{
			std::cout << "you are in level selection screen" << std::endl;

			if (keystate_T)
			{
				isCutscene = false;
				isMenuState = false;
				isQuestTab = false;
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
				isDialogue = false;
				isHowToPlay = false;
				areyousure_prompt = false;
				isLevelSelection = true;
				SceneManager::restartLevel();

				keystate_T = false;
			}
		}

		if (mouseLeft)
		{
			//place_obj = true;
			//if (place_obj)
			//{
				//std::cout << "placing obj at x: " << ingredient->transformation.position.x << "and y: " << ingredient->transformation.position.y << std::endl;
				//place_obj = false;
			//}
		}

		if (keystate_escape && gameIsPaused)
		{
			areyousure_prompt = false;
		}
		if (keystate_escape && (isTut1 || isTut2 || isLevel1 || isLevel2 || isLevel3 || isLevel4 || isLevel5 || isLevel6 || isLevel7 || isLevel8 || isLevel9 || isLevel10 || isLevel11 || isTestLevel) && isDialogue == false)
		{
			gameIsPaused = !gameIsPaused;

			keystate_escape = false;
		}
		if (keystate_escape && areyousure_prompt)
		{
			areyousure_prompt = false;
		}

		/**************************************/
		//BUTTONS DISPLAYED AT MAIN MENU
		/**************************************/

		if (mouseLeft && isMenuState == true)
		{
			//std::cout << "mouse clicking (windows.cpp)" << std::endl;
			double xpos = 0, ypos = 0;
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);

			//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;

			//MENU BUTTON - START (PLAY GAME), reference StartButton.json 
			if (static_cast<int>(xpos) > 275 && static_cast<int>(xpos) < (275 + 266) && static_cast<int>(ypos) > 349 && static_cast<int>(ypos) < (349 + 96))
			{

				isMenuState = false;
				isCutscene = true;
				/*isLevelSelection = true;*/

				//std::cout << "exit main menu" << std::endl;
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Sprite::menu->transformation.Position.x = screenwidth;
				Sprite::menu->transformation.Position.y = screenheight;*/

			}
			//HOW TO PLAY
			if (static_cast<int>(xpos) > 275 && static_cast<int>(xpos) < (275 + 266) && static_cast<int>(ypos) > 520 && static_cast<int>(ypos) < (520 + 96))
			{
				isHowToPlay = true;
				//std::cout << "in how to play screen" << std::endl;
			}
			//SETTINGS
			if (static_cast<int>(xpos) > 275 && static_cast<int>(xpos) < (275 + 266) && static_cast<int>(ypos) > 700 && static_cast<int>(ypos) < (700 + 96))
			{
				isSettings = true;
			}
			//MENU BUTTON - QUIT, reference ExitButton.json
			if (static_cast<int>(xpos) > 275 && static_cast<int>(xpos) < (275 + 266) && static_cast<int>(ypos) > 890 && static_cast<int>(ypos) < (890 + 96))
			{
				areyousure_prompt = true;

				/*glfwSetWindowShouldClose(window_ptr, true);*/
			}

		}
		/**************************************/
		//BUTTONS DISPLAYED WHEN GAME IS PAUSED
		/**************************************/
		if (mouseLeft && gameIsPaused == true)
		{
			double xpos = 0, ypos = 0;
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
			//std::cout << xpos << " " << ypos << "\n";
			for (auto& x : CoreSystem->objfactory->ObjectContainer)
			{
				if (x.first == "ResumeButton")
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					gfxVector2 position = { transcomp->Position.x, transcomp->Position.y };
					gfxVector2 scale = { transcomp->Scale.x, transcomp->Scale.y };

					//RESUME THE GAME BUTTON
					if (((float)xpos > position.x) &&
						((float)ypos > position.y) &&
						((float)xpos < (position.x + scale.x)) &&
						((float)ypos < (position.y + scale.y)))
					{
						gameIsPaused = false;
						//std::cout << "game resume, no more pause screen" << std::endl;
						int screenwidth = 0, screenheight = 0;
						glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
						SceneManager::howtoplay_overlay1->transformation.Position.x = static_cast<float>(screenwidth);
						SceneManager::howtoplay_overlay1->transformation.Position.y = static_cast<float>(screenheight);



					}
				}
				else if (x.first == "MenuButton")
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					gfxVector2 position = { transcomp->Position.x, transcomp->Position.y };
					gfxVector2 scale = { transcomp->Scale.x, transcomp->Scale.y };

					//Level Selection
					if (((float)xpos > position.x) &&
						((float)ypos > position.y) &&
						((float)xpos < (position.x + scale.x)) &&
						((float)ypos < (position.y + scale.y)))
					{

						keystate_T = true;
						int screenwidth = 0, screenheight = 0;
						glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
						SceneManager::howtoplay_overlay1->transformation.Position.x = static_cast<float>(screenwidth);
						SceneManager::howtoplay_overlay1->transformation.Position.y = static_cast<float>(screenheight);
					}
				}
				else if (x.first == "QuitButton")
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					gfxVector2 position = { transcomp->Position.x, transcomp->Position.y };
					gfxVector2 scale = { transcomp->Scale.x, transcomp->Scale.y };

					//QUIT THE GAME BUTTON
					if (((float)xpos > position.x) &&
						((float)ypos > position.y) &&
						((float)xpos < (position.x + scale.x)) &&
						((float)ypos < (position.y + scale.y)))
					{
						areyousure_prompt = true;
						if (keystate_Y)
						{

							glfwSetWindowShouldClose(window_ptr, true);
						}
						else if (keystate_N)
						{
							areyousure_prompt = false;
							keystate_N = false;
						}



					}
				}
			}
			////std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;


			////RETURN TO MAIN MENU
			//if (xpos > 600 && ypos > 585 && xpos < 1310 && ypos < 687)
			//{
			//	isMenuState = true;
			//	isLevel1 = false;
			//	isLevel2 = false;
			//	SceneManager::restartLevel();
			//	AudioManager.StopMusic();
			//	AudioManager.PlayMusic("BGM.ogg");
			//}
			////QUIT GAME
			//if (xpos > 600 && ypos > 714 && xpos < 1310 && ypos < 815)
			//{
			//	glfwSetWindowShouldClose(window_ptr, true);
			//}
		}
		/**************************************/
		//BUTTONS DISPLAYED ON LEVEL SELECT
		/**************************************/
		if (mouseLeft && isLevelSelection == true)
		{
			double xpos = 0, ypos = 0;
			glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);

			//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;

			//TUTORIAL1 and play cutscene
			if (xpos > 394 && ypos > 139 && xpos < 472 && ypos < 200)
			{
				isLevelSelection = false;
				isCutscene = true;
			}
			//Tutorial2
			if (xpos > 331 && ypos > 283 && xpos < 405 && ypos < 339)
			{
				isLevelSelection = false;
				isTut2 = true;

			}
			//LEVEL1
			if (xpos > 474 && ypos > 272 && xpos < 551 && ypos < 333)
			{
				isLevelSelection = false;
				isLevel1 = true;

			}
			//LEVEL2
			if (xpos > 568 && ypos > 163 && xpos < 633 && ypos < 223)
			{
				isLevelSelection = false;
				isLevel2 = true;

			}
		}
		//note: escape should be mapped to pause/menu
		//if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE))
		//{
		//	

		//	//the code below closes the game
		//	//glfwSetWindowShouldClose(window_ptr, true);
		//}
		if ((keystate_right || keystate_D) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false)
		{
			keystate_right = true;
			keystate_D = true;
			if (keystate_right || keystate_D)
			{
				Map::collision_check_right();
				Map::print_map_to_console();
				AudioManager.PlaySFX(walkingsfx);
				keystate_right = false;
				keystate_D = false;
			}
		}

		else if ((keystate_left || keystate_A) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false)
		{
			keystate_left = true;
			keystate_A = true;
			//player only move on one press
			//holding key or let go key, player stop
			if (keystate_left || keystate_A)
			{
				Map::collision_check_left();
				Map::print_map_to_console();
				AudioManager.PlaySFX(walkingsfx);
				keystate_left = false;
				keystate_A = false;
			}
		}

		else if ((keystate_up || keystate_W) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false)
		{
			keystate_up = true;
			keystate_W = true;

			if (keystate_up || keystate_W)
			{
				Map::collision_check_up();
				Map::print_map_to_console();
				AudioManager.PlaySFX(walkingsfx);
				//isWalk = true; //play walking sfx
				keystate_up = false;
				keystate_W = false;

			}
		}

		else if ((keystate_down || keystate_S) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false)
		{
			keystate_down = true;
			keystate_S = true;
			if (keystate_down || keystate_S)
			{
				Map::collision_check_down();
				Map::print_map_to_console();
				AudioManager.PlaySFX(walkingsfx);
				keystate_down = false;
				keystate_S = false;
			}
		}

		/***************************
			restart key "R" resets the level
		*******************************/
		if (keystate_R && (gameIsPaused == false && isWinCondition == false))
		{
			keystate_R = true;
			if (keystate_R)
			{
				Window::player->resetCount++;
				if(Window::player->resetCount == 1)
					AudioManager.PlayVoice("Dialogue_1.ogg");
				if (Window::player->resetCount == 2)
					AudioManager.PlayVoice("Dialogue_2.ogg");
				if (Window::player->resetCount == 3)
					AudioManager.PlayVoice("Dialogue_3.ogg");
				if (Window::player->resetCount == 4)
					AudioManager.PlayVoice("Dialogue_4.ogg");
				if (Window::player->resetCount >=5)
					AudioManager.PlayVoice("Dialogue_5.ogg");
				//restart

				//reset quest tab
				for (size_t i{}; i < Window::winningBoxes.size(); ++i)
					winningBoxes[i] = { " ", -1 };
				questDrawItems.clear();

				Map::RestartMap();
				std::cout << "restarting level" << std::endl;
				std::cout << "player is moved back to x: " << player->playerpos_restart.x << " and y: " << player->playerpos_restart.y << std::endl;

				keystate_R = false;
			}

		}
		if ((keystate_down || keystate_up || keystate_left || keystate_right) && !gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false)
			player->stop();

#endif //editor
	}

	void Window::Resize()
	{
		int width_, height_;
		glfwGetWindowSize(window_ptr, &width_, &height_);
		if (width_ != m_width || height_ != m_height)
		{
			m_width = width_;
			m_height = height_;
			glViewport(0, 0, width_, height_);
			camera->Update_Viewport(width_, height_);
			printf("resized \n");
		}
	}

	void Window::Mainloop()
	{
		starttime = glfwGetTime();

		while (!glfwWindowShouldClose(window_ptr))
		{
			/*FOR DEBUGGING PURPOSES*/
			//std::cout << "Player x: " << player->playerpos.x << " , " << "Player y: " << player->playerpos.y << std::endl;
			/*--------------------------*/
			pseudomain::update();
			AudioManager.Update();
			//for each frame 
			Resize();
			Input();
			if (isTut1 || isLevel1 || isLevel2 || isLevel3)
			{
				glClearColor((float)112 / 255, (float)153 / 255, (float)49 / 255, 1.0f);
			}
			else if (isLevel4 || isLevel5 || isLevel6)
			{
				glClearColor((float)207 / 255, (float)181 / 255, (float)142 / 255, 1.0f);
			}
			else
			{
				glClearColor((float)112 / 255, (float)153 / 255, (float)49 / 255, 1.0f);
			}
			glClear(GL_COLOR_BUFFER_BIT);

			Shaders->Textured_Shader()->use();
			if (isLevel7 || isLevel8 || isLevel9 || isLevel10)
			{
				SceneManager::load_Wood_BG();
				SceneManager::draw_Wood_BG();

			}
			else if (isLevel11)
			{
				SceneManager::load_City_BG();
				SceneManager::draw_City_BG();

			}
			/*Editor::LevelEditor::AddToFactory(CoreSystem)*/
			//Map::DrawMap(); //shifted into boolean

			// all drawing goes here ..
			//Sprite::menu->transformation.Position = glm::vec2(0, 0);
			//Sprite::menu->transformation.Scale = glm::vec2(1000, 800);

			Shaders->Textured_Shader()->Send_Mat4("projection", camera->Get_Projection());

			/*Shaders->Textured_Shader()->Send_Mat4("model_matrx", sp->transformation.Get());
			sp->draw();*/

			//the moving ingredient
#if defined(EDITOR) | defined(_EDITOR)
			//Camera::Update_Viewport(2560, 1200);
			/*
			ingredient = new Sprite(Editor::LevelEditor::texpath);
			Sprite(Editor::LevelEditor::texpath);
			ingredient->transformation.Scale = glm::vec2(100, 100);
			ingredient->transformation.Position = glm::vec2(600,600);
			*/
			//display object at imgui cursor
			Core::Editor::LevelEditor::imguiObjectCursor();
			/*
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", ingredient->transformation.Get());
			ingredient->draw();
			*/

			if (!loaded)
			{
				if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
				{
					Map::ResetMap();
				}

				std::cout << "current level displayed in editor mode is: " << Editor::LevelEditor::imguiloadedmap << std::endl;
				Map::initMap(Editor::LevelEditor::imguiloadedmap);
				Map::LoadMap();
				loaded = true;

		}
			if (loaded == true)
			{
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());
				player->draw(delta);

			}
			Map::DrawMap();



			//display object at imgui cursor
			Core::Editor::LevelEditor::imguiObjectCursor();


#endif

			//FOR OBJ CONTAINER DEBUGGING
			// 
			//std::cout << "what is inside obj container:" << std::endl;
			//for (auto& x : CoreSystem->objfactory->ObjectContainer)
			//{
			//	std::cout << x.first << std::endl; //should print out menu.json

			//	Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));

			//	//menu->transformation.Position = { 0,0 };
			//	//menu->transformation.Scale = { 50,50 };
			//
			//	//std::cout << x.second->characteristics->GetID(); // should print the transform ID saved into container
			//}
			//std::cout << "end of obj container\n";

			//Sprite::menu->transformation.Position = {0.f,0.f};
			//Sprite::menu->transformation.Scale = { 50,50 };
			//Shaders->Textured_Shader()->Send_Mat4("model_matrx", Sprite::menu->transformation.Get());
#ifndef EDITOR

			if (isLevelSelection)
			{
				//star is complete quest 
				//flag is complete entire level
				isMenuState = false;
				isCutscene = false;
				isLevel1 = false;
				isLevel2 = false;
				isLevel3 = false;
				isLevel4 = false;
				isLevel5 = false;
				isLevel6 = false;
				SceneManager::loadLevelSelect(0, 0);
				SceneManager::drawLevelSelect();
			}

			if (isCutscene)
			{
				SceneManager::loadCutscene();
				SceneManager::drawCutscene();
				if ((keystate_space) && isMenuState == false)
				{
					keystate_space = true;
					if (keystate_space)
					{
						double xpos = 0, ypos = 0;
						glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
						//NEXT PAGE
						if (CutscenePage < 8)
						{

							CutscenePage++;

							//std::cout << "next page" << std::endl;

						}
						if (CutscenePage == 7)
						{
							isCutscene = false;
							isTut1 = true;
							CutscenePage = 0;
							AudioManager.StopMusic();
						}
						keystate_space = false;
					}

				}

			}

			/*********************************
				LEVELS LOAD & WIN CHECK
			*********************************/
			
			if (isTut1 == true) { level = GameState::TUT1; Levels::Tutorial1(); walkingsfx = "Gravel_Drag-Movement_1.ogg"; }
			if (isTut2 == true) { level = GameState::TUT2;  Levels::Tutorial2(); walkingsfx = "Gravel_Drag-Movement_1.ogg";}
			if (isLevel1 == true) { level = GameState::LEVEL1;  Levels::Level1(); walkingsfx = "Gravel_Drag-Movement_1.ogg"; }
			if (isLevel2 == true) { level = GameState::LEVEL2; Levels::Level2(); walkingsfx = "Gravel_Drag-Movement_1.ogg";	}
			if (isLevel3 == true) { level = GameState::LEVEL3; Levels::Level3(); walkingsfx = "Gravel_Drag-Movement_1.ogg";	}
			if (isLevel4 == true) { level = GameState::LEVEL4; Levels::Level4(); walkingsfx = "WalkSFX.ogg"; }
			if (isLevel5 == true) { level = GameState::LEVEL5; Levels::Level5(); walkingsfx = "WalkSFX.ogg"; }
			if (isLevel6 == true) { level = GameState::LEVEL6; Levels::Level6(); walkingsfx = "WalkSFX.ogg"; }
			if (isLevel7 == true) { level = GameState::LEVEL7; Levels::Level7(); walkingsfx = "Hard Floor Walking.ogg";	}
			if (isLevel8 == true) { level = GameState::LEVEL8; Levels::Level8(); walkingsfx = "Hard Floor Walking.ogg"; }
			if (isLevel9 == true) { level = GameState::LEVEL9; Levels::Level9(); walkingsfx = "Hard Floor Walking.ogg"; }
			if (isLevel10 == true) { level = GameState::LEVEL10; Levels::Level10(); walkingsfx = "Hard Floor Walking.ogg"; }
			if (isLevel11 == true) { level = GameState::LEVEL11; Levels::Level11(); walkingsfx = "Hard Floor Walking.ogg";	}
			if (isTestLevel == true) { Levels::TestLevel(); }

			/**********************************
				DIALOGUE DISPLAY (riceplain)
			*************************************/
			if (isDialogue)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				
				SceneManager::load_Dialogue();
				SceneManager::draw_Dialogue();
				std::string first_line, second_line, third_line = "";

				if (curr_len <= realstring.length())
				{
					if (realstring.length() < 60) //only 1 line of dialogue
					{
						std::string one_by_one = realstring.substr(0, curr_len);

						Font::RenderText(*Shaders, one_by_one, screenwidth * 0.35f, screenheight * 0.15f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);
						if (Get_Delta())
						{
							curr_len += 1/* ((Get_Delta()) * 150)*/; // dialogue render speed is 200 * delta time
							//std::cout << "value of i is : " << curr_len << std::endl;
							if (curr_len > realstring.length())
							{
								curr_len = realstring.length();
							}

						}
					}
					else if (realstring.length() >= 60 && realstring.length() < 107) //2 lines of dialogue
					{
						if (curr_len <= 60)
						{
							first_line = realstring.substr(0, curr_len);

						}
						else if (curr_len > 60)
						{
							first_line = realstring.substr(0, 60);
							second_line = realstring.substr(60, curr_len);

						}
						
						/*std::cout << "new length read: " << realstring.length() << std::endl;*/
						if (Get_Delta())
						{
							curr_len += 1/*((Get_Delta()) * 150)*/; // dialogue render speed is 200 * delta time
							//std::cout << "value of i is : " << curr_len << std::endl;
							if (curr_len > realstring.length())
							{
								curr_len = realstring.length();
							}

						}
						Font::RenderText(*Shaders, first_line, screenwidth * 0.34f, screenheight * 0.17f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);
						Font::RenderText(*Shaders, second_line, screenwidth * 0.34f, screenheight * 0.12f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);

					}
					else if (realstring.length() >= 107) //3 lines of dialogue
					{
						//std::cout << "this text is soo long " << std::endl;
						if (curr_len <= 55)
						{
							first_line = realstring.substr(0, curr_len);

						}
						else if (curr_len <= 107)
						{
							first_line = realstring.substr(0, 55);
							second_line = realstring.substr(55, curr_len - 55);

						}
						else if (curr_len >= 107)
						{
							first_line = realstring.substr(0, 55);
							second_line = realstring.substr(55, 107 - 55);
							third_line = realstring.substr(107, curr_len);
						}
						/*std::cout << "new length read: " << realstring.length() << std::endl;*/
						if (Get_Delta())
						{
							curr_len += 1/*((Get_Delta()) * 150)*/; // dialogue render speed is 200 * delta time
							//std::cout << "value of i is : " << curr_len << std::endl;
							if (curr_len > realstring.length())
							{
								curr_len = realstring.length();
							}

						}
						Font::RenderText(*Shaders, first_line, screenwidth * 0.34f, screenheight * 0.17f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);
						Font::RenderText(*Shaders, second_line, screenwidth * 0.34f, screenheight * 0.12f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);
						Font::RenderText(*Shaders, third_line, screenwidth * 0.34f, screenheight * 0.07f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);
					}
				}
				

				//if there are still pages to display
				if (SceneManager::num_dialogue_clicks > 0)
				{
					isDialogue = true;
					//isQuestTab = false; need to check if there is dialogues for level 4 onwards,  turned off to enable questTabs 
					//std::cout << "dialogue is displaying" << std::endl;
					if (keystate_space)
					{
						if (curr_len != realstring.length()) //finish the current string when clicking
						{
							curr_len = realstring.length();
						}
						else //OR get the next line of dialogue
						{
							curr_len = 0;
							--SceneManager::num_dialogue_clicks;
							if (!fin.eof())
							{
								std::getline(fin, realstring);
							}
							//std::cout << "got the next line, decreasing dialogue clicks to: " << SceneManager::num_dialogue_clicks << std::endl;

						}
						keystate_space = false;
					}

				}
				else
				{
					isDialogue = false;
					isQuestTab = true;
				}
			}



			//*****************Draw Main Menu*****************************************
			if (isMenuState == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				for (auto& x : CoreSystem->objfactory->ObjectContainer)
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp = static_cast<Sprite*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Renderer));

					spritecomp->transformation.Position = transcomp->Position;
					if (x.first == "Menu")
					{
						spritecomp->transformation.Scale = glm::vec2(screenwidth, screenheight);
					}
					else
						spritecomp->transformation.Scale = transcomp->Scale;

					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());
					glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), spritecomp->alpha);

					if (x.first == "Menu") //draw menu
						spritecomp->draw();

					if (x.first == "StartButton")
						spritecomp->draw();

					if (x.first == "HowToPlay")
						spritecomp->draw();

					if (x.first == "SettingsButton")
						spritecomp->draw();

					if (x.first == "ExitButton")
						spritecomp->draw();
				}
			}

			if (gameIsPaused == true)
			{
				for (auto& x : CoreSystem->objfactory->ObjectContainer)
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp = static_cast<Sprite*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Renderer));

					spritecomp->transformation.Position = transcomp->Position;
					spritecomp->transformation.Scale = transcomp->Scale;

					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());
					if (x.first == "PauseMenu")
						spritecomp->draw();

					if (x.first == "ResumeButton")
						spritecomp->draw();

					if (x.first == "QuitButton")
						spritecomp->draw();

					if (x.first == "MenuButton")
						spritecomp->draw();
				}
			}

			/*If quest tab is loaded, check what are the ingredients loaded for the level*/
			if (isQuestTab && !isWinCondition && !gameIsPaused && !isMenuState && !isDialogue && !isCutscene && !isLevelSelection)
			{
				//	fixed position for quest items and chop (shld only work tut1 - lvl10
				gfxVector2 pos1 = { 50.f, 140.f }, pos2 = { 150.f, 140.f }, pos3 = { 250.f, 140.f };

				//	current level
				std::string sLevel = EnumToString(level);
				//	check if ingredient landed on box
				checkWin(sLevel);

				Core::Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at("questBase");
				Transform* transcomp1 = static_cast<Transform*>(obj1->GetObjectProperties()->GetComponent(ComponentID::Transform));
				Sprite* spritecomp1 = static_cast<Sprite*>(obj1->GetObjectProperties()->GetComponent(ComponentID::Renderer));

				spritecomp1->transformation.Position = transcomp1->Position;
				spritecomp1->transformation.Scale = transcomp1->Scale;

				Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
				spritecomp1->draw();

				auto checkifquestexists = Sprite::quest_boxes.find(sLevel);
				if (checkifquestexists != Sprite::quest_boxes.end()) //if the quest does not exist for the level (eg test level, or lvl 9-11 quest not done yet)
				{
					currentQuestIngredient = Sprite::quest_boxes.at(sLevel);
				std::vector<std::string> current_quest_ingredient = Sprite::quest_boxes.at(sLevel);

					// update ingredients' position to draw on quest tab at fixed position
					for (int i{}; i < currentQuestIngredient.size(); ++i)
					{
						switch (i)
						{
						case 0:
							questDrawItems.insert({ currentQuestIngredient[i] , pos1 });
							updateChop(i, pos1);
							break;
						case 1:
							questDrawItems.insert({ currentQuestIngredient[i] , pos2 });
							updateChop(i, pos2);
							break;
						case 2:
							questDrawItems.insert({ currentQuestIngredient[i] , pos3 });
							updateChop(i, pos3);
							break;
						default:
							break;
						}
					}

				}

				//	draw ingredients and chops
				for (auto& ingredient : questDrawItems)
				{
					auto checkifitexists = CoreSystem->objfactory->ObjectContainer.find(ingredient.first);
					//check if what you are accessing exists so it does not throw exception
					if (checkifitexists != CoreSystem->objfactory->ObjectContainer.end())
					{
						Core::Object::GameObject* obj2 = CoreSystem->objfactory->ObjectContainer.at(ingredient.first);
						//Transform* transcomp2 = static_cast<Transform*>(obj2->GetObjectProperties()->GetComponent(ComponentID::Transform));
						Sprite* spritecomp2 = static_cast<Sprite*>(obj2->GetObjectProperties()->GetComponent(ComponentID::Renderer));

						spritecomp2->transformation.Position = { ingredient.second.x, ingredient.second.y };

						Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp2->transformation.Get());
						spritecomp2->draw();
					}
				}
			}

			/*	quest tab shift to left side */
			/*	disable quest tab in all the listed cases in the else-if condition	*/
			/*	so that quest tab will only shown in levels	*/
			else if (!isWinCondition && !gameIsPaused && !isMenuState && !isDialogue && !isCutscene && !isLevelSelection && !isHowToPlay)
			{
				Core::Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at("questBase");
				Transform* transcomp1 = static_cast<Transform*>(obj1->GetObjectProperties()->GetComponent(ComponentID::Transform));
				Sprite* spritecomp1 = static_cast<Sprite*>(obj1->GetObjectProperties()->GetComponent(ComponentID::Renderer));

				spritecomp1->transformation.Position = { transcomp1->Position.x - 387.f, transcomp1->Position.y };
				spritecomp1->transformation.Scale = transcomp1->Scale;

				Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
				spritecomp1->draw();
			}

			if (isWalk == true)
			{
				AudioManager.PlaySFX("Gravel_Drag-Movement_1.ogg");
				isWalk = false;
			}

			if (isHowToPlay == true)
			{
				isMenuState = false; //disable menu buttons
				gameIsPaused = false;

				isTut1, isTut2, isLevel1, isLevel2, isLevel3, isLevel4, isLevel5, isLevel6, isLevel7, isLevel8, isLevel9, isLevel10, isLevel11, isTestLevel = false;
				isQuestTab = false;

				//SceneManager::loadHowToOverlay(0, 0);
				//std::cout << HowToPlayPage << "current page\n";
				SceneManager::drawHowToOverlay(HowToPlayPage);
				if (keystate_escape)
				{
					isMenuState = true;
					HowToPlayPage = 0;
					isHowToPlay = false;
					keystate_escape = false;
				}
				else if (keystate_right)
				{
					if (HowToPlayPage < 5)
					{
						HowToPlayPage++;
						keystate_right = false;
					}
					else if (HowToPlayPage >= 5)
					{
						HowToPlayPage = 0;
						keystate_right = false;
					}
				}
				else if (keystate_left)
				{
					//PREV PAGE 
					if (HowToPlayPage > 0)
					{
						HowToPlayPage--;
						keystate_left = false;
					}
					else if (HowToPlayPage <= 0)
					{
						HowToPlayPage = 5;
						keystate_left = false;
					}
				}
			}

			if (areyousure_prompt == true)
			{
				SceneManager::load_Are_You_Sure();
				SceneManager::draw_Are_You_Sure();
				if (keystate_Y && (gameIsPaused || isMenuState))
				{

					glfwSetWindowShouldClose(window_ptr, true);
				}
				else if (keystate_N)
				{
					areyousure_prompt = false;
					keystate_N = false;
				}
			}

			if (isSettings == true)
			{
				SceneManager::loadSettings();
				SceneManager::drawSettings();
				if (mouseLeft)
				{
					double xpos = 0, ypos = 0;
					glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);

					//volume up setting
					if (xpos > 1036 && xpos < 1139 && ypos > 410 && ypos < 500)
					{
						AudioManager.IncreaseMusicVolume();
						AudioManager.IncreaseSFXVolume();
						AudioManager.IncreaseVoiceVolume();
					}

					//volume down setting
					if (xpos > 1163 && xpos < 1268 && ypos > 410 && ypos < 500)
					{
						AudioManager.DecreaseMusicVolume();
						AudioManager.DecreaseSFXVolume();
						AudioManager.DecreaseVoiceVolume();
					}

					//PRESS CREDITS
					if (xpos > 814 && xpos < 1047 && ypos > 536 && ypos < 612)
					{
						isCredits = true;

					}
					//PRESS BACK
					if (xpos > 814 && xpos < 1047 && ypos > 635 && ypos < 708)
					{
						isSettings = false;
					}
				}
			}

			if (isEndingCutscene == true)
			{
				SceneManager::load_Bami_End_Room();
				SceneManager::draw_Bami_End_Room();

			}

			if (isCredits == true)
			{
				if (mouseLeft)
				{
					double xpos = 0, ypos = 0;
					glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
					//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;
					if (xpos > 673 && xpos < 1023 && ypos > 710 && ypos < 817)
					{
						isCredits = false;
					}
	}
}

			////display object at imgui cursor
			//Core::Editor::LevelEditor::imguiObjectCursor();

#endif

#if EDITOR
			for (auto test : Editor::LevelEditor::newobjarr)
			{
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", test.spritepath->transformation.Get());
				test.spritepath->draw();
			}
#endif
			endtime = glfwGetTime();
			delta = (endtime - starttime);
			starttime = endtime;

			pseudomain::draw(); //swap buffers and glfwpollevents are already done here, do not call again below


		}

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();

		//void Window::ImGuiToObjContainer(ObjectFactory* c)
		//{

		//	//Editor::LevelEditor::AddToFactory(ObjectFactory)
		//}
	}
}
