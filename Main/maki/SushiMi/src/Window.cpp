/*
File: Window.cpp
@author		louishetong.wang@digipen.edu
co-Author:  thea.sea@digipen.edu
co-Author:  Aurelia (fei.x@digipen.edu)
co-Author:  w.chongsheng@digipen.edu

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
#include "../Engine/Components/Texture/Sprite.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Camera/Camera2D.h"
#include "../Headers/SceneManager.h"
#include "../Engine/Audio/AudioEngine.h"
#include "../Engine/TileMap/Map.h"
#include "../Engine/Core/Core.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "Engine/Font/Font.h"

namespace Core
{
	static Core::MainSystem* CoreSystem;
	static int width, height;

	std::vector<Basket> CurrentIngredients; // retreive the curent level loaded ingredients

	//std::vector<std::pair<wall_type, Sprite*>> tilecontainer;
	//std::vector<std::pair<grid_number, Sprite*>> ingredientcontainer;
	/*                                                             game states
	----------------------------------------------------------------------------- */
	enum class GameState {
		LEVEL1,
		MENU

	};


	/*                                                             input key states
	----------------------------------------------------------------------------- */
	static bool keystate_left = false;
	static bool keystate_right = false;
	static bool keystate_up = false;
	static bool keystate_down = false;
	static bool keystate_R = false;
	static bool keystate_M = false;
	static bool keystate_tab = false;
	static bool keystate_space = false;
	static bool keystate_1 = false;
	static bool keystate_2 = false;
	static bool keystate_3 = false;
	static bool keystate_4 = false;
	static bool keystate_5 = false;
	static bool keystate_6 = false;
	static bool keystate_7 = false;
	static bool keystate_8 = false;
	static bool keystate_9 = false;
	static bool keystate_0 = false;
	static bool keystate_J = false;
	static bool keystate_K = false;
	static bool keystate_L = false;
	static bool keystate_T = false;
	static bool keystate_escape = false;
	static bool place_obj = false;

	static bool keystate_W = false;
	static bool keystate_A = false;
	static bool keystate_S = false;
	static bool keystate_D = false;

	static bool mouseLeft = false;
	Player* player;
	int curr_len = 0;
	std::string realstring = "";
	std::ifstream fin;

	float volume{ 1.f };

	void mouseCallBack(GLFWwindow* window_ptr, int button, int action, int mod)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			mouseLeft = (button == GLFW_MOUSE_BUTTON_LEFT) ? true : false;
			break;
		}

		switch (action)
		{
		case GLFW_PRESS:
			mouseLeft = (action == GLFW_PRESS) ? true : false;
			break;

		case GLFW_RELEASE:
			mouseLeft = false;
			break;
		}
	}


	//SceneManager* scnmanager = new SceneManager(); //this is dangerous!! write it in a function so that the new is deleted!!

	/*					key  callback function  , helper function for controlling input
		----------------------------------------------------------------------------- */
	void keyCallBack(GLFWwindow* window_ptr, int key, int scancode, int action, int mod)
	{
		if (GLFW_REPEAT == action)
		{
			keystate_left = (key == GLFW_KEY_LEFT) ? true : false;
			keystate_tab = (key == GLFW_KEY_TAB) ? true : false;
			keystate_right = (key == GLFW_KEY_RIGHT) ? true : false;
			keystate_up = (key == GLFW_KEY_UP) ? true : false;
			keystate_down = (key == GLFW_KEY_DOWN) ? true : false;
			keystate_R = (key == GLFW_KEY_R) ? true : false;
			keystate_M = (key == GLFW_KEY_M) ? true : false;
			keystate_escape = (key == GLFW_KEY_ESCAPE) ? true : false;


		}
		else if (GLFW_RELEASE == action)
		{
			keystate_left = false;
			keystate_right = false;
			keystate_up = false;
			keystate_down = false;
			keystate_R = false;
			keystate_M = false;
			keystate_escape = false;
			keystate_tab = false;
			keystate_space = false;
		}
		else if (GLFW_PRESS == action)
		{
			keystate_M = (key == GLFW_KEY_M) ? true : false;
			keystate_left = (key == GLFW_KEY_LEFT) ? true : false;
			keystate_right = (key == GLFW_KEY_RIGHT) ? true : false;
			keystate_up = (key == GLFW_KEY_UP) ? true : false;;
			keystate_down = (key == GLFW_KEY_DOWN) ? true : false;
			keystate_R = (key == GLFW_KEY_R) ? true : false;
			keystate_M = (key == GLFW_KEY_M) ? true : false;
			keystate_T = (key == GLFW_KEY_T) ? true : false;
			keystate_tab = (key == GLFW_KEY_TAB) ? true : false;
			keystate_escape = (key == GLFW_KEY_ESCAPE) ? true : false;
			keystate_space = (key == GLFW_KEY_SPACE) ? true : false;


			keystate_J = (key == GLFW_KEY_J) ? true : false;
			keystate_K = (key == GLFW_KEY_K) ? true : false;
			keystate_L = (key == GLFW_KEY_L) ? true : false;
			keystate_1 = (key == GLFW_KEY_1) ? true : false;
			keystate_2 = (key == GLFW_KEY_2) ? true : false;
			keystate_3 = (key == GLFW_KEY_3) ? true : false;
			keystate_4 = (key == GLFW_KEY_4) ? true : false;
			keystate_5 = (key == GLFW_KEY_5) ? true : false;
			keystate_6 = (key == GLFW_KEY_6) ? true : false;
			keystate_7 = (key == GLFW_KEY_7) ? true : false;
			keystate_8 = (key == GLFW_KEY_8) ? true : false;
			keystate_9 = (key == GLFW_KEY_9) ? true : false;
			keystate_0 = (key == GLFW_KEY_0) ? true : false;

			keystate_W = (key == GLFW_KEY_W) ? true : false;
			keystate_A = (key == GLFW_KEY_A) ? true : false;
			keystate_S = (key == GLFW_KEY_S) ? true : false;
			keystate_D = (key == GLFW_KEY_D) ? true : false;

		}
	}

	bool Window::checkWin()
	{
		//checking through all loaded box for the current level
		for (auto& box : SceneManager::tilecontainer)
		{
			//checking through all loaded ingredient for the current level
			for (auto& ingredient : SceneManager::ingredientcontainer)
			{
				//convert coordinates back into row and column (dont know why need to plus 1)
				int ingredientRow = static_cast<int>(ingredient.spr->transformation.Position.x * (static_cast<float>(Map::max_grid_cols_x) / m_width)) + 1;
				int ingredientCol = static_cast<int>(ingredient.spr->transformation.Position.y * (static_cast<float>(Map::max_grid_rows_y) / m_height)) + 1;
				std::pair<int, int> ingredientCoordinates(ingredientRow, ingredientCol);

				int BoxRow = static_cast<int>(box.second->transformation.Position.x * (static_cast<float>(Map::max_grid_cols_x) / m_width) + 1);
				int BoxCol = static_cast<int>(box.second->transformation.Position.y * (static_cast<float>(Map::max_grid_rows_y) / m_height) + 1);
				std::pair<int, int> boxCoordinates(BoxRow, BoxCol);

				//checking through level win condition (check if ingredient land on box position)
				if (ingredientCoordinates == boxCoordinates)
				{
					//ingredient row and col matches box row and col
					std::pair<grid_number, wall_type> checkCondition(ingredient.nametag, box.first);
					for (auto& y : levelWinConditions)//suggest to change to map
					{
						//check whether is correct ingredient to box
						if (checkCondition == y)
						{
							std::cout << "ingredient landed correct box\n";
							//check if quest tab is open
							if (isQuestTab)
							{
								for (auto& x : CoreSystem->objfactory->ObjectContainer)
								{
									Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
									Sprite* spritecomp = static_cast<Sprite*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Renderer));
									spritecomp->transformation.Position = transcomp->Position;
									spritecomp->transformation.Scale = transcomp->Scale;

									Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());

									if (x.first == "done")
										spritecomp->draw();
								}

							}
						}
					}
				}
			}
		}
		return false;
	}

	Window::Window(int width, int height)
		:m_width(width),
		m_height(height),
		isCutscene(0),
		isHowToPlay(0),
		isLevelSelection(0),
		isMenuState(1),
		isSettings(0),
		isWalk(0),
		isWinCondition(0)

	{
		starttime = endtime = delta = fps = 0;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, true);

		window_ptr = glfwCreateWindow(width, height, "SushiMi", NULL, NULL);
		if (window_ptr == nullptr)
		{
			std::cout << "erorr initilize glfw" << std::endl;
			return;
		}

		glfwMakeContextCurrent(window_ptr);
		std::cout << "GLEW Error: " << glewGetErrorString(glewInit()) << std::endl;  //it says "No error"

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

		//SceneManager::loadHowToOverlay(0, 0);

		/*SceneManager::howtoplay_overlay1 = new Sprite("../textures/How To Play/HowToPlayBox_1.png");
		SceneManager::howtoplay_overlay2 = new Sprite("../textures/How To Play/HowToPlayBox_2.png");
		SceneManager::howtoplay_overlay3 = new Sprite("../textures/How To Play/HowToPlayBox_3.png");
		SceneManager::howtoplay_overlay4 = new Sprite("../textures/How To Play/HowToPlayBox_4.png");
		SceneManager::howtoplay_overlay5 = new Sprite("../textures/How To Play/HowToPlayBox_5.png");*/

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

		SceneManager::riceplain_dialogue = new Sprite("../textures/UI/DialogueBox_RicePlain.png");
		SceneManager::gunkan_dialogue = new Sprite("../textures/UI/DialogueBox_Gunkan.png");
		SceneManager::fishingvillage_dialogue = new Sprite("../textures/UI/DialogueBox_FishingVillage.png");

		SceneManager::win_overlay = new Sprite("../textures/Victory.png");
		//SceneManager::cover1 = new Sprite("../textures/Tiles/Pods/PodCover_3.png");
		//SceneManager::player_stuck = new Sprite("../textures/Bami/Sinking/BaMi_Sinking_1.png");
		SceneManager::rec = new Sprite("../textures/bg.jpg");

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

		if (keystate_M)
		{
			isMenuState = true;
			isQuestTab = false;
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
			loaded = false;
			SceneManager::num_dialogue_clicks = 0; //do not show dialogue in menu

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
				isTestLevel = true;
				loaded = false;

				SceneManager::restartLevel();

				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


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
				loaded = false;

				SceneManager::restartLevel();

				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


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
				loaded = false;

				SceneManager::restartLevel();

				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();
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
				loaded = false;

				SceneManager::restartLevel();

				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


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
				loaded = false;

				SceneManager::restartLevel();
				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


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
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();
				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


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
				isTestLevel = false;
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
				isLevel10 = false;
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
				isTestLevel = false;
				loaded = false;

				SceneManager::restartLevel();
				//SceneManager::tilecontainer.clear();
				//SceneManager::ingredientcontainer.clear();


				keystate_8 = false;
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
				isTestLevel = false;
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

		if (keystate_escape && (isTut1|| isTut2|| isLevel1 || isLevel2 || isLevel3 || isLevel4 || isLevel5 || isLevel6 || isLevel7 || isLevel8))
		{
			gameIsPaused = !gameIsPaused;
			keystate_escape = false;
			/*if (keystate_escape && (isLevel1 || isLevel2))
			{
				gameIsPaused = true;
				//std::cout << "game paused, pause screen showing" << std::endl;
				keystate_escape = false;
			}
			else if (!keystate_escape && (isLevel1 || isLevel2) )
			{
				gameIsPaused = false;
				keystate_escape = false;
			} */
		}
		//game is paused
		if (gameIsPaused == false)
		{
			keystate_escape = true;
			if (keystate_escape)
			{
				gameIsPaused = false;
				//std::cout << "game resume, no more pause screen" << std::endl;
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				//SceneManager::pause_overlay->transformation.Position.x = screenwidth;
				//SceneManager::pause_overlay->transformation.Position.y = screenheight;
				keystate_escape = false;
			}
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
				glfwSetWindowShouldClose(window_ptr, true);
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
						SceneManager::howtoplay_overlay1->transformation.Position.x = screenwidth;
						SceneManager::howtoplay_overlay1->transformation.Position.y = screenheight;

				

					}
				}
			}
			//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;


			//RETURN TO MAIN MENU
			if (xpos > 600 && ypos > 585 && xpos < 1310 && ypos < 687)
			{
				isMenuState = true;
				isLevel1 = false;
				isLevel2 = false;
				SceneManager::restartLevel();
				AudioManager.StopMusic();
				AudioManager.PlayMusic("BGM.wav");
			}
			//QUIT GAME
			if (xpos > 600 && ypos > 714 && xpos < 1310 && ypos < 815)
			{
				glfwSetWindowShouldClose(window_ptr, true);
			}
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
		if ((keystate_right || keystate_D) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false)
		{
			keystate_right = true;
			keystate_D = true;
			if (keystate_right || keystate_D)
			{
				Map::collision_check_right();
				Map::print_map_to_console();
				AudioManager.PlaySFX("Gravel_Drag-Movement_1.wav");
				keystate_right = false;
				keystate_D = false;
			}
		}

		else if ((keystate_left || keystate_A) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false)
		{
			keystate_left = true;
			keystate_A = true;
			//player only move on one press
			//holding key or let go key, player stop
			if (keystate_left || keystate_A)
			{
				Map::collision_check_left();
				Map::print_map_to_console();
				AudioManager.PlaySFX("Gravel_Drag-Movement_1.wav");
				keystate_left = false;
				keystate_A = false;
			}
		}

		else if ((keystate_up || keystate_W) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false)
		{
			keystate_up = true;
			keystate_W = true;

			if (keystate_up || keystate_W)
			{
				Map::collision_check_up();
				Map::print_map_to_console();
				AudioManager.PlaySFX("Gravel_Drag-Movement_1.wav");
				//isWalk = true; //play walking sfx
				keystate_up = false;
				keystate_W = false;

			}
		}

		else if ((keystate_down || keystate_S) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false)
		{
			keystate_down = true;
			keystate_S = true;
			if (keystate_down || keystate_S)
			{
				Map::collision_check_down();
				Map::print_map_to_console();
				AudioManager.PlaySFX("Gravel_Drag-Movement_1.wav");
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
				//restart
				Map::RestartMap();
				std::cout << "restarting level" << std::endl;
				std::cout << "player is moved back to x: " << player->playerpos_restart.x << " and y: " << player->playerpos_restart.y << std::endl;

				keystate_R = false;
			}

		}
		if (keystate_down || keystate_up || keystate_left || keystate_right == true)
			player->stop();

