#pragma once

#include "Sprite.h"
#include "Shared.h"

class CNut : public CSprite
{
private:
	int targetX;
	int targetY;
	float passedTime;
	float nutStartX;
	float nutStartY;
	bool selected;
public:
	int stackIndex;
public:
	Player owner;
	CNut(Player owner);
	CNut();
	~CNut();
	void Move(int targetX,int targetY);
	void Tick(float deltaTime);
	void SetSelected(bool isSelected);
};

