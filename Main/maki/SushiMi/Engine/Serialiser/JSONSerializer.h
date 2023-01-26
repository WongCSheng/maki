/*!
@file		JSONSerializer.h
@author		fei.x@digipen.edu
@date		06/01/2022

This file contains a Serializer class that can parse json files.
You can choose to print to console or directly deserialize into your
chosen game object.

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
#include <rapidJSON/document.h>

namespace Core
{
		// Calling of these 2 functions are inside Window.cpp's Window(int, int) function
	Player* Deserialize(std::string const& filepath);
	static inline std::string LevelLoadPath;
	static inline std::string* LevelLoadPathPtr = &LevelLoadPath;
	void DeserializeEntity(std::string const& filepath, std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
	void Serialize(const Player& player, std::string const& filepath);
	static inline std::string LevelSavePath;
	static inline std::string* LevelSavePathPtr = &LevelSavePath;
	
	static Transform* transComp;
}

#endif