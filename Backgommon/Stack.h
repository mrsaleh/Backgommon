#pragma once

#include "Sprite.h"

enum struct StackType {
	Wooden_Two,
	White_One
};

class CStack :public CSprite
{
private:
	StackType type;
public:
	CStack();
	CStack(StackType type);
	~CStack();
};

