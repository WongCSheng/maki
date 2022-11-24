#pragma once
#include "../Engine/Texture/Texture.h"
#include "../Engine/Texture/Rectangle.h"
#include <../glm/glm/glm.hpp>
#include <vector>
using namespace std;


enum AnimationType
{
	Idle,
	Run,
	Jump
};

class Animation2D
{
public:
	Animation2D(const char* filename);

	~Animation2D();


	void play(Texture& spritetexture, Rect& rectangle, double deltatime);

	void set_animation_speed(float newspeed);


private:
	double anim_cursor;
	int current_frame_indx;
	int frames_count;
	float speed;

	vector<glm::vec4> frames;
};