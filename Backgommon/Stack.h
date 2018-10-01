#pragma once

#include "Sprite.h"
#include "Nut.h"

enum struct StackType {
	Wooden_Two,
	White_One
};

class CStack :public CSprite
{
public:
	std::vector<CNut * > nuts;
private:
	StackType type;
	int index;
	CNut * removedNut;
public:
	CStack();
	CStack(StackType type,int index);
	void AddNut(CNut * nut);
	bool CanAdd(CNut * nut);
	//Returns removed nut from AddNut operation , if there was one
	CNut * PickRemovedNut();
	CNut * Select(int x, int y,Player owner);
	CNut * PopNut();
	CNut * PeekNut();
	~CStack();
};

