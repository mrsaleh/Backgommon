#pragma once

#include "Sprite.h"

enum struct NutType {
	Wooden_Two,
	White_One
};

class CNut : public CSprite
{
private:
	int targetX;
	int targetY;
	float passedTime;
	float nutStartX;
	float nutStartY;
	NutType type;
public:
	CNut(NutType type);
	CNut();
	~CNut();
	void Move(int targetX,int targetY);
	void Tick(float deltaTime);
};

