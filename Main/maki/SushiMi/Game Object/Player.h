/*

\file		Player.h
\author		louishetong.wang@digipen.edu
\co-author	thea.sea@digipen.edu
\brief		file to control player movement
*/
#pragma once

#include "../Engine/Components/Texture/Sprite.h"
#include <string>
#include <vector>

namespace Core
{
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
		void restart();

		void stop();

		glm::mat4 Transformation();

		void draw(double deltatime);

		static inline struct PlayerSavedPos {
			int x;
			int y;
		} playerpos;

		static inline struct PlayerInitialPos {
			int x;
			int y;
		} playerpos_restart;

	private:
		Sprite* sp;
		AnimationType current_anim;
	};
}
