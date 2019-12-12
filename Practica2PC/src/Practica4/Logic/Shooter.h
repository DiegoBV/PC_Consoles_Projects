#pragma once
#include "GameObject.h"
#include <Utils/Emitter.h>

class Shooter :	public GameObject, public Emitter 
{
private:
	float _deadZone;

public:
	Shooter();
	~Shooter();

	virtual void init();
	virtual void handleInput();
};