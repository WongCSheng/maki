#pragma once
#ifndef RTTR_H
#define RTTR_H

class TestClass
{
public://methods
	TestClass();
	~TestClass();
public://variables
	int testInt = 0;
	float testFloat = 0;
	float testDouble = 0;
	bool testBool = 1;
	int testNull = 2;
	std::string testStr = "nothing here";
	//need to declare your rttr macro here in public
	RTTR_ENABLE();

};

#endif