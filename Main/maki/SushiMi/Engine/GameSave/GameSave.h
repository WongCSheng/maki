/*!*****************************************************************************

\file       GameSave.h
\author     Thea Sea (100%)
\par        DP email: thea.sea@digipen.edu
\date       24-03-2023

\brief
This program implements a Game Save File

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/

#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream> //for stringstream

namespace Core
{
	
	struct LevelStatus {
	
		std::string LevelStat_Lvl;
		int isUnlocked;
		int isLevelClear;
		int isQuestClear;
	};

	class GameSave {
	public:

		/*LevelStatus level_status;*/
		static inline LevelStatus T1, T2, L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11;
		static inline std::vector<LevelStatus> LevelStatusContainer;
		

		static inline void SetAllGameSaveZero() {
		
			for (auto it : LevelStatusContainer)
			{
				
				it.isUnlocked = 0;
				it.isLevelClear = 0;
				it.isQuestClear = 0;
				
			}
		}

		//sets the level status container from a game save file
		static inline void LoadGameSave(std::string filepath)
		{
			std::ifstream ifs(filepath);

			if (!ifs.is_open())
			{
				std::cout << "unable to read game save!" << std::endl;
			}

			//ignore first & second line
			ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::string checklvlstatus;
			while (getline(ifs, checklvlstatus))
			{
				std::istringstream line_sstm{ checklvlstatus };
				LevelStatus it;
				line_sstm >> it.LevelStat_Lvl;
				line_sstm >> it.isUnlocked;
				line_sstm >> it.isLevelClear;
				line_sstm >> it.isQuestClear;
				std::cout << "Unlock: " << it.isUnlocked << " Level Clear: " << it.isLevelClear << " Quest Clear: " << it.isQuestClear << std::endl;
				LevelStatusContainer.push_back(it);

			}
			ifs.close();
		}

		//write the game progress into a text file
		static inline void WriteGameSave(std::string filepath)
		{
			std::ofstream ofs(filepath);

			if (!ofs.is_open())
			{
				std::cout << "unable to write game save!" << std::endl;
			}

			ofs << "	Unlock Status | Level Clear | Quest Clear" << std::endl;
			ofs << "	   Lock		  |	  Crown		|	Star" << std::endl;

			for (auto it : LevelStatusContainer)
			{
				ofs << it.LevelStat_Lvl << "		" << it.isUnlocked << "				" << it.isLevelClear << "			" << it.isQuestClear << std::endl;
				//std::cout << it.isUnlocked << " " << it.isLevelClear << " " << it.isQuestClear << std::endl;
				//std::cout << "Unlock: " << it.isUnlocked << " Level Clear: " << it.isLevelClear << " Quest Clear: " << it.isQuestClear << std::endl;

			}

			ofs.close();
		}
		
	};

}