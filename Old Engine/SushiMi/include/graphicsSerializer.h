/*!************************************
\file		graphicsSerializer.cpp
\author		thea.sea, thea.sea@digipen.edu (for graphics object serializing)
\co-author	aurelia.chong (for AABB calculations)
\brief		function to initialize the graphics scene from a .txt file
**************************************/
#pragma once

class Scene
{
public:
	static void sceneInitializer(std::string scene_filename);
	static std::vector<std::string> ObjVector;
	static std::vector<const char*> objectString;
	
};
