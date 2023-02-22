/*

\file		Player.h
\author		louishetong.wang@digipen.edu
\co-author	thea.sea@digipen.edu
\brief		file to control player movement
*/
#pragma once

#include "../Engine/Texture/Sprite.h"
#include <string>
#include <vector>
class Player
{
public:
	Player();
	Player(const char* spriteFilepath, float* spritePos, float* spriteScale, std::vector<std::string> const& animationList);

	~Player();

	void move_left();

	void move_right();

	void move_up();

	void move_down();


	void stop();

	glm::mat4 Transformation();

	void draw(double deltatime);

	static inline struct PlayerSavedPos {
		static inline int x;
		static inline int y;
	};

	static inline struct PlayerSavedPos playerpos;
	static inline struct PlayerSavedPos* playerptr = &playerpos;

private:
	Sprite* sp;
	AnimationType current_anim;
};