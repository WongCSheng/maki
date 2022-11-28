#pragma once

class Sprite;
enum AnimationType;
struct fakemat4;
class Player
{
public:
	Player();

	~Player();

	void move_left();

	void move_right();


	void stop();

	fakemat4* Transformation();

	void draw(double deltatime);


private:
	Sprite* sp;
	AnimationType* current_anim;
};