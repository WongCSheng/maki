
#include "RTTR.h"

//rttr doesnt work yet
//register your class for rttr here
//RTTR_REGISTRATION
//{
//	using namespace rttr;
//registration::class_<TestClass>("TestClass")
//.property("testInt", &TestClass::testInt)
//.property("testFloat", &TestClass::testFloat)
//.property("testDouble", &TestClass::testDouble)
//.property("testBool", &TestClass::testBool)
//.property("testNull", &TestClass::testNull)
//.property("testStr", &TestClass::testStr);
//
//}


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


#endif