#endif //editor
	}

	void Window::Resize()
	{
		int width, height;
		glfwGetWindowSize(window_ptr, &width, &height);
		if (width != m_width || height != m_height)
		{
			m_width = width;
			m_height = height;
			glViewport(0, 0, width, height);
			camera->Update_Viewport(width, height);
			printf("resized \n");
		}
	}

	void Window::Mainloop()
	{
		while (!glfwWindowShouldClose(window_ptr))
		{
			/*FOR DEBUGGING PURPOSES*/
			//std::cout << "Player x: " << player->playerpos.x << " , " << "Player y: " << player->playerpos.y << std::endl;
			/*--------------------------*/
			starttime = glfwGetTime();
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
			if (isLevel7 || isLevel8 || isLevel9)
			{
				SceneManager::load_Wood_BG();
				SceneManager::draw_Wood_BG();

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
			Camera::Update_Viewport(2560, 1200);
			/*
			ingredient = 
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
			if (loaded = true)
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
				TUTORIAL 1 LOAD & WIN CHECK
			*********************************/
			if (isTut1 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/_tut1.txt");

					Map::LoadMap();
					loaded = true;
					isQuestTab = false;
					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("BGM with Forest Day volume test.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("BGM with Forest Day volume test.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/_tut1_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::T1);
					curr_len = 0;
					SceneManager::num_dialogue_clicks = 7; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}

				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}

				//draw lv1 tile map
				Map::DrawMap();

				//draw playerpos at lvl 1
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				if (gameIsPaused == false)
				{
					player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0);
					//SceneManager::drawHowToOverlay();

				}
				if (Map::isWin())
				{
					//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					isWinCondition = true;
				}
			}
			if (isWinCondition == true && isTut1 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.2), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isTut1 = false;
					isTut2 = true;
					isWinCondition = false;
					loaded = false;
					keystate_space = false;


				}

			}
			/*********************************
				TUTORIAL 2 LOAD & WIN CHECK
			*********************************/
			if (isTut2 == true)
			{
				//fadeComplete = SceneManager::FadeOut();
				//if (fadeComplete == 0)
				//{
				//	SceneManager::FadeOut();
				//}
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}
					Map::initMap("../TileMap/_tut2.txt");

					Map::LoadMap();
					isQuestTab = false;
					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("BGM with Forest Day volume test.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("BGM with Forest Day volume test.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/_tut2_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);



					dialogue_style = static_cast<int>(dialogue::T2);
					curr_len = 0;
					SceneManager::num_dialogue_clicks = 5; //num of dialogue pages BEFORE game starts
					isDialogue = true;
					//also need dialogue after game end
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				//draw lv1 tile map
				Map::DrawMap();


				//draw playerpos at lvl 1
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;
				if (gameIsPaused == false)
				{
					player->draw(Get_Delta());

				}

				else if (gameIsPaused == true)
				{
					player->draw(0);
					//SceneManager::drawHowToOverlay();

				}
				if (Map::isWin())
				{
					//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					isWinCondition = true;
				}

			}
			if (isWinCondition == true && isTut2 == true)
			{
				float alpha = 0;
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

				/*Fade In Effect*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.2), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();

				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isTut2 = false;
					isLevel1 = true;
					isWinCondition = false;
					loaded = false;
					keystate_space = false;

				}

			}
			//order of rendering
			//step 1: map
			//step 2: pause overlay
			//step 3: main menu

			/*********************************
				LEVEL 1 LOAD & WIN CHECK
			*********************************/
			if (isLevel1 == true)
			{

				if (!loaded)
				{
					
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level1.txt");
					//Map::initMap("../TileMap/pod_rendering_test.txt");

					Map::LoadMap();
					isQuestTab = false;
					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("BGM with Forest Day volume test.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("BGM with Forest Day volume test.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl1_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);




					dialogue_style = static_cast<int>(dialogue::L1);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 3; //num of dialogue pages BEFORE game starts
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
					//also need dialogue after game end
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				//draw lv1 tile map
				Map::DrawMap();

				//draw playerpos at lvl 1
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;

				if (gameIsPaused == false)
				{
					player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0);

				}
				if (Map::isWin())
				{
					//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					isWinCondition = true;
				}
			}

			if (isWinCondition == true && isLevel1 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isLevel1 = false; //unload curr level
					isLevel2 = true; //load new level
					isWinCondition = false; //reset win condition
					loaded = false; //set to load
					keystate_space = false;
				}

			}

			/*********************************
				LEVEL 2 LOAD & WIN CHECK
			*********************************/
			if (isLevel2 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level2.txt");
					Map::LoadMap();

					isQuestTab = false;
					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("BGM with Forest Day volume test.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("BGM with Forest Day volume test.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl2_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L2);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 2; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				//draw lv2 tile map
				Map::DrawMap(); //this will also set numQuests

				//draw playerpos at lvl 2
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;

				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0);

				}
				if (Map::isWin())
				{
					isWinCondition = true;

				}
			}

			if (isWinCondition == true && isLevel2 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isWinCondition = false;
					isLevel2 = false;
					isLevel3 = true;
					loaded = false;
					keystate_space = false;
				}
			}
			/*********************************
				LEVEL 3 LOAD & WIN CHECK
			*********************************/
			if (isLevel3 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level3.txt");
					Map::LoadMap();

					isQuestTab = false;
					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("BGM with Forest Day volume test.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("BGM with Forest Day volume test.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl3_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L3);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 1; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				//draw lv3 tile map
				Map::DrawMap(); //this will also set numQuests

				//draw playerpos at lvl 3
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;


				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0); //draw stationary player
				}
				if (Map::isWin())
				{
					isWinCondition = true;
				}
			}

			if (isWinCondition == true && isLevel3 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					isWinCondition = false;
					isLevel3 = false;
					isLevel4 = true;
					loaded = false;
					keystate_space = false;
				}
			}
			/*********************************
				LEVEL 4 LOAD & WIN CHECK
			*********************************/
			if (isLevel4 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level4.txt");
					Map::LoadMap();

					isQuestTab = false;
					loaded = true;
					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("Forest_bgm.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("Forest_bgm.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl4_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L4);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 3; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				Map::DrawMap(); //this will also set numQuests

				//draw playerpos at lvl 4
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;
				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0); //draw stationary player
				}
				if (Map::isWin())
				{
					isWinCondition = true;
				}
			}

			if (isWinCondition == true && isLevel4 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					isWinCondition = false;
					isLevel4 = false;
					isLevel5 = true;
					loaded = false;
					keystate_space = false;
				}
			}

			/*********************************
				LEVEL 5 LOAD & WIN CHECK
			*********************************/
			if (isLevel5 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level5.txt");
					Map::LoadMap();

					isQuestTab = false;
					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("Forest_bgm.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("Forest_bgm.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl5_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L5);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 1; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				Map::DrawMap(); //this will also set numQuests

				//draw playerpos at lvl 2
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;
				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0); //draw stationary player
				}
				if (Map::isWin())
				{
					isWinCondition = true;
				}
			}

			if (isWinCondition == true && isLevel5 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isWinCondition = false;
					isLevel5 = false;
					isLevel6 = true;
					loaded = false;
					keystate_space = false;
				}
			}
			/*********************************
				LEVEL 6 LOAD & WIN CHECK
			*********************************/
			if (isLevel6 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level6.txt");
					Map::LoadMap();

					isQuestTab = false;
					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("Forest_bgm.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("Forest_bgm.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl6_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L6);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 3; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				Map::DrawMap(); //this will also set numQuests

				//draw playerpos at lvl 2
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;
				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0); //draw stationary player
				}
				if (Map::isWin())
				{
					isWinCondition = true;
				}
			}

			if (isWinCondition == true && isLevel6 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isWinCondition = false;
					isLevel6 = false;
					isLevel7 = true;
					loaded = false;
					keystate_space = false;
				}
			}

			/*********************************
				LEVEL 7 LOAD & WIN CHECK
			*********************************/
			if (isLevel7 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level7.txt");
					Map::LoadMap();

					isQuestTab = false;
					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("Fishing_Village.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("Fishing_Village.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl7_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L7);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 3; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				Map::DrawMap(); //this will also set numQuests

				//draw playerpos at lvl 2
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				//std::cout << "goals no " << Window::numQuests << std::endl;
				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0); //draw stationary player
				}
				if (Map::isWin())
				{
					isWinCondition = true;
				}
			}
			if (isWinCondition == true && isLevel7 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isWinCondition = false;
					isLevel7 = false;
					isLevel8 = true;
					loaded = false;
					keystate_space = false;

				}
			}
			/*********************************
				LEVEL 8 LOAD & WIN CHECK
			*********************************/
			if (isLevel8 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level8.txt");
					Map::LoadMap();

					isQuestTab = false;
					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("Fishing_Village.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("Fishing_Village.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl8_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L8);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 1; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				Map::DrawMap();

				//draw playerpos at lvl 2
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());
				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0); //draw stationary player
				}
				if (Map::isWin())
				{
					isWinCondition = true;
				}
			}
			if (isWinCondition == true && isLevel8 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isWinCondition = false;
					isLevel8 = false;
					isLevel9 = true;
					loaded = false;
					keystate_space = false;

				}
			}
			/*********************************
				LEVEL 9 LOAD & WIN CHECK
			*********************************/
			if (isLevel9 == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/level9.txt");
					Map::LoadMap();

					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("Fishing_Village.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("Fishing_Village.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl9_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L9);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 1; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				Map::DrawMap();

				//draw playerpos at lvl 2
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0); //draw stationary player
				}
				if (Map::isWin())
				{
					isWinCondition = true;
				}
			}
			if (isWinCondition == true && isLevel9 == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isWinCondition = false;
					isLevel9 = false;
					isLevel10 = true;
					loaded = false;
					keystate_space = false;
				}
			}

			/*********************************
				TEST LEVEL LOAD & WIN CHECK
			*********************************/
			if (isTestLevel == true)
			{
				if (!loaded)
				{
					if (SceneManager::tilecontainer.size() > 0 && SceneManager::ingredientcontainer.size() > 0)
					{
						Map::ResetMap();
					}

					Map::initMap("../TileMap/_tut1_bak.txt");
					Map::LoadMap();

					loaded = true;

					AudioManager.LoadSFX("Gravel_Drag-Movement_1.wav");
					AudioManager.LoadMusic("Fishing_Village.wav");
					AudioManager.SetMusicVolume(0.01f);
					AudioManager.PlayMusic("Fishing_Village.wav");

					if (fin)
					{
						fin.close();
					}
					fin.open("../Data/Dialogue/lvl9_dialogue.txt");
					if (!fin)
					{
						std::cout << "Unable to open dialogue file!";
						return;
					}
					std::getline(fin, realstring);

					dialogue_style = static_cast<int>(dialogue::L9);
					curr_len = 0;

					SceneManager::num_dialogue_clicks = 0; //num of dialogue pages BEFORE game starts
					//also need dialogue after game end
					isDialogue = true;
					CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																			// for quest tab drawing of ingredients
				}
				/*Fade out effect*/
				if (!isWinCondition)
				{
					SceneManager::FadeOut();
					SceneManager::drawBlackOverlay();
				}
				Map::DrawMap();

				//draw playerpos at lvl 2
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());

				if (gameIsPaused == false)
				{
					if (isPlayerinSinkhole)
					{

					}
					else
						player->draw(Get_Delta());

				}
				else if (gameIsPaused == true)
				{
					player->draw(0); //draw stationary player
				}
				if (Map::isWin())
				{
					isWinCondition = true;
				}
			}
			if (isWinCondition == true && isTestLevel == true)
			{
				int screenwidth = 0, screenheight = 0;
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
				SceneManager::drawWinOverlay();
				//stop all player controls
				//press button to undraw level 1, and draw level 2
				if (keystate_space && isWinCondition == true)
				{
					isWinCondition = false;
					isTestLevel = false;
					isTut1 = true;
					loaded = false;
					keystate_space = false;
				}
			}
			/**********************************
				DIALOGUE DISPLAY (riceplain)
			*************************************/
			if (isDialogue)
			{
				if (dialogue_style >= static_cast<int>(dialogue::T1) && dialogue_style <= static_cast<int>(dialogue::L3))
				{
					SceneManager::load_Dialogue();
					SceneManager::draw_Dialogue();

					if (curr_len <= realstring.length())
					{
						if (curr_len < 54)
						{
							std::string one_by_one = realstring.substr(0, curr_len);
							/*std::cout << "new length read: " << realstring.length() << std::endl;*/
							Font::RenderText(*Shaders, one_by_one, 190, 90, .25f, glm::vec3(0.f, 0.f, 0.f));
							if (/*Window::GetInstance(0, 0)->getDelta() * 150 < 2*/ (Get_Delta()) * 150 < 2 || (Get_Delta()) * 100 < 2)
							{
								curr_len += 1; // dialogue render speed is 200 * delta time
								//std::cout << "value of i is : " << curr_len << std::endl;
								if (curr_len > realstring.length())
								{
									curr_len = realstring.length();
								}

							}
						}
						else if (curr_len >= 54)
						{
							std::string first_line = realstring.substr(0, 54);
							std::string second_line = realstring.substr(54, curr_len);
							/*std::cout << "new length read: " << realstring.length() << std::endl;*/
							Font::RenderText(*Shaders, first_line, 190, 90, .25f, glm::vec3(0.f, 0.f, 0.f));
							Font::RenderText(*Shaders, second_line, 190, 70, .25f, glm::vec3(0.f, 0.f, 0.f));
							if ((Get_Delta()) * 150 < 2 || (Get_Delta()) * 100 < 2)
							{
								curr_len += 1/*(GLHelper::delta_time * 150)*/; // dialogue render speed is 200 * delta time
								//std::cout << "value of i is : " << curr_len << std::endl;
								if (curr_len > realstring.length())
								{
									curr_len = realstring.length();
								}

							}
						}
					}

				}
				else if (dialogue_style >= static_cast<int>(dialogue::L4) && dialogue_style <= static_cast<int>(dialogue::L6))
				{
					SceneManager::load_Dialogue();
					SceneManager::draw_Dialogue();



					if (curr_len <= realstring.length())
					{
						if (realstring.length() < 55)
						{
							std::string one_by_one = realstring.substr(0, curr_len);

							Font::RenderText(*Shaders, one_by_one, 190, 90, .22f, glm::vec3(0.f, 0.f, 0.f));
							if ((Get_Delta()) * 150 < 2 || (Get_Delta()) * 100 < 2)
							{
								curr_len += 1/* (GLHelper::delta_time * 150)*/; // dialogue render speed is 200 * delta time
								//std::cout << "value of i is : " << curr_len << std::endl;
								if (curr_len > realstring.length())
								{
									curr_len = realstring.length();
								}

							}
						}
						else if (realstring.length() >= 55 && realstring.length() < 107)
						{
							std::string first_line = realstring.substr(0, 53);
							std::string second_line = realstring.substr(53, curr_len);

							/*std::cout << "new length read: " << realstring.length() << std::endl;*/
							Font::RenderText(*Shaders, first_line, 190, 90, .22f, glm::vec3(0.f, 0.f, 0.f));
							Font::RenderText(*Shaders, second_line, 190, 70, .22f, glm::vec3(0.f, 0.f, 0.f));

							if ((Get_Delta()) * 150 < 2 || (Get_Delta()) * 100 < 2)
							{
								curr_len += 1/*(GLHelper::delta_time * 150)*/; // dialogue render speed is 200 * delta time
								//std::cout << "value of i is : " << curr_len << std::endl;
								if (curr_len > realstring.length())
								{
									curr_len = realstring.length();
								}

							}
						}
						else if (realstring.length() >= 107)
						{
							//std::cout << "this text is soo long " << std::endl;
							std::string first_line = realstring.substr(0, 53);
							std::string second_line = realstring.substr(53, 107 - 53);
							std::string third_line = realstring.substr(107, curr_len);
							/*std::cout << "new length read: " << realstring.length() << std::endl;*/
							Font::RenderText(*Shaders, first_line, 190, 90, .22f, glm::vec3(0.f, 0.f, 0.f));
							Font::RenderText(*Shaders, second_line, 190, 70, .22f, glm::vec3(0.f, 0.f, 0.f));
							Font::RenderText(*Shaders, third_line, 190, 50, .22f, glm::vec3(0.f, 0.f, 0.f));
							if ((Get_Delta()) * 150 < 2 || (Get_Delta()) * 100 < 2)
							{
								curr_len += 1/*(GLHelper::delta_time * 150)*/; // dialogue render speed is 200 * delta time
								//std::cout << "value of i is : " << curr_len << std::endl;
								if (curr_len > realstring.length())
								{
									curr_len = realstring.length();
								}

							}
						}
					}

				}
				else if (dialogue_style >= static_cast<int>(dialogue::L7) && dialogue_style <= static_cast<int>(dialogue::L9))
				{
					SceneManager::load_Dialogue();
					SceneManager::draw_Dialogue();


					if (curr_len <= realstring.length())
					{
						if (realstring.length() < 56)
						{
							std::string one_by_one = realstring.substr(0, curr_len);

							Font::RenderText(*Shaders, one_by_one, 190, 90, .21f, glm::vec3(0.f, 0.f, 0.f));
							if ((Get_Delta()) * 150 < 2 || (Get_Delta()) * 100 < 2)
							{
								curr_len += 1/* (GLHelper::delta_time * 150)*/; // dialogue render speed is 200 * delta time
								//std::cout << "value of i is : " << curr_len << std::endl;
								if (curr_len > realstring.length())
								{
									curr_len = realstring.length();
								}

							}
						}
						else if (realstring.length() >= 56 && realstring.length() < 107)
						{
							std::string first_line = realstring.substr(0, 56);
							std::string second_line = realstring.substr(56, curr_len);

							/*std::cout << "new length read: " << realstring.length() << std::endl;*/
							Font::RenderText(*Shaders, first_line, 190, 90, .21f, glm::vec3(0.f, 0.f, 0.f));
							Font::RenderText(*Shaders, second_line, 190, 70, .21f, glm::vec3(0.f, 0.f, 0.f));

							if ((Get_Delta()) * 150 < 2 || (Get_Delta()) * 100 < 2)
							{
								curr_len += 1/*(GLHelper::delta_time * 150)*/; // dialogue render speed is 200 * delta time
								//std::cout << "value of i is : " << curr_len << std::endl;
								if (curr_len > realstring.length())
								{
									curr_len = realstring.length();
								}

							}
						}
						else if (realstring.length() >= 107)
						{
							//std::cout << "this text is soo long " << std::endl;
							std::string first_line = realstring.substr(0, 56);
							std::string second_line = realstring.substr(56, 107 - 56);
							std::string third_line = realstring.substr(107, curr_len);
							/*std::cout << "new length read: " << realstring.length() << std::endl;*/
							Font::RenderText(*Shaders, first_line, 190, 90, .2f, glm::vec3(0.f, 0.f, 0.f));
							Font::RenderText(*Shaders, second_line, 190, 70, .2f, glm::vec3(0.f, 0.f, 0.f));
							Font::RenderText(*Shaders, third_line, 190, 50, .2f, glm::vec3(0.f, 0.f, 0.f));
							if ((Get_Delta()) * 150 < 2 || (Get_Delta()) * 100 < 2)
							{
								curr_len += 1/*(GLHelper::delta_time * 150)*/; // dialogue render speed is 200 * delta time
								//std::cout << "value of i is : " << curr_len << std::endl;
								if (curr_len > realstring.length())
								{
									curr_len = realstring.length();
								}

							}
						}
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
						curr_len = 0;
						--SceneManager::num_dialogue_clicks;
						if (!fin.eof())
						{
							std::getline(fin, realstring);
						}
						//std::cout << "got the next line, decreasing dialogue clicks to: " << SceneManager::num_dialogue_clicks << std::endl;
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
				AudioManager.SetMusicVolume(0.4f);

				for (auto& x : CoreSystem->objfactory->ObjectContainer)
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp = static_cast<Sprite*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Renderer));

					spritecomp->transformation.Position = transcomp->Position;
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
			if (isQuestTab && !isWinCondition && !gameIsPaused && !isMenuState && !isDialogue && !isCutscene && !isLevelSelection && !isHowToPlay)
			{
				Core::Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at("questBase");
				Transform* transcomp1 = static_cast<Transform*>(obj1->GetObjectProperties()->GetComponent(ComponentID::Transform));
				Sprite* spritecomp1 = static_cast<Sprite*>(obj1->GetObjectProperties()->GetComponent(ComponentID::Renderer));

				spritecomp1->transformation.Position = transcomp1->Position;
				spritecomp1->transformation.Scale = transcomp1->Scale;

				Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
				//spritecomp1->draw();

				std::map<std::string, gfxVector2> loadedIngredients;    // mapping of ingredients to position based on how many ingredients loaded
				size_t numOfLoadedIngredient = CurrentIngredients.size();    // number of ingredients loaded for current level

				float increment = 0.f;    // increment to position each ingredient onto quest tab

				//checking through all loaded ingredient for the current level
				for (auto& ingredient : CurrentIngredients)
				{
					std::string loadedIngredient = Map::EnumToString(ingredient.nametag);    // convert enum to string
					//std::cout << "loading in " << loadedIngredient << "\n";

					// determine each ingredient location based on number of ingredient loaded
					switch (numOfLoadedIngredient)
					{
					case(1):
						//loading 1 ingredient
						loadedIngredients.insert({ loadedIngredient, {50.0f, 140.0f} });
						break;

					case(2):
						//loading 2 ingredients
						loadedIngredients.insert({ loadedIngredient, {50.0f + increment, 140.0f} });
						break;

					case(3):
						//loading 3 ingredients
						loadedIngredients.insert({ loadedIngredient, {50.0f + increment, 140.0f} });
						break;

						//******IMPT : need to expand on the case number if level contains more than 3 ingredients******//
					}
					increment += 100.0f;
				}

				// drawing of loaded ingredients using new positions
				for (auto& ingredient : loadedIngredients)
				{
					Core::Object::GameObject* obj2 = CoreSystem->objfactory->ObjectContainer.at(ingredient.first);
					Transform* transcomp2 = static_cast<Transform*>(obj2->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp2 = static_cast<Sprite*>(obj2->GetObjectProperties()->GetComponent(ComponentID::Renderer));

					spritecomp2->transformation.Position = { ingredient.second.x, ingredient.second.y };
					spritecomp2->transformation.Scale = transcomp2->Scale;

					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp2->transformation.Get());
					spritecomp2->draw();
				}

				/*if (isTut2)
				{
					Object::GameObject* x = CoreSystem->objfactory->ObjectContainer.at("QuestT2");

					Transform* transcomp = static_cast<Transform*>(x->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp = static_cast<Sprite*>(x->GetObjectProperties()->GetComponent(ComponentID::Renderer));

					spritecomp->transformation.Position = transcomp->Position;
					spritecomp->transformation.Scale = transcomp->Scale;
					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());

					spritecomp->draw();
					checkWin();
				}
				*/
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
				AudioManager.PlaySFX("Gravel_Drag-Movement_1.wav");
				isWalk = false;
			}

			if (isHowToPlay == true)
			{
				isMenuState = false; //disable menu buttons
				gameIsPaused = false;

				//SceneManager::loadHowToOverlay(0, 0);
				//std::cout << HowToPlayPage << "current page\n";
				SceneManager::drawHowToOverlay(HowToPlayPage);
				if (mouseLeft && isMenuState == false)
				{
					double xpos = 0, ypos = 0;
					glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
					//NEXT PAGE
					//std::cout << "clicking button at x: " << xpos << " and y: " << ypos << std::endl;

					if (HowToPlayPage < 4)
					{
						if (xpos > 1595 && xpos < 1681 && ypos > 811 && ypos < 889)
						{

							HowToPlayPage++;

							//std::cout << "next page" << std::endl;
							mouseLeft = false;
						}
					}
					//PREV PAGE 
					if (HowToPlayPage > 0)
					{
						if (xpos > 1474 && xpos < 1560 && ypos > 812 && ypos < 888)
						{

							HowToPlayPage--;

							//std::cout << "previous page" << std::endl;
							mouseLeft = false;
						}
					}


					//BACK

					if (xpos > 223 && xpos < 485 && ypos > 799 && ypos < 890)
					{

						isMenuState = true;
						HowToPlayPage = 0;
						isHowToPlay = false;

						//std::cout << "return to main menu" << std::endl;

					}


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
			fps++;
			delta = (endtime - starttime);
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
