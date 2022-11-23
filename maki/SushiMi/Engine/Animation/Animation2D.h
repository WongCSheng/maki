#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../../lib/stb-master/stb_image.h"
#include <iostream>
#include "../Engine/Animation/Rectangle.h"
#include "../include/texture.h"

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
