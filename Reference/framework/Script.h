#ifndef SCRIPT_H
#define SCRIPT_H

#include "Component.h"
#include "script_common.h"

class Script :
	public Component
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