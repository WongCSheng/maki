#pragma once

#include "../../glm/glm/glm.hpp"
class Sprite;
enum AnimationType;
class Player
{
public:
	Player();

	~Player();

	void move_left();

	void move_right();


	void stop();

	glm::mat4 Transformation();

	void draw(double deltatime);


private:
	Sprite* sp;
	AnimationType* current_anim;
};