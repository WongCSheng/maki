#pragma once
#include "../include/texture.h"
#include "../Engine/Animation/Rectangle.h"
#include <glm/glm/glm.hpp>
#include <vector>

using namespace std;


enum AnimationType
{
	Idle,
	Run
};

class Animation2D
{
public:
	Animation2D(const char* filename);

	~Animation2D();


	void play(Texture& spritetexture, Rectangle& rectangle, double deltatime);

	void set_animation_speed(float newspeed);


private:
	double anim_cursor;
	int current_frame_indx;
	int frames_count;
	float speed;

	vector<glm::vec4> frames;
};
