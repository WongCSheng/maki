#pragma once
#include "../include/common_headers.hpp"
#include "../../../lib/stb-master/stb_image.h"
#include "../../include/glhelper.h"
#include "../../include/glapp.h"
#include "../Texture.h"
#include "../System/Rectangle.h"

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

	std::vector<glm::vec4> frames;
};