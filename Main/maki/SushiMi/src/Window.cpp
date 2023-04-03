/*
File: Window.cpp
@author		louishetong.wang@digipen.edu 20%
co-Author:  thea.sea@digipen.edu 30%
co-Author:  Aurelia (fei.x@digipen.edu) 30%
co-Author:  w.chongsheng@digipen.edu  20%

Description: This file contains functions for the processes running in the Window 
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
#include "../Headers/Log.h"
#include "../Level State/LevelsHeader.h"
#include "../Engine/GameSave/GameSave.h"

namespace Core
{
	static Core::MainSystem* CoreSystem;
	std::ifstream fin;						// retrieve the current level dialogue file
	std::vector<Basket> CurrentIngredients; // retreive the current level loaded ingredients
	std::vector<std::pair< grid_number, wall_type>> stack;
	static bool keystate_fps = false;
	static std::string walkingsfx;
	std::vector<std::string> Window::currentQuestIngredient;
	std::array<std::pair<std::string, int>, 5> Window::winningBoxes;
	Window::GameState Window::level;
	bool isStartCutscenePlayed = false;
	std::map<std::string, gfxVector2> Window::questDrawItems;
	double lastframe = 0;
	static std::map<std::string, gfxVector2> chops;
	int screenwidth = 0, screenheight = 0;

	std::random_device dede;
	std::mt19937 gen(dede());
	std::uniform_int_distribution<int> dialogues(0, 4);
	/*																  game states
	----------------------------------------------------------------------------- */
	void mouseCallBack([[maybe_unused]] GLFWwindow* window_ptr, int button, int action, [[maybe_unused]] int mod)
	{
		if (GLFW_RELEASE == action)
		{
			Window::mouseLeft = false;
		}
		else if (GLFW_PRESS == action)
		{
			Window::mouseLeft = (button == GLFW_MOUSE_BUTTON_LEFT) ? true : false;
		}

	}

	std::string Window::GetDocumentsFolder()
	{
		char path[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, path)))
		{
			return std::string(path);
		}
		else
		{
			return "";
		}
	}

	/*					key  callback function  , helper function for controlling input
		----------------------------------------------------------------------------- */
	void keyCallBack([[maybe_unused]] GLFWwindow* window_ptr, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mod)
	{
		
		if (GLFW_RELEASE == action)
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
			Window::keystate_W = false;
			Window::keystate_D = false;
			Window::keystate_A = false;
			Window::keystate_S = false;
		}
		else if (GLFW_PRESS == action)
		{
			Window::keystate_M = (key == GLFW_KEY_M) ? true : false;
			Window::keystate_left = (key == GLFW_KEY_LEFT) ? true : false;
			Window::keystate_right = (key == GLFW_KEY_RIGHT) ? true : false;
			Window::keystate_up = (key == GLFW_KEY_UP) ? true : false;
			Window::keystate_down = (key == GLFW_KEY_DOWN) ? true : false;
			Window::keystate_R = (key == GLFW_KEY_R) ? true : false;

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
			Window::keystate_equal = (key == GLFW_KEY_EQUAL) ? true : false;	//cheat code

			Window::keystate_W = (key == GLFW_KEY_W) ? true : false;	//up
			Window::keystate_A = (key == GLFW_KEY_A) ? true : false;	//left
			Window::keystate_S = (key == GLFW_KEY_S) ? true : false;	//down
			Window::keystate_D = (key == GLFW_KEY_D) ? true : false;	//right
#ifndef RELEASE
			Window::keystate_T = (key == GLFW_KEY_T) ? true : false;

#endif // !RELEASE
		}
	}
	void Window::checkWin(std::string currentlevel)
	{
		std::vector<std::string> levelBoxes;
		//	load current level boxes for quest

		levelBoxes = Sprite::quest_boxes.at(currentlevel);

		//	checking through each ingredient loaded in the level
		for (auto& ingredient : Map::loadedIngredients) //loadedingredients does not contain mixed
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
					int state = checkCombination(ingredient.first, box.first, levelBoxes);

					for (size_t i{}; i < levelBoxes.size(); ++i)
					{
						std::size_t check = levelBoxes[i].find(ingredient.first);
						if (check != std::string::npos)
							winningBoxes[i] = { ingredient.first, state };
						//if (levelBoxes[i] == ingredient.first)
					}
				}
			}
		}
	}

	int Window::checkCombination(std::string ingredient, std::string box, std::vector<std::string> container)
	{
		std::size_t found = box.find(ingredient);	//	check base ingredient matches box

		if (found != std::string::npos)	//	if base ingredient matches box
		{
			//	check for special ingredient (salmon, tuna, roes, octopus)
			for (auto& x : container)
			{
				std::size_t check = x.find(ingredient);
				if (check != std::string::npos)
				{
					//	check special ingrdient for add on
					for (auto& _ingredient : SceneManager::ingredientcontainer)
					{
						std::size_t wasabi = x.find("Wasabi");
						std::size_t soya = x.find("Soya");
						std::size_t both = x.find("Both");

						if (!Map::maki_city)
						{
							if ((_ingredient.nametag == grid_number::octopus) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
								case 0:
								{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
								}
								case 1:
								{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 2:
								{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 3:
								{
									// added both
									if (both != std::string::npos)
										return 1;
									else
										return 0;
								}
								}
							}

							else if ((_ingredient.nametag == grid_number::salmon) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
								case 0:
								{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
								}
								case 1:
								{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 2:
								{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 3:
								{
									// added both
									if (both != std::string::npos)
										return 1;
									else
										return 0;
								}
								}

							}

							else if ((_ingredient.nametag == grid_number::tuna) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
								case 0:
								{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
								}
								case 1:
								{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 2:
								{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 3:
								{
									// added both
									if (both != std::string::npos)
										return 1;
									else
										return 0;
								}
								}

							}

							else if ((_ingredient.nametag == grid_number::roes) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
								case 0:
								{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
								}
								case 1:
								{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 2:
								{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 3:
								{
									// added both
									if (both != std::string::npos)
										return 1;
									else
										return 0;
								}
								}

							}
						}

						if(Map::maki_city)
						{
							if ((_ingredient.nametag == grid_number::corn) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
								case 0:
								{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
								}
								case 1:
								{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 2:
								{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
								}
								}
							}
							else if ((_ingredient.nametag == grid_number::inari) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
								case 0:
								{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
								}
								case 1:
								{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
								}

								case 2:
								{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
								}
								}
							}

							else if ((_ingredient.nametag == grid_number::avocado) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
								case 0:
								{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
								}
								case 1:
								{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
								}

								case 2:
								{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
								}
								}
							}
							else if ((_ingredient.nametag == grid_number::tuna) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
								case 0:
								{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
								}
								case 1:
								{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
								}
								case 2:
								{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
								}
								}
							}
							else if ((_ingredient.nametag == grid_number::roes) && (Map::IngredientToString(_ingredient.nametag) == ingredient))
							{
								switch (_ingredient.spr->status)
								{
									case 0:
									{
									if ((wasabi == std::string::npos) && (soya == std::string::npos) && (both == std::string::npos))
										return 1;
									else
										return 0;
									}
									case 1:
									{
									// added soya
									if (soya != std::string::npos)
										return 1;
									else
										return 0;
									}
								case 2:
									{
									// added wasabi
									if (wasabi != std::string::npos)
										return 1;
									else
										return 0;
									}
								}
							}

						}
					}
				}
			}
			return 1;
		}
		else
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
			case 3:
				chop = "done_4";
				break;
			case 4:
				chop = "done_5";
				break;
			}
			chops.insert({ chop, pos });
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
			case 3:
				chop = "denied_4";
				break;
			case 4:
				chop = "denied_5";
				break;
			}
			chops.insert({ chop, pos });
		}

	}


	void Window::resetQuest()
	{
		//reset quest tab
		Map::loadedIngredients.clear();
		Map::loadedBoxes.clear();

		for (size_t i{}; i < Window::winningBoxes.size(); ++i)
			winningBoxes[i] = { " ", -1 };

		questDrawItems.clear();
		chops.clear();
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
		levelprogress = 0;
		// Get the path to the Documents folder
		std::string documentsFolder = Window::GetDocumentsFolder();
		GameSave::LoadGameSave(documentsFolder + "/Data/LevelProgress/Gamesave.txt");
		//GameSave::SetAllGameSaveZero();
#ifdef EDITOR

		//the first level displayed on the map's launch
		Editor::LevelEditor::imguiloadedmap = "../TileMap/level1.txt";

#endif


		player = Core::Deserialize(*Core::LevelLoadPathPtr);
#ifndef EDITOR

		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		gameIsPaused = false;
		isMenuState = true;
		isEndingloaded = false;
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
		isDrawResetPrompt = false;
		loaded = false;
		HowToPlayPage = 0;
		areyousure_prompt = false;
		CutscenePage = 0;
#endif // !EDITOR

	}

	Window::~Window()
	{
		// Get the path to the Documents folder
		std::string documentsFolder = Window::GetDocumentsFolder();
		GameSave::WriteGameSave(documentsFolder + "/Data/LevelProgress/Gamesave.txt"); //Save Level Progress
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
		SceneManager::destroy_Particle();
		SceneManager::destroy_fading();
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
			AudioManager.StopMusic();
			setAllStatesFalse();
			isMenuState = true;
			isEndingloaded = false;
			SceneManager::num_dialogue_clicks = 0; //do not show dialogue in menu
			AudioManager.PlayMusic("BGM.ogg");
		}

		//Play End Cutscene
		if (keystate_P)
		{
			if (isEndingloaded == false) //clear screen for ending cutscene
			{
				keystate_T = true;
				isEndingloaded = true;
			}
			else
			{
				setAllStatesFalse();
				/*finallevelclear = true;*/
				isEndingCutscene = true;

				SceneManager::num_dialogue_clicks = 0; //do not show dialogue in end cutscene
				SceneManager::restartLevel();
				SceneManager::Ending_Cutscene->timer = 0;
				keystate_P = false;

			}
		}

		if (keystate_tab)
		{
			gameIsPaused = false; // if i press tab, isquestab(false) = true; off the tab state
			areyousure_prompt = false; // if i press tab again, isquestab(true) = false; off the tab state

			isQuestTab = !isQuestTab;
			keystate_tab = false;
		}

		if (keystate_J)
		{
			std::cout << "you have loaded test level for debugging" << std::endl;
			setAllStatesFalse();
			isTestLevel = true;
			SceneManager::restartLevel();
			keystate_J = false;
		}
		if (keystate_K)
		{
			std::cout << "you have loaded tutorial 1" << std::endl;
			setAllStatesFalse();
			isTut1 = true;
			SceneManager::restartLevel();
			keystate_K = false;
		}
		if (keystate_L)
		{
			std::cout << "you have loaded tutorial 2" << std::endl;
			setAllStatesFalse();
			isTut2 = true;
			SceneManager::restartLevel();
			keystate_L = false;
		}
		if (keystate_1)
		{
			std::cout << "you have loaded level 1" << std::endl;
			setAllStatesFalse();
			isLevel1 = true;
			SceneManager::restartLevel();
			keystate_1 = false;
		}
		if (keystate_2)
		{
			std::cout << "you have loaded level 2" << std::endl;
			setAllStatesFalse();
			isLevel2 = true;
			SceneManager::restartLevel();
			keystate_2 = false;
		}
		if (keystate_3)
		{
			std::cout << "you have loaded level 3" << std::endl;
			setAllStatesFalse();
			isLevel3 = true;
			SceneManager::restartLevel();
			keystate_3 = false;
		}
		if (keystate_4)
		{
			std::cout << "you have loaded level 4" << std::endl;
			setAllStatesFalse();
			isLevel4 = true;
			SceneManager::restartLevel();
			keystate_4 = false;
		}
		if (keystate_5)
		{
			std::cout << "you have loaded level 5" << std::endl;
			setAllStatesFalse();
			isLevel5 = true;
			SceneManager::restartLevel();
			keystate_5 = false;
		}
		if (keystate_6)
		{
			std::cout << "you have loaded level 6" << std::endl;
			setAllStatesFalse();
			isLevel6 = true;
			SceneManager::restartLevel();
			keystate_6 = false;
		}
		if (keystate_7)
		{
			std::cout << "you have loaded level 7" << std::endl;
			setAllStatesFalse();
			isLevel7 = true;
			SceneManager::restartLevel();
			keystate_7 = false;
		}
		if (keystate_8)
		{
			std::cout << "you have loaded level 8" << std::endl;
			setAllStatesFalse();
			isLevel8 = true;  
			SceneManager::restartLevel();
			keystate_8 = false;

		}
		if (keystate_9)
		{
			std::cout << "you have loaded level 9" << std::endl;
			setAllStatesFalse();
			isLevel9 = true;
			SceneManager::restartLevel();
			keystate_9 = false;

		}
		if (keystate_0)
		{
			std::cout << "you have loaded level 10" << std::endl;
			setAllStatesFalse();
			isLevel10 = true;
			SceneManager::restartLevel();
			keystate_0 = false;
		}
		if (keystate_minus)
		{
			std::cout << "you have loaded level 11" << std::endl;
			setAllStatesFalse();
			isLevel11 = true;
			SceneManager::restartLevel();
			keystate_minus = false;
			
		}
		if (keystate_equal)
		{
			std::cout << "cheating..." << std::endl;
			isWinCondition = true;
			keystate_equal = false;
		}
		if (keystate_T)
		{
			std::cout << "you are in level selection screen" << std::endl;
			setAllStatesFalse();
			isLevelSelection = true;
			SceneManager::restartLevel();
			keystate_T = false;
		}

		if (keystate_escape && gameIsPaused)
		{
			areyousure_prompt = false;
		}
		if (keystate_escape && (isTut1 || isTut2 || isLevel1 || isLevel2 || isLevel3 || isLevel4 || isLevel5 || isLevel6 || isLevel7 || isLevel8 || isLevel9 || isLevel10 || isLevel11 || isTestLevel) && isDialogue == false && isHowToPlay == false)
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
				if (isStartCutscenePlayed == false)
				{
				isCutscene = true;
				}
				else
				{
					isLevelSelection = true;
				}
				mouseLeft = false;
			}
			//HOW TO PLAY
			if (static_cast<int>(xpos) > 275 && static_cast<int>(xpos) < (275 + 266) && static_cast<int>(ypos) > 520 && static_cast<int>(ypos) < (520 + 96))
			{
				isHowToPlay = true;
				mouseLeft = false;
			}
			//SETTINGS
			if (static_cast<int>(xpos) > 275 && static_cast<int>(xpos) < (275 + 266) && static_cast<int>(ypos) > 700 && static_cast<int>(ypos) < (700 + 96))
			{
				isSettings = true;
				mouseLeft = false;
			}
			//MENU BUTTON - QUIT, reference ExitButton.json
			if (static_cast<int>(xpos) > 275 && static_cast<int>(xpos) < (275 + 266) && static_cast<int>(ypos) > 890 && static_cast<int>(ypos) < (890 + 96))
			{
				areyousure_prompt = true;
				mouseLeft = false;
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
					//Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Transform* transcomp = x.second->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
					gfxVector2 position = { transcomp->Position.x, transcomp->Position.y };
					gfxVector2 scale = { transcomp->Scale.x, transcomp->Scale.y };

					//RESUME THE GAME BUTTON
					if (((float)xpos > position.x) &&
						((float)ypos > position.y) &&
						((float)xpos < (position.x + scale.x)) &&
						((float)ypos < (position.y + scale.y)))
					{
						gameIsPaused = false;
						mouseLeft = false;
					}
				}
				else if (x.first == "HowToPlay1")
				{
					Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform));
					gfxVector2 position = { transcomp->Position.x, transcomp->Position.y };
					gfxVector2 scale = { transcomp->Scale.x, transcomp->Scale.y };

					//RESUME THE GAME BUTTON
					if (((float)xpos > position.x) &&
						((float)ypos > position.y) &&
						((float)xpos < (position.x + scale.x)) &&
						((float)ypos < (position.y + scale.y)))
					{
						if (!keystate_escape)
							isHowToPlay = true;
						mouseLeft = false;
					}
				}
				else if (x.first == "MenuButton")
				{
					//Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Transform* transcomp = x.second->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
					gfxVector2 position = { transcomp->Position.x, transcomp->Position.y };
					gfxVector2 scale = { transcomp->Scale.x, transcomp->Scale.y };

					//Level Selection
					if (((float)xpos > position.x) &&
						((float)ypos > position.y) &&
						((float)xpos < (position.x + scale.x)) &&
						((float)ypos < (position.y + scale.y)))
					{

						keystate_T = true;
						mouseLeft = false;
					}
				}
				else if (x.first == "QuitButton")
				{
					
					Transform* transcomp = x.second->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
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
		}
		
		
		if ((keystate_right || keystate_D) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false && isEndingCutscene == false)
		{
		
			if (keystate_right || keystate_D)
			{
				Map::collision_check_right();
				Map::print_map_to_console();
				AudioManager.PlaySFX(walkingsfx);
				keystate_right = false;
				keystate_D = false;
				SceneManager::up_key = false;
				SceneManager::down_key = false;
				SceneManager::left_key = false;
				SceneManager::right_key = true;
			}
		}

		else if ((keystate_left || keystate_A) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false && isEndingCutscene == false)
		{
	
			//player only move on one press
			//holding key or let go key, player stop
			if (keystate_left || keystate_A)
			{
				Map::collision_check_left();
				Map::print_map_to_console();
				AudioManager.PlaySFX(walkingsfx);
				keystate_left = false;
				keystate_A = false;
				SceneManager::up_key = false;
				SceneManager::down_key = false;
				SceneManager::left_key = true;
				SceneManager::right_key = false;
			}
		}

		else if ((keystate_up || keystate_W) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false && isEndingCutscene == false)
		{
		
			if (keystate_up || keystate_W)
			{
				Map::collision_check_up();
				Map::print_map_to_console();
				AudioManager.PlaySFX(walkingsfx);
				keystate_up = false;
				keystate_W = false;
				SceneManager::up_key = true;
				SceneManager::down_key = false;
				SceneManager::left_key = false;
				SceneManager::right_key = false;

			}
		}

		else if ((keystate_down || keystate_S) && gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false && isEndingCutscene == false)
		{

			if (keystate_down || keystate_S)
			{
				Map::collision_check_down();
				Map::print_map_to_console();
				AudioManager.PlaySFX(walkingsfx);

				keystate_down = false;
				keystate_S = false;
				SceneManager::up_key = false;
				SceneManager::down_key = true;
				SceneManager::left_key = false;
				SceneManager::right_key = false;
			}
		}

		/***************************
			restart key "R" resets the level
		*******************************/
		if (keystate_R && (gameIsPaused == false && isWinCondition == false)) 
		{
			isDrawResetPrompt = false;
			transparent = 0.f;

			if (keystate_R)
			{
				Window::player->resetCount++;
				if (Window::player->resetCount == 1)
					AudioManager.PlayVoice("Dialogue_1.ogg");
				if (Window::player->resetCount == 2)
					AudioManager.PlayVoice("Dialogue_2.ogg");
				if (Window::player->resetCount == 3)
					AudioManager.PlayVoice("Dialogue_3.ogg");
				if (Window::player->resetCount == 4)
					AudioManager.PlayVoice("Dialogue_4.ogg");
				if (Window::player->resetCount >= 5)
					AudioManager.PlayVoice("Dialogue_5.ogg");
				//restart

				//reset quest tab
				for (size_t i{}; i < Window::winningBoxes.size(); ++i)
					winningBoxes[i] = { " ", -1 };
				questDrawItems.clear();
				chops.clear();
				SceneManager::resetColor();

				Map::RestartMap();
				std::cout << "restarting level" << std::endl;
				std::cout << "player is moved back to x: " << player->playerpos_restart.x << " and y: " << player->playerpos_restart.y << std::endl;
				SceneManager::r_key = true;
				keystate_R = false;
			}

		}
		if ((keystate_down || keystate_up || keystate_left || keystate_right) && !gameIsPaused == false && isWinCondition == false && isMenuState == false && isDialogue == false && isHowToPlay == false)
			player->stop();

