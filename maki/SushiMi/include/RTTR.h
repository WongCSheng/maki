#pragma once
//need to include your rttr file
#include <rttr/type>

struct vec3
{
	float x = 0;
	float y = 0;
	float z = 0;
};
class DemoClass
{
public://methods
	DemoClass();
	~DemoClass();
	vec3 GetPosition();
	void SetPosition(vec3 pos);
public://variables
	int health = 0;
	int damage = 0;
	//need to declare your rttr macro here in public
	RTTR_ENABLE();
private://variables
	vec3 position;

};