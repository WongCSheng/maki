/*!
@file		RTTR.cpp
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file contains code that use the rttr library. Currently it contains
getters and setters for TestClass that is used to debug json parsing.
*//*__________________________________________________________________________*/

#pragma once
#include "../Headers/STL_Header.h"
#include "../RTTR_Header.h"

//register your class for rttr here
RTTR_REGISTRATION
{
	using namespace rttr;
registration::class_<TestClass>("TestClass")
.property("testInt", &TestClass::testInt)
.property("testFloat", &TestClass::testFloat)
.property("testDouble", &TestClass::testDouble)
.property("testBool", &TestClass::testBool)
.property("testNull", &TestClass::testNull)
.property("testStr", &TestClass::testStr);

//	using namespace rttr;
//registration::class_<Object>("Object")
//.property("orientation", &Object::orientation)
//.property("scaling", &Object::scaling)
//.property("position", &Object::position)
//.property("initialPos", &Object::initialPos)
//.property("velocity", &Object::velocity)
//.property("dirCurr", &Object::dirCurr)
//.property("aabb", &Object::aabb)
//.property("status", &Object::status)
//.property("mass", &Object::mass)
//.property("mdl_to_ndc_xform", &Object::mdl_to_ndc_xform)
//.property("mdl_ref", &Object::mdl_ref)
//.property("shd_ref", &Object::shd_ref)
////.property("square", &Object::square) //we don't have any squares rn
//.property("color", &Object::color)
//.property("mdl_xform", &Object::mdl_xform)
//.property("objects", &Object::objects)
//.property("anim_rainbow", &Object::anim_rainbow)
//.property("rainbowCount", &Object::rainbowCount)
//.property("anim_bw", &Object::anim_bw)
//.property("bwCount", &Object::bwCount)
//.property("flip", &Object::flip)
//.property("rot_right", &Object::rot_right)
//.property("rot_left", &Object::rot_left)
//.property("scale_up", &Object::scale_up)
//.property("scale_down", &Object::scale_down);
}


TestClass::TestClass()
{
}

TestClass::~TestClass()
{
}

//setters

void TestClass::SetInt(int val)
{
	testInt = val;
}

void TestClass::SetFloat(float val)
{
	testFloat = val;
}

void TestClass::SetDouble(double val)
{
	testDouble = val;
}

void TestClass::SetBool(bool val)
{
	testBool = val;
}

void TestClass::SetNull()
{
	testNull = NULL;
}

void TestClass::SetStr(std::string val)
{
	testStr = val;
}



//getters

int TestClass::GetInt()
{
	return testInt;
}

float TestClass::GetFloat()
{
	return testFloat;
}

double TestClass::GetDouble()
{
	return testDouble;
}

bool TestClass::GetBool()
{
	return testBool;
}

int TestClass::GetNull()
{
	return NULL;
}

std::string TestClass::GetStr()
{
	return testStr;
}
