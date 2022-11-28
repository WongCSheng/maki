/*!
@file		Script.h
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file currently contains framework for scripting that we will include later.
*//*__________________________________________________________________________*/

#pragma once
#ifndef SCRIPT_H
#define SCRIPT_H


class Script
	//can inherit from component next time
{
public:
	Script();
	virtual ~Script();

	virtual void Start(void);
	virtual void Awake(void);
	virtual void Update(const double dt);
	//virtual void OnCollisionEnter
	//virtual void OnTriggerEnter
};

#endif