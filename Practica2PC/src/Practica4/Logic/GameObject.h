#pragma once

#include <Logic/SpriteSheet.h>

class RendererThread;

class GameObject {
protected:
	SpriteSheet _spriteSheet;
	float _x, _y;
	bool _active;
    int _pendingFrames;
	void setDirty();

public:
	GameObject();
	~GameObject();

	virtual void init();
	virtual void render(RendererThread* renderThread);
	virtual void update(double deltaTime);
	virtual void handleInput() {};

	virtual void reset();

	bool getActive();
	void setActive(bool value);

	float const getX() const;
	float const getY() const;
	void setX(float value);
	void setY(float value);
};

