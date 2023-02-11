/*!
@file		JSONSerializer.cpp
@author		Chong Rui Xuan Aurelia
@par		fei.x@digipen.edu
@date		6/1/2022

			This is header file for JSONSerializer.cpp

*//*__________________________________________________________________________*/

#pragma once
#include "../Headers/STL_Header.h"
#include "../Headers/RapidJSON_Header.h"
#include "../Editors/LevelEditor.h"
#include "../Editors/imfilebrowser.h"

//#include "../Game Object/object.h"


#ifndef JSERIALIZE_H
#define JSERIALIZE_H

#include "../Game Object/Player.h"
#include <string>
#include <rapidjson.h>

namespace Core
{
	// Calling of these 2 functions are inside Window.cpp's Window(int, int) function
	Player* Deserialize(std::string const& filepath);
	static inline std::string LevelLoadPath;
	static inline std::string* LevelLoadPathPtr = &LevelLoadPath;
	void DeserializeEntity(std::string const& filepath, ObjectFactory* objfact);
	void Serialize(const Player& player, std::string const& filepath);
	static inline std::string LevelSavePath;
	static inline std::string* LevelSavePathPtr = &LevelSavePath;
	
	static Transform* transComp;
}

#endif