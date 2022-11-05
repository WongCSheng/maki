/*!
@file		RTTR.h
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file currently contains TestClass that is used to debug json parsing.
It will be used for rttr registration further on.
*//*__________________________________________________________________________*/

#pragma once

#include <rttr/type.h>
#include <rttr/property.h>
#include <rttr/variant.h>
#include <rttr/registration.h>
#include "../Game Object/object.h"

#ifndef RTTR_H
#define RTTR_H

class TestClass
{
public://methods
	TestClass();
	~TestClass();

	//setters
	void SetInt(int val);
	void SetFloat(float val);
	void SetDouble(double val);
	void SetBool(bool val);
	void SetNull();
	void SetStr(std::string val);
	template<typename testArr>
	void SetArr(testArr newArr) {
		testArr = newArr;
	}

	//getters
	int GetInt();
	float GetFloat();
	double GetDouble();
	bool GetBool();
	int GetNull();
	std::string GetStr();
	std::string* GetArr()
	{
		return testArr;
	}

public://variables
	int testInt = 0;
	float testFloat = 0;
	double testDouble = 0;
	bool testBool = 1;
	int testNull = 2;
	std::string testStr = "nothing here";
	std::string* testArr = NULL;
	RTTR_ENABLE();

};

#endif