#endif //editor
	}

	void Window::Init()
	{
		//retrieve
		auto* objFact = ObjectFactory::GetInstance();
		auto* obj = objFact->ObjectContainer["map"];
		auto objProp = obj->GetObjectProperties();
		//load map image
		SceneManager::level_select = objProp->GetComponent<Sprite>(ComponentID::Renderer);

		SceneManager::settings_page = new Sprite("../textures/Settings/settings.png");
		SceneManager::credits_page = new Sprite("../textures/Credits/NEWCreditsRoll.png");
		

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
		SceneManager::fader = new Sprite("../textures/bg.jpg");
		SceneManager::fader->alpha = 0.f;
		SceneManager::fader->timer = 0.f;
		SceneManager::Ending_Cutscene = new Sprite("../textures/Cutscene/Ending/EndingScene.png");
		SceneManager::Ending_Cutscene->isSpriteSheet = 0;
		SceneManager::Ending_Cutscene->Add_animation("../textures/Cutscene/Ending/Bami_End.txt");
		SceneManager::Ending_Cutscene->curr_anim = AnimationType::Idle;
		SceneManager::Ending_Cutscene->timer = 0;

		SceneManager::are_you_sure = new Sprite("../textures/UI/AREYOUSURE.png"); //confirmation page
		SceneManager::particle = new Sprite("../textures/Bami/RiceParticle/particlespritesheet.png");
		SceneManager::particle->isSpriteSheet = 0;
		SceneManager::particle->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
		SceneManager::particle->curr_anim = AnimationType::Idle;
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
			int focused = glfwGetWindowAttrib(window_ptr, GLFW_FOCUSED);

			std::cout << focused << std::endl;
			if (focused == 0)
			{
				AudioManager.SetMusicVolume(0);
			}
			else
			{
				AudioManager.SetMusicVolume(1);
			}
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
			else if (!isEndingCutscene)
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

			Shaders->Textured_Shader()->Send_Mat4("projection", camera->Get_Projection());

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

		
#ifndef EDITOR



			if (isCutscene)
			{
				/*SceneManager::loadCutscene();*/
				isStartCutscenePlayed = true;
				SceneManager::drawCutscene(CutscenePage);

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

			if (isTut1 == true) { level = GameState::TUT1; Levels::Tutorial1(); AudioManager.RandomWalking(walkingsfx, 0); }
			if (isTut2 == true) { level = GameState::TUT2;  Levels::Tutorial2(); AudioManager.RandomWalking(walkingsfx, 0); }
			if (isLevel1 == true) { level = GameState::LEVEL1;  Levels::Level1(); AudioManager.RandomWalking(walkingsfx, 0); }
			if (isLevel2 == true) { level = GameState::LEVEL2; Levels::Level2(); AudioManager.RandomWalking(walkingsfx, 0); }
			if (isLevel3 == true) { level = GameState::LEVEL3; Levels::Level3(); AudioManager.RandomWalking(walkingsfx, 0); }
			if (isLevel4 == true) { level = GameState::LEVEL4; Levels::Level4(); AudioManager.RandomWalking(walkingsfx, 2); }
			if (isLevel5 == true) { level = GameState::LEVEL5; Levels::Level5(); AudioManager.RandomWalking(walkingsfx, 2); }
			if (isLevel6 == true) { level = GameState::LEVEL6; Levels::Level6(); AudioManager.RandomWalking(walkingsfx, 2); }
			if (isLevel7 == true) { level = GameState::LEVEL7; Levels::Level7(); AudioManager.RandomWalking(walkingsfx, 1); }
			if (isLevel8 == true) { level = GameState::LEVEL8; Levels::Level8(); AudioManager.RandomWalking(walkingsfx, 1); }
			if (isLevel9 == true) { level = GameState::LEVEL9; Levels::Level9(); AudioManager.RandomWalking(walkingsfx, 1); }
			if (isLevel10 == true) { level = GameState::LEVEL10; Levels::Level10(); AudioManager.RandomWalking(walkingsfx, 1); }
			if (isLevel11 == true) { level = GameState::LEVEL11; Levels::Level11(); AudioManager.RandomWalking(walkingsfx, 1); }
			if (isTestLevel == true) { Levels::TestLevel(); }

			/**********************************
				DIALOGUE DISPLAY (riceplain)
			*************************************/
			if (isDialogue)
			{
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
							curr_len += 1; 
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
							curr_len += 1; 
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
						Font::RenderText(*Shaders, first_line, screenwidth * 0.34f, screenheight * 0.19f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);
						Font::RenderText(*Shaders, second_line, screenwidth * 0.34f, screenheight * 0.14f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);
						Font::RenderText(*Shaders, third_line, screenwidth * 0.34f, screenheight * 0.09f, .6f, glm::vec3(0.f, 0.f, 0.f), 1.f);
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
				for (auto& x : CoreSystem->objfactory->ObjectContainer)
				{
					/*Transform* transcomp = static_cast<Transform*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Transform));
					Sprite* spritecomp = static_cast<Sprite*>(x.second->GetObjectProperties()->GetComponent(ComponentID::Renderer));*/
					Transform* transcomp = x.second->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
					Sprite* spritecomp = x.second->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

					spritecomp->transformation.Position = transcomp->Position;
					if (x.first == "Menu")
					{
						glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
						spritecomp->transformation.Scale = glm::vec2(screenwidth, screenheight);
					}
					else
						spritecomp->transformation.Scale = transcomp->Scale;

					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());
					Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);

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
					Transform* transcomp = x.second->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
					Sprite* spritecomp = x.second->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

					spritecomp->transformation.Position = transcomp->Position;
					spritecomp->transformation.Scale = transcomp->Scale;

					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp->transformation.Get());
					Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
					if (x.first == "PauseMenu")
						spritecomp->draw();

					if (x.first == "ResumeButton")
						spritecomp->draw();

					if (x.first == "HowToPlay1")
						spritecomp->draw();

					if (x.first == "QuitButton")
						spritecomp->draw();

					if (x.first == "MenuButton")
						spritecomp->draw();
				}
			}

			/*Draw QuestTab*/
			gfxVector2 pos1, pos2, pos3, pos4, pos5;
			/*If quest tab is loaded, check what are the ingredients loaded for the level*/
			if (isQuestTab && !gameIsPaused && !isMenuState && !isDialogue && !isCutscene && !isLevelSelection)
			{
				if (!Map::maki_city)
				{
					//	fixed position for quest items and chop (shld only work tut1 - lvl10
					pos1 = { 50.f, 140.f }, pos2 = { 150.f, 140.f }, pos3 = { 250.f, 140.f };
				}
				else
				{
					pos1 = { 38.f, 145.f }, pos2 = { 185.f, 145.f }, pos3 = { 335.f, 145.f }, pos4 = { 80.f, 245.f }, pos5 = { 280.f, 245.f };
				}

				//	current level
				std::string sLevel = EnumToString(level);
				//	check if ingredient landed on box
				checkWin(sLevel);
				if (!Map::maki_city)
				{
					if(isTut2)
					{
						Core::Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at("quest_tut2");
						Transform* transcomp1 = obj1->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
						Sprite* spritecomp1 = obj1->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);
						spritecomp1->transformation.Position = transcomp1->Position;
						spritecomp1->transformation.Scale = transcomp1->Scale;
						Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
						Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
						spritecomp1->draw();
					}
					else
					{
						Core::Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at("questBase");
						Transform* transcomp1 = obj1->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
						Sprite* spritecomp1 = obj1->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);
						spritecomp1->transformation.Position = transcomp1->Position;
						spritecomp1->transformation.Scale = transcomp1->Scale;
						Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
						Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
						spritecomp1->draw();
					}
					
				}
				else //if(Map::maki_city)
				{
					Core::Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at("makicity");
					Transform* transcomp1 = obj1->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
					Sprite* spritecomp1 = obj1->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

					spritecomp1->transformation.Position = transcomp1->Position;
					spritecomp1->transformation.Scale = transcomp1->Scale * 1.25f;
					Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
					spritecomp1->draw();
				}
				// draw level indicator
				if (isTut1 || isTut2 || isLevel1 || isLevel2 || isLevel3 || isLevel4 || isLevel5 || isLevel6 || isLevel7 || isLevel8 || isLevel9 || isLevel10 || isLevel11)
				{
					if (!isDialogue)
					{
						Core::Object::GameObject* obj1 = nullptr;
						if (isTut1)
						{
							SceneManager::drawTut1();
							obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateT1");
						}
						else if (isTut2)
						{
							SceneManager::drawTut2();
							obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateT2");
						}
						else if (isLevel1) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL1"); }
						else if (isLevel2) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL2"); }
						else if (isLevel3) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL3"); }
						else if (isLevel4) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL4"); }
						else if (isLevel5) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL5"); }
						else if (isLevel6) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL6"); }
						else if (isLevel7) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL7"); }
						else if (isLevel8) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL8"); }
						else if (isLevel9) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL9"); }
						else if (isLevel10) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL10"); }
						else if (isLevel11) { obj1 = CoreSystem->objfactory->ObjectContainer.at("IndicateL11"); }

						Sprite* spritecomp1 = obj1->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

						spritecomp1->transformation.Position = glm::vec2(screenwidth * 0.78f, screenheight * 0.88f);
						spritecomp1->transformation.Scale = glm::vec2((405 * screenwidth) / 1920, (126 * screenheight) / 1080);
						Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
						Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
						spritecomp1->draw();
					}
				}
				

				auto checkifquestexists = Sprite::quest_boxes.find(sLevel);
				if (checkifquestexists != Sprite::quest_boxes.end()) 
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
						case 3:
							questDrawItems.insert({ currentQuestIngredient[i] , pos4 });
							updateChop(i, pos4);
							break;

						case 4:
							questDrawItems.insert({ currentQuestIngredient[i] , pos5 });
							updateChop(i, pos5);
							break;

						default:
							break;
						}
					}

				}

				//	draw ingredients and chops
				for (auto& [name, position] : questDrawItems)
				{
					//check if what you are accessing exists so it does not throw exception
						Object::GameObject* obj2 = CoreSystem->objfactory->ObjectContainer.at(name);
						Sprite* spritecomp2 = obj2->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

						spritecomp2->transformation.Position = { position.x, position.y };
						//Shaders->Textured_Shader()->use();
						Shaders->Textured_Shader()->Send_Alpha("alpha", 1.0f);
						if (Map::maki_city)
						{
							//turn off texture for ingredients in makicity
							Shaders->Textured_Shader()->Send_Alpha("alpha", 0.f); 
						}
						Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp2->transformation.Get());
						spritecomp2->draw();
				}

				for (auto& [name, position] : chops)
				{
					Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at(name);
					
					Sprite* spritecomp1 = obj1->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

					spritecomp1->transformation.Position = { position.x, position.y };
					//Shaders->Textured_Shader()->use();
					Shaders->Textured_Shader()->Send_Alpha("alpha", 1.0f);
					Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
					spritecomp1->draw();
				}
			}
			
			/*	quest tab shift to left side */
			/*	disable quest tab in all the listed cases in the else-if condition	*/
			/*	so that quest tab will only shown in levels	*/
			else if (!isWinCondition && !gameIsPaused && !isMenuState && !isDialogue && !isCutscene && !isLevelSelection && !isHowToPlay)
			{
				Core::Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at("questBase");

				Transform* transcomp1 = obj1->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
				Sprite* spritecomp1 = obj1->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);


				spritecomp1->transformation.Position = { transcomp1->Position.x - 387.f, transcomp1->Position.y };
				spritecomp1->transformation.Scale = transcomp1->Scale;

				Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
				Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
				spritecomp1->draw();
			}

			if (isWalk == true)
			{
				AudioManager.PlaySFX("Gravel_Drag-Movement_1.ogg");
				isWalk = false;
			}

			if (isHowToPlay == true)
			{
				glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
				double xpos = 0, ypos = 0;

				glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
				//std::cout << "X percentage: " << xpos / screenwidth * 100 << " " << "Y percentage: " << ypos / screenheight * 100 << std::endl;

				isMenuState = false; //disable menu buttons
			
				isQuestTab = false;

				//SceneManager::loadHowToOverlay(0, 0);
				//std::cout << HowToPlayPage << "current page\n";
				SceneManager::drawHowToOverlay(HowToPlayPage);
				if (mouseLeft)
				{
					if (xpos > screenwidth * 0.11f && xpos < screenwidth * 0.25f && ypos > screenheight * 0.78f && ypos < screenheight * 0.88f)
					{
						isHowToPlay = false;
						if (!isTut1 && !isTut2 && !isLevel1 && !isLevel2 && !isLevel3 && !isLevel4 && !isLevel5 && !isLevel6 && !isLevel7 && !isLevel8 && !isLevel9 && !isLevel10 && !isLevel11 && !isTestLevel)
							isMenuState = true;
						HowToPlayPage = 0;
						mouseLeft = false;
					}
					else if (xpos > screenwidth * 0.84f && xpos < screenwidth * 0.91f && ypos > screenheight * 0.78f && ypos < screenheight * 0.88f)
					{
						if (HowToPlayPage < 5)
						{
							HowToPlayPage++;
						}
						mouseLeft = false;
					}
					else if (xpos > screenwidth * 0.75f && xpos < screenwidth * 0.82f && ypos > screenheight * 0.78f && ypos < screenheight * 0.88f)
					{
						//PREV PAGE 
						if (HowToPlayPage > 0)
						{
							HowToPlayPage--;
						}
						mouseLeft = false;
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
					glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
					double xpos = 0, ypos = 0;
					
					glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
					//volume up setting 
					if (xpos > screenwidth * 0.61f && xpos < screenwidth * 0.65f && ypos > screenheight * 0.41f && ypos < screenheight * 0.49f)
					{
						AudioManager.IncreaseMusicVolume();
						AudioManager.IncreaseSFXVolume();
						AudioManager.IncreaseVoiceVolume();
						mouseLeft = false;
					}

					//volume down setting
					if (xpos > screenwidth * 0.54f && xpos < screenwidth * 0.60f && ypos > screenheight * 0.41f && ypos < screenheight * 0.49f)
					{
						AudioManager.DecreaseMusicVolume();
						AudioManager.DecreaseSFXVolume();
						AudioManager.DecreaseVoiceVolume();
						mouseLeft = false;
					}
					//PRESS CREDITS
					if (xpos > screenwidth * 0.42f && xpos < screenwidth * 0.55f && ypos > screenheight * 0.51f && ypos < screenheight * 0.59f)
					{
						isCredits = true;
						mouseLeft = false;
					}
					//PRESS BACK
					if (xpos > screenwidth * 0.42f && xpos < screenwidth * 0.55f && ypos > screenheight * 0.61f && ypos < screenheight * 0.69f)
					{
						isSettings = false;
						mouseLeft = false;
					}
				}
			}

			if (isDrawResetPrompt == true)
			{
				//draw reset overlay
				Core::Object::GameObject* obj1 = CoreSystem->objfactory->ObjectContainer.at("reset_overlay");
				Transform* transcomp1 = obj1->GetObjectProperties()->GetComponent<Transform>(ComponentID::Transform);
				Sprite* spritecomp1 = obj1->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);

				spritecomp1->transformation.Position = transcomp1->Position;
				spritecomp1->transformation.Scale = transcomp1->Scale;
				
				Shaders->Textured_Shader()->Send_Alpha("alpha", transparent);
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", spritecomp1->transformation.Get());
				spritecomp1->draw();
				if (transparent < 1.0f)
				{
					transparent += getDelta();
				}
				

			}

			if (isEndingCutscene == true)
			{
				SceneManager::load_Bami_End_Room();
				lastframe = 0;

				if (SceneManager::Ending_Cutscene->timer < 14.8f) //if count equals the number of frames animated (the number of times draw is called)
				{
					SceneManager::draw_Bami_End_Room();
					SceneManager::Ending_Cutscene->timer += Get_Delta();
					lastframe = Get_Delta();
				}
				else
				{
					Shaders->Textured_Shader()->Send_Mat4("model_matrx", SceneManager::Ending_Cutscene->transformation.Get());
					SceneManager::Ending_Cutscene->draw(lastframe, SceneManager::Ending_Cutscene->curr_anim);
				}
			}

			if (isCredits == true)
			{
				if (keystate_escape)
				{
					isCredits = false;
				}
			}
			if (finallevelclear)
			{
				isEndingCutscene = true;
			}

			if (isLevelSelection)
			{
				setAllStatesFalse();
				isLevelSelection = true;
				SceneManager::loadLevelSelect(0, 0);
				SceneManager::drawLevelSelect();
				Levels::LevelSelect();
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
	}
